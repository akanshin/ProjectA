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

TEST(GMatrix4DTest, test_constructor)
{
    GMatrix4D e;
    for (std::size_t rowIdx = 0; rowIdx < 4; ++rowIdx)
    {
        for (std::size_t colIdx = 0; colIdx < 4; ++colIdx)
        {
            ASSERT_NEAR(e(rowIdx, colIdx), ((rowIdx == colIdx) ? 1.0 : 0.0), GTolerance::zeroTol());
        }
    }
}

TEST(GMatrix4DTest, test_constructorInitializerList)
{
    GMatrix4D m({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 });
    double r = 1.0;
    for (std::size_t rowIdx = 0; rowIdx < 4; ++rowIdx)
    {
        for (std::size_t colIdx = 0; colIdx < 4; ++colIdx)
        {
            ASSERT_NEAR(m(rowIdx, colIdx), r, GTolerance::zeroTol());
            r += 1.0;
        }
    }
}

TEST(GMatrix4DTest, test_constructorWCS)
{
    GPoint3D origin{ 2.0, 2.0, 2.0 };
    GVector3D axisX{ 0.0, 1.0, 0.0 };
    GVector3D axisY{ 0.0, 0.0, 1.0 };
    GVector3D axisZ{ -1.0, 0.0, 0.0 };

    GMatrix4D m{origin, axisX, axisY, axisZ};

    ASSERT_NEAR(m(0, 0), axisX[0], GTolerance::zeroTol());
    ASSERT_NEAR(m(1, 0), axisX[1], GTolerance::zeroTol());
    ASSERT_NEAR(m(2, 0), axisX[2], GTolerance::zeroTol());
    ASSERT_NEAR(m(3, 0), 0.0, GTolerance::zeroTol());
    ASSERT_NEAR(m(0, 1), axisY[0], GTolerance::zeroTol());
    ASSERT_NEAR(m(1, 1), axisY[1], GTolerance::zeroTol());
    ASSERT_NEAR(m(2, 1), axisY[2], GTolerance::zeroTol());
    ASSERT_NEAR(m(3, 1), 0.0, GTolerance::zeroTol());
    ASSERT_NEAR(m(0, 2), axisZ[0], GTolerance::zeroTol());
    ASSERT_NEAR(m(1, 2), axisZ[1], GTolerance::zeroTol());
    ASSERT_NEAR(m(2, 2), axisZ[2], GTolerance::zeroTol());
    ASSERT_NEAR(m(3, 2), 0.0, GTolerance::zeroTol());
    ASSERT_NEAR(m(0, 3), origin[0], GTolerance::zeroTol());
    ASSERT_NEAR(m(1, 3), origin[1], GTolerance::zeroTol());
    ASSERT_NEAR(m(2, 3), origin[2], GTolerance::zeroTol());
    ASSERT_NEAR(m(3, 3), 1.0, GTolerance::zeroTol());
}
