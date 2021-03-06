/***************************************************************************
                              qgswmsparameters.h
                              ------------------
  begin                : March 17, 2017
  copyright            : (C) 2017 by Paul Blottiere
  email                : paul dot blottiere at oslandia dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSWMSPARAMETERS_H
#define QGSWMSPARAMETERS_H

#include <QMap>
#include <QObject>
#include <QMetaEnum>
#include <QColor>

#include "qgsrectangle.h"
#include "qgswmsserviceexception.h"
#include "qgsserverrequest.h"
#include "qgslegendsettings.h"
#include "qgsgeometry.h"
#include "qgsprojectversion.h"

/**
 * QgsWmsParameters provides an interface to retrieve and manipulate WMS
 *  parameters received from the client.
 * \since QGIS 3.0
 */
namespace QgsWms
{
  struct QgsWmsParametersLayer
  {
    QString mNickname; // name, id or short name
    int mOpacity = -1;
    QStringList mFilter; // list of filter
    QStringList mSelection; // list of string fid
    QString mStyle;
  };

  struct QgsWmsParametersHighlightLayer
  {
    QString mName;
    QgsGeometry mGeom;
    QString mSld;
    QString mLabel;
    QColor mColor;
    int mSize = 0;
    int mWeight = 0;
    QString mFont;
    float mBufferSize = 0;
    QColor mBufferColor;
  };

  struct QgsWmsParametersComposerMap
  {
    int mId = 0; // composer map id
    bool mHasExtent = false; // does the request contains extent for this composer map
    QgsRectangle mExtent; // the request extent for this composer map
    float mScale = -1;
    float mRotation = 0;
    float mGridX = 0;
    float mGridY = 0;
    QList<QgsWmsParametersLayer> mLayers; // list of layers for this composer map
    QList<QgsWmsParametersHighlightLayer> mHighlightLayers; // list of highlight layers for this composer map
  };

  class QgsWmsParameters
  {
      Q_GADGET

    public:
      enum ParameterName
      {
        BOXSPACE,
        CRS, // instead of SRS for WMS 1.3.0
        SRS, // for WMS 1.1.1
        WIDTH,
        HEIGHT,
        BBOX,
        ICONLABELSPACE,
        ITEMFONTFAMILY,
        ITEMFONTBOLD,
        ITEMFONTITALIC,
        ITEMFONTSIZE,
        ITEMFONTCOLOR,
        LAYER,
        LAYERFONTFAMILY,
        LAYERFONTBOLD,
        LAYERFONTITALIC,
        LAYERFONTSIZE,
        LAYERFONTCOLOR,
        LAYERTITLE,
        LAYERS,
        LAYERSPACE,
        LAYERTITLESPACE,
        QUERY_LAYERS,
        FEATURE_COUNT,
        SHOWFEATURECOUNT,
        STYLE,
        STYLES,
        SYMBOLSPACE,
        SYMBOLHEIGHT,
        SYMBOLWIDTH,
        OPACITIES,
        SLD,
        FILTER,
        FILTER_GEOM,
        FORMAT,
        INFO_FORMAT,
        I,
        J,
        X,
        Y,
        RULE,
        RULELABEL,
        SCALE,
        SELECTION,
        HIGHLIGHT_GEOM,
        HIGHLIGHT_SYMBOL,
        HIGHLIGHT_LABELSTRING,
        HIGHLIGHT_LABELFONT,
        HIGHLIGHT_LABELSIZE,
        HIGHLIGHT_LABELWEIGHT,
        HIGHLIGHT_LABELCOLOR,
        HIGHLIGHT_LABELBUFFERCOLOR,
        HIGHLIGHT_LABELBUFFERSIZE,
        WMS_PRECISION,
        TRANSPARENT,
        BGCOLOR,
        DPI,
        TEMPLATE,
        EXTENT,
        ROTATION,
        GRID_INTERVAL_X,
        GRID_INTERVAL_Y,
        WITH_GEOMETRY,
        WITH_MAPTIP
      };
      Q_ENUM( ParameterName )

      enum Format
      {
        NONE,
        JPG,
        PNG,
        TEXT,
        XML,
        HTML,
        GML
      };

      struct Parameter
      {
        ParameterName mName;
        QVariant::Type mType;
        QVariant mDefaultValue;
        QVariant mValue;
      };

      /**
       * Constructor.
       * \param map of parameters where keys are parameters' names.
       */
      QgsWmsParameters( const QgsServerRequest::Parameters &parameters );

      /**
       * Constructor.
        */
      QgsWmsParameters();

      /**
       * Loads new parameters.
       * \param map of parameters
       */
      void load( const QgsServerRequest::Parameters &parameters );

      /**
       * Dumps parameters.
       */
      void dump() const;

      /**
       * Returns CRS or an empty string if none is defined.
       * \returns crs parameter as string
       */
      QString crs() const;

      /**
       * Returns WIDTH parameter or an empty string if not defined.
       * \returns width parameter
       */
      QString width() const;

      /**
       * Returns WIDTH parameter as an int or its default value if not
       *  defined. An exception is raised if WIDTH is defined and cannot be
       *  converted.
       * \returns width parameter
       * \throws QgsBadRequestException
       */
      int widthAsInt() const;

      /**
       * Returns HEIGHT parameter or an empty string if not defined.
       * \returns height parameter
       */
      QString height() const;

      /**
       * Returns HEIGHT parameter as an int or its default value if not
       *  defined. An exception is raised if HEIGHT is defined and cannot be
       *  converted.
       * \returns height parameter
       * \throws QgsBadRequestException
       */
      int heightAsInt() const;

      /**
       * Returns VERSION parameter as a string or an empty string if not
       *  defined.
       * \returns version
       */
      QString version() const;

      /**
       * Returns VERSION parameter if defined or its default value.
       * \returns version
       */
      QgsProjectVersion versionAsNumber() const;

      /**
       * Returns BBOX if defined or an empty string.
       * \returns bbox parameter
       */
      QString bbox() const;

      /**
       * Returns BBOX as a rectangle if defined and valid. An exception is
       *  raised if the BBOX string cannot be converted into a rectangle.
       * \returns bbox as rectangle
       * \throws QgsBadRequestException
       */
      QgsRectangle bboxAsRectangle() const;

      /**
       * Returns SLD if defined or an empty string.
       * \returns sld
       */
      QString sld() const;

      /**
       * Returns the list of feature selection found in SELECTION parameter.
       * \returns the list of selection
       */
      QStringList selections() const;

      /**
       * Returns the list of filters found in FILTER parameter.
       * \returns the list of filter
       */
      QStringList filters() const;

      /**
       * Returns the filter geometry found in FILTER_GEOM parameter.
       * \returns the filter geometry as Well Known Text.
       */
      QString filterGeom() const;

      /**
       * Returns the list of opacities found in OPACITIES parameter.
       * \returns the list of opacities in string
       */
      QStringList opacities() const;

      /**
       * Returns the list of opacities found in OPACITIES parameter as
       * integers. If an opacity cannot be converted into an integer, then an
       * exception is raised
       * \returns a list of opacities as integers
       * \throws QgsBadRequestException
       */
      QList<int> opacitiesAsInt() const;

      /**
       * Returns nickname of layers found in LAYER and LAYERS parameters.
       * \returns nickname of layers
       */
      QStringList allLayersNickname() const;

      /**
       * Returns nickname of layers found in QUERY_LAYERS parameter.
       * \returns nickname of layers
       */
      QStringList queryLayersNickname() const;

      /**
       * Returns styles found in STYLE and STYLES parameters.
       * \returns name of styles
       */
      QStringList allStyles() const;

      /**
       * Returns parameters for each layer found in LAYER/LAYERS.
       * \returns layer parameters
       */
      QList<QgsWmsParametersLayer> layersParameters() const;

      /**
       * Returns FORMAT parameter as a string.
       * \returns FORMAT parameter as string
       */
      QString formatAsString() const;

      /**
       * Returns format. If the FORMAT parameter is not used, then the
       *  default value is PNG.
       * \returns format
       */
      Format format() const;

      /**
       * Returns INFO_FORMAT parameter as a string.
       * \returns INFO_FORMAT parameter as string
       */
      QString infoFormatAsString() const;

      /**
       * Returns infoFormat. If the INFO_FORMAT parameter is not used, then the
       *  default value is text/plain.
       * \returns infoFormat
       */
      Format infoFormat() const;

      /**
       * Returns the infoFormat version for GML. If the INFO_FORMAT is not GML,
       *  then the default value is -1.
       * \returns infoFormat version
       */
      int infoFormatVersion() const;

      /**
       * Returns I parameter or an empty string if not defined.
       * \returns i parameter
       */
      QString i() const;

      /**
       * Returns I parameter as an int or its default value if not
       *  defined. An exception is raised if I is defined and cannot be
       *  converted.
       * \returns i parameter
       * \throws QgsBadRequestException
       */
      int iAsInt() const;

      /**
       * Returns J parameter or an empty string if not defined.
       * \returns j parameter
       */
      QString j() const;

      /**
       * Returns J parameter as an int or its default value if not
       *  defined. An exception is raised if J is defined and cannot be
       *  converted.
       * \returns j parameter
       * \throws QgsBadRequestException
       */
      int jAsInt() const;

      /**
       * Returns X parameter or an empty string if not defined.
       * \returns x parameter
       */
      QString x() const;

      /**
       * Returns X parameter as an int or its default value if not
       *  defined. An exception is raised if X is defined and cannot be
       *  converted.
       * \returns x parameter
       * \throws QgsBadRequestException
       */
      int xAsInt() const;

      /**
       * Returns Y parameter or an empty string if not defined.
       * \returns y parameter
       */
      QString y() const;

      /**
       * Returns Y parameter as an int or its default value if not
       *  defined. An exception is raised if Y is defined and cannot be
       *  converted.
       * \returns j parameter
       * \throws QgsBadRequestException
       */
      int yAsInt() const;

      /**
       * Returns RULE parameter or an empty string if none is defined
       * \returns RULE parameter or an empty string if none is defined
       */
      QString rule() const;

      /**
       * Returns RULELABEL parameter or an empty string if none is defined
       * \returns RULELABEL parameter or an empty string if none is defined
       */
      QString ruleLabel() const;

      /**
       * Returns RULELABEL as a bool. An exception is raised if an invalid
       *  parameter is found.
       * \returns ruleLabel
       * \throws QgsBadRequestException
       */
      bool ruleLabelAsBool() const;

      /**
       * Returns SHOWFEATURECOUNT parameter or an empty string if none is defined
       * \returns SHOWFEATURECOUNT parameter or an empty string if none is defined
       */
      QString showFeatureCount() const;

      /**
       * Returns SHOWFEATURECOUNT as a bool. An exception is raised if an invalid
       *  parameter is found.
       * \returns showFeatureCount
       * \throws QgsBadRequestException
       */
      bool showFeatureCountAsBool() const;

      /**
       * Returns FEATURE_COUNT parameter or an empty string if none is defined
       * \returns FEATURE_COUNT parameter or an empty string if none is defined
       */
      QString featureCount() const;

      /**
       * Returns FEATURE_COUNT as an integer. An exception is raised if an invalid
       *  parameter is found.
       * \returns FeatureCount
       * \throws QgsBadRequestException
       */
      int featureCountAsInt() const;

      /**
       * Returns SCALE parameter or an empty string if none is defined
       * \returns SCALE parameter or an empty string if none is defined
       */
      QString scale() const;

      /**
       * Returns SCALE as a double. An exception is raised if an invalid
       *  parameter is found.
       * \returns scale
       * \throws QgsBadRequestException
       */
      double scaleAsDouble() const;

      /**
       * Returns BOXSPACE parameter or an empty string if not defined.
       * \returns BOXSPACE parameter or an empty string if not defined.
       */
      QString boxSpace() const;

      /**
       * Returns BOXSPACE as a double or its default value if not defined.
       *  An exception is raised if an invalid parameter is found.
       * \returns boxSpace
       * \throws QgsBadRequestException
       */
      double boxSpaceAsDouble() const;

      /**
       * Returns LAYERSPACE parameter or an empty string if not defined.
       * \returns LAYERSPACE parameter or an empty string if not defined.
       */
      QString layerSpace() const;

      /**
       * Returns LAYERSPACE as a double or its default value if not defined.
       *  An exception is raised if an invalid parameter is found.
       * \returns layerSpace
       * \throws QgsBadRequestException
       */
      double layerSpaceAsDouble() const;

      /**
       * Returns LAYERTITLESPACE parameter or an empty string if not defined.
       * \returns LAYERTITLESPACE parameter or an empty string if not defined.
       */
      QString layerTitleSpace() const;

      /**
       * Returns LAYERTITLESPACE as a double. An exception is raised if an invalid
       *  parameter is found.
       * \returns layerTitleSpace
       * \throws QgsBadRequestException
       */
      double layerTitleSpaceAsDouble() const;

      /**
       * Returns SYMBOLSPACE parameter or an empty string if not defined.
       * \returns SYMBOLSPACE parameter or an empty string if not defined.
       */
      QString symbolSpace() const;

      /**
       * Returns SYMBOLSPACE as a double or its default value if not defined.
       *  An exception is raised if an invalid parameter is found.
       * \returns symbolSpace
       * \throws QgsBadRequestException
       */
      double symbolSpaceAsDouble() const;

      /**
       * Returns ICONLABELSPACE parameter or an empty string if not defined.
       * \returns ICONLABELSPACE parameter or an empty string if not defined.
       */
      QString iconLabelSpace() const;

      /**
       * Returns ICONLABELSPACE as a double or its default value if not
       *  defined. An exception is raised if an invalid parameter is found.
       * \returns iconLabelSpace
       * \throws QgsBadRequestException
       */
      double iconLabelSpaceAsDouble() const;

      /**
       * Returns SYMBOLWIDTH parameter or an empty string if not defined.
       * \returns SYMBOLWIDTH parameter or an empty string if not defined.
       */
      QString symbolWidth() const;

      /**
       * Returns SYMBOLWIDTH as a double or its default value if not defined.
       *  An exception is raised if an invalid parameter is found.
       * \returns symbolWidth
       * \throws QgsBadRequestException
       */
      double symbolWidthAsDouble() const;

      /**
       * Returns SYMBOLHEIGHT parameter or an empty string if not defined.
       * \returns SYMBOLHEIGHT parameter or an empty string if not defined.
       */
      QString symbolHeight() const;

      /**
       * Returns SYMBOLHEIGHT as a double or its default value if not defined.
       *  An exception is raised if an invalid parameter is found.
       * \returns symbolHeight
       * \throws QgsBadRequestException
       */
      double symbolHeightAsDouble() const;

      /**
       * Returns the layer font (built thanks to the LAYERFONTFAMILY,
       *  LAYERFONTSIZE, LAYERFONTBOLD, ... parameters).
       * \returns layerFont
       */
      QFont layerFont() const;

      /**
       * Returns LAYERFONTFAMILY parameter or an empty string if not defined.
       * \returns LAYERFONTFAMILY parameter or an empty string if not defined.
       */
      QString layerFontFamily() const;

      /**
       * Returns LAYERFONTBOLD parameter or an empty string if not defined.
       * \returns LAYERFONTBOLD parameter or an empty string if not defined.
       */
      QString layerFontBold() const;

      /**
       * Returns LAYERFONTBOLD as a boolean or its default value if not
       *  defined. An exception is raised if an
       *  invalid parameter is found.
       * \returns layerFontBold
       * \throws QgsBadRequestException
       */
      bool layerFontBoldAsBool() const;

      /**
       * Returns LAYERFONTITALIC parameter or an empty string if not defined.
       * \returns LAYERFONTITALIC parameter or an empty string if not defined.
       */
      QString layerFontItalic() const;

      /**
       * Returns LAYERFONTITALIC as a boolean or its default value if not
       *  defined. An exception is raised if an invalid parameter is found.
       * \returns layerFontItalic
       * \throws QgsBadRequestException
       */
      bool layerFontItalicAsBool() const;

      /**
       * Returns LAYERFONTSIZE parameter or an empty string if not defined.
       * \returns LAYERFONTSIZE parameter or an empty string if not defined.
       */
      QString layerFontSize() const;

      /**
       * Returns LAYERFONTSIZE as a double. An exception is raised if an invalid
       *  parameter is found.
       * \returns layerFontSize
       * \throws QgsBadRequestException
       */
      double layerFontSizeAsDouble() const;

      /**
       * Returns LAYERFONTCOLOR parameter or an empty string if not defined.
       * \returns LAYERFONTCOLOR parameter or an empty string if not defined.
       */
      QString layerFontColor() const;

      /**
       * Returns LAYERFONTCOLOR as a color or its defined value if not
       *  defined. An exception is raised if an invalid parameter is found.
       * \returns layerFontColor
       * \throws QgsBadRequestException
       */
      QColor layerFontColorAsColor() const;

      /**
       * Returns the item font (built thanks to the ITEMFONTFAMILY,
       *  ITEMFONTSIZE, ITEMFONTBOLD, ... parameters).
       * \returns itemFont
       */
      QFont itemFont() const;

      /**
       * Returns ITEMFONTFAMILY parameter or an empty string if not defined.
       * \returns ITEMFONTFAMILY parameter or an empty string if not defined.
       */
      QString itemFontFamily() const;

      /**
       * Returns ITEMFONTBOLD parameter or an empty string if not defined.
       * \returns ITEMFONTBOLD parameter or an empty string if not defined.
       */
      QString itemFontBold() const;

      /**
       * Returns ITEMFONTBOLD as a boolean or its default value if not
       *  defined. An exception is raised if an invalid parameter is found.
       * \returns itemFontBold
       * \throws QgsBadRequestException
       */
      bool itemFontBoldAsBool() const;

      /**
       * Returns ITEMFONTITALIC parameter or an empty string if not defined.
       * \returns ITEMFONTITALIC parameter or an empty string if not defined.
       */
      QString itemFontItalic() const;

      /**
       * Returns ITEMFONTITALIC as a boolean or its default value if not
       *  defined. An exception is raised if an invalid parameter is found.
       * \returns itemFontItalic
       * \throws QgsBadRequestException
       */
      bool itemFontItalicAsBool() const;

      /**
       * Returns ITEMFONTSIZE parameter or an empty string if not defined.
       * \returns ITEMFONTSIZE parameter or an empty string if not defined.
       */
      QString itemFontSize() const;

      /**
       * Returns ITEMFONTSIZE as a double. An exception is raised if an
       *  invalid parameter is found.
       * \returns itemFontSize
       * \throws QgsBadRequestException
       */
      double itemFontSizeAsDouble() const;

      /**
       * Returns ITEMFONTCOLOR parameter or an empty string if not defined.
       * \returns ITEMFONTCOLOR parameter or an empty string if not defined.
       */
      QString itemFontColor() const;

      /**
       * Returns ITEMFONTCOLOR as a color. An exception is raised if an
       *  invalid parameter is found.
       * \returns itemFontColor
       * \throws QgsBadRequestException
       */
      QColor itemFontColorAsColor() const;

      /**
       * Returns LAYERTITLE parameter or an empty string if not defined.
       * \returns LAYERTITLE parameter or an empty string if not defined.
       */
      QString layerTitle() const;

      /**
       * Returns LAYERTITLE as a bool or its default value if not defined. An
       *  exception is raised if an invalid parameter is found.
       * \returns layerTitle
       * \throws QgsBadRequestException
       */
      bool layerTitleAsBool() const;

      /**
       * Returns legend settings
       * \returns legend settings
       */
      QgsLegendSettings legendSettings() const;

      /**
       * Returns parameters for each highlight layer.
       * \returns parameters for each highlight layer
       */
      QList<QgsWmsParametersHighlightLayer> highlightLayersParameters() const;

      /**
       * Returns HIGHLIGHT_GEOM as a list of string in WKT.
       * \returns highlight geometries
       */
      QStringList highlightGeom() const;

      /**
       * Returns HIGHLIGHT_GEOM as a list of geometries. An exception is
       *  raised if an invalid geometry is found.
       * \returns highlight geometries
       * \throws QgsBadRequestException
       */
      QList<QgsGeometry> highlightGeomAsGeom() const;

      /**
       * Returns HIGHLIGHT_SYMBOL as a list of string.
       * \returns highlight sld symbols
       */
      QStringList highlightSymbol() const;

      /**
       * Returns HIGHLIGHT_LABELSTRING as a list of string.
       * \returns highlight label string
       */
      QStringList highlightLabelString() const;

      /**
       * Returns HIGHLIGHT_LABELCOLOR as a list of string.
       * \returns highlight label color
       */
      QStringList highlightLabelColor() const;

      /**
       * Returns HIGHLIGHT_LABELCOLOR as a list of color. An exception is
       *  raised if an invalid color is found.
       * \returns highlight label color
       * \throws QgsBadRequestException
       */
      QList<QColor> highlightLabelColorAsColor() const;

      /**
       * Returns HIGHLIGHT_LABELSIZE as a list of string.
       * \returns highlight label size
       */
      QStringList highlightLabelSize() const;

      /**
       * Returns HIGHLIGHT_LABELSIZE as a list of int An exception is raised
       *  if an invalid size is found.
       * \returns highlight label size
       * \throws QgsBadRequestException
       */
      QList<int> highlightLabelSizeAsInt() const;

      /**
       * Returns HIGHLIGHT_LABELWEIGHT as a list of string.
       * \returns highlight label weight
       */
      QStringList highlightLabelWeight() const;

      /**
       * Returns HIGHLIGHT_LABELWEIGHT as a list of int. An exception is
       *  raised if an invalid weight is found.
       * \returns highlight label weight
       * \throws QgsBadRequestException
       */
      QList<int> highlightLabelWeightAsInt() const;

      /**
       * Returns HIGHLIGHT_LABELFONT
       * \returns highlight label font
       */
      QStringList highlightLabelFont() const;

      /**
       * Returns HIGHLIGHT_LABELBUFFERSIZE
       * \returns highlight label buffer size
       */
      QStringList highlightLabelBufferSize() const;

      /**
       * Returns HIGHLIGHT_LABELBUFFERSIZE as a list of float. An exception is
       *  raised if an invalid size is found.
       * \returns highlight label buffer size
       * \throws QgsBadRequestException
       */
      QList<float> highlightLabelBufferSizeAsFloat() const;

      /**
       * Returns HIGHLIGHT_LABELBUFFERCOLOR as a list of string.
       * \returns highlight label buffer color
       */
      QStringList highlightLabelBufferColor() const;

      /**
       * Returns HIGHLIGHT_LABELBUFFERCOLOR as a list of colors. An axception
       *  is raised if an invalid color is found.
       * \returns highlight label buffer color
       * \throws QgsBadRequestException
       */
      QList<QColor> highlightLabelBufferColorAsColor() const;

      /**
       * Returns WMS_PRECISION parameter or an empty string if not defined.
       * \returns wms precision parameter
       */
      QString wmsPrecision() const;

      /**
       * Returns WMS_PRECISION parameter as an int or its default value if not
       *  defined. An exception is raised if WMS_PRECISION is defined and cannot be
       *  converted.
       * \returns wms precision parameter
       * \throws QgsBadRequestException
       */
      int wmsPrecisionAsInt() const;

      /**
       * Returns TRANSPARENT parameter or an empty string if not defined.
       * \returns TRANSPARENT parameter
       */
      QString transparent() const;

      /**
       * Returns TRANSPARENT parameter as a bool or its default value if not
       * defined. An exception is raised if TRANSPARENT is defined and cannot
       * be converted.
       * \returns transparent parameter
       * \throws QgsBadRequestException
       */
      bool transparentAsBool() const;

      /**
       * Returns BGCOLOR parameter or an empty string if not defined.
       * \returns BGCOLOR parameter
       */
      QString backgroundColor() const;

      /**
       * Returns BGCOLOR parameter as a QColor or its default value if not
       * defined. An exception is raised if BGCOLOR is defined and cannot
       * be converted.
       * \returns background color parameter
       * \throws QgsBadRequestException
       */
      QColor backgroundColorAsColor() const;

      /**
       * Returns DPI parameter or an empty string if not defined.
       * \returns DPI parameter
       */
      QString dpi() const;

      /**
       * Returns DPI parameter as an int or its default value if not
       * defined. An exception is raised if DPI is defined and cannot
       * be converted.
       * \returns dpi parameter
       * \throws QgsBadRequestException
       */
      int dpiAsInt() const;

      /**
       * Returns TEMPLATE parameter or an empty string if not defined.
       * \returns TEMPLATE parameter
       */
      QString composerTemplate() const;

      /**
       * Returns the requested parameters for a composer map parameter.
       * An exception is raised if parameters are defined and cannot be
       * converted like EXTENT, SCALE, ROTATION, GRID_INTERVAL_X and
       * GRID_INTERVAL_Y.
       * \param mapId the composer map id.
       * \returns parameters for the composer map.
       * \throws QgsBadRequestException
       */
      QgsWmsParametersComposerMap composerMapParameters( int mapId ) const;

      /**
       * Return the external WMS uri
       * \param id the id of the external wms
       * @return uri string or an empty string if the external wms id does not exist
       */
      QString externalWMSUri( const QString &id ) const;

      /**
       * \brief Returns if the client wants the feature info response with geometry information
       * \returns true if geometry information is requested for feature info response
       */
      bool withGeometry() const;

      /**
       * \brief withMapTip
       * \returns true if maptip information is requested for feature info response
       */
      bool withMapTip() const;

    private:
      QString name( ParameterName name ) const;
      void raiseError( ParameterName name ) const;
      void raiseError( ParameterName name, int mapId ) const;
      void raiseError( const QString &msg ) const;
      void initParameters();
      void save( const Parameter &parameter );
      QVariant value( ParameterName name ) const;
      QVariant defaultValue( ParameterName name ) const;
      void save( const Parameter &parameter, int mapId );
      QVariant value( ParameterName name, int mapId ) const;
      QVariant defaultValue( ParameterName name, int mapId ) const;
      void log( const QString &msg ) const;
      double toDouble( const QVariant &value, const QVariant &defaultValue, bool *error = Q_NULLPTR ) const;
      double toDouble( ParameterName name ) const;
      double toDouble( ParameterName name, int mapId ) const;
      bool toBool( const QVariant &value, const QVariant &defaultValue ) const;
      bool toBool( ParameterName name ) const;
      bool toBool( ParameterName name, int mapId ) const;
      int toInt( const QVariant &value, const QVariant &defaultValue, bool *error = Q_NULLPTR ) const;
      int toInt( ParameterName name ) const;
      int toInt( ParameterName name, int mapId ) const;
      QColor toColor( const QVariant &value, const QVariant &defaultValue, bool *error = Q_NULLPTR ) const;
      QColor toColor( ParameterName name ) const;
      QColor toColor( ParameterName name, int mapId ) const;
      QgsRectangle toRectangle( const QVariant &value, bool *error = Q_NULLPTR ) const;
      QgsRectangle toRectangle( ParameterName name ) const;
      QgsRectangle toRectangle( ParameterName name, int mapId ) const;
      QStringList toStringList( ParameterName name, char delimiter = ',' ) const;
      QStringList toStringList( ParameterName name, int mapId, char delimiter = ',' ) const;
      QList<int> toIntList( const QStringList &l, bool *error = Q_NULLPTR ) const;
      QList<int> toIntList( const QStringList &l, ParameterName name ) const;
      QList<int> toIntList( const QStringList &l, ParameterName name, int mapId ) const;
      QList<float> toFloatList( const QStringList &l, bool *error = Q_NULLPTR ) const;
      QList<float> toFloatList( const QStringList &l, ParameterName name ) const;
      QList<float> toFloatList( const QStringList &l, ParameterName name, int mapId ) const;
      QList<QColor> toColorList( const QStringList &l, bool *error = Q_NULLPTR ) const;
      QList<QColor> toColorList( const QStringList &l, ParameterName name ) const;
      QList<QColor> toColorList( const QStringList &l, ParameterName name, int mapId ) const;
      QList<QgsGeometry> toGeomList( const QStringList &l, bool *error = Q_NULLPTR ) const;
      QList<QgsGeometry> toGeomList( const QStringList &l, ParameterName name ) const;
      QList<QgsGeometry> toGeomList( const QStringList &l, ParameterName name, int mapId ) const;
      QMultiMap<QString, QString> getLayerFilters( const QStringList &layers ) const;

      QgsServerRequest::Parameters mRequestParameters;
      QMap<ParameterName, Parameter> mParameters;
      QMap<int, QMap<ParameterName, Parameter>> mComposerParameters;
      QMap<QString, QMap<QString, QString> > mExternalWMSParameters;
      QList<QgsProjectVersion> mVersions;
  };
}

#endif
