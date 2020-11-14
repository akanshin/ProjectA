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

#include "GPrecompiled.h"
#include "GMatrix4D.h"
#include "GVector3D.h"
#include "GUtils.h"

namespace sgl
{

const GMatrix4D &GMatrix4D::identity()
{
    static GMatrix4D s_identity;
    return s_identity;
}

GMatrix4D::GMatrix4D()
{
    setIdentity();
}

GMatrix4D::GMatrix4D(const GMatrix4D &m)
{
    std::memcpy(m_pData, m.m_pData, 16 * sizeof(double));
}

GMatrix4D::GMatrix4D(GMatrix4D &&m) noexcept = default;

GMatrix4D::GMatrix4D(std::initializer_list<double> l)
{
    std::copy(l.begin(), l.end(), m_pData);
}

GMatrix4D::GMatrix4D(const GPoint3D &o, const GVector3D &x, const GVector3D &y, const GVector3D &z)
    : GMatrix4D({ x[0], y[0], z[0], o[0],
                  x[1], y[1], z[1], o[1],
                  x[2], y[2], z[2], o[2],
                   0.0,  0.0,  0.0,  1.0 })
{}

GMatrix4D::~GMatrix4D() = default;

GMatrix4D & GMatrix4D::operator=(const GMatrix4D &m)
{
    std::memcpy(m_pData, m.m_pData, 16 * sizeof(double));
    return *this;
}

void GMatrix4D::setIdentity()
{
    for (std::size_t idx = 0; idx < 16; ++idx)
        m_pData[idx] = idx % 5 == 0 ? 1.0 : 0.0;
}

GPoint3D GMatrix4D::origin() const
{
    return GPoint3D(m_pData[3], m_pData[7], m_pData[11]);
}

GVector3D GMatrix4D::x() const
{
    return GVector3D(m_pData[0], m_pData[4], m_pData[8]);
}

GVector3D GMatrix4D::y() const
{
    return GVector3D(m_pData[1], m_pData[5], m_pData[9]);
}

GVector3D GMatrix4D::z() const
{
    return GVector3D(m_pData[2], m_pData[6], m_pData[10]);
}

const double * const GMatrix4D::operator[](std::size_t row) const
{
    return &m_pData[4 * row];
}

double * GMatrix4D::operator[](std::size_t row)
{
    return &m_pData[4 * row];
}

double GMatrix4D::operator()(std::size_t row, std::size_t column) const
{
    return m_pData[4 * row + column];
}

double & GMatrix4D::operator()(std::size_t row, std::size_t column)
{
    return m_pData[4 * row + column];
}

GMatrix4D & GMatrix4D::postMultiplyBy(const GMatrix4D &m)
{
    return *this = *this * m;
}

GMatrix4D &GMatrix4D::preMultiplyBy(const GMatrix4D &m)
{
    return *this = m * *this;
}

GMatrix4D &GMatrix4D::product(const GMatrix4D &m1, const GMatrix4D &m2)
{
    return *this = m1 * m2;
}

GMatrix4D GMatrix4D::transpose() const
{
    const auto & m = *this;
    return { m(0, 0), m(1, 0), m(2, 0), m(3, 0),
             m(0, 1), m(1, 1), m(2, 1), m(3, 1),
             m(0, 2), m(1, 2), m(2, 2), m(3, 2),
             m(0, 3), m(1, 3), m(2, 3), m(3, 3) };
}

GMatrix4D & GMatrix4D::invert()
{
    return *this = inverse();
}

GMatrix4D GMatrix4D::inverse() const
{
    const auto & m = *this;
    return { m(0, 0), m(0, 1), m(0, 2), -m(0, 0) * m(3, 0) - m(0, 1) * m(3, 1) - m(0, 2) * m(3, 2),
             m(1, 0), m(1, 1), m(1, 2), -m(1, 0) * m(3, 0) - m(1, 1) * m(3, 1) - m(1, 2) * m(3, 2),
             m(2, 0), m(2, 1), m(2, 2), -m(2, 0) * m(3, 0) - m(2, 1) * m(3, 1) - m(2, 2) * m(3, 2),
             0.0, 0.0, 0.0, 1.0 };
}

bool GMatrix4D::singular(double tolerance /*= GTolerance::zeroTol()*/) const
{
    return equal(determinant(), 0.0, tolerance);
}

double GMatrix4D::determinant() const
{
    const auto & m = *this;
    return m(0,0) * m(1, 1) * m(2, 2) - m(2, 0) * m(1, 1) * m(0, 2);
}

bool GMatrix4D::equals(const GMatrix4D & m, double tolerance /*= GTolerance::zeroTol()*/)
{
    for (std::size_t idx = 0; idx < 16; ++idx)
    {
        if (!equal(m_pData[idx], m.m_pData[idx], tolerance))
            return false;
    }
    return true;
}

GMatrix4D GMatrix4D::translation(const GVector3D & v)
{
    return { 1.0, 0.0, 0.0, v[0],
             0.0, 1.0, 0.0, v[1],
             0.0, 0.0, 1.0, v[2],
             0.0, 0.0, 0.0, 1.0 };
}

GMatrix4D GMatrix4D::rotation(double angle, const GVector3D &axis, const GPoint3D &center)
{
    double cos = std::cos(angle);
    double sin = std::sin(angle);

    double a11 = cos + axis[0] * axis[0] * (1.0 - cos);
    double a21 = axis[0] * axis[1] * (1.0 - cos) + axis[2] * sin;
    double a31 = axis[0] * axis[2] * (1.0 - cos) - axis[1] * sin;
    double a12 = axis[0] * axis[1] * (1.0 - cos) - axis[2] * sin;
    double a22 = cos + axis[1] * axis[1] * (1.0 - cos);
    double a32 = axis[1] * axis[2] * (1.0 - cos) + axis[0] * sin;
    double a13 = axis[0] * axis[2] * (1.0 - cos) + axis[1] * sin;
    double a23 = axis[1] * axis[2] * (1.0 - cos) - axis[0] * sin;
    double a33 = cos + axis[2] * axis[2] * (1.0 - cos);

    return { a11, a12, a13, center[0],
             a21, a22, a23, center[1],
             a31, a32, a33, center[2],
             0.0, 0.0, 0.0,       1.0 };
}

GMatrix4D GMatrix4D::scale(double scale, const GPoint3D &base)
{
    return { scale,   0.0,   0.0, base[0],
               0.0, scale,   0.0, base[1],
               0.0,   0.0, scale, base[2],
               0.0,   0.0,   0.0,     1.0 };
}

GMatrix4D GMatrix4D::scale(double scaleX, double scaleY, double scaleZ, const GPoint3D &base)
{
    return { scaleX,    0.0,    0.0, base[0],
                0.0, scaleY,    0.0, base[1],
                0.0,    0.0, scaleZ, base[2],
                0.0,    0.0,    0.0,     1.0 };
}

GMatrix4D GMatrix4D::scale(double scale, const GVector3D &direction, const GPoint3D &base)
{
    return { scale * direction[0],                  0.0,                  0.0, base[0],
                              0.0, scale * direction[1],                  0.0, base[1],
                              0.0,                  0.0, scale * direction[2], base[2],
                              0.0,                  0.0,                  0.0,     1.0 };
}

GMatrix4D GMatrix4D::mirror(const GPoint3D &base, const GVector3D &direction)
{
    GVector3D n = std::move(direction.normalize());
    double coef = 2 * (base[0] * n[0] + base[1] * n[1] + base[2] * n[2]);
    double a11 = 1.0 - 2.0 * n[0] * n[0];
    double a22 = 1.0 - 2.0 * n[1] * n[1];
    double a33 = 1.0 - 2.0 * n[2] * n[2];
    double a12 = -n[0] * n[0];
    double a13 = -n[0] * n[2];
    double a23 = -n[1] * n[2];

    return { a11, a12, a13, n[0] * coef,
             a12, a22, a23, n[1] * coef,
             a13, a23, a33, n[2] * coef,
             0.0, 0.0, 0.0,         1.0 };
}

GMatrix4D GMatrix4D::projection(const GPoint3D &plnPoint, const GVector3D &plnNormal, const GVector3D &prjDir)
{
    GVector3D n = std::move(plnNormal.normalize());
    GVector3D udir = std::move(prjDir.normalize());

    const double coef1 = 1.0 / (n % udir);
    const double coef2 = (n % plnPoint.asVector()) * coef1;

    return { 1.0 - udir[0] * n[0] * coef1,      -udir[1] * n[0] * coef1,      -udir[2] * n[0] * coef1, udir[0] * coef2,
                  -udir[0] * n[1] * coef1, 1.0 - udir[1] * n[1] * coef1,      -udir[2] * n[1] * coef1, udir[1] * coef2,
                  -udir[0] * n[2] * coef1,      -udir[1] * n[2] * coef1, 1.0 - udir[2] * n[2] * coef1, udir[2] * coef2,
             0.0, 0.0, 0.0, 1.0 };
}

GMatrix4D GMatrix4D::projection(const GPoint3D &plnPoint, const GVector3D &plnNormal)
{
    GVector3D n = std::move(plnNormal.normalize());
    const double coef = n % plnPoint.asVector();
    double a11 = 1.0 - n[0] * n[0];
    double a22 = 1.0 - n[1] * n[1];
    double a33 = 1.0 - n[2] * n[2];
    double a12 = -n[0] * n[1];
    double a13 = -n[0] * n[2];
    double a23 = -n[1] * n[2];
    return { a11, a12, a13, n[0] * coef,
             a12, a22, a23, n[1] * coef,
             a13, a23, a33, n[2] * coef,
             0.0, 0.0, 0.0,         1.0 };
}

GMatrix4D operator*(const GMatrix4D & m1, const GMatrix4D & m2)
{
    return { m1(0, 0) * m2(0, 0) + m1(1, 0) * m2(0, 1) + m1(2, 0) * m2(0, 2) + m1(3, 0) * m2(0, 3),
             m1(0, 1) * m2(0, 0) + m1(1, 1) * m2(0, 1) + m1(2, 1) * m2(0, 2) + m1(3, 1) * m2(0, 3),
             m1(0, 2) * m2(0, 0) + m1(1, 2) * m2(0, 1) + m1(2, 2) * m2(0, 2) + m1(3, 2) * m2(0, 3),
             m1(0, 3) * m2(0, 0) + m1(1, 3) * m2(0, 1) + m1(2, 3) * m2(0, 2) + m1(3, 3) * m2(0, 3),

             m1(0, 0) * m2(1, 0) + m1(1, 0) * m2(1, 1) + m1(2, 0) * m2(1, 2) + m1(3, 0) * m2(1, 3),
             m1(0, 1) * m2(1, 0) + m1(1, 1) * m2(1, 1) + m1(2, 1) * m2(1, 2) + m1(3, 1) * m2(1, 3),
             m1(0, 2) * m2(1, 0) + m1(1, 2) * m2(1, 1) + m1(2, 2) * m2(1, 2) + m1(3, 2) * m2(1, 3),
             m1(0, 3) * m2(1, 0) + m1(1, 3) * m2(1, 1) + m1(2, 3) * m2(1, 2) + m1(3, 3) * m2(1, 3),

             m1(0, 0) * m2(2, 0) + m1(1, 0) * m2(2, 1) + m1(2, 0) * m2(2, 2) + m1(3, 0) * m2(2, 3),
             m1(0, 1) * m2(2, 0) + m1(1, 1) * m2(2, 1) + m1(2, 1) * m2(2, 2) + m1(3, 1) * m2(2, 3),
             m1(0, 2) * m2(2, 0) + m1(1, 2) * m2(2, 1) + m1(2, 2) * m2(2, 2) + m1(3, 2) * m2(2, 3),
             m1(0, 3) * m2(2, 0) + m1(1, 3) * m2(2, 1) + m1(2, 3) * m2(2, 2) + m1(3, 3) * m2(2, 3),

             m1(0, 0) * m2(3, 0) + m1(1, 0) * m2(3, 1) + m1(2, 0) * m2(3, 2) + m1(3, 0) * m2(3, 3),
             m1(0, 1) * m2(3, 0) + m1(1, 1) * m2(3, 1) + m1(2, 1) * m2(3, 2) + m1(3, 1) * m2(3, 3),
             m1(0, 2) * m2(3, 0) + m1(1, 2) * m2(3, 1) + m1(2, 2) * m2(3, 2) + m1(3, 2) * m2(3, 3),
             m1(0, 3) * m2(3, 0) + m1(1, 3) * m2(3, 1) + m1(2, 3) * m2(3, 2) + m1(3, 3) * m2(3, 3) };
}

} //namespace sgl
