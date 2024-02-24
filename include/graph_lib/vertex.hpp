#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include <graph_lib/concepts.hpp>


namespace graph_lib
{
// Forward Declarations
template <typename T> requires Graphable<T>
struct Vertex;

template <typename T>
struct VertexHash;


template <typename T> requires Graphable<T>
struct Edge
{
  Edge(std::shared_ptr<const Vertex<T>> v): vertex(v), weight(0) {}
  Edge(std::shared_ptr<const Vertex<T>> v, float w): vertex(v), weight(w) {}

  const std::shared_ptr<const Vertex<T>> vertex;
  const float weight;

  // Relational and comparison operators
  inline bool operator==(const Edge<T>& rhs)                      const { return *vertex == *rhs.vertex; }
  inline bool operator==(const T& rhs)                            const { return *vertex == rhs; }
  inline friend bool operator==(const T& lhs, const Edge<T>& rhs)       { return lhs == *rhs.vertex; }
};

template <typename T>
struct EdgeHash
{
  size_t operator()(const graph_lib::Edge<T> &x) const
  {
    return VertexHash<T>()(*x.vertex);
  }
};


template <typename T> requires Graphable<T>
struct Vertex
{
  //! \brief Construct a graph vertex with the specified value.
  //! \param [in] value The value to store in the vertex.
  Vertex(const T& value):
    id_(getCount()), data(new T(value))
  {}

  //! \brief Copy constructor
  //! \param [in] vertex The vertex from which to construct the copy.
  Vertex(const Vertex<T>& vertex):
    id_(vertex.id_), data(new T(*vertex.data))
  {}

  size_t getID() { return id_; }

  //! \brief The value stored in the vertex.
  std::unique_ptr<T> data;

  //! \brief The adjacent vertices in the graph.
  std::unordered_set<Edge<T>, EdgeHash<T>> adj;

  // Relational and comparison operators
  inline bool operator==(const Vertex<T>& rhs)                      const { return *data == *rhs.data; }
  inline bool operator==(const T& rhs)                              const { return *data == rhs; }
  inline friend bool operator==(const T& lhs, const Vertex<T>& rhs)       { return lhs == *rhs.data; }

  // Stream insertion operator
  inline friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) { os << "[id: " << vertex.id_ << " data: " << *vertex.data << "]"; return os;}

private:
  //! \brief The value stored in the vertex.
  size_t id_;

  static unsigned int getCount()
  {
    static size_t count = 0;
    return count++;
  }
};

template <typename T>
struct VertexHash
{
  size_t operator()(const graph_lib::Vertex<T> &x) const
  {
    return std::hash<T>()(*x.data);
  }
};

} // namespace graph_lib