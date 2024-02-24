#include <algorithm>
#include <optional>

#include <gtest/gtest.h>
#include <graph_lib/directed_graph.hpp>
#include <graph_lib/undirected_graph.hpp>
#include <graph_lib/vertex.hpp>

class GraphTestBasic : public testing::Test
{
public:
  graph_lib::UnweightedDirectedGraph<int>   unweighted_directed_graph;
  graph_lib::WeightedDirectedGraph<int>     weighted_directed_graph;
  graph_lib::UnweightedUndirectedGraph<int> unweighted_undirected_graph;
  graph_lib::WeightedUndirectedGraph<int>   weighted_undirected_graph;
};

class GraphTestWithVertices : public testing::Test
{
public:
  graph_lib::UnweightedDirectedGraph<int>   unweighted_directed_graph;
  graph_lib::WeightedDirectedGraph<int>     weighted_directed_graph;
  graph_lib::UnweightedUndirectedGraph<int> unweighted_undirected_graph;
  graph_lib::WeightedUndirectedGraph<int>   weighted_undirected_graph;

  std::optional<unsigned int> vertex_10;
  std::optional<unsigned int> vertex_11;
  std::optional<unsigned int> vertex_20;
  std::optional<unsigned int> vertex_21;
  std::optional<unsigned int> vertex_30;
  std::optional<unsigned int> vertex_31;
  std::optional<unsigned int> vertex_40;
  std::optional<unsigned int> vertex_41;

  void SetUp()
  {
    vertex_10 = unweighted_directed_graph.addVertex(0);
    vertex_11 = unweighted_directed_graph.addVertex(1);

    vertex_20 = weighted_directed_graph.addVertex(0);
    vertex_21 = weighted_directed_graph.addVertex(1);

    vertex_30 = unweighted_undirected_graph.addVertex(0);
    vertex_31 = unweighted_undirected_graph.addVertex(1);

    vertex_40 = weighted_undirected_graph.addVertex(0);
    vertex_41 = weighted_undirected_graph.addVertex(1);
  }
};

class UnweightedDirectedGraphTestBasic : public testing::Test
{
public:
  graph_lib::UnweightedDirectedGraph<int> graph;

  void SetUp()
  {
    auto id0 = graph.addVertex(0);
    auto id1 = graph.addVertex(1);
    auto id2 = graph.addVertex(2);
    auto id3 = graph.addVertex(3);
    auto id4 = graph.addVertex(4);

    graph.addEdge(*id0, *id1);
    graph.addEdge(*id0, *id3);
    graph.addEdge(*id1, *id2);
    graph.addEdge(*id3, *id2);
    graph.addEdge(*id3, *id4);
  }
};

class WeightedDirectedGraphTestBasic : public testing::Test
{
public:
  graph_lib::WeightedDirectedGraph<int> graph;

  void SetUp()
  {
    auto id0 = graph.addVertex(0);
    auto id1 = graph.addVertex(1);
    auto id2 = graph.addVertex(2);
    auto id3 = graph.addVertex(3);
    auto id4 = graph.addVertex(4);

    graph.addEdge(*id0, *id1, 0.1);
    graph.addEdge(*id0, *id3, 0.2);
    graph.addEdge(*id1, *id2, 0.4);
    graph.addEdge(*id3, *id2, 0.5);
    graph.addEdge(*id3, *id4, 0.6);
  }
};

class UnweightedUndirectedGraphTestBasic : public testing::Test
{
public:
  graph_lib::UnweightedUndirectedGraph<int> graph;

  void SetUp()
  {
    auto id0 = graph.addVertex(0);
    auto id1 = graph.addVertex(1);
    auto id2 = graph.addVertex(2);
    auto id3 = graph.addVertex(3);
    auto id4 = graph.addVertex(4);

    graph.addEdge(*id0, *id1);
    graph.addEdge(*id0, *id3);
    graph.addEdge(*id1, *id2);
    graph.addEdge(*id3, *id2);
    graph.addEdge(*id3, *id4);
  }
};

class WeightedUndirectedGraphTestBasic : public testing::Test
{
public:
  graph_lib::WeightedUndirectedGraph<int> graph;

  void SetUp()
  {
    auto id0 = graph.addVertex(0);
    auto id1 = graph.addVertex(1);
    auto id2 = graph.addVertex(2);
    auto id3 = graph.addVertex(3);
    auto id4 = graph.addVertex(4);

    graph.addEdge(*id0, *id1, 0.1);
    graph.addEdge(*id0, *id3, 0.2);
    graph.addEdge(*id1, *id2, 0.4);
    graph.addEdge(*id3, *id2, 0.5);
    graph.addEdge(*id3, *id4, 0.6);
  }
};

TEST_F(GraphTestBasic, TestAddVertex)
{
  std::optional<unsigned int> vertex_1 = unweighted_directed_graph.addVertex(4);
  std::optional<unsigned int> vertex_2 = weighted_directed_graph.addVertex(4);
  std::optional<unsigned int> vertex_3 = unweighted_undirected_graph.addVertex(4);
  std::optional<unsigned int> vertex_4 = weighted_undirected_graph.addVertex(4);

  // Vertex ID is static and increments after every vertex creation
  EXPECT_EQ(vertex_1, std::optional<unsigned int>(0));
  EXPECT_EQ(vertex_2, std::optional<unsigned int>(1));
  EXPECT_EQ(vertex_3, std::optional<unsigned int>(2));
  EXPECT_EQ(vertex_4, std::optional<unsigned int>(3));
}

TEST_F(GraphTestBasic, TestAddVertexTwice)
{
  std::optional<unsigned int> vertex_10 = unweighted_directed_graph.addVertex(8);
  std::optional<unsigned int> vertex_11 = unweighted_directed_graph.addVertex(8);

  std::optional<unsigned int> vertex_20 = weighted_directed_graph.addVertex(8);
  std::optional<unsigned int> vertex_21 = weighted_directed_graph.addVertex(8);

  std::optional<unsigned int> vertex_30 = unweighted_undirected_graph.addVertex(8);
  std::optional<unsigned int> vertex_31 = unweighted_undirected_graph.addVertex(8);

  std::optional<unsigned int> vertex_40 = weighted_undirected_graph.addVertex(8);
  std::optional<unsigned int> vertex_41 = weighted_undirected_graph.addVertex(8);

  // Vertex ID is static and increments after every vertex creation
  EXPECT_EQ(vertex_10, std::optional<unsigned int>(4));
  EXPECT_EQ(vertex_11, std::optional<unsigned int>());
  
  EXPECT_EQ(vertex_20, std::optional<unsigned int>(5));
  EXPECT_EQ(vertex_21, std::optional<unsigned int>());
  
  EXPECT_EQ(vertex_30, std::optional<unsigned int>(6));
  EXPECT_EQ(vertex_31, std::optional<unsigned int>());
  
  EXPECT_EQ(vertex_40, std::optional<unsigned int>(7));
  EXPECT_EQ(vertex_41, std::optional<unsigned int>());
}

TEST_F(GraphTestBasic, TestGetVertex)
{
  std::optional<unsigned int> vertex_1 = unweighted_directed_graph.addVertex(12);
  std::optional<unsigned int> vertex_2 = weighted_directed_graph.addVertex(12);
  std::optional<unsigned int> vertex_3 = unweighted_undirected_graph.addVertex(12);
  std::optional<unsigned int> vertex_4 = weighted_undirected_graph.addVertex(12);

  EXPECT_EQ(**unweighted_directed_graph.getVertex(*vertex_1), 12);
  EXPECT_EQ(**weighted_directed_graph.getVertex(*vertex_2), 12);
  EXPECT_EQ(**unweighted_undirected_graph.getVertex(*vertex_3), 12);
  EXPECT_EQ(**weighted_undirected_graph.getVertex(*vertex_4), 12);
}

TEST_F(GraphTestWithVertices, TestAddEdge1)
{
  EXPECT_TRUE(unweighted_directed_graph.addEdge(*vertex_10, *vertex_11));
  EXPECT_TRUE(weighted_directed_graph.addEdge(*vertex_20, *vertex_21, 0.1f));
  EXPECT_TRUE(unweighted_undirected_graph.addEdge(*vertex_30, *vertex_31));
  EXPECT_TRUE(weighted_undirected_graph.addEdge(*vertex_40, *vertex_41, 0.1f));
}

TEST_F(GraphTestWithVertices, TestAddEdge2)
{
  // IDs will never be negative, vertex guaranteed not to exist
  EXPECT_FALSE(unweighted_directed_graph.addEdge(*vertex_10, -1));
  EXPECT_FALSE(weighted_directed_graph.addEdge(*vertex_20, -1, 0.1f));
  EXPECT_FALSE(unweighted_undirected_graph.addEdge(*vertex_30, -1));
  EXPECT_FALSE(weighted_undirected_graph.addEdge(*vertex_40, -1, 0.1f));
}

TEST_F(GraphTestWithVertices, TestGraphSize)
{
  // IDs will never be negative, vertex guaranteed not to exist
  EXPECT_EQ(unweighted_directed_graph.getSize(), 2);
  EXPECT_EQ(weighted_directed_graph.getSize(), 2);
  EXPECT_EQ(unweighted_undirected_graph.getSize(), 2);
  EXPECT_EQ(weighted_undirected_graph.getSize(), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}