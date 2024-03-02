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

template <typename T> requires Hashable<T>
struct VertexHash;

template <typename T> requires Graphable<T>
struct VertexPtrHash;


template <typename T> requires Graphable<T>
struct Edge
{
  Edge(std::shared_ptr<Vertex<T>> v): vertex(v), weight(0) {}
  Edge(std::shared_ptr<Vertex<T>> v, float w): vertex(v), weight(w) {}

  const std::shared_ptr<Vertex<T>> vertex;
  const float weight;

  // Relational and comparison operators
  inline        bool operator==(const Edge<T>& rhs)                       const { return *vertex == *rhs.vertex; }
  inline        bool operator==(const Vertex<T>& rhs)                     const { return *vertex == rhs; }
  inline        bool operator==(const T& rhs)                             const { return *vertex == rhs; }
  inline friend bool operator==(const Vertex<T>& lhs, const Edge<T>& rhs)       { return lhs == *rhs.vertex; }
  inline friend bool operator==(const T& lhs, const Edge<T>& rhs)               { return lhs == *rhs.vertex; }
};

template <typename T> requires Hashable<T>
struct EdgeHash
{
  size_t operator()(const graph_lib::Edge<T> &x) const
  {
    return VertexHash<T>()(*x.vertex);
  }
};

template <typename T> requires Graphable<T>
struct EdgePtrHash {
  using is_transparent = void;

  std::size_t operator() (const std::unique_ptr<Edge<T>>& p)   const { return EdgeHash<T>()(*p); }
  std::size_t operator() (const Edge<T>& p)                    const { return EdgeHash<T>()(p); }
  std::size_t operator() (const std::shared_ptr<Vertex<T>>& p) const { return VertexPtrHash<T>()(p); }
  std::size_t operator() (const Vertex<T>& p)                  const { return VertexHash<T>()(p); }
};

template <typename T> requires Graphable<T>
struct EdgePtrCompare {
  using is_transparent = void;

  bool operator() (const std::unique_ptr<Edge<T>>& a, const std::unique_ptr<Edge<T>>& b)   const { return (*a) == (*b); }

  bool operator() (const Edge<T>& a, const std::unique_ptr<Edge<T>>& b)                    const { return a == (*b); }
  bool operator() (const std::unique_ptr<Edge<T>>& a, const Edge<T>& b)                    const { return (*a) == b; }
  
  bool operator() (const std::shared_ptr<Vertex<T>>& a, const std::unique_ptr<Edge<T>>& b) const { return (*a) == (*b); }
  bool operator() (const std::unique_ptr<Edge<T>>& a, const std::shared_ptr<Vertex<T>>& b) const { return (*a) == (*b); }

  bool operator() (const Vertex<T>& a, const std::unique_ptr<Edge<T>>& b)                  const { return a == (*b); }
  bool operator() (const std::unique_ptr<Edge<T>>& a, const Vertex<T>& b)                  const { return (*a) == b; }

  bool operator() (const T& a, const std::unique_ptr<Edge<T>>& b)                          const { return a == (*b); }
  bool operator() (const std::unique_ptr<Edge<T>>& a, const T& b)                          const { return (*a) == b; }
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

  unsigned int getID() { return id_; }

  //! \brief The value stored in the vertex.
  std::unique_ptr<T> data;

  //! \brief The adjacent vertices in the graph.
  std::unordered_set<std::unique_ptr<Edge<T>>, EdgePtrHash<T>, EdgePtrCompare<T>> adj;

  // EQ operator
  inline        bool operator==(const Vertex<T>& rhs)               const { return *data == *rhs.data; }
  inline        bool operator==(const T& rhs)                       const { return *data == rhs; }
  inline friend bool operator==(const T& lhs, const Vertex<T>& rhs)       { return lhs == *rhs.data; }

  // Stream insertion operator
  // TODO: Remove this after testing
  inline friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) { os << "[id: " << vertex.id_ << " data: " << *vertex.data << "]"; return os;}

private:
  //! \brief The value stored in the vertex.
  unsigned int id_;

  static unsigned int getCount()
  {
    static unsigned int count = 0;
    return count++;
  }
};

template <typename T> requires Hashable<T>
struct VertexHash
{
  size_t operator()(const graph_lib::Vertex<T> &x) const
  {
    return std::hash<T>()(*x.data);
  }
};

template <typename T> requires Graphable<T>
struct VertexPtrHash {
  using is_transparent = void;

  std::size_t operator() (const std::shared_ptr<Vertex<T>>& p) const { return VertexHash<T>()(*p); }
  std::size_t operator() (const Vertex<T>& p)                  const { return VertexHash<T>()(p); }
  std::size_t operator() (const T& p)                          const { return std::hash<T>()(p); }
};

template <typename T> requires Graphable<T>
struct VertexPtrCompare {
  using is_transparent = void;

  bool operator() (const std::shared_ptr<Vertex<T>>& a, const std::shared_ptr<Vertex<T>>& b) const { return (*a) == (*b); }

  bool operator() (const Vertex<T>& a, const std::shared_ptr<Vertex<T>>& b)                  const { return a == (*b); }
  bool operator() (const std::shared_ptr<Vertex<T>>& a, const Vertex<T>& b)                  const { return (*a) == b; }

  bool operator() (const T& a, const std::shared_ptr<Vertex<T>>& b)                          const { return a == (*b); }
  bool operator() (const std::shared_ptr<Vertex<T>>& a, const T& b)                          const { return (*a) == b; }
};

} // namespace graph_lib