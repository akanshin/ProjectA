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

#ifndef _GINTERVAL_H_
#define _GINTERVAL_H_

#include "GExports.h"
#include "GTolerance.h"

namespace sgl
{

/**
 * @brief Class represents linear interval. 'from' <= 'to'
 */
class SGL_API GInterval
{
public:
    /**
     * @brief Initializes interval [0, 1]
     */
    GInterval();

    /**
     * @brief Copy constructor
     */
    GInterval(const GInterval &);

    /**
     * @brief Move constructor
     */
    GInterval(GInterval&&) noexcept;

    /**
     * @brief Initializes interval ['from', 'to'] if 'from' <= 'to' or ['to', 'from'] if 'from' > 'to'
     * @param from - from
     * @param to - to
     */
    GInterval(double from, double to);

    /**
     * @brief Initializes interval by initializer list
     */
    GInterval(std::initializer_list<double>);

    /** No doc */
    ~GInterval();

    /**
     * @brief Assignment operator
     * @return reference to this interval object
     */
    GInterval & operator=(const GInterval&);

    /**
     * @brief Returns first value of interval
     * @return first value of interval
     */
    double from() const;

    /**
     * @brief Sets 'from' value. Inverts if new 'from' is more than current 'to'
     * @param from - new 'from' value
     */
    void setFrom(double from);

    /**
     * @brief Returns second value of interval
     * @return second value of interval
     */
    double to() const;

    /**
     * @brief Sets 'to' value. Inverts if new 'to' is less than current 'from'
     * @param to - new 'to' value
     */
    void setTo(double to);

    /**
     * @brief Checks equality
     * @param interval - interval to check equality
     * @param tolerance - tolerance
     * @return true if 'this' interval equals to given interval within tolerance, otherwise false
     */
    bool equals(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    /**
     * @brief Checks intersection
     * @param interval - interval to check intersection
     * @param tolerance - tolerance
     * @return true if 'this' and given interval intersect within tolerance
     */
    bool intersects(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    /**
     * @brief Returns true if this->to() < interval.from()
     * @param interval - interval to check
     * @param tolerance - tolerance
     * @return true if this->to() < interval.from(), otherwise false
     */
    bool less(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    /**
     * @brief Returns true if this->from() > interval.to()
     * @param interval - interval to check
     * @param tolerance - tolerance
     * @return true if this->from() > interval.to(), otherwise false
     */
    bool more(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    /**
     * @brief Creates interval [std::min(this->from(), interval.from()), std::max(this->to(), interval.to())]
     * @param interval - interval to add
     * @return Reference to this interval object
     */
    GInterval & operator+=(const GInterval & interval);

private:
    double m_from{0}, m_to{1.0};
};

} //namespace sgl

#endif //_GINTERVAL_H_
