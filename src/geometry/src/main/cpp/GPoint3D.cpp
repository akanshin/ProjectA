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
#include "GPoint3D.h"

namespace glib
{

GPoint3D::GPoint3D()
    : m_x{ 0 }, m_y{ 0 }, m_z{ 0 }
{}

GPoint3D::GPoint3D(const GPoint3D & other) = default
GPoint3D::GPoint3D(GPoint3D && other) = default;

GPoint3D::GPoint3D(double x, double y, double z)
    : m_x{ x }, m_y{ y }, m_z{ z }
{}

GPoint3D::GPoint3D(double * pCoords)
    : m_x{ *(pCoords++) }, m_y{ *(pCoords++) }, m_z{ *pCoords }
{}

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
    
}

} //namespace glib