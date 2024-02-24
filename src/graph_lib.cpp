#include <iostream>
#include <string>

// #include <graph_lib/iterators.hpp>
#include <graph_lib/directed_graph.hpp>
#include <graph_lib/undirected_graph.hpp>
#include <graph_lib/vertex.hpp>

template <typename T>
void printGraph(graph_lib::Graph<T> graph, unsigned int idx)
{
  std::cout << "Graph " << idx << ": [" << std::endl;

  for (auto vertex : graph)
    std::cout << '\t' << *vertex << std::endl;

  std::cout << "]" << std::endl;
}

template <typename T>
void printVerifyIndex(graph_lib::Graph<T> graph, std::optional<unsigned int> idx)
{
//  ===========
  (idx)
    ? (graph.getVertex(*idx))
      ? std::cout << "We got the vertex!: " << *graph.getVertex(*idx) << std::endl
      : std::cout << "Couldn't get the vertex at index " << *idx << std::endl
    : std::cout << "Add vertex must have failed?" << std::endl;
//  ===========
//  if (idx)
//    if (auto vertex = graph.getVertex(*idx); vertex)
//      std::cout << "We got the vertex!: " << *vertex << std::endl;
//    else
//      std::cout << "Couldn't get the vertex at index " << *idx << std::endl;
//  else
//    std::cout << "Add vertex must have failed?" << std::endl;
//  ===========
//  if (idx.has_value())
//  {
//    auto vertex = graph.getVertex(*idx);
//    if (vertex.has_value())
//    {
//      std::cout << "We got the vertex!: " << **vertex << std::endl;
//    }
//    else
//    {
//      std::cout << "Couldn't get the vertex at index " << *idx << std::endl;
//    }
//  }
//  else
//  {
//    std::cout << "Add vertex must have failed?" << std::endl;
//  }
}

int main(int argc, char const *argv[])
{
  // graph_lib::Vertex<int> v0{5};
  // graph_lib::Vertex<int> v1{6};
  // graph_lib::Vertex<int> v2{7};
  // graph_lib::Vertex<int> v3{8};
  // graph_lib::Vertex<int> v4{9};

  // v0.adj.emplace(std::make_shared<graph_lib::Vertex<int>>(v1), 0);
  // v0.adj.emplace(std::make_shared<graph_lib::Vertex<int>>(v3), 0);
  // v1.adj.emplace(std::make_shared<graph_lib::Vertex<int>>(v2), 0);
  // v3.adj.emplace(std::make_shared<graph_lib::Vertex<int>>(v2), 0);
  // v3.adj.emplace(std::make_shared<graph_lib::Vertex<int>>(v4), 0);

  // v0.adj.emplace(v1, 0);
  // v0.adj.emplace(v3, 0);
  // v1.adj.emplace(v2, 0);
  // v3.adj.emplace(v2, 0);
  // v3.adj.emplace(v4, 0);

  // std::cout << v0 << std::endl;
  // std::cout << v1 << std::endl;
  // std::cout << v2 << std::endl;
  // std::cout << v3 << std::endl;
  // std::cout << v4 << std::endl;

  graph_lib::UnweightedDirectedGraph<int> graph1;
  auto idx1 = graph1.addVertex(0);
  graph1.addVertex(1);
  graph1.addVertex(2);
  graph1.addVertex(3);
  graph1.addVertex(4);
  graph1.addEdge(0, 1);
  graph1.addEdge(0, 3);
  graph1.addEdge(1, 2);
  graph1.addEdge(3, 2);
  graph1.addEdge(3, 4);

  printGraph<int>(graph1, 1);

  graph_lib::WeightedDirectedGraph<int> graph2;
  auto idx2 = graph2.addVertex(0);
  graph2.addVertex(1);
  graph2.addVertex(2);
  graph2.addVertex(3);
  graph2.addVertex(4);
  graph2.addEdge(0, 1, 0.1);
  graph2.addEdge(0, 3, 0.2);
  graph2.addEdge(1, 2, 0.4);
  graph2.addEdge(3, 2, 0.5);
  graph2.addEdge(3, 4, 0.6);

  printGraph<int>(graph2, 2);

  printVerifyIndex(graph1, idx1);
  printVerifyIndex(graph1, idx2);
  printVerifyIndex(graph2, idx1);
  printVerifyIndex(graph2, idx2);

  graph_lib::UnweightedUndirectedGraph<int> graph3;
  graph3.addVertex(0);
  graph3.addVertex(1);
  graph3.addVertex(2);
  graph3.addVertex(3);
  graph3.addVertex(4);
  graph3.addEdge(0, 1);
  graph3.addEdge(0, 3);
  graph3.addEdge(1, 2);
  graph3.addEdge(3, 2);
  graph3.addEdge(3, 4);

  printGraph<int>(graph3, 3);

  graph_lib::WeightedUndirectedGraph<int> graph4;
  graph4.addVertex(0);
  graph4.addVertex(1);
  graph4.addVertex(2);
  graph4.addVertex(3);
  graph4.addVertex(4);
  graph4.addEdge(0, 1, 0.1);
  graph4.addEdge(0, 3, 0.2);
  graph4.addEdge(1, 2, 0.4);
  graph4.addEdge(3, 2, 0.5);
  graph4.addEdge(3, 4, 0.6);

  printGraph<int>(graph4, 4);

  return 0;
}
