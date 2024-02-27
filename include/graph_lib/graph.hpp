#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_set>

#include <graph_lib/iterators.hpp>
#include <graph_lib/vertex.hpp>


namespace graph_lib
{
template <typename T> requires Graphable<T>
class Graph
{
public:
  using VertexPtr = std::shared_ptr<Vertex<T>>;
  using VertexSet = std::unordered_set<VertexPtr, VertexPtrHash<T>, VertexPtrCompare<T>>;

public:
  GraphIterator<T> begin() { return GraphIterator<T>(new BasicGraphIterator(*this)); }
  GraphIterator<T> end() { return GraphIterator<T>(new BasicGraphIterator(*this, this->vertices_.size())); }

  virtual GraphIterator<T> dfs_begin() { throw std::exception(); };
  virtual GraphIterator<T> dfs_end() { throw std::exception(); };

  // virtual GraphIterator<T> bfs_begin() { throw std::exception(); };
  // virtual GraphIterator<T> bfs_end() { throw std::exception(); };

  //! \brief Get the number of vertices in the graph.
  //!
  //! \return size_t The number of vertices in the graph.
  size_t getSize() const { return vertices_.size(); } 

  //! \brief Add a vertex to the graph.
  //!
  //! \param [in] value The value to store in the new vertex.
  //! \return true If the vertex is successfully added.
  //! \return false If the vertex is not successfully added.
  std::optional<unsigned int> addVertex(const T& value) noexcept
  {
    // If the vertex already exists, return false
    if (vertices_.contains(value)) { return {}; }

    // Add the vertex to the graph
    auto [vertex, success] = vertices_.emplace(new Vertex<T>(value));
    if (!success) { return {}; }
    return (**vertex).getID();
  }

  //! \brief Get a const reference to the vertex with the specified value.
  //!
  //! \param [in] value The value stored in the vertex to return.
  //! \exception GraphException Thrown when the requested vertex is not found in the graph.
  //! \return std::optional<const Vertex<T>> An optional of the vertex that contains the value specified.
  std::optional<VertexPtr> getVertex(const size_t& id) const noexcept
  {
    for (auto v : vertices_) { if ((*v).getID() == id) { return v; } }
    return {};
  }

  //! \brief Whether or not the graph is cyclic.
  //! \return true If the graph is cyclic.
  //! \return false If the graph is not cyclic.
  bool isCyclic()
  {
    return true;
  }

protected:
  Graph() = default;

  //! \brief The set of vertices in the graph.
  VertexSet vertices_;

  friend struct GraphIteratorBase<T>;
};

template <typename T> requires Graphable<T>
class UnweightedGraph : public Graph<T>
{
public:
  virtual bool addEdge(const size_t& origin_id, const size_t& dest_id) noexcept = 0;
};

template <typename T> requires Graphable<T>
class WeightedGraph : public Graph<T>
{
public:
  virtual bool addEdge(const size_t& origin_id, const size_t& dest_id, float weight) noexcept = 0;
};

} // namespace graph_lib