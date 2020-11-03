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

#ifndef _GTOLERANCE_H_
#define _GTOLERANCE_H_

#include "GExports.h"

namespace sgl
{

/**
 * @brief Utility class which provides access to tolerance constants.
 */
class SGL_API GTolerance
{
public:
    GTolerance() = delete;
    ~GTolerance() = delete;

    /**
     * @return Length tolerance (defaults to 1.0e-6)
     */
    static double lengthTol();

    /**
     * @return Angular tolerance (defaults to 1.0e-10)
     */
    static double angularTol();

    /**
     * @return Zero tolerance (defaults to 1.0e-30)
     */
    static double zeroTol();

    /**
     * @brief Sets length tolerance
     * @param tolerance - length tolerance value
     */
    static void setLengthTol(double tolerance);

    /**
     * @brief Sets angular tolerance
     * @param tolerance - angular tolerance value
     */
    static void setAngularTol(double tolerance);

    /**
     * @brief Sets zero tolerance
     * @param tolerance - zero tolerance value
     */
    static void setZeroTol(double tolerance);
};

} //namespace sgl

#endif //_GTOLERANCE_H_
