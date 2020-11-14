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

#ifndef _GMATRIX4D_H_
#define _GMATRIX4D_H_

#include "GExports.h"
#include "GTolerance.h"
#include "GPoint3D.h"

#include <initializer_list>

namespace sgl
{

class GVector3D;

/**
 * @brief Transformation matrix
 *   <br>[ a00, a10, a20, t0 ]
 *   <br>[ q01, a11, a21, t1 ]
 *   <br>[ a02, a12, a22, t2 ]
 *   <br>[   0,   0,   0,  1 ]
 *   <p/> Example of translation matrix:
 *   <br> GMatrix4D translation { 1.0, 0.0, 0.0, 5.0,
 *   <br>                         0.0, 1.0, 0.0, 7.0,
 *   <br>                         0.0, 0.0, 1.0, 4.0,
 *   <br>                         0.0, 0.0, 0.0, 1.0 };
 * @author Artemiy Kanshin
 */
class SGL_API GMatrix4D
{
public:
    /**
     * @return identity matrix
     */
    static const GMatrix4D & identity();

public:
    /**
     * @brief Initializes identity matrix
     */
    GMatrix4D();

    /**
     * @brief Copy constructor
     */
    GMatrix4D(const GMatrix4D &);

    /**
     * @brief Move constructor
     */
    GMatrix4D(GMatrix4D &&) noexcept;

    /**
     * @brief Initializes matrix by initializer list which should have 16 numbers
     */
    GMatrix4D(std::initializer_list<double>);

    /**
     * @brief Initializes matrix with coordinate system parameters
     * @param origin - coordinate system origin
     * @param x - x axis
     * @param y - y axis
     * @param z - z axis
     */
    explicit GMatrix4D(const GPoint3D & origin, const GVector3D & x, const GVector3D & y, const GVector3D & z);

    /** No doc */
    ~GMatrix4D();

    /**
     * @brief operator =
     * @param m - matrix
     * @return reference to this matrix object
     */
    GMatrix4D & operator=(const GMatrix4D & m);

    /**
     * @brief Makes this matrix identity
     */
    void setIdentity();

    /**
     * @return coordinate system origin
     */
    GPoint3D origin() const;

    /**
     * @return coordinate system x axis
     */
    GVector3D x() const;

    /**
     * @return coordinate system y axis
     */
    GVector3D y() const;

    /**
     * @return coordinate system z axis
     */
    GVector3D z() const;

    /**
     * @brief Gives read only access to the matrix row by index
     * @param row - row index
     * @return const pointer to row
     */
    const double * const operator[](std::size_t row) const;

    /**
     * @brief Gives write access to the matrix row by index
     * @param row - row index
     * @return pointer to row
     */
    double * operator[](std::size_t row);

    /**
     * @brief Returns element of matrix
     * @param row - row index
     * @param column - column index
     * @return element of matrix
     */
    double operator()(std::size_t row, std::size_t column) const;

    /**
     * @brief Returns reference to element of matrix
     * @param row - row index
     * @param column - column index
     * @return reference to element of matrix
     */
    double & operator()(std::size_t row, std::size_t column);

    /**
     * @brief Produces multiplication of matrix: this * m
     * @param m - another matrix
     * @return reference to this matrix object
     */
    GMatrix4D & postMultiplyBy(const GMatrix4D & m);

    /**
     * @brief Produces multiplication of matrix: m * this
     * @param m - another matrix
     * @return reference to this matrix object
     */
    GMatrix4D & preMultiplyBy(const GMatrix4D & m);

    /**
     * @brief Sets this matrix as result of multiplication of given matrices
     * @param m1 - first matrix
     * @param m2 - second matrix
     * @return reference to this matrix object
     */
    GMatrix4D & product(const GMatrix4D & m1, const GMatrix4D & m2);

    /**
     * @brief Returns transposed copy of this matrix
     * @return transposed copy of this matrix
     */
    GMatrix4D transpose() const;

    /**
     * @brief Inverts this matrix
     * @return reference to this matrix object
     */
    GMatrix4D & invert();

    /**
     * @brief Returns inverted copy of this matrix
     * @return inverted copy of this matrix
     */
    GMatrix4D inverse() const;

    /**
     * @brief Checks matrix singularity
     * @param tolerance - zero tolerance
     * @return true if matrix determinant equals to zero, otherwise false
     */
    bool singular(double tolerance = GTolerance::zeroTol()) const;

    /**
     * @brief Computes determinant of this matrix
     * @return determinant of this matrix
     */
    double determinant() const;

    /**
     * @brief Compares this matrix with given within tolerance
     * @param m - matrix to check equality
     * @param tolerance - zero tolerance
     * @return true if this matrix is equal to given within tolerance, otherwise false
     */
    bool equals(const GMatrix4D & m, double tolerance = GTolerance::zeroTol());

    /**
     * @brief Creates translation matrix
     * @param v - translation vector
     * @return translation matrix
     */
    static GMatrix4D translation(const GVector3D & v);

    /**
     * @brief Creates rotation matrix
     * @param angle - rotation angle
     * @param axis - rotation axis
     * @param center - center of rotation
     * @return rotation matrix
     */
    static GMatrix4D rotation(double angle, const GVector3D & axis, const GPoint3D & center = GPoint3D::origin());

    /**
     * @brief Creates scale matrix
     * @param scale - scale
     * @param base - base point
     * @return scale matrix
     */
    static GMatrix4D scale(double scale, const GPoint3D & base = GPoint3D::origin());

    /**
     * @brief Creates scale matrix
     * @param scaleX - x-axis scale
     * @param scaleY - y-axis scale
     * @param scaleZ - z-axis scale
     * @param base - base point
     * @return scale matrix
     */
    static GMatrix4D scale(double scaleX, double scaleY, double scaleZ, const GPoint3D & base = GPoint3D::origin());

    /**
     * @brief Creates scale matrix
     * @param scale - scale value
     * @param direction - scale direction
     * @param base - base point
     * @return scale matrix
     */
    static GMatrix4D scale(double scale, const GVector3D & direction, const GPoint3D & base = GPoint3D::origin());

    /**
     * @brief Creates mirror matrix
     * @param base - base point
     * @param direction - mirroring direction
     * @return mirror matrix
     */
    static GMatrix4D mirror(const GPoint3D & base, const GVector3D & direction);

    /**
     * @brief Creates projection matrix
     * @param plnPoint - projection plane point
     * @param plnNormal - projection plane normal
     * @param prjDir - projection direction
     * @return projection matrix
     */
    static GMatrix4D projection(const GPoint3D & plnPoint, const GVector3D & plnNormal, const GVector3D & prjDir);

    /**
     * @brief Creates projection matrix
     * @param plnPoint - projection plane point
     * @param plnNormal - projection plane normal
     * @return projection matrix
     */
    static GMatrix4D projection(const GPoint3D & plnPoint, const GVector3D & plnNormal);

private:
    double m_pData[16];
};

/**
 * @brief operator * for matrices
 * @param m1 - left matrix
 * @param m2 - right matrix
 * @return Result matrix
 */
SGL_API GMatrix4D operator*(const GMatrix4D & m1, const GMatrix4D & m2);

} //namespace sgl

#endif //_GMATRIX4D_H_
