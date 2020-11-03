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

#ifndef _GINTERVAL_H_
#define _GINTERVAL_H_

#include "GExports.h"
#include "GTolerance.h"

namespace glib
{

/**
 * @brief Class represents linear interval. 'from' <= 'to'
 */
class GLIB_API GInterval
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
    GInterval(GInterval&&);

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
     * @brief Sets 'from' value. Inverts if new 'from' more than current 'to'
     * @param from - new from value
     */

    void setFrom(double from);

    double to() const;

    double setTo(double to);

    double operator=(std::size_t idx) const;

    double & operator=(std::size_t idx);

    bool equals(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    bool intersects(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    bool less(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    bool more(const GInterval & interval, double tolerance = GTolerance::zeroTol()) const;

    GInterval & operator+=(const GInterval & interval);

    GInterval & operator&=(const GInterval & interval);

private:
    double m_from{0}, m_to{1.0};
};

GLIB_API GInterval operator&(const GInterval & i1, const GInterval & i2);

} //namespace glib

#endif //_GINTERVAL_H_
