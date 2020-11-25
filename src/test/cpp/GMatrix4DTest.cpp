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

TEST(GMatrix4DTest, test_setIdentity)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    m.setIdentity();
    for (std::size_t rowIdx = 0; rowIdx < 4; ++rowIdx)
    {
        for (std::size_t colIdx = 0; colIdx < 4; ++colIdx)
        {
            ASSERT_NEAR(m(rowIdx, colIdx), ((rowIdx == colIdx) ? 1.0 : 0.0), GTolerance::zeroTol());
        }
    }
}

TEST(GMatrix4DTest, test_origin)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GPoint3D origin = m.origin();
    ASSERT_NEAR(origin.x(), 4.0, GTolerance::zeroTol());
    ASSERT_NEAR(origin.y(), 8.0, GTolerance::zeroTol());
    ASSERT_NEAR(origin.z(), 12.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_x)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GVector3D x = m.x();
    ASSERT_NEAR(x.x(), 1.0, GTolerance::zeroTol());
    ASSERT_NEAR(x.y(), 5.0, GTolerance::zeroTol());
    ASSERT_NEAR(x.z(), 9.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_y)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GVector3D y = m.y();
    ASSERT_NEAR(y.x(), 2.0, GTolerance::zeroTol());
    ASSERT_NEAR(y.y(), 6.0, GTolerance::zeroTol());
    ASSERT_NEAR(y.z(), 10.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_z)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GVector3D z = m.z();
    ASSERT_NEAR(z.x(), 3.0, GTolerance::zeroTol());
    ASSERT_NEAR(z.y(), 7.0, GTolerance::zeroTol());
    ASSERT_NEAR(z.z(), 11.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_operatorSquareBrackets)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    ASSERT_NEAR(m[2][1], 10.0, GTolerance::zeroTol());
    m[2][1] = -10;
    ASSERT_NEAR(m[2][1], -10.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_operatorRoundBrackets)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    ASSERT_NEAR(m(2, 1), 10.0, GTolerance::zeroTol());
    m(2, 1) = -10;
    ASSERT_NEAR(m(2, 1), -10.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_postMultiplyBy)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GMatrix4D mult{ 16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    m.postMultiplyBy(mult);
    ASSERT_NEAR(m[0][0], 80.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 70.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 60.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], 50.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 240.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 214.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], 188.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 162.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 400.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], 358.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 316.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 274.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], 560.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 502.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 444.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 386.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_preMultiplyBy)
{
    GMatrix4D m{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GMatrix4D mult{ 16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    m.preMultiplyBy(mult);
    ASSERT_NEAR(m[0][0], 386.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 444.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 502.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], 560.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 274.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 316.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], 358.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 400.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 162.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], 188.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 214.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 240.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], 50.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 60.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 70.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 80.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_product)
{
    GMatrix4D m1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GMatrix4D m2{ 16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
    GMatrix4D m{};
    m.product(m1, m2);
    ASSERT_NEAR(m[0][0], 80.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 70.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 60.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], 50.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 240.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 214.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], 188.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 162.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 400.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], 358.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 316.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 274.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], 560.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 502.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 444.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 386.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_transpose)
{
    GMatrix4D m1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    GMatrix4D m{ std::move(m1.transpose()) };
    ASSERT_NEAR(m[0][0], 1.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 5.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 9.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], 13.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 2.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 6.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], 10.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 14.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 3.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], 7.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 11.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 15.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], 4.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 8.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 12.0, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 16.0, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_invert)
{
    GMatrix4D det0{ 0, 1, 1, 1,
                    1, 1, 1, 1,
                    0, 1, 1, 1,
                    0, 0, 0, 1 };
    ASSERT_THROW(det0.invert(), std::logic_error);

    GMatrix4D m{ 1, 1, 1, -1,
                 1, 1, -1, 1,
                 1, -1, 1, 1,
                 -1, 1, 1, 1 };
    ASSERT_NEAR(m.determinant(), -16.0, GTolerance::zeroTol());

    m.invert();
    ASSERT_NEAR(m[0][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 0.25, GTolerance::zeroTol());
}

TEST(GMatrix4DTest, test_inverse)
{
    GMatrix4D det0{ 0, 1, 1, 1,
                    1, 1, 1, 1,
                    0, 1, 1, 1,
                    0, 0, 0, 1 };
    ASSERT_THROW(det0.invert(), std::logic_error);

    GMatrix4D m1{ 1, 1, 1, -1,
                 1, 1, -1, 1,
                 1, -1, 1, 1,
                 -1, 1, 1, 1 };
    ASSERT_NEAR(m1.determinant(), -16.0, GTolerance::zeroTol());

    auto m = std::move(m1.inverse());
    ASSERT_NEAR(m[0][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[0][3], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][2], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[1][3], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][0], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][1], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[2][3], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][0], -0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][1], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][2], 0.25, GTolerance::zeroTol());
    ASSERT_NEAR(m[3][3], 0.25, GTolerance::zeroTol());
}
