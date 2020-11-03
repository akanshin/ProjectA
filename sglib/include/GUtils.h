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

#ifndef _GUTILS_H_
#define _GUTILS_H_

#include "GExports.h"
#include "GTolerance.h"

namespace sgl
{

/**
 * @brief Returns true if input numbers are equal within tolerance
 * @param d1 - first number
 * @param d2 - second number
 * @param tolerance - tolerance
 * @return true if input numbers are equal within tolerance, otherwise false
 */
SGL_API bool equal(double d1, double d2, double tolerance = GTolerance::zeroTol());

/**
 * @brief Returns true if the first number is less than the second within tolerance
 * @param d1 - first number
 * @param d2 - second number
 * @param tolerance - tolerance
 * @return true if the first number is less than the second within tolerance, otherwise false
 */
SGL_API bool less(double d1, double d2, double tolerance = GTolerance::zeroTol());

/**
 * @brief Returns true if the first number is greater than the second within tolerance
 * @param d1 - first number
 * @param d2 - second number
 * @param tolerance - tolerance
 * @return true if the first number is greater than the second within tolerance, otherwise false
 */
SGL_API bool greater(double d1, double d2, double tolerance = GTolerance::zeroTol());

} //namespace sgl

#endif //_GUTILS_H_
