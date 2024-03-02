#pragma once

#include <optional>

#include <graph_lib/concepts.hpp>
#include <graph_lib/graph.hpp>
#include <graph_lib/iterators.hpp>


namespace graph_lib
{
template <typename T> requires Graphable<T>
class UnweightedDirectedGraph: public UnweightedGraph<T>
{
private:
  using DFSIter = DFSIterator<UnweightedDirectedGraph, T>;
  using BFSIter = BFSIterator<UnweightedDirectedGraph, T>;

public:
  GraphIterator<T> dfs_begin() { return GraphIterator<T>(new DFSIter(*this)); }
  GraphIterator<T> dfs_end() { return GraphIterator<T>(new DFSIter(*this, this->vertices_.size())); }

  GraphIterator<T> bfs_begin() { return GraphIterator<T>(new BFSIter(*this)); }
  GraphIterator<T> bfs_end() { return GraphIterator<T>(new BFSIter(*this, this->vertices_.size())); }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] origin_id The ID of the origin vertex.
  //! \param [in] dest_id The ID of the destination vertex.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  bool addEdge(const unsigned int& origin_id, const unsigned int& dest_id) noexcept override
  {
    // Get references to the specified vertices
    auto origin_vertex = UnweightedGraph<T>::getVertex(origin_id);
    auto dest_vertex = UnweightedGraph<T>::getVertex(dest_id);

    // If either of the vertices don't exist, return false
    if (!origin_vertex.has_value() || !dest_vertex.has_value()) { return false; }

    // If the edge already exists return false
    if ((**origin_vertex).adj.contains(*dest_vertex)) { return false; }

    // Add dest to the adjacency list of origin
    auto [_, success] = (**origin_vertex).adj.emplace(new Edge<T>(*dest_vertex));
    return success;
  }
};

template <typename T> requires Graphable<T>
class WeightedDirectedGraph: public WeightedGraph<T>
{
private:
  using DFSIter = DFSIterator<WeightedDirectedGraph, T>;
  using BFSIter = BFSIterator<WeightedDirectedGraph, T>;

public:
  GraphIterator<T> dfs_begin() { return GraphIterator<T>(new DFSIter(*this)); }
  GraphIterator<T> dfs_end() { return GraphIterator<T>(new DFSIter(*this, this->vertices_.size())); }

  GraphIterator<T> bfs_begin() { return GraphIterator<T>(new BFSIter(*this)); }
  GraphIterator<T> bfs_end() { return GraphIterator<T>(new BFSIter(*this, this->vertices_.size())); }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] origin_id The ID of the origin vertex.
  //! \param [in] dest_id The ID of the destination vertex.
  //! \param [in] weight The weight of the edge between the vertices.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  bool addEdge(const unsigned int& origin_id, const unsigned int& dest_id, float weight) noexcept override
  {
    // Get references to the specified vertices
    auto origin_vertex = WeightedGraph<T>::getVertex(origin_id);
    auto dest_vertex = WeightedGraph<T>::getVertex(dest_id);

    // If either of the vertices don't exist, return false
    if (!origin_vertex.has_value() || !dest_vertex.has_value()) { return false; }

    // If the edge already exists return false
    if ((**origin_vertex).adj.contains(*dest_vertex)) { return false; }

    // Add dest to the adjacency list of origin
    auto [_, success] = (**origin_vertex).adj.emplace(new Edge<T>(*dest_vertex, weight));
    return success;
  }
};

} // namespace graph_lib