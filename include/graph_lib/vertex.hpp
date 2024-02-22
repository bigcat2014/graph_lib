#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

namespace graph_lib
{

template<typename T>
concept Hashable = requires(T a) {
  std::hash<T>{}(a);
};

template<typename T>
concept Eqable = requires(T a, T b) {
  { a == b } -> std::convertible_to<bool>;
};

template <typename T>
concept Graphable = Hashable<T> && Eqable<T>;

template <typename T> requires Graphable<T>
struct Vertex
{
  //! \brief Construct a graph vertex with the specified value.
  //! \param [in] value The value to store in the vertex.
  Vertex(const T& value): data(value) {}

  //! \brief The value stored in the vertex.
  T data;

  //! \brief The adjacent vertices in the graph.
  std::unordered_set<Vertex<T>> adj;

  // Arithmetic operators
  inline T operator+(const Vertex<T>& rhs)                      const { return data + rhs.data; }
  inline T operator+(const T& rhs)                              const { return data + rhs; }
  inline friend T operator+(const T& lhs, const Vertex<T>& rhs)       { return lhs + rhs.data; }

  inline T operator-(const Vertex<T>& rhs)                      const { return data - rhs.data; }
  inline T operator-(const T& rhs)                              const { return data - rhs; }
  inline friend T operator-(const T& lhs, const Vertex<T>& rhs)       { return lhs - rhs.data; }

  inline T operator*(const Vertex<T>& rhs)                      const { return data * rhs.data; }
  inline T operator*(const T& rhs)                              const { return data * rhs; }
  inline friend T operator*(const T& lhs, const Vertex<T>& rhs)       { return lhs * rhs.data; }

  inline T operator/(const Vertex<T>& rhs)                      const { return data / rhs.data; }
  inline T operator/(const T& rhs)                              const { return data / rhs; }
  inline friend T operator/(const T& lhs, const Vertex<T>& rhs)       { return lhs / rhs.data; }

  inline T operator%(const Vertex<T>& rhs)                      const { return data % rhs.data; }
  inline T operator%(const T& rhs)                              const { return data % rhs; }
  inline friend T operator%(const T& lhs, const Vertex<T>& rhs)       { return lhs % rhs.data; }

  // Compound assignment operators
  inline Vertex<T>& operator+=(const Vertex<T>& rhs)                      const { data = rhs.data; return *this; }
  inline Vertex<T>& operator+=(const T& rhs)                              const { data = rhs; return *this; }
  inline friend Vertex<T>& operator+=(const T& lhs, const Vertex<T>& rhs)       { lhs += rhs.data; return lhs; }

  // Increment and decrement

  // Relational and comparison operators
  inline bool operator==(const Vertex<T>& rhs)                      const { return data == rhs.data; }
  inline bool operator==(const T& rhs)                              const { return data == rhs; }
  inline friend bool operator==(const T& lhs, const Vertex<T>& rhs)       { return lhs == rhs.data; }

  inline bool operator!=(const Vertex<T>& rhs)                      const { return data != rhs.data; }
  inline bool operator!=(const T& rhs)                              const { return data != rhs; }
  inline friend bool operator!=(const T& lhs, const Vertex<T>& rhs)       { return lhs != rhs.data; }

  inline bool operator>(const Vertex<T>& rhs)                       const { return data > rhs.data; }
  inline bool operator>(const T& rhs)                               const { return data > rhs; }
  inline friend bool operator>(const T& lhs, const Vertex<T>& rhs)        { return lhs > rhs.data; }

  inline bool operator>=(const Vertex<T>& rhs)                      const { return data >= rhs.data; }
  inline bool operator>=(const T& rhs)                              const { return data >= rhs; }
  inline friend bool operator>=(const T& lhs, const Vertex<T>& rhs)       { return lhs >= rhs.data; }

  inline bool operator<(const Vertex<T>& rhs)                       const { return data < rhs.data; }
  inline bool operator<(const T& rhs)                               const { return data < rhs; }
  inline friend bool operator<(const T& lhs, const Vertex<T>& rhs)        { return lhs < rhs.data; }

  inline bool operator<=(const Vertex<T>& rhs)                      const { return data <= rhs.data; }
  inline bool operator<=(const T& rhs)                              const { return data <= rhs; }
  inline friend bool operator<=(const T& lhs, const Vertex<T>& rhs)       { return lhs <= rhs.data; }

  // Logical operators
  inline bool operator!()                                           const { return !data; }

  inline bool operator&&(const Vertex<T>& rhs)                      const { return data && rhs.data; }
  inline bool operator&&(const T& rhs)                              const { return data && rhs; }
  inline friend bool operator&&(const T& lhs, const Vertex<T>& rhs)       { return lhs && rhs.data; }

  inline bool operator||(const Vertex<T>& rhs)                      const { return data || rhs.data; }
  inline bool operator||(const T& rhs)                              const { return data || rhs; }
  inline friend bool operator||(const T& lhs, const Vertex<T>& rhs)       { return lhs || rhs.data; }

  // Conditional ternary operator

  // Bitwise operators
  inline T operator&(const Vertex<T>& rhs)                      const { return data & rhs.data; }
  inline T operator&(const T& rhs)                              const { return data & rhs; }
  inline friend T operator&(const T& lhs, const Vertex<T>& rhs)       { return lhs & rhs.data; }

  inline T operator|(const Vertex<T>& rhs)                      const { return data | rhs.data; }
  inline T operator|(const T& rhs)                              const { return data | rhs; }
  inline friend T operator|(const T& lhs, const Vertex<T>& rhs)       { return lhs | rhs.data; }

  inline T operator^(const Vertex<T>& rhs)                      const { return data ^ rhs.data; }
  inline T operator^(const T& rhs)                              const { return data ^ rhs; }
  inline friend T operator^(const T& lhs, const Vertex<T>& rhs)       { return lhs ^ rhs.data; }

  inline T operator~()                                          const { return ~data; }

  // Stream insertion operator
  inline friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) { os << vertex.data; return os;}
};
} // namespace graph_lib

template <typename T>
struct std::hash<graph_lib::Vertex<T>>
{
  size_t operator()(const graph_lib::Vertex<T> &x) const
  {
    return hash<T>()(x.data);
  }
};