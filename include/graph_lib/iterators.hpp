#pragma once

#include <iterator>
#include <stack>
#include <vector>

#include <graph_lib/vertex.hpp>

namespace graph_lib
{

// TODO: I have no idea what I'm doing here

template <typename T> requires Graphable<T>
class Graph;
template <typename T> requires Graphable<T>
class DirectedGraph;
template <typename T> requires Graphable<T>
class UndirectedGraph;

template<typename Graph, typename T> requires Graphable<T>
struct GraphIterator
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<T>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphIterator(pointer ptr):
    done_(false), ptr_(ptr)
  {}

  // explicit operator bool() const { return !done_; }

  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }

  virtual void increment() = 0;

  // Prefix increment
  // virtual GraphIterator& operator++() = 0;

  // Postfix increment
  // virtual GraphIterator operator++(int) = 0;

  friend bool operator== (const GraphIterator& a, const GraphIterator& b) { return a.ptr_ == b.ptr_; };
  friend bool operator!= (const GraphIterator& a, const GraphIterator& b) { return a.ptr_ != b.ptr_; };

protected:
  bool done_;
  pointer ptr_;
};

template <typename U, typename T> requires Graphable<T>
struct GraphDFSIterator: public GraphIterator<U, T> {};

template<typename T> requires Graphable<T> 
struct GraphDFSIterator<DirectedGraph<T>, T>: public GraphIterator<DirectedGraph<T>, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename DirectedGraph<T>::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphDFSIterator(pointer ptr): GraphIterator<DirectedGraph<T>, T>(ptr) {}

  void increment() override
  {
    this->ptr_++;
  }

  // Prefix increment
  GraphDFSIterator<DirectedGraph<T>, T>& operator++()
  {
    // TODO: Implement DFS
    // ptr_++; return *this;
    this->increment(); return *this;
  }

  // Postfix increment
  GraphDFSIterator<DirectedGraph<T>, T> operator++(int)
  {
    // TODO: I don't know what to do here either
    // auto tmp = *this; ++(*this); return tmp;
    GraphDFSIterator<DirectedGraph<T>, T> tmp = (*this);
    this->increment();
    return tmp;
  }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T>
struct GraphDFSIterator<UndirectedGraph<T>, T>: public GraphIterator<UndirectedGraph<T>, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename UndirectedGraph<T>::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphDFSIterator(pointer ptr): GraphIterator<UndirectedGraph<T>, T>(ptr) {}

  // Prefix increment
  GraphDFSIterator& operator++() override
  {
    // TODO: Implement DFS
  }

  // Postfix increment
  GraphDFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }

private:
  enum VisitedState
  {
    UNVISITED,
    VISITED_ONCE,
    VISITED_TWICE
  };

  std::vector<VisitedState> visited_;
  std::stack<value_type> stack_;
};

template <typename U, typename T> requires Graphable<T>
struct GraphBFSIterator: public GraphIterator<U, T> {};

template<typename T> requires Graphable<T>
struct GraphBFSIterator<DirectedGraph<T>, T>: public GraphIterator<DirectedGraph<T>, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename DirectedGraph<T>::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphBFSIterator(pointer ptr): GraphIterator<DirectedGraph<T>, T>(ptr) {}

  // Prefix increment
  GraphBFSIterator& operator++() override
  {
    // TODO: Implement BFS
  }

  // Postfix increment
  GraphBFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }
};

template<typename T> requires Graphable<T>
struct GraphBFSIterator<UndirectedGraph<T>, T>: public GraphIterator<UndirectedGraph<T>, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename UndirectedGraph<T>::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphBFSIterator(pointer ptr): GraphIterator<UndirectedGraph<T>, T>(ptr) {}

  // Prefix increment
  GraphBFSIterator& operator++() override
  {
    // TODO: Implement BFS
  }

  // Postfix increment
  GraphBFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }
};

} // namespace graph_lib