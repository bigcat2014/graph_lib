#pragma once

#include <optional>
#include <unordered_set>

#include <graph_lib/graph.hpp>
#include <graph_lib/vertex.hpp>


namespace graph_lib
{

template <typename T> requires Graphable<T>
class DirectedGraph: public Graph<T>
{
public:
  DirectedGraph(): Graph<T>() {};

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] value_1 The value of the origin vertex.
  //! \param [in] value_2 The value of the destination vertex.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  bool addEdge(const T& value_1, const T& value_2) noexcept override
  {
    // Get references to the specified vertices
    auto value_1_vertex = Graph<T>::getVertex(value_1);
    auto value_2_vertex = Graph<T>::getVertex(value_2);

    // If either of the vertices don't exist, return false
    if (!value_1_vertex.has_value() || !value_2_vertex.has_value()) { return false; }

    // If the edge already exists return false
    if ((*value_1_vertex).adj.contains(value_2)) { return false; }

    // Add value_2 to the adjacency list of value_1
    auto [_, success_1] = (*value_1_vertex).adj.insert((*value_2_vertex));
    return success_1;
  }
};

} // namespace graph_lib