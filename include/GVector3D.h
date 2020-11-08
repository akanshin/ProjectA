////////////////////////////////////////////////////////////////////////
// Simple Geometric Library (sglib)
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

#ifndef _GVECTOR3D_H_
#define _GVECTOR3D_H_

#include "GExports.h"
#include "GTolerance.h"

#include <initializer_list>

namespace sgl
{

class GMatrix;
class GPoint3D;

/**
 * @brief 3D Vector class for mathematical operations
 * @author Artemiy Kanshin
 */
class SGL_API GVector3D
{
public:
    /**
     * @return const reference to [1.0, 0.0, 0.0] vector
     */
    static const GVector3D & axisX();

    /**
     * @return const reference to [0.0, 1.0, 0.0] vector
     */
    static const GVector3D & axisY();

    /**
     * @return const reference to [0.0, 0.0, 1.0] vector
     */
    static const GVector3D & axisZ();

public:
    /**
     * @brief Initializes zero vector.
     */
    GVector3D();

    /**
     * @brief Copy constructor
     * @param other - other vector
     */
    GVector3D(const GVector3D & other);

    /**
     * @brief Move constructor
     * @param other
     */
    GVector3D(GVector3D && other) noexcept;

    /**
     * @brief Initializes vector with specified coordinates
     * @param x - X coordinate
     * @param y - Y coordinate
     * @param z - Z coordinate
     */
    explicit GVector3D(double x, double y, double z);

    /**
     * @brief Initializes vector with pointer to array of (at least) 3 doubles
     * @param pCoords - Pointer to array with coordinates
     */
    explicit GVector3D(double * pCoords);

    /**
     * @brief Initializes vector by initializer list
     */
    GVector3D(std::initializer_list<double>);

    /** No doc */
    virtual ~GVector3D();

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
     * @brief Sets new coordinates to the vector.
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
     * @brief Returns length of vector
     * @return vector length
     */
    double length() const;

    /**
     * @brief Returns true if vector has zero length
     * @param tolerance - length tolerance
     * @return true if vector has zero length, otherwise false
     */
    bool isZero(double tolerance = GTolerance::lengthTol()) const;

    /**
     * @brief Returns true if vector is an unit vector
     * @param tolerance - length tolrance
     * @return true if vector is an unit vector, otherwise false
     */
    bool isUnit(double tolerance = GTolerance::lengthTol()) const;

    /**
     * @brief Transforms vector to an unit vector.
     * @return Reference to this vector object
     * @throws std::logic_error
     */
    GVector3D & normalize();

    /**
     * @brief Returns normalized copy of this vector
     * @return normalized copy of this vector
     */
    GVector3D normalize() const;

    /**
     * @brief Returns true if this vector is equal to given within tolerance.
     * @param v - vector to check equality
     * @param tolerance - length tolerance
     * @return true if this vector is equal to given within tolerance, otherwise false
     */
    bool equals(const GVector3D & v, double tolerance = GTolerance::lengthTol()) const;

    /**
     * @brief Returns true if this vector is parallel to given within tolerance.
     * @param v - vector to check parallelism
     * @param tolerance - angular tolerance
     * @return true if this vector is parallel to given within tolerance, otherwise false.
     * @throws std::logic_error
     */
    bool parallel(const GVector3D & v, double tolerance = GTolerance::angularTol()) const;

    /**
     * @brief Returns true if this vector is antiparallel to given within tolerance
     * @param v - vector to check antiparallelism
     * @param tolerance - angular tolerance
     * @return true if this vector is antiparallel to given within tolerance, otherwise false
     * @throws std::logic_error
     */
    bool antiparallel(const GVector3D & v, double tolerance = GTolerance::angularTol()) const;

    /**
     * @brief Returns true if this vector is biparallel to given within tolerance
     * @param v - vector to check biparallelism
     * @param tolerance - angular tolerance
     * @return true if this vector is biparallel to given within tolerance, otherwise false
     * @throws std::logic_error
     */
    bool biparallel(const GVector3D & v, double tolerance = GTolerance::angularTol()) const;

    /**
     * @brief Returns true if this is perpendicular to given within tolerance
     * @param v - vector to check perpendicularity
     * @param tolerance - angular tolerance
     * @return true if this vector is perpendicular to given within tolerance, otherwise false
     * @throws std::logic_error
     */
    bool perpendicular(const GVector3D & v, double tolerance = GTolerance::angularTol()) const;

    /**
     * @brief operator =
     * @param v - vector
     * @return reference to this vector object
     */
    GVector3D & operator=(const GVector3D & v);

    /**
     * @brief Adds input vector coordinates
     * @param v - vector
     * @return Reference to this vector object
     */
    GVector3D & operator+=(const GVector3D & v);

    /**
     * @brief Subtracts input vector coordinates
     * @param v - vector
     * @return Reference to this vector object
     */
    GVector3D & operator-=(const GVector3D & v);

    /**
     * @brief Multiplies this vector coordinates by scalar
     * @param scalar - scalar
     * @return Reference to this vector object
     */
    GVector3D & operator*=(double scalar);

    /**
     * @brief Divides this vector coordinates by scalar
     * @param scalar - scalar
     * @return Reference to this vector object
     */
    GVector3D & operator/=(double scalar);

    /**
     * @brief Transforms this vector by given transformation matrix
     * @param m - transformation matrix
     * @return Reference to this vector object
     */
    GVector3D & operator*=(const GMatrix & m);

private:
    double m_x{0}, m_y{0}, m_z{0};
};

/**
 * @brief Scalar product operator
 * @param v1 - first vector
 * @param v2 - second vector
 * @return scalar product result
 */
SGL_API double operator%(const GVector3D & v1, const GVector3D & v2);

/**
 * @brief Cross product operator
 * @param v1 - first vector
 * @param v2 - second vector
 * @return vector which is cross product result
 */
SGL_API GVector3D operator*(const GVector3D & v1, const GVector3D & v2);

/**
 * @brief Returns a sum of given vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return a sum of given vectors
 */
SGL_API GVector3D operator+(const GVector3D & v1, const GVector3D & v2);

/**
 * @brief Returns transformed copy of given vector
 * @param m - transformation matrix
 * @param v - vector to transform
 * @return transformed copy of given vector
 */
SGL_API GVector3D operator*(const GMatrix & m, const GVector3D & v);

} //namespace sgl

#endif //_GVECTOR3D_H_
