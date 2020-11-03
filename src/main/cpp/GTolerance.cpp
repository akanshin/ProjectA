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
#include "GTolerance.h"

namespace sgl
{

static double s_lengthTolerance = 1.0e-6;
static double s_angularTolerance = 1.0e-10;
static double s_zeroTolerance = 1.0e-30;

double GTolerance::lengthTol()
{
    return s_lengthTolerance;
}

double GTolerance::angularTol()
{
    return s_angularTolerance;
}

double GTolerance::zeroTol()
{
    return s_zeroTolerance;
}

void GTolerance::setLengthTol(double tolerance)
{
    s_lengthTolerance = tolerance;
}

void GTolerance::setAngularTol(double tolerance)
{
    s_angularTolerance = tolerance;
}

void GTolerance::setZeroTol(double tolerance)
{
    s_zeroTolerance = tolerance;
}


} //namespace sgl
