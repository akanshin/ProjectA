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

#include "GPoint3D.h"
#include "GUtils.h"

#include "gtest/gtest.h"

using namespace sgl;

TEST(GPoint3DTest, test_constructor)
{
    GPoint3D p;
    ASSERT(equal(p[0], 1.0, GTolerance::zeroTol()));
    ASSERT(equal(p[1], 0.0, GTolerance::zeroTol()));
    ASSERT(equal(p[2], 0.0, GTolerance::zeroTol()));
}
