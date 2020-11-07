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
#include "GVector3D.h"
#include "GMatrix.h"
#include "GUtils.h"

namespace sgl
{

GVector3D::GVector3D() = default;

GVector3D::GVector3D(const GVector3D & other) = default;

GVector3D::GVector3D(GVector3D && other) noexcept = default;

GVector3D::GVector3D(double x, double y, double z)
    : m_x{ x }, m_y{ y }, m_z{ z }
{}

GVector3D::GVector3D(double * pCoords)
    : m_x{ *(pCoords++) }, m_y{ *(pCoords++) }, m_z{ *pCoords }
{}

GVector3D::GVector3D(std::initializer_list<double> l)
{
    auto it = l.begin();
    set(*it, *(it + 1), *(it + 2));
}

GVector3D::~GVector3D() = default;

double GVector3D::x() const
{
    return m_x;
}

void GVector3D::setX(double newX)
{
    m_x = newX;
}

double GVector3D::y() const
{
    return m_y;
}

void GVector3D::setY(double newY)
{
    m_y = newY;
}

double GVector3D::z() const
{
    return m_z;
}

void GVector3D::setZ(double newZ)
{
    m_z = newZ;
}

void GVector3D::set(double newX, double newY, double newZ)
{
    m_x = newX;
    m_y = newY;
    m_z = newZ;
}

double GVector3D::operator[](std::size_t coordIdx) const
{
    switch (coordIdx)
    {
        case 0: return m_x;
        case 1: return m_y;
        case 2: return m_z;
        default: break;
    }
    throw std::invalid_argument("GVector3D: index out of bounds");
}

double & GVector3D::operator[](std::size_t coordIdx)
{
    switch (coordIdx)
    {
        case 0: return m_x;
        case 1: return m_y;
        case 2: return m_z;
        default: break;
    }
    throw std::invalid_argument("GVector3D: index out of bounds");
}

double GVector3D::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

bool GVector3D::isZero(double tolerance /*= GTolerance::lengthTol()*/) const
{
    return equal(length(), 0.0, tolerance);
}

bool GVector3D::isUnit(double tolerance /*= GTolerance::lengthTol()*/) const
{
    return equal(length(), 1.0, tolerance);
}

GVector3D & GVector3D::normalize()
{
    double len = length();
    if (equal(len, 0, GTolerance::zeroTol()))
        throw std::logic_error("GVector3D: division by zero");
    *this /= len;
    return *this;
}

GVector3D GVector3D::normalize() const
{
    GVector3D res(*this);
    res.normalize();
    return res;
}

bool GVector3D::equals(const GVector3D & v, double tolerance /*= GTolerance::lengthTol()*/) const
{
    const GVector3D & rthis = *this;
    for (std::size_t idx = 0; idx < 3; ++idx)
        if (!equal(rthis[idx], v[idx], tolerance))
            return false;
    return true;
}

bool GVector3D::parallel(const GVector3D & v, double tolerance /*= GTolerance::angularTol()*/) const
{
    double cosAngle = (*this % v) / (length() * v.length());
    return equal(cosAngle, 1.0, tolerance);
}

bool GVector3D::antiparallel(const GVector3D & v, double tolerance /*= GTolerance::angularTol()*/) const
{
    double cosAngle = (*this % v) / (length() * v.length());
    return equal(cosAngle, -1.0, tolerance);
}

bool GVector3D::biparallel(const GVector3D & v, double tolerance /*= GTolerance::angularTol()*/) const
{
    double cosAngle = (*this % v) / (length() * v.length());
    return equal(cosAngle, -1.0, tolerance) || equal(cosAngle, 1.0, tolerance);
}

bool GVector3D::perpendicular(const GVector3D & v, double tolerance /*= GTolerance::angularTol()*/) const
{
    double cosAngle = (*this % v) / (length() * v.length());
    return equal(cosAngle, 0.0, tolerance);
}

GVector3D & GVector3D::operator=(const GVector3D & v) = default;

GVector3D & GVector3D::operator+=(const GVector3D & v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
}

GVector3D & GVector3D::operator-=(const GVector3D & v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
}

GVector3D & GVector3D::operator*=(double scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

GVector3D & GVector3D::operator/=(double scalar)
{
    if (equal(scalar, 0, GTolerance::zeroTol()))
        throw std::logic_error("GVector3D: division by zero");
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

GVector3D & GVector3D::operator*=(const GMatrix & m)
{
    double x = m(0, 0) * m_x + m(1, 0) * m_y + m(2, 0) * m_z;
    double y = m(0, 1) * m_x + m(1, 1) * m_y + m(2, 1) * m_z;
    double z = m(0, 2) * m_x + m(1, 2) * m_y + m(2, 2) * m_z;
    set(x, y, z);
    return *this;
}

double operator%(const GVector3D & v1, const GVector3D & v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

GVector3D operator*(const GVector3D & v1, const GVector3D & v2)
{
    return GVector3D(v1[1] * v2[2], v1[2] * v2[0], v1[0] * v2[1]);
}

GVector3D operator*(const GMatrix & m, const GVector3D & v)
{
    GVector3D res;
    res *= m;
    return res;
}

} //namespace sgl
