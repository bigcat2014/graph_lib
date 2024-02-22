#include <gtest/gtest.h>
#include <graph_lib/graph/vertex.hpp>

namespace wfc = graph_lib;

class VertexTestBasic : public testing::Test
{
public:
    wfc::Vertex<int> v1{1};
    wfc::Vertex<int> v2{2};
};

TEST(VertexTest, OperatorIsEqual)
{
    wfc::Vertex<int> v1{1};
    wfc::Vertex<int> v2{1};
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 == 1);
    EXPECT_TRUE(1 == v1);
}

TEST_F(VertexTestBasic, OperatorNotIsEqual)
{
    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v1 == 2);
    EXPECT_FALSE(1 == v2);
}

TEST_F(VertexTestBasic, OperatorIsNotEqual)
{
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v1 != 2);
    EXPECT_TRUE(2 != v1);
}

TEST(VertexTest, OperatorNotIsNotEqual)
{
    wfc::Vertex<int> v1{1};
    wfc::Vertex<int> v2{1};
    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v1 != 1);
    EXPECT_FALSE(1 != v2);
}

TEST_F(VertexTestBasic, OperatorGT)
{
    EXPECT_FALSE(v1 > v1);
    EXPECT_FALSE(v1 > 1);
    EXPECT_FALSE(1 > v1);

    EXPECT_FALSE(v2 > v2);
    EXPECT_FALSE(v2 > 2);
    EXPECT_FALSE(2 > v2);

    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 > 2);
    EXPECT_FALSE(1 > v2);

    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v2 > 1);
    EXPECT_TRUE(2 > v1);
}

TEST_F(VertexTestBasic, OperatorGTE)
{
    EXPECT_TRUE(v1 >= v1);
    EXPECT_TRUE(v1 >= 1);
    EXPECT_TRUE(1 >= v1);

    EXPECT_TRUE(v2 >= v2);
    EXPECT_TRUE(v2 >= 2);
    EXPECT_TRUE(2 >= v2);

    EXPECT_FALSE(v1 >= v2);
    EXPECT_FALSE(v1 >= 2);
    EXPECT_FALSE(1 >= v2);

    EXPECT_TRUE(v2 >= v1);
    EXPECT_TRUE(v2 >= 1);
    EXPECT_TRUE(2 >= v1);
}

TEST_F(VertexTestBasic, OperatorLT)
{
    EXPECT_FALSE(v1 < v1);
    EXPECT_FALSE(v1 < 1);
    EXPECT_FALSE(1 < v1);

    EXPECT_FALSE(v2 < v2);
    EXPECT_FALSE(v2 < 2);
    EXPECT_FALSE(2 < v2);

    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 < 2);
    EXPECT_TRUE(1 < v2);

    EXPECT_FALSE(v2 < v1);
    EXPECT_FALSE(v2 < 1);
    EXPECT_FALSE(2 < v1);
}

TEST_F(VertexTestBasic, OperatorLTE)
{
    EXPECT_TRUE(v1 <= v1);
    EXPECT_TRUE(v1 <= 1);
    EXPECT_TRUE(1 <= v1);

    EXPECT_TRUE(v2 <= v2);
    EXPECT_TRUE(v2 <= 2);
    EXPECT_TRUE(2 <= v2);

    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= 2);
    EXPECT_TRUE(1 <= v2);

    EXPECT_FALSE(v2 <= v1);
    EXPECT_FALSE(v2 <= 1);
    EXPECT_FALSE(2 <= v1);
}

TEST_F(VertexTestBasic, ArithmeticOperators)
{
    EXPECT_EQ(v1 + v2, 3);
    EXPECT_EQ(v1 + 2, 3);
    EXPECT_EQ(1 + v2, 3);

    EXPECT_EQ(v1 - v2, -1);
    EXPECT_EQ(v1 - 2, -1);
    EXPECT_EQ(1 - v2, -1);

    EXPECT_EQ(v1 * v2, 2);
    EXPECT_EQ(v1 * 2, 2);
    EXPECT_EQ(1 * v2, 2);

    EXPECT_EQ(v1 / v2, 0);
    EXPECT_EQ(v1 / 2, 0);
    EXPECT_EQ(1 / v2, 0);

    EXPECT_EQ(v1 % v2, 1);
    EXPECT_EQ(v1 % 2, 1);
    EXPECT_EQ(1 % v2, 1);
}

TEST_F(VertexTestBasic, BitwiseOperators)
{
    EXPECT_EQ(v1 ^ v2, 3);
    EXPECT_EQ(v1 ^ 2, 3);
    EXPECT_EQ(1 ^ v2, 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}