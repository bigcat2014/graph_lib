#pragma once

#include <iterator>
#include <memory>
#include <stack>
#include <vector>

#include <graph_lib/vertex.hpp>


namespace graph_lib
{

// TODO: I have no idea what I'm doing here
template <typename T> requires Graphable<T>
class Graph;

template <typename T> requires Graphable<T>
class UnweightedDirectedGraph;

template <typename T> requires Graphable<T>
class WeightedDirectedGraph;

template <typename T> requires Graphable<T>
class UnweightedUndirectedGraph;

template <typename T> requires Graphable<T>
class WeightedUndirectedGraph;


template <typename T> requires Graphable<T>
struct GraphIterator
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  using VertexPtr = std::shared_ptr<Vertex<T>>;
  using VertexSet = std::unordered_set<VertexPtr, VertexPtrHash<T>, VertexPtrCompare<T>>;

  GraphIterator(const Graph<T> &graph, size_t offset):
    graph_(graph), itr_(graph_.vertices_.begin()), end_pos_(graph_.vertices_.size()), done_(false)
  {
    setCurrentPos(offset);
  }

  virtual void increment()
  {
    this->itr_++; setCurrentPos(current_pos_ + 1);
  }

  // Prefix increment
  GraphIterator& operator++()
  {
    this->increment(); return *this;
  }

  // Postfix increment
  GraphIterator operator++(int)
  {
    GraphIterator<T> tmp = *this;
    this->increment();
    return tmp;
  }

  reference operator*() const { return *itr_; }
  pointer operator->() { return &(*itr_); }
  friend bool operator== (const GraphIterator& a, const GraphIterator& b) { return a.current_pos_ == b.current_pos_; };
  friend bool operator!= (const GraphIterator& a, const GraphIterator& b) { return a.current_pos_ != b.current_pos_; };

protected:
  Graph<T> graph_;
  VertexSet::const_iterator itr_;
  size_t current_pos_;
  const size_t end_pos_;
  bool done_;

  void setCurrentPos(size_t pos)
  {
    current_pos_ = pos;
    if (current_pos_ == end_pos_) { done_ = true; }
  }
};

template<template <typename> typename G, typename T> requires Graphable<T>
struct DFSIterator;

template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedDirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedDirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedUndirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedUndirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};


template<template <typename> typename G, typename T> requires Graphable<T>
struct BFSIterator;

template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedDirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedDirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedUndirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedUndirectedGraph, T> : public GraphIterator<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    GraphIterator<T>(graph, offset)
  {}

  void increment() override { this->itr_++; }
};


} // namespace graph_lib