#include <iostream>
#include <string>

#include <graph_lib/undirected_graph.hpp>

#include <graph_lib/directed_graph.hpp>
int main(int argc, char const *argv[])
{
  // graph_lib::Graph<int> graph1;
  // graph1.addVertex(1);
  // graph1.addVertex(2);

  // graph_lib::Graph<int> graph2;
  // graph2.addVertex(3);
  // graph2.addVertex(4);

  // graph_lib::Graph<std::string> graph4;
  // graph4.addVertex("Hello");
  // graph4.addVertex("world");

  // auto a = "Hello" * "world";
  // auto b = graph_lib::Vertex<std::string>("Hello") * graph_lib::Vertex<std::string>("world");

  // graph_lib::Graph<graph_lib::Graph<int>> graph3;
  // graph3.addVertex(graph1);
  // graph3.addVertex(graph2);

  // std::cout << "Graph 1: [ ";
  // for (const auto& vertex : graph1)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  // std::cout << "Graph 2: [ ";
  // for (const auto& vertex : graph2)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  // std::cout << "Graph 3: [ ";
  // for (auto vertex : graph3)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  // std::cout << "Graph 4: [ ";
  // for (const auto& vertex : graph4)
  // {
  //   std::cout << vertex << " ";
  // }
  // std::cout << "]" << std::endl;

  graph_lib::UndirectedGraph<int> graph5;
  graph5.addVertex(1);
  graph5.addVertex(2);
  graph5.addEdge(1, 2);

  std::cout << "Graph 5: [ ";
  for (const auto& vertex : graph5)
  {
    std::cout << vertex << " ";
  }
  std::cout << "]" << std::endl;

  graph_lib::DirectedGraph<int> graph6;
  graph6.addVertex(1);
  graph6.addVertex(2);
  graph6.addEdge(1, 2);

  std::cout << "Graph 6: [ ";
  for (const auto& vertex : graph6)
  {
    std::cout << vertex << " ";
  }
  std::cout << "]" << std::endl;

  return 0;
}
