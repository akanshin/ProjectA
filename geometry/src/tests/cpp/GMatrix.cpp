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

#include "GPrecompiled.h"
#include "GMatrix.h"
#include "GVector3D.h"
#include "GUtils.h"

namespace glib
{

const GMatrix &GMatrix::identity()
{
    static GMatrix s_identity;
    return s_identity;
}

GMatrix::GMatrix()
{
    setIdentity();
}

GMatrix::GMatrix(const GMatrix &m) = default;

GMatrix::GMatrix(GMatrix &&m) noexcept = default;

GMatrix::GMatrix(std::initializer_list<double> l)
{
    std::copy(l.begin(), l.end(), m_pData);
}

GMatrix::GMatrix(const GPoint3D &o, const GVector3D &x, const GVector3D &y, const GVector3D &z)
    : GMatrix({ x[0], x[1], x[2], 0.0,
                y[0], y[1], y[2], 0.0,
                z[0], z[1], z[2], 0.0,
                o[0], o[1], o[2], 1.0 })
{}

GMatrix::~GMatrix() = default;

GMatrix &GMatrix::operator=(const GMatrix &m)
{
    std::memcpy(m_pData, m.m_pData, 16 * sizeof(double));
}

void GMatrix::setIdentity()
{
    for (std::size_t idx = 0; idx < 16; ++idx)
        m_pData[idx] = idx % 5 == 0 ? 1.0 : 0.0;
}

GPoint3D GMatrix::origin() const
{
    return GPoint3D(m_pData[12], m_pData[13], m_pData[14]);
}

GVector3D GMatrix::x() const
{
    return GVector3D(m_pData[0], m_pData[1], m_pData[2]);
}

GVector3D GMatrix::y() const
{
    return GVector3D(m_pData[4], m_pData[5], m_pData[6]);
}

GVector3D GMatrix::z() const
{
    return GVector3D(m_pData[8], m_pData[9], m_pData[10]);
}

const double * const GMatrix::operator[](std::size_t column) const
{
    return &m_pData[4 * column];
}

double * GMatrix::operator[](std::size_t column)
{
    return &m_pData[4 * column];
}

double GMatrix::operator()(std::size_t column, std::size_t row) const
{
    return m_pData[4 * column + row];
}

double & GMatrix::operator()(std::size_t column, std::size_t row)
{
    return m_pData[4 * column + row];
}

GMatrix & GMatrix::postMultiplyBy(const GMatrix &m)
{
    return *this = *this * m;
}

GMatrix &GMatrix::preMultiplyBy(const GMatrix &m)
{
    return *this = m * *this;
}

GMatrix &GMatrix::product(const GMatrix &m1, const GMatrix &m2)
{
    return *this = m1 * m2;
}

GMatrix GMatrix::transpose() const
{
    const auto & m = *this;
    return { m(0, 0), m(1, 0), m(2, 0), m(3, 0),
             m(0, 1), m(1, 1), m(2, 1), m(3, 1),
             m(0, 2), m(1, 2), m(2, 2), m(3, 2),
             m(0, 3), m(1, 3), m(2, 3), m(3, 3) };
}

GMatrix & GMatrix::invert()
{
    return *this = inverse();
}

GMatrix GMatrix::inverse() const
{
    const auto & m = *this;
    return { m(0, 0), m(1, 0), m(2, 0), 0.0,
             m(0, 1), m(1, 1), m(2, 1), 0.0,
             m(0, 2), m(1, 2), m(2, 2), 0.0,
             -m(0, 0) * m(3, 0)
             -m(0, 1) * m(3, 1)
             -m(0, 2) * m(3, 2),
             -m(1, 0) * m(3, 0)
             -m(1, 1) * m(3, 1)
             -m(1, 2) * m(3, 2),
             -m(2, 0) * m(3, 0)
             -m(2, 1) * m(3, 1)
             -m(2, 2) * m(3, 2),
             1.0 };
}

bool GMatrix::singular(double tolerance /*= GTolerance::zeroTol()*/) const
{
    return equal(determinant(), 0.0, tolerance);
}

double GMatrix::determinant() const
{
    const auto & m = *this;
    return m(0,0) * m(1, 1) * m(2, 2) * m(3, 3);
}

bool GMatrix::equals(const GMatrix & m, double tolerance /*= GTolerance::zeroTol()*/)
{
    for (std::size_t idx = 0; idx < 16; ++idx)
    {
        if (!equal(m_pData[idx], m.m_pData[idx], tolerance))
            return false;
    }
    return true;
}

GMatrix GMatrix::translation(const GVector3D & v)
{
    return {  1.0,  0.0,  0.0, 0.0,
              0.0,  1.0,  0.0, 0.0,
              0.0,  0.0,  1.0, 0.0,
             v[0], v[1], v[2], 1.0 };
}

GMatrix GMatrix::rotation(double angle, const GVector3D &axis, const GPoint3D &center)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::scale(double scale, const GPoint3D &base)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::scale(double scaleX, double scaleY, double scaleZ, const GPoint3D &base)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::scale(double scale, const GVector3D &direction, const GPoint3D &base)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::mirror(const GPoint3D &base, const GVector3D &direction)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::projection(const GPoint3D &plnPoint, const GVector3D &plnNormal, const GVector3D &prjDir)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix GMatrix::projection(const GPoint3D &plnPoint, const GVector3D &plnNormal)
{
    // TODO implement
    throw std::runtime_error("Not implemented");
}

GMatrix operator*(const GMatrix & m1, const GMatrix & m2)
{
    return { m1(0, 0) * m2(0, 0) + m1(1, 0) * m2(0, 1) + m1(2, 0) * m2(0, 2) + m1(3, 0) * m2(0, 3),
             m1(0, 0) * m2(1, 0) + m1(1, 0) * m2(1, 1) + m1(2, 0) * m2(1, 2) + m1(3, 0) * m2(1, 3),
             m1(0, 0) * m2(2, 0) + m1(1, 0) * m2(2, 1) + m1(2, 0) * m2(2, 2) + m1(3, 0) * m2(2, 3),
             m1(0, 0) * m2(3, 0) + m1(1, 0) * m2(3, 1) + m1(2, 0) * m2(3, 2) + m1(3, 0) * m2(3, 3),
             m1(0, 1) * m2(0, 0) + m1(1, 1) * m2(0, 1) + m1(2, 1) * m2(0, 2) + m1(3, 1) * m2(0, 3),
             m1(0, 1) * m2(1, 0) + m1(1, 1) * m2(1, 1) + m1(2, 1) * m2(1, 2) + m1(3, 1) * m2(1, 3),
             m1(0, 1) * m2(2, 0) + m1(1, 1) * m2(2, 1) + m1(2, 1) * m2(2, 2) + m1(3, 1) * m2(2, 3),
             m1(0, 1) * m2(3, 0) + m1(1, 1) * m2(3, 1) + m1(2, 1) * m2(3, 2) + m1(3, 1) * m2(3, 3),
             m1(0, 2) * m2(0, 0) + m1(1, 2) * m2(0, 1) + m1(2, 2) * m2(0, 2) + m1(3, 2) * m2(0, 3),
             m1(0, 2) * m2(1, 0) + m1(1, 2) * m2(1, 1) + m1(2, 2) * m2(1, 2) + m1(3, 2) * m2(1, 3),
             m1(0, 2) * m2(2, 0) + m1(1, 2) * m2(2, 1) + m1(2, 2) * m2(2, 2) + m1(3, 2) * m2(2, 3),
             m1(0, 2) * m2(3, 0) + m1(1, 2) * m2(3, 1) + m1(2, 2) * m2(3, 2) + m1(3, 2) * m2(3, 3),
             m1(0, 3) * m2(0, 0) + m1(1, 3) * m2(0, 1) + m1(2, 3) * m2(0, 2) + m1(3, 3) * m2(0, 3),
             m1(0, 3) * m2(1, 0) + m1(1, 3) * m2(1, 1) + m1(2, 3) * m2(1, 2) + m1(3, 3) * m2(1, 3),
             m1(0, 3) * m2(2, 0) + m1(1, 3) * m2(2, 1) + m1(2, 3) * m2(2, 2) + m1(3, 3) * m2(2, 3),
             m1(0, 3) * m2(3, 0) + m1(1, 3) * m2(3, 1) + m1(2, 3) * m2(3, 2) + m1(3, 3) * m2(3, 3) };
}

} //namespace glib
