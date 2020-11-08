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

#include "GMatrix.h"
#include "GPoint3D.h"
#include "GVector3D.h"
#include "GUtils.h"

#include <utility>

#include "gtest/gtest.h"

using namespace sgl;

TEST(GPoint3DTest, test_origin)
{
    const auto & origin = GPoint3D::origin();
    ASSERT_EQ(equal(origin[0], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(origin[1], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(origin[2], 0.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_constructor)
{
    GPoint3D p;
    ASSERT_EQ(equal(p[0], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 0.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_copyConstructor)
{
    const GPoint3D p1(1.0, 2.0, 3.0);
    GPoint3D p2{ p1 };
    ASSERT_EQ(equal(p2[0], p1[0], GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p2[1], p1[1], GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p2[2], p1[2], GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_moveConstructor)
{
    const GPoint3D p1(1.0, 2.0, 3.0);
    GPoint3D p2{ std::move(p1) };
    ASSERT_EQ(equal(p1[0], 1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[2], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p2[0], 1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p2[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p2[2], 3.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_constructorXYZ)
{
    GPoint3D p(1.0, 2.0, 3.0);
    ASSERT_EQ(equal(p[0], 1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 3.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_constructorPointer)
{
    double * pCoords = new double[3] { 3.0, 2.0, 1.0 };
    GPoint3D p(pCoords);
    delete[] pCoords;
    ASSERT_EQ(equal(p[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_constructorInitializerList)
{
    GPoint3D p({ 3.0, 2.0, 1.0 });
    ASSERT_EQ(equal(p[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_getSetX)
{
    GPoint3D p;
    ASSERT_EQ(equal(p.x(), 0.0, GTolerance::zeroTol()), true);
    p.setX(1.0);
    ASSERT_EQ(equal(p.x(), 1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_getSetY)
{
    GPoint3D p;
    ASSERT_EQ(equal(p.y(), 0.0, GTolerance::zeroTol()), true);
    p.setY(1.0);
    ASSERT_EQ(equal(p.y(), 1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_getSetZ)
{
    GPoint3D p;
    ASSERT_EQ(equal(p.z(), 0.0, GTolerance::zeroTol()), true);
    p.setZ(1.0);
    ASSERT_EQ(equal(p.z(), 1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_set)
{
    GPoint3D p({ 3.0, 2.0, 1.0 });
    ASSERT_EQ(equal(p[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 1.0, GTolerance::zeroTol()), true);
    p.set(6.0, 5.0, 4.0);
    ASSERT_EQ(equal(p[0], 6.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 5.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 4.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_equals)
{
    GPoint3D p1{ 1.0, 2.0, 3.0 };
    GPoint3D p2{ 1.0, 2.0, 3.0 };
    GPoint3D p3{ 3.0, 2.0, 1.0 };
    GPoint3D p4{ 6.0, 2.0, 8.0 };
    ASSERT_EQ(p1.equals(p2), true);
    ASSERT_EQ(p2.equals(p1), true);
    ASSERT_EQ(p1.equals(p3), false);
    ASSERT_EQ(p3.equals(p2), false);
    ASSERT_EQ(p2.equals(p4), false);
    ASSERT_EQ(p4.equals(p4), true);
}

TEST(GPoint3DTest, test_operatorSquareBrackets)
{
    GPoint3D p({ 3.0, 2.0, 1.0 });
    ASSERT_EQ(equal(p[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 1.0, GTolerance::zeroTol()), true);
    p[0] = 10.0;
    p[1] = 11.0;
    p[2] = 12.0;
    ASSERT_EQ(equal(p[0], 10.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 11.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 12.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorPlusAssign)
{
    GPoint3D p1{ 1.0, 2.0, 3.0 };
    GPoint3D p2{ 2.0, 3.0, 4.0 };
    p1 += p2;
    ASSERT_EQ(equal(p1[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[1], 5.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[2], 7.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorMinusAssign)
{
    GPoint3D p1{ 1.0, 2.0, 3.0 };
    GPoint3D p2{ 2.0, 3.0, 4.0 };
    p1 -= p2;
    ASSERT_EQ(equal(p1[0], -1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[1], -1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p1[2], -1.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorPlusAssignVector)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GVector3D v{ 2.0, 3.0, 8.0 };
    p += v;
    ASSERT_EQ(equal(p[0], 3.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 5.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 11.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorMinusAssignVector)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GVector3D v{ 2.0, 3.0, 8.0 };
    p -= v;
    ASSERT_EQ(equal(p[0], -1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], -1.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], -5.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorMultiplyAssignMatrix)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GMatrix m{ 1.0, 2.0, 3.0, 0.0,
               2.0, 1.0, 4.0, 0.0,
               3.0, 4.0, 1.0, 0.0,
               5.0, 5.0, 5.0, 1.0 };
    p *= m;
    ASSERT_EQ(equal(p[0], 19.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[1], 21.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(p[2], 19.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_asVector)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GVector3D v = std::move(p.asVector());
    ASSERT_EQ(equal(v[0], p[0], GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(v[1], p[1], GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(v[2], p[2], GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorPlus)
{
    GPoint3D p1{ 1.0, 2.0, 3.0 };
    GPoint3D p2{ -1.0, -2.0, -3.0 };
    GPoint3D r = p1 + p2;
    ASSERT_EQ(equal(r[0], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[1], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[2], 0.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorMinus)
{
    GPoint3D p1{ 1.0, 2.0, 3.0 };
    GPoint3D p2{ -1.0, -2.0, -3.0 };
    GVector3D r = p1 - p2;
    ASSERT_EQ(equal(r[0], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[1], 4.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[2], 6.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorPlusVector)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GVector3D v{ -1.0, -2.0, -3.0 };
    GPoint3D r1 = p + v;
    ASSERT_EQ(equal(r1[0], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r1[1], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r1[2], 0.0, GTolerance::zeroTol()), true);
    GPoint3D r2 = v + p;
    ASSERT_EQ(equal(r2[0], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r2[1], 0.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r2[2], 0.0, GTolerance::zeroTol()), true);
}

TEST(GPoint3DTest, test_operatorMinusVector)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GVector3D v{ -1.0, -2.0, -3.0 };
    GPoint3D r = p - v;
    ASSERT_EQ(equal(r[0], 2.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[1], 4.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[2], 6.0, GTolerance::zeroTol()), true);
}


TEST(GPoint3DTest, test_operatorMultiplyMatrix)
{
    GPoint3D p{ 1.0, 2.0, 3.0 };
    GMatrix m{ 1.0, 2.0, 3.0, 0.0,
               2.0, 1.0, 4.0, 0.0,
               3.0, 4.0, 1.0, 0.0,
               5.0, 5.0, 5.0, 1.0 };
    GPoint3D r = m * p;
    ASSERT_EQ(equal(r[0], 19.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[1], 21.0, GTolerance::zeroTol()), true);
    ASSERT_EQ(equal(r[2], 19.0, GTolerance::zeroTol()), true);
}
