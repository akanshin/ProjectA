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
#include "GPoint3D.h"
#include "GVector3D.h"
#include "GMatrix.h"
#include "GUtils.h"

namespace sgl
{

const GPoint3D & GPoint3D::origin()
{
    static GPoint3D s_origin;
    return s_origin;
}

GPoint3D::GPoint3D()
    : m_x{ 0 }, m_y{ 0 }, m_z{ 0 }
{}

GPoint3D::GPoint3D(const GPoint3D & other) = default;

GPoint3D::GPoint3D(GPoint3D && other) noexcept = default;

GPoint3D::GPoint3D(double x, double y, double z)
    : m_x{ x }, m_y{ y }, m_z{ z }
{}

GPoint3D::GPoint3D(double * pCoords)
    : m_x{ *(pCoords++) }, m_y{ *(pCoords++) }, m_z{ *pCoords }
{}

GPoint3D::GPoint3D(std::initializer_list<double> l)
{
    auto it = l.begin();
    set(*it, *(it + 1), *(it + 2));
}

GPoint3D::~GPoint3D() = default;

double GPoint3D::x() const
{
    return m_x;
}

void GPoint3D::setX(double newX)
{
    m_x = newX;
}

double GPoint3D::y() const
{
    return m_y;
}

void GPoint3D::setY(double newY)
{
    m_y = newY;
}

double GPoint3D::z() const
{
    return m_z;
}

void GPoint3D::setZ(double newZ)
{
    m_z = newZ;
}

void GPoint3D::set(double newX, double newY, double newZ)
{
    m_x = newX;
    m_y = newY;
    m_z = newZ;
}

bool GPoint3D::equals(const GPoint3D & pt, double tolerance /*= GTolerance::lengthTol()*/) const
{
    const GPoint3D & rthis = *this;
    for (std::size_t idx = 0; idx < 3; ++idx)
        if (!equal(rthis[idx], pt[idx], tolerance))
            return false;
    return true;
}

double GPoint3D::operator[](std::size_t coordIdx) const
{
    switch (coordIdx)
    {
        case 0: return m_x;
        case 1: return m_y;
        case 2: return m_z;
        default: break;
    }
    throw std::invalid_argument("GPoint3D: index out of range");
}

double & GPoint3D::operator[](std::size_t coordIdx)
{
    switch (coordIdx)
    {
        case 0: return m_x;
        case 1: return m_y;
        case 2: return m_z;
        default: break;
    }
    throw std::invalid_argument("GPoint3D: index out of range");
}

GPoint3D & GPoint3D::operator=(const GPoint3D & pt)
{
    set(pt[0], pt[1], pt[2]);
}

GPoint3D & GPoint3D::operator+=(const GPoint3D & pt)
{
    m_x += pt.m_x;
    m_y += pt.m_y;
    m_z += pt.m_z;
    return *this;
}

GPoint3D & GPoint3D::operator-=(const GPoint3D & pt)
{
    m_x -= pt.m_x;
    m_y -= pt.m_y;
    m_z -= pt.m_z;
    return *this;
}

GPoint3D & GPoint3D::operator+=(const GVector3D & v)
{
    m_x += v.x();
    m_y += v.y();
    m_z += v.z();
    return *this;
}

GPoint3D & GPoint3D::operator-=(const GVector3D & v)
{
    m_x -= v.x();
    m_y -= v.y();
    m_z -= v.z();
    return *this;
}

GPoint3D & GPoint3D::operator*=(const GMatrix & m)
{
    double x = m(0, 0) * m_x + m(1, 0) * m_y + m(2, 0) * m_z + m(3, 0);
    double y = m(0, 1) * m_x + m(1, 1) * m_y + m(2, 1) * m_z + m(3, 1);
    double z = m(0, 2) * m_x + m(1, 2) * m_y + m(2, 2) * m_z + m(3, 2);
    set(x, y, z);
    return *this;
}

GVector3D GPoint3D::asVector() const
{
    return GVector3D(m_x, m_y, m_z);
}

GVector3D operator-(const GPoint3D & pt1, const GPoint3D & pt2)
{
    return GVector3D(pt1.x() - pt2.x(), pt1.y() - pt2.y(), pt1.z() - pt2.z());
}

GPoint3D operator+(const GPoint3D & pt1, const GPoint3D & pt2)
{
    return GPoint3D(pt1.x() + pt2.x(), pt1.y() + pt2.y(), pt1.z() + pt2.z());
}

GPoint3D operator+(const GPoint3D & pt, const GVector3D & v)
{
    return GPoint3D(pt.x() + v.x(), pt.y() + v.y(), pt.z() + v.z());
}

GPoint3D operator+(const GVector3D & v, const GPoint3D & pt)
{
    return GPoint3D(pt.x() + v.x(), pt.y() + v.y(), pt.z() + v.z());
}

GPoint3D operator-(const GPoint3D & pt, const GVector3D & v)
{
    return GPoint3D(pt.x() - v.x(), pt.y() - v.y(), pt.z() - v.z());
}

GPoint3D operator*(const GMatrix & m, const GPoint3D & pt)
{
    GPoint3D res = pt;
    res *= m;
    return res;
}

} //namespace sgl
