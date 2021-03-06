/***************************************************************************
    qgsdatetimeeditconfig.cpp
     --------------------------------------
    Date                 : 03.2014
    Copyright            : (C) 2014 Denis Rouzaud
    Email                : denis.rouzaud@gmail.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsdatetimeeditconfig.h"
#include "qgsdatetimeeditfactory.h"
#include "qgsvectorlayer.h"
#include "qgsdatetimefieldformatter.h"

QgsDateTimeEditConfig::QgsDateTimeEditConfig( QgsVectorLayer *vl, int fieldIdx, QWidget *parent )
  : QgsEditorConfigWidget( vl, fieldIdx, parent )
{
  setupUi( this );

  mDemoDateTimeEdit->setDateTime( QDateTime::currentDateTime() );

  connect( mDisplayFormatEdit, &QLineEdit::textChanged, this, &QgsDateTimeEditConfig::updateDemoWidget );
  connect( mCalendarPopupCheckBox, &QAbstractButton::toggled, this, &QgsDateTimeEditConfig::updateDemoWidget );

  connect( mFieldFormatComboBox, static_cast<void ( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, &QgsDateTimeEditConfig::updateFieldFormat );
  connect( mFieldFormatEdit, &QLineEdit::textChanged, this, &QgsDateTimeEditConfig::updateDisplayFormat );
  connect( mDisplayFormatComboBox, static_cast<void ( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, &QgsDateTimeEditConfig::displayFormatChanged );

  connect( mFieldHelpToolButton, &QAbstractButton::clicked, this, &QgsDateTimeEditConfig::showHelp );
  connect( mDisplayHelpToolButton, &QAbstractButton::clicked, this, &QgsDateTimeEditConfig::showHelp );

  connect( mFieldFormatEdit, &QLineEdit::textChanged, this, &QgsEditorConfigWidget::changed );
  connect( mDisplayFormatEdit, &QLineEdit::textChanged, this, &QgsEditorConfigWidget::changed );
  connect( mCalendarPopupCheckBox, &QAbstractButton::toggled, this, &QgsEditorConfigWidget::changed );
  connect( mAllowNullCheckBox, &QAbstractButton::toggled, this, &QgsEditorConfigWidget::changed );

  // initialize
  updateFieldFormat( mFieldFormatComboBox->currentIndex() );
  displayFormatChanged( mDisplayFormatComboBox->currentIndex() );
}


void QgsDateTimeEditConfig::updateDemoWidget()
{
  mDemoDateTimeEdit->setDisplayFormat( mDisplayFormatEdit->text() );
  mDemoDateTimeEdit->setCalendarPopup( mCalendarPopupCheckBox->isChecked() );
}


void QgsDateTimeEditConfig::updateFieldFormat( int idx )
{
  if ( idx == 0 )
  {
    mFieldFormatEdit->setText( QgsDateTimeFieldFormatter::DEFAULT_DATE_FORMAT );
  }
  else if ( idx == 1 )
  {
    mFieldFormatEdit->setText( QgsDateTimeFieldFormatter::DEFAULT_TIME_FORMAT );
  }
  else if ( idx == 2 )
  {
    mFieldFormatEdit->setText( QgsDateTimeFieldFormatter::DEFAULT_DATETIME_FORMAT );
  }

  mFieldFormatEdit->setVisible( idx == 3 );
  mFieldHelpToolButton->setVisible( idx == 3 );
  if ( mFieldHelpToolButton->isHidden() && mDisplayHelpToolButton->isHidden() )
  {
    mHelpScrollArea->setVisible( false );
  }
}


void QgsDateTimeEditConfig::updateDisplayFormat( const QString &fieldFormat )
{
  if ( mDisplayFormatComboBox->currentIndex() == 0 )
  {
    mDisplayFormatEdit->setText( fieldFormat );
  }
}


void QgsDateTimeEditConfig::displayFormatChanged( int idx )
{
  mDisplayFormatEdit->setEnabled( idx == 1 );
  mDisplayHelpToolButton->setVisible( idx == 1 );
  if ( mFieldHelpToolButton->isHidden() && mDisplayHelpToolButton->isHidden() )
  {
    mHelpScrollArea->setVisible( false );
  }
  if ( idx == 0 )
  {
    mDisplayFormatEdit->setText( mFieldFormatEdit->text() );
  }
}

void QgsDateTimeEditConfig::showHelp( bool buttonChecked )
{
  mFieldHelpToolButton->setChecked( buttonChecked );
  mDisplayHelpToolButton->setChecked( buttonChecked );
  mHelpScrollArea->setVisible( buttonChecked );
}


QVariantMap QgsDateTimeEditConfig::config()
{
  QVariantMap myConfig;

  myConfig.insert( QStringLiteral( "field_format" ), mFieldFormatEdit->text() );
  myConfig.insert( QStringLiteral( "display_format" ), mDisplayFormatEdit->text() );
  myConfig.insert( QStringLiteral( "calendar_popup" ), mCalendarPopupCheckBox->isChecked() );
  myConfig.insert( QStringLiteral( "allow_null" ), mAllowNullCheckBox->isChecked() );

  return myConfig;
}

void QgsDateTimeEditConfig::setConfig( const QVariantMap &config )
{
  const QgsField fieldDef = layer()->fields().at( field() );
  const QString fieldFormat = config.value( QStringLiteral( "field_format" ), QgsDateTimeFieldFormatter::defaultFormat( fieldDef.type() ) ).toString();
  mFieldFormatEdit->setText( fieldFormat );

  if ( fieldFormat == QgsDateTimeFieldFormatter::DEFAULT_DATE_FORMAT )
    mFieldFormatComboBox->setCurrentIndex( 0 );
  else if ( fieldFormat == QgsDateTimeFieldFormatter::DEFAULT_TIME_FORMAT )
    mFieldFormatComboBox->setCurrentIndex( 1 );
  else if ( fieldFormat == QgsDateTimeFieldFormatter::DEFAULT_DATETIME_FORMAT )
    mFieldFormatComboBox->setCurrentIndex( 2 );
  else
    mFieldFormatComboBox->setCurrentIndex( 3 );

  QString displayFormat = config.value( QStringLiteral( "display_format" ), QgsDateTimeFieldFormatter::defaultFormat( fieldDef.type() ) ).toString();
  mDisplayFormatEdit->setText( displayFormat );
  if ( displayFormat == mFieldFormatEdit->text() )
  {
    mDisplayFormatComboBox->setCurrentIndex( 0 );
  }
  else
  {
    mDisplayFormatComboBox->setCurrentIndex( 1 );
  }

  mCalendarPopupCheckBox->setChecked( config.value( QStringLiteral( "calendar_popup" ), true ).toBool() );
  mAllowNullCheckBox->setChecked( config.value( QStringLiteral( "allow_null" ), true ).toBool() );
}
