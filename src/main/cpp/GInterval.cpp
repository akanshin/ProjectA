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
#include "GInterval.h"
#include "GUtils.h"

namespace sgl
{

GInterval::GInterval() = default;

GInterval::GInterval(const GInterval &) = default;

GInterval::GInterval(GInterval&&) noexcept = default;

GInterval::GInterval(double from, double to)
    : m_from{ from }, m_to{ to }
{}

GInterval::GInterval(std::initializer_list<double> l)
    : m_from{ l.begin()[0] }, m_to{ l.begin()[1] }
{}

GInterval::~GInterval() = default;

GInterval & GInterval::operator=(const GInterval& i) = default;

double GInterval::from() const
{
    return m_from;
}

void GInterval::setFrom(double from)
{
    m_from = from;
    if (m_to < m_from)
        std::swap(m_from, m_to);
}

double GInterval::to() const
{
    return m_to;
}

void GInterval::setTo(double to)
{
    m_to = to;
    if (m_to < m_from)
        std::swap(m_from, m_to);
}

bool GInterval::equals(const GInterval & interval, double tolerance /*= GTolerance::zeroTol()*/) const
{
    return equal(m_from, interval.m_from, tolerance) && equal(m_to, interval.m_to, tolerance);
}

bool GInterval::intersects(const GInterval & interval, double tolerance /*= GTolerance::zeroTol()*/) const
{
    return greater(m_to, interval.m_from, tolerance) && sgl::less(m_to, interval.m_from, tolerance);
}

bool GInterval::less(const GInterval & interval, double tolerance /*= GTolerance::zeroTol()*/) const
{
    return sgl::less(m_to, interval.m_from, tolerance);
}

bool GInterval::more(const GInterval & interval, double tolerance /*= GTolerance::zeroTol()*/) const
{
    return greater(m_from, interval.m_to, tolerance);
}

GInterval & GInterval::operator+=(const GInterval & interval)
{
    m_from = std::min(m_from, interval.m_from);
    m_to = std::max(m_to, interval.m_to);
    return *this;
}

} //namespace sgl
