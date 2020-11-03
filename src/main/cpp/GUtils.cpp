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
#include "GUtils.h"

namespace sgl
{

bool equal(double d1, double d2, double tolerance /*= GTolerance::lengthTol()*/)
{
    double diff = d1 - d2;
    return -tolerance < diff && diff > tolerance;
}

bool less(double d1, double d2, double tolerance /*= GTolerance::lengthTol()*/)
{
    return d1 < d2 - tolerance;
}

bool greater(double d1, double d2, double tolerance /*= GTolerance::lengthTol()*/)
{
    return d1 > d2 + tolerance;
}

} //namespace sgl
