#include <iostream>
#include <memory>
#include <string>

// #include <graph_lib/iterators.hpp>
#include <graph_lib/directed_graph.hpp>
#include <graph_lib/undirected_graph.hpp>
#include <graph_lib/vertex.hpp>

template <typename T>
void printGraphDFS(graph_lib::Graph<T>* graph, unsigned int idx)
{
  std::cout << "Graph " << idx << ": [" << std::endl;
  for (auto itr = graph->dfs_begin(); itr != graph->dfs_end(); itr++)
  {
    std::cout << '\t' << **itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

template <typename T>
void printGraphBFS(graph_lib::Graph<T>* graph, unsigned int idx)
{
  std::cout << "Graph " << idx << ": [" << std::endl;
  for (auto itr = graph->bfs_begin(); itr != graph->bfs_end(); itr++)
  {
    std::cout << '\t' << **itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

template <typename T>
void printGraph(graph_lib::Graph<T>* graph, unsigned int idx)
{
  std::cout << "Graph " << idx << ": [" << std::endl;
  for (auto itr = graph->begin(); itr != graph->end(); itr++)
  {
    std::cout << '\t' << **itr << std::endl;
  }
  std::cout << "]" << std::endl;
  std::cout << std::endl;
}

template <typename T>
void printVerifyIndex(graph_lib::Graph<T> graph, std::optional<unsigned int> id, unsigned int idx)
{
  if (id.has_value())
  {
    auto vertex = graph.getVertex(*id);
    if (vertex.has_value())
    {
      std::cout << "Found vertex " << **vertex << " in graph " << idx << std::endl;
    }
    else
    {
      std::cout << "Couldn't get the vertex at index " << *id << " in graph " << idx << std::endl;
    }
  }
  else
  {
    std::cout << "Add vertex must have failed?" << std::endl;
  }
}

int main(int argc, char const *argv[])
{
  std::vector<graph_lib::Graph<int> *> graphs;
  std::vector<graph_lib::Graph<std::string> *> graphs2;

  graph_lib::UnweightedDirectedGraph<int> graph1;
  graphs.push_back(&graph1);
  auto id10 = graph1.addVertex(0);
  auto id11 = graph1.addVertex(1);
  auto id12 = graph1.addVertex(2);
  auto id13 = graph1.addVertex(3);
  auto id14 = graph1.addVertex(4);

  bool success_1 = true;
  success_1 &= graph1.addEdge(*id10, *id11);
  success_1 &= graph1.addEdge(*id10, *id13);
  success_1 &= graph1.addEdge(*id11, *id12);
  success_1 &= graph1.addEdge(*id13, *id12);
  success_1 &= graph1.addEdge(*id13, *id14);
  std::cout << "Graph 1 successfully created: " << (success_1 ? "true" : "false") << std::endl;
  printGraph<int>(graphs[0], 1);
  printGraphDFS<int>(graphs[0], 1);
  printGraphBFS<int>(graphs[0], 1);

  graph_lib::WeightedDirectedGraph<int> graph2;
  graphs.push_back(&graph2);
  auto id20 = graph2.addVertex(0);
  auto id21 = graph2.addVertex(1);
  auto id22 = graph2.addVertex(2);
  auto id23 = graph2.addVertex(3);
  auto id24 = graph2.addVertex(4);

  bool success_2 = true;
  success_2 &= graph2.addEdge(*id20, *id21, 0.1);
  success_2 &= graph2.addEdge(*id20, *id23, 0.2);
  success_2 &= graph2.addEdge(*id21, *id22, 0.4);
  success_2 &= graph2.addEdge(*id23, *id22, 0.5);
  success_2 &= graph2.addEdge(*id23, *id24, 0.6);
  std::cout << "Graph 2 successfully created: " << (success_2 ? "true" : "false") << std::endl;
  printGraph<int>(graphs[1], 2);
  printGraphDFS<int>(graphs[1], 2);
  printGraphBFS<int>(graphs[1], 2);

  graph_lib::UnweightedUndirectedGraph<int> graph3;
  graphs.push_back(&graph3);
  auto id30 = graph3.addVertex(0);
  auto id31 = graph3.addVertex(1);
  auto id32 = graph3.addVertex(2);
  auto id33 = graph3.addVertex(3);
  auto id34 = graph3.addVertex(4);

  bool success_3 = true;
  success_3 &= graph3.addEdge(*id30, *id31);
  success_3 &= graph3.addEdge(*id30, *id33);
  success_3 &= graph3.addEdge(*id31, *id32);
  success_3 &= graph3.addEdge(*id33, *id32);
  success_3 &= graph3.addEdge(*id33, *id34);
  std::cout << "Graph 3 successfully created: " << (success_3 ? "true" : "false") << std::endl;
  printGraph<int>(graphs[2], 3);
  printGraphDFS<int>(graphs[2], 3);
  printGraphBFS<int>(graphs[2], 3);

  graph_lib::WeightedUndirectedGraph<int> graph4;
  graphs.push_back(&graph4);
  auto id40 = graph4.addVertex(0);
  auto id41 = graph4.addVertex(1);
  auto id42 = graph4.addVertex(2);
  auto id43 = graph4.addVertex(3);
  auto id44 = graph4.addVertex(4);

  bool success_4 = true;
  success_4 &= graph4.addEdge(*id40, *id41, 0.1);
  success_4 &= graph4.addEdge(*id40, *id43, 0.2);
  success_4 &= graph4.addEdge(*id41, *id42, 0.4);
  success_4 &= graph4.addEdge(*id43, *id42, 0.5);
  success_4 &= graph4.addEdge(*id43, *id44, 0.6);
  std::cout << "Graph 4 successfully created: " << (success_4 ? "true" : "false") << std::endl;
  printGraph<int>(graphs[3], 4);
  printGraphDFS<int>(graphs[3], 4);
  printGraphBFS<int>(graphs[3], 4);

  printVerifyIndex(graph1, id10, 1);
  printVerifyIndex(graph1, id20, 1);
  printVerifyIndex(graph1, id30, 1);
  printVerifyIndex(graph1, id40, 1);
  std::cout << std::endl;

  printVerifyIndex(graph2, id10, 2);
  printVerifyIndex(graph2, id20, 2);
  printVerifyIndex(graph2, id30, 2);
  printVerifyIndex(graph2, id40, 2);
  std::cout << std::endl;

  printVerifyIndex(graph3, id10, 3);
  printVerifyIndex(graph3, id20, 3);
  printVerifyIndex(graph3, id30, 3);
  printVerifyIndex(graph3, id40, 3);
  std::cout << std::endl;

  printVerifyIndex(graph4, id10, 4);
  printVerifyIndex(graph4, id20, 4);
  printVerifyIndex(graph4, id30, 4);
  printVerifyIndex(graph4, id40, 4);

  graph_lib::UnweightedDirectedGraph<std::string> graph5;
  graphs2.push_back(&graph5);
  auto id52 = graph5.addVertex("23");
  auto id51 = graph5.addVertex("9");
  auto id54 = graph5.addVertex("7");
  auto id53 = graph5.addVertex("14");
  auto id50 = graph5.addVertex("6");

  bool success_5 = true;
  success_5 &= graph5.addEdge(*id50, *id51);
  success_5 &= graph5.addEdge(*id50, *id53);
  success_5 &= graph5.addEdge(*id51, *id52);
  success_5 &= graph5.addEdge(*id53, *id52);
  success_5 &= graph5.addEdge(*id53, *id54);
  std::cout << "Graph 5 successfully created: " << (success_5 ? "true" : "false") << std::endl;
  printGraph<std::string>(graphs2[0], 5);
  printGraphDFS<std::string>(graphs2[0], 5);
  printGraphBFS<std::string>(graphs2[0], 5);

  return 0;
}
