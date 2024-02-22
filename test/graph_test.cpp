#include <algorithm>
#include <gtest/gtest.h>
#include <graph_lib/graph/graph.hpp>

namespace wfc = graph_lib;

class GraphTestBasic : public testing::Test
{
public:
    wfc::Graph<int> graph;

    void SetUp()
    {
        graph.addVertex(1);
        graph.addVertex(2);
    }
};

TEST(GraphTest, AddVertex)
{
    wfc::Graph<int> graph;
    EXPECT_TRUE(graph.addVertex(1));
    EXPECT_FALSE(graph.addVertex(1));
}

TEST_F(GraphTestBasic, GetVertex)
{
    EXPECT_EQ(graph.getVertex(1), 1);
    EXPECT_EQ(graph.getVertex(2), 2);
    EXPECT_THROW(graph.getVertex(3), wfc::GraphException);
}

TEST_F(GraphTestBasic, AddEdge1)
{
    EXPECT_TRUE(graph.addEdge(1, 1));
    EXPECT_FALSE(graph.addEdge(1, 1));
    EXPECT_TRUE(graph.addEdge(1, 2));
    EXPECT_FALSE(graph.addEdge(1, 3));
    EXPECT_FALSE(graph.addEdge(3, 1));

    wfc::Vertex<int> vertex = graph.getVertex(1);
    EXPECT_EQ(std::count(vertex.adj.begin(), vertex.adj.end(), 1), 1);
    EXPECT_EQ(std::count(vertex.adj.begin(), vertex.adj.end(), 2), 1);
    EXPECT_EQ(std::count(vertex.adj.begin(), vertex.adj.end(), 3), 0);

    vertex = graph.getVertex(2);
    EXPECT_EQ(std::count(vertex.adj.begin(), vertex.adj.end(), 1), 1);
}

TEST(GraphTest, AddEdge2)
{
    wfc::Graph<int> graph;
    graph.addVertex(1);
    ASSERT_TRUE(graph.addEdge(1, 1));
    wfc::Vertex<int> vertex = graph.getVertex(1);
    EXPECT_EQ(std::count(vertex.adj.begin(), vertex.adj.end(), 1), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}