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

#include "GVector3D.h"
#include "GPoint3D.h"
#include "GUtils.h"

#include <cmath>
#include <utility>

#include "gtest/gtest.h"

using namespace sgl;

TEST(GVector3DTest, test_axisX)
{
    const auto & v = GVector3D::axisX();
    ASSERT_TRUE(equal(v[0], 1.0));
    ASSERT_TRUE(equal(v[1], 0.0));
    ASSERT_TRUE(equal(v[2], 0.0));
}

TEST(GVector3DTest, test_axisY)
{
    const auto & v = GVector3D::axisY();
    ASSERT_TRUE(equal(v[0], 0.0));
    ASSERT_TRUE(equal(v[1], 1.0));
    ASSERT_TRUE(equal(v[2], 0.0));
}

TEST(GVector3DTest, test_axisZ)
{
    const auto & v = GVector3D::axisZ();
    ASSERT_TRUE(equal(v[0], 0.0));
    ASSERT_TRUE(equal(v[1], 0.0));
    ASSERT_TRUE(equal(v[2], 1.0));
}

TEST(GVector3DTest, test_constructor)
{
    GVector3D v;
    ASSERT_TRUE(equal(v[0], 0.0));
    ASSERT_TRUE(equal(v[1], 0.0));
    ASSERT_TRUE(equal(v[2], 0.0));
}

TEST(GVector3DTest, test_copyConstructor)
{
    GVector3D v{ 5.0, 4.0, 3.0 };
    GVector3D copy{ v };
    ASSERT_TRUE(equal(copy[0], v[0]));
    ASSERT_TRUE(equal(copy[1], v[1]));
    ASSERT_TRUE(equal(copy[2], v[2]));
}

TEST(GVector3DTest, test_moveConstructor)
{
    GVector3D v{ 5.0, 4.0, 3.0 };
    GVector3D move{ std::move(v) };
    ASSERT_TRUE(equal(move[0], v[0]));
    ASSERT_TRUE(equal(move[1], v[1]));
    ASSERT_TRUE(equal(move[2], v[2]));
}

TEST(GVector3DTest, test_constructorXYZ)
{
    GVector3D v(5.0, 4.0, 3.0);
    ASSERT_TRUE(equal(v[0], 5.0));
    ASSERT_TRUE(equal(v[1], 4.0));
    ASSERT_TRUE(equal(v[2], 3.0));
}

TEST(GVector3DTest, test_constructorPointer)
{
    double * pCoords = new double[3] { 4.0, 6.0, 2.0 };
    GVector3D v(pCoords);
    delete[] pCoords;
    ASSERT_TRUE(equal(v[0], 4.0));
    ASSERT_TRUE(equal(v[1], 6.0));
    ASSERT_TRUE(equal(v[2], 2.0));
}

TEST(GVector3DTest, test_constructorInitializerList)
{
    GVector3D v({ 4.0, 6.0, 2.0 });
    ASSERT_TRUE(equal(v[0], 4.0));
    ASSERT_TRUE(equal(v[1], 6.0));
    ASSERT_TRUE(equal(v[2], 2.0));
}

TEST(GVector3DTest, test_getSetX)
{
    GVector3D v;
    ASSERT_TRUE(equal(v.x(), 0.0));
    v.setX(4.0);
    ASSERT_TRUE(equal(v.x(), 4.0));
}

TEST(GVector3DTest, test_getSetY)
{
    GVector3D v;
    ASSERT_TRUE(equal(v.y(), 0.0));
    v.setY(10.0);
    ASSERT_TRUE(equal(v.y(), 10.0));
}

TEST(GVector3DTest, test_getSetZ)
{
    GVector3D v;
    ASSERT_TRUE(equal(v.z(), 0.0));
    v.setZ(3.0);
    ASSERT_TRUE(equal(v.z(), 3.0));
}

TEST(GVector3DTest, test_set)
{
    GVector3D v;
    ASSERT_TRUE(equal(v[0], 0.0));
    ASSERT_TRUE(equal(v[1], 0.0));
    ASSERT_TRUE(equal(v[2], 0.0));
    v.set(4.0, 6.0, 2.0);
    ASSERT_TRUE(equal(v[0], 4.0));
    ASSERT_TRUE(equal(v[1], 6.0));
    ASSERT_TRUE(equal(v[2], 2.0));
}

TEST(GVector3DTest, test_operatorSquareBrackets)
{
    GVector3D v { 4.0, 6.0, 2.0 };
    ASSERT_TRUE(equal(v[0], 4.0));
    ASSERT_TRUE(equal(v[1], 6.0));
    ASSERT_TRUE(equal(v[2], 2.0));
    ASSERT_THROW(equal(v[3], 10), std::invalid_argument);
}

TEST(GVector3DTest, test_length)
{
    GVector3D v { 4.0, 6.0, 2.0 };
    ASSERT_TRUE(equal(v.length(), 7.483314774));
}

TEST(GVector3DTest, test_isZero)
{
    GVector3D v;
    ASSERT_TRUE(v.isZero());
}

TEST(GVector3DTest, test_isUnit)
{
    GVector3D v{ std::sin(0.4), std::cos(0.4), 0.0 };
    ASSERT_TRUE(v.isUnit());

    v = { 2.0, 2.0, 2.0 };
    ASSERT_FALSE(v.isUnit());
}

TEST(GVector3DTest, test_normalize)
{
    GVector3D v{ 2.0, 2.0, 2.0 };
    ASSERT_FALSE(v.isUnit());
    auto & v2 = v.normalize();
    ASSERT_EQ(&v, &v2);
    ASSERT_TRUE(v.isUnit());
}

TEST(GVector3DTest, test_normalizeConst)
{
    GVector3D v{ 2.0, 2.0, 2.0 };
    ASSERT_FALSE(v.isUnit());
    GVector3D v2 = v.normalize();
    ASSERT_FALSE(v.isUnit());
    ASSERT_NE(&v, &v2);
    ASSERT_TRUE(v2.isUnit());
}

TEST(GVector3DTest, test_equals)
{
    GVector3D v1{ 2.0, 2.0, 2.0 };
    GVector3D v2{ 2.0, 2.0, 2.0 };
    GVector3D v3{ 2.1, 2.0, 2.0 };
    ASSERT_TRUE(v1.equals(v2));
    ASSERT_TRUE(v2.equals(v1));
    ASSERT_FALSE(v1.equals(v3));
    ASSERT_FALSE(v3.equals(v2));
}

TEST(GVector3DTest, test_parallel)
{
    GVector3D v1{ 2.0, 2.0, 2.0 };
    GVector3D v2{ 4.0, 4.0, 4.0 };
    GVector3D v3{ 2.1, 2.0, 2.0 };
    ASSERT_TRUE(v1.parallel(v2));
    ASSERT_TRUE(v2.parallel(v1));
    ASSERT_FALSE(v1.parallel(v3));
    ASSERT_FALSE(v3.parallel(v2));
}

TEST(GVector3DTest, test_antiparallel)
{
    GVector3D v1{ 2.0, 2.0, 2.0 };
    GVector3D v2{ 4.0, 4.0, 4.0 };
    GVector3D v3{ 2.1, 2.0, 2.0 };
    GVector3D v4{ -2.1, -2.0, -2.0 };
    ASSERT_FALSE(v1.antiparallel(v2));
    ASSERT_FALSE(v2.antiparallel(v1));
    ASSERT_FALSE(v1.antiparallel(v3));
    ASSERT_FALSE(v3.antiparallel(v2));
    ASSERT_TRUE(v3.antiparallel(v4));
}

TEST(GVector3DTest, test_biparallel)
{
    GVector3D v1{ 2.0, 2.0, 2.0 };
    GVector3D v2{ 4.0, 4.0, 4.0 };
    GVector3D v3{ 2.1, 2.0, 2.0 };
    GVector3D v4{ -2.1, -2.0, -2.0 };
    ASSERT_TRUE(v1.biparallel(v2));
    ASSERT_TRUE(v2.biparallel(v1));
    ASSERT_FALSE(v1.biparallel(v3));
    ASSERT_FALSE(v3.biparallel(v2));
    ASSERT_TRUE(v3.biparallel(v4));
    ASSERT_TRUE(v4.biparallel(v3));
}

TEST(GVector3DTest, test_perpendicular)
{
    GVector3D v1{ 2.0, 2.0, 2.0 };
    GVector3D v2{ 4.0, 4.0, 4.0 };
    GVector3D v3{ 2.1, 2.0, 2.0 };
    GVector3D v4{ 0.5, -1.0, 0.5 };
    ASSERT_FALSE(v1.perpendicular(v2));
    ASSERT_FALSE(v2.perpendicular(v3));
    ASSERT_FALSE(v3.perpendicular(v4));
    ASSERT_TRUE(v4.perpendicular(v1));
    ASSERT_TRUE(v4.perpendicular(v2));
    ASSERT_FALSE(v4.perpendicular(v3));
}
