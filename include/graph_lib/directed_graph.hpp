#pragma once

#include <optional>

#include <graph_lib/concepts.hpp>
#include <graph_lib/graph.hpp>
// #include <graph_lib/iterators.hpp>


namespace graph_lib
{
template <typename T> requires Graphable<T>
class UnweightedDirectedGraph: public UnweightedGraph<T>
{
// public:
//   using DFSIterator = GraphDFSIterator<UnweightedDirectedGraph<T>, T>;
//   using BFSIterator = GraphBFSIterator<UnweightedDirectedGraph<T>, T>;

public:
  // DFSIterator dfs_begin() { return DFSIterator(this->vertices_.begin()); }
  // DFSIterator dfs_end() { return DFSIterator(this->vertices_.end()); }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] origin_id The ID of the origin vertex.
  //! \param [in] dest_id The ID of the destination vertex.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  bool addEdge(const size_t& origin_id, const size_t& dest_id) noexcept override
  {
    // Get references to the specified vertices
    auto origin_vertex = UnweightedGraph<T>::getVertex(origin_id);
    auto dest_vertex = UnweightedGraph<T>::getVertex(dest_id);

    // If either of the vertices don't exist, return false
    if (!origin_vertex.has_value() || !dest_vertex.has_value()) { return false; }

    // If the edge already exists return false
    if ((**origin_vertex).adj.contains(Edge<T>(*dest_vertex))) { return false; }

    // Add dest to the adjacency list of origin
    auto [_, success] = (**origin_vertex).adj.insert(Edge<T>(*dest_vertex));
    return success;
  }
};

template <typename T> requires Graphable<T>
class WeightedDirectedGraph: public WeightedGraph<T>
{
// public:
//   using DFSIterator = GraphDFSIterator<WeightedDirectedGraph<T>, T>;
//   using BFSIterator = GraphBFSIterator<WeightedDirectedGraph<T>, T>;

public:
  // DFSIterator dfs_begin() { return DFSIterator(this->vertices_.begin()); }
  // DFSIterator dfs_end() { return DFSIterator(this->vertices_.end()); }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] origin_id The ID of the origin vertex.
  //! \param [in] dest_id The ID of the destination vertex.
  //! \param [in] weight The weight of the edge between the vertices.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  bool addEdge(const size_t& origin_id, const size_t& dest_id, float weight) noexcept override
  {
    // Get references to the specified vertices
    auto origin_vertex = WeightedGraph<T>::getVertex(origin_id);
    auto dest_vertex = WeightedGraph<T>::getVertex(dest_id);

    // If either of the vertices don't exist, return false
    if (!origin_vertex.has_value() || !dest_vertex.has_value()) { return false; }

    // If the edge already exists return false
    if ((**origin_vertex).adj.contains(Edge<T>(*dest_vertex, weight))) { return false; }

    // Add dest to the adjacency list of origin
    auto [_, success] = (**origin_vertex).adj.insert(Edge<T>(*dest_vertex, weight));
    return success;
  }
};

} // namespace graph_lib