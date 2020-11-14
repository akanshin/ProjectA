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

#include "gtest/gtest.h"
#include "GMatrix4D.h"
#include "GVector3D.h"
#include "GPoint3D.h"
#include "GUtils.h"

using namespace sgl;

TEST(GMatrix4DTest, test_identity)
{
    const auto & e = GMatrix4D::identity();
    for (std::size_t rowIdx = 0; rowIdx < 4; ++rowIdx)
    {
        for (std::size_t colIdx = 0; colIdx < 4; ++colIdx)
        {
            ASSERT_NEAR(e(rowIdx, colIdx), ((rowIdx == colIdx) ? 1.0 : 0.0), GTolerance::zeroTol());
        }
    }
}
