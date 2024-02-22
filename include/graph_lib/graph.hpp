#pragma once

#include <algorithm>
#include <optional>
#include <unordered_set>

#include <graph_lib/vertex.hpp>


namespace graph_lib
{

template <typename T> requires Graphable<T>
class Graph
{
public:
  using ValueType = T;

public:
  Graph() = default;

  std::unordered_set<Vertex<T>>::const_iterator begin() const { return cbegin(); }
  std::unordered_set<Vertex<T>>::const_iterator end() const { return cend(); }
  std::unordered_set<Vertex<T>>::const_iterator cbegin() const { return vertices_.cbegin(); }
  std::unordered_set<Vertex<T>>::const_iterator cend() const { return vertices_.cend(); }

  //! \brief Get the number of vertices in the graph.
  //!
  //! \return unsigned int The number of vertices in the graph.
  unsigned int getSize() const { return vertices_.size(); }

  //! \brief Add a vertex to the graph.
  //!
  //! \param [in] value The value to store in the new vertex.
  //! \return true If the vertex is successfully added.
  //! \return false If the vertex is not successfully added.
  virtual bool addVertex(const T& value) noexcept { return addVertex(Vertex<T>(value)); }

  //! \brief Add an edge to the graph.
  //! Add an undirected edge between two vertices of the graph.
  //!
  //! \param [in] value_1 The value of the first of two vertices to create the edge between.
  //! \param [in] value_2 The value of the second of two vertices to create the edge between.
  //! \return true If the edge is successfully added.
  //! \return false If the edge is not successfully added.
  virtual bool addEdge(const T& value_1, const T& value_2) noexcept = 0;

  //! \brief Get a const reference to the vertex with the specified value.
  //!
  //! \param [in] value The value stored in the vertex to return.
  //! \exception GraphException Thrown when the requested vertex is not found in the graph.
  //! \return std::optional<const Vertex<T>> An optional of the vertex that contains the value specified.
  std::optional<const Vertex<T>> getVertex(const T& value) const noexcept
  {
    // Find the vertex
    auto vertex_itr = std::find(vertices_.begin(), vertices_.end(), value);

    // Return empty optional if vertex is not found
    if (vertex_itr == vertices_.end()) { return {}; }
    return *vertex_itr;
  }

  //! \brief Whether or not the graph is cyclic.
  //! \return true If the graph is cyclic.
  //! \return false If the graph is not cyclic.
  bool isCyclic()
  {
    return true;
  }

protected:
  //! \brief The set of vertices in the graph.
  std::unordered_set<Vertex<T>> vertices_;

  //! \brief Add a vertex to the graph.
  //!
  //! \param [in] vertex The vertex to add to the graph.
  //! \return true If the vertex is successfully added.
  //! \return false If the vertex is not successfully added.
  bool addVertex(const Vertex<T>& vertex) noexcept
  {
    // If the vertex already exists, return false
    if (vertices_.contains(vertex)) { return false; }

    // Add the vertex to the graph
    auto [_, success] = vertices_.insert(vertex);
    return success;
  }

  //! \brief Get a reference to the vertex with the specified value.
  //!
  //! \param [in] value The value stored in the vertex to return.
  //! \return std::optional<const Vertex<T>> An optional of the vertex that contains the value specified.
  std::optional<Vertex<T>> getVertex(const T& value) noexcept
  {
    // Find the vertex
    auto vertex_itr = std::find(vertices_.begin(), vertices_.end(), value);

    // Return empty optional if vertex is not found
    if (vertex_itr == vertices_.end()) { return {}; }
    return *vertex_itr;
  }
};

} // namespace graph_lib