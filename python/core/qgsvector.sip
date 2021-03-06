/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/qgsvector.h                                                 *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/



class QgsVector
{
%Docstring
A class to represent a vector.
Currently no Z axis / 2.5D support is implemented.
%End

%TypeHeaderCode
#include "qgsvector.h"
%End
  public:

    QgsVector();
%Docstring
Default constructor for QgsVector. Creates a vector with length of 0.0.
%End

    QgsVector( double x, double y );
%Docstring
Constructor for QgsVector taking x and y component values.

:param x: x-component
:param y: y-component
%End

    QgsVector operator-() const;
%Docstring
Swaps the sign of the x and y components of the vector.
%End

    QgsVector operator*( double scalar ) const;
%Docstring
Returns a vector where the components have been multiplied by a scalar value.

:param scalar: factor to multiply by
%End

    QgsVector operator/( double scalar ) const;
%Docstring
Returns a vector where the components have been divided by a scalar value.

:param scalar: factor to divide by
%End

    double operator*( QgsVector v ) const;
%Docstring
Returns the dot product of two vectors, which is the sum of the x component
of this vector multiplied by the x component of another
vector plus the y component of this vector multiplied by the y component of another vector.
%End

    QgsVector operator+( QgsVector other ) const;
%Docstring
Adds another vector to this vector.

.. versionadded:: 3.0
%End

    QgsVector &operator+=( const QgsVector other );
%Docstring
Adds another vector to this vector in place.

.. versionadded:: 3.0
%End

    QgsVector operator-( const QgsVector other ) const;
%Docstring
Subtracts another vector to this vector.

.. versionadded:: 3.0
%End

    QgsVector &operator-=( const QgsVector other );
%Docstring
Subtracts another vector to this vector in place.

.. versionadded:: 3.0
%End

    double length() const;
%Docstring
Returns the length of the vector.
%End

    double x() const;
%Docstring
Returns the vector's x-component.

.. seealso:: y()
%End

    double y() const;
%Docstring
Returns the vector's y-component.

.. seealso:: x()
%End

    QgsVector perpVector() const;
%Docstring
Returns the perpendicular vector to this vector (rotated 90 degrees counter-clockwise)
%End

    double angle() const;
%Docstring
Returns the angle of the vector in radians.
%End

    double angle( QgsVector v ) const;
%Docstring
Returns the angle between this vector and another vector in radians.
%End

    QgsVector rotateBy( double rot ) const;
%Docstring
Rotates the vector by a specified angle.

:param rot: angle in radians
%End

    QgsVector normalized() const;
%Docstring
Returns the vector's normalized (or "unit") vector (ie same angle but length of 1.0).
Will throw a QgsException if called on a vector with length of 0.
%End

    bool operator==( QgsVector other ) const;

    bool operator!=( QgsVector other ) const;
%Docstring
Inequality operator
%End

};

/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/qgsvector.h                                                 *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
