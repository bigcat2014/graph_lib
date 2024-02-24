#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <unordered_set>

#include <graph_lib/vertex.hpp>


namespace graph_lib
{

template <typename T> requires Hashable<T>
struct VertexPtrHash {
  using is_transparent = void;

  std::size_t operator() (const std::shared_ptr<Vertex<T>>& p) const {
    return VertexHash<T>()(*p);
  }

  std::size_t operator() (const Vertex<T>& p) const {
    return VertexHash<T>()(p);
  }

  std::size_t operator() (const T& p) const {
    return std::hash<T>()(p);
  }
};

template <typename T> requires Graphable<T>
struct VertexPtrCompare {
  using is_transparent = void;

  bool operator() (const std::shared_ptr<Vertex<T>>& a, const std::shared_ptr<Vertex<T>>& b) const {
    return (*a) == (*b);
  }

  bool operator() (const Vertex<T>& a, const std::shared_ptr<Vertex<T>>& b) const {
    return a == (*b);
  }

  bool operator() (const std::shared_ptr<Vertex<T>>& a, const Vertex<T>& b) const {
    return (*a) == b;
  }

  bool operator() (const T& a, const std::shared_ptr<Vertex<T>>& b) const {
    return a == (*b);
  }

  bool operator() (const std::shared_ptr<Vertex<T>>& a, const T& b) const {
    return (*a) == b;
  }
};

template <typename T> requires Graphable<T>
class Graph
{
public:
  using VertexPtr = std::shared_ptr<Vertex<T>>;
  using VertexSet = std::unordered_set<VertexPtr, VertexPtrHash<T>, VertexPtrCompare<T>>;

public:
  VertexSet::const_iterator begin() { return this->vertices_.begin(); }
  VertexSet::const_iterator end() { return this->vertices_.end(); }

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
  // TODO: Convert this to take in vertex id instead of value
  std::optional<VertexPtr> getVertex(const T& value) const noexcept
  {
    // Find the vertex
    // TODO: Is there a way around needing to create this shared pointer here?
    VertexPtr v = std::make_shared<Vertex<T>>(value);
    auto vertex_itr = vertices_.find(v);

    // Return empty optional if vertex is not found
    if (vertex_itr == vertices_.end()) { return {}; }

    // Test that friend class works
    // std::cout << "------------- GetVertex -------------" << std::endl;
    // std::cout << (**vertex_itr).id_ << std::endl;
    // std::cout << "------------- End GetVertex -------------" << std::endl;

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
  Graph() = default;

  //! \brief The set of vertices in the graph.
  VertexSet vertices_;
};

template <typename T> requires Graphable<T>
class UnweightedGraph : public Graph<T>
{
public:
  virtual bool addEdge(const T& origin, const T& dest) noexcept = 0;
};

template <typename T> requires Graphable<T>
class WeightedGraph : public Graph<T>
{
public:
  virtual bool addEdge(const T& origin, const T& dest, float weight) noexcept = 0;
};

} // namespace graph_lib