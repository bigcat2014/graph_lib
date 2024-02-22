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

template<typename Graph>
struct GraphIterator
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename Graph::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  GraphIterator(pointer ptr):
    done_(false), ptr_(ptr)
  {}

  explicit operator bool() const { return !done_; }

  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }

  // Prefix increment
  virtual GraphIterator& operator++() = 0;

  // Postfix increment
  virtual GraphIterator operator++(int) = 0;

  friend bool operator== (const GraphIterator& a, const GraphIterator& b) { return a.ptr_ == b.ptr_; };
  friend bool operator!= (const GraphIterator& a, const GraphIterator& b) { return a.ptr_ != b.ptr_; };

private:
  bool done_;
  pointer ptr_;
};

template<>
struct DFSIterator<DirectedGraph>: public GraphIterator<DirectedGraph>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename DirectedGraph::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(pointer ptr): GraphIterator<DirectedGraph>(ptr) {}

  // Prefix increment
  DFSIterator& operator++() override
  {
    // TODO: Implement DFS
  }

  // Postfix increment
  DFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }

private:
  bool done_;
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
  pointer ptr_;
};

template<UndirectedGraph>
struct DFSIterator: public GraphIterator<UndirectedGraph>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename UndirectedGraph::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(pointer ptr): GraphIterator<UndirectedGraph>(ptr) {}

  // Prefix increment
  DFSIterator& operator++() override
  {
    // TODO: Implement DFS
  }

  // Postfix increment
  DFSIterator operator++(int) override
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

  bool done_;
  std::vector<VisitedState> visited_;
  std::stack<value_type> stack_;
  pointer ptr_;
};

template<typename DirectedGraph>
struct DirectedBFSIterator: public GraphIterator<DirectedGraph>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename DirectedGraph::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DirectedBFSIterator(pointer ptr): GraphIterator<DirectedGraph>(ptr) {}

  // Prefix increment
  DirectedBFSIterator& operator++() override
  {
    // TODO: Implement BFS
  }

  // Postfix increment
  DirectedBFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }

private:
  bool done_;
  pointer ptr_;
};

template<typename UndirectedGraph>
struct UndirectedBFSIterator: public GraphIterator<UndirectedGraph>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Vertex<typename UndirectedGraph::ValueType>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  UndirectedBFSIterator(pointer ptr): GraphIterator<UndirectedGraph>(ptr) {}

  // Prefix increment
  UndirectedBFSIterator& operator++() override
  {
    // TODO: Implement BFS
  }

  // Postfix increment
  UndirectedBFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }

private:
  bool done_;
  pointer ptr_;
};

} // namespace graph_lib