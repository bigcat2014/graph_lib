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
struct DFSIterator
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = Graph::ValueType;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(pointer ptr):
    done_(false), ptr_(ptr)
  {}

  explicit operator bool() const { return !done_; }

  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }

  // Prefix increment
  virtual DFSIterator& operator++() = 0;

  // Postfix increment
  virtual DFSIterator operator++(int) = 0;

  friend bool operator== (const DFSIterator& a, const DFSIterator& b) { return a.ptr_ == b.ptr_; };
  friend bool operator!= (const DFSIterator& a, const DFSIterator& b) { return a.ptr_ != b.ptr_; };

  private:
    bool done_;
    pointer ptr_;
};

template<typename T> requires Graphable<T>
struct DirectedDFSIterator: public DFSIterator<DirectedGraph<T>>
{
  DirectedDFSIterator(pointer ptr): DFSIterator<DirectedGraph<T>>(ptr) {}

  explicit operator bool() const { return !done_; }

  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }

  // Prefix increment
  DirectedDFSIterator& operator++() override
  {
    // TODO: Implement DFS
  }

  // Postfix increment
  DirectedDFSIterator operator++(int) override
  {
    // TODO: I don't know what to do here either
  }

  friend bool operator== (const DirectedDFSIterator& a, const DirectedDFSIterator& b) { return a.ptr_ == b.ptr_; };
  friend bool operator!= (const DirectedDFSIterator& a, const DirectedDFSIterator& b) { return a.ptr_ != b.ptr_; };

  private:
    bool done_;
    std::vector<bool> visited_;
    std::stack<value_type> stack_;
    pointer ptr_;
};

} // namespace graph_lib