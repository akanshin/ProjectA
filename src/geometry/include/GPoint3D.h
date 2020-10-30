////////////////////////////////////////////////////////////////////////
// ProjectA/geometry
// Copyright (C) 2020   Artemiy Kanshin
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#ifndef _GPOINT3D_H_
#define _GPOINT3D_H_

#include "GExports.h"

namespace glib
{

class GVector3D;
class GMatrix;

/**
 * @brief 3D Point class for mathematical operations
 * @author Artemiy Kanshin
 */
class GLIB_API GPoint3D
{
public:
    /**
     * @brief Initializes zero point.
     */
    GPoint3D();

    /**
     * @brief Copy constructor
     * @param other - other point
     */
    GPoint3D(const GPoint3D & other);

    /**
     * @brief Move constructor
     * @param other
     */
    GPoint3D(GPoint3D && other);

    /**
     * @brief Initializes point with specified coordinates
     * @param x - X coordinate
     * @param y - Y coordinate
     * @param z - Z coordinate
     */
    explicit GPoint3D(double x, double y, double z);

    /**
     * @brief Initializes point with pointer to array of (at least) 3 doubles
     * @param pCoords - Pointer to array with coordinates
     */
    explicit GPoint3D(double * pCoords);

    /** No doc */
    ~GPoint3D();

    /**
     * @return X coordinate
     */
    double x() const;

    /**
     * @brief Sets new value of x coordinate
     * @param newX - new value of x coordinate
     */
    void setX(double newX);

    /**
     * @return Y coordinate
     */
    double y() const;

    /**
     * @brief Sets new value of y coordinate
     * @param newY - new value of y coordinate
     */
    void setY(double newY);

    /**
     * @return Z coordinate
     */
    double z() const;

    /**
     * @brief Sets new value of z coordinate
     * @param newZ - new value of z coordinate
     */
    void setZ(double newZ);

    /**
     * @brief Sets new coordinates to the point.
     * @param newX - new value of x coordinate
     * @param newY - new value of y coordinate
     * @param newZ - new value of z coordinate
     */
    void set(double newX, double newY, double newZ);

    /**
     * @brief operator [] for read only access
     * @param coordIdx - index of coordinate [0-2]
     * @return coordinate value
     * @throws std::invalid_argument
     */
    double operator[](std::size_t coordIdx) const;

    /**
     * @brief operator [] for write access
     * @param coordIdx - index of coordinate [0-2]
     * @return reference to coordinate value
     * @throws std::invalid_argument
     */
    double & operator[](std::size_t coordIdx);

    /**
     * @brief Adds input point coordinates
     * @param pt - point
     * @return reference to this point object
     */
    GPoint3D & operator+=(const GPoint3D & pt);

    /**
     * @brief Subtracts input point coordinates
     * @param pt - point
     * @return reference to this point object
     */
    GPoint3D & operator-=(const GPoint3D & pt);

    /**
     * @brief Adds input vector coordinates
     * @param v - vector
     * @return reference to this point object
     */
    GPoint3D & operator+=(const GVector3D & v);

    /**
     * @brief Subtracts input vector coordinates
     * @param v - vector
     * @return reference to this point object
     */
    GPoint3D & operator-=(const GVector3D & v);

    /**
     * @brief Transforms by matrix
     * @param m - matrix
     * @return reference to this point object
     */
    GPoint3D & operator*=(const GMatrix & m);

private:
    double m_x, m_y, m_z;
};

} //namespace glib

#endif //_GPOINT3D_H_
