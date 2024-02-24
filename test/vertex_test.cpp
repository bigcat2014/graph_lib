#include <functional>
#include <gtest/gtest.h>
#include <graph_lib/vertex.hpp>


class VertexTestCustomClass : public testing::Test
{
public:
  struct MyTestStruct
  {
    unsigned int x;

    MyTestStruct(int val): x(val) {}

    // Custom data type must implement operator==
    inline bool        operator==(const MyTestStruct& rhs)                          const { return x == rhs.x; }
    inline bool        operator==(const unsigned int& rhs)                          const { return x == rhs; }
    inline friend bool operator==(const unsigned int& lhs, const MyTestStruct& rhs)       { return lhs == rhs.x; }

    // TODO: Remove this after testing
    inline friend std::ostream& operator<<(std::ostream& os, const MyTestStruct& test) { os << test.x; return os;}
  };
};

// Custom data type must be hashable
template <>
struct std::hash<VertexTestCustomClass::MyTestStruct>
{
  size_t operator()(const VertexTestCustomClass::MyTestStruct &val) const
  {
    return std::hash<unsigned int>()(val.x);
  }
};


TEST(VertexTest, TestIDIncrement)
{
  graph_lib::Vertex<int> v1{2};
  EXPECT_EQ(v1.getID(), 0);

  graph_lib::Vertex<int> v2{2};
  EXPECT_EQ(v2.getID(), 1);

  // Ensure v1 id unchanged
  EXPECT_EQ(v1.getID(), 0);
}

TEST(VertexTest, TestData)
{
  graph_lib::Vertex<int> v1{1};
  EXPECT_EQ(*(v1.data), 1);

  graph_lib::Vertex<std::string> v2{"Test"};
  EXPECT_EQ(*(v2.data), "Test");

  graph_lib::Vertex<float> v3{1.2345f};
  EXPECT_FLOAT_EQ(*(v3.data), 1.2345f);

  graph_lib::Vertex<double> v4{6.7890};
  EXPECT_DOUBLE_EQ(*(v4.data), 6.7890);
}

TEST_F(VertexTestCustomClass, TestCustomData)
{
  graph_lib::Vertex<MyTestStruct> v1{MyTestStruct(1)};
  EXPECT_EQ(v1, MyTestStruct(1));
  EXPECT_EQ(v1, 1);
}

TEST(VertexTest, TestOperatorIsEqual)
{
  graph_lib::Vertex<int> v1{1};
  graph_lib::Vertex<int> v2{1};

  EXPECT_TRUE(v1 == v2);
  EXPECT_TRUE(v1 == 1);
  EXPECT_TRUE(1 == v1);
}

TEST(VertexTest, TestOperatorNotIsEqual)
{
  graph_lib::Vertex<int> v1{1};
  graph_lib::Vertex<int> v2{2};

  EXPECT_FALSE(v1 == v2);
  EXPECT_FALSE(v1 == 2);
  EXPECT_FALSE(1 == v2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}