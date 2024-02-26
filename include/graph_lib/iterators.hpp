#pragma once

#include <iterator>
#include <memory>
#include <stack>
#include <vector>

#include <graph_lib/vertex.hpp>


namespace graph_lib
{

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
struct GraphIterator;


template <typename T> requires Graphable<T>
struct GraphIteratorBase
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  using VertexPtr = std::shared_ptr<Vertex<T>>;
  using VertexSet = std::unordered_set<VertexPtr, VertexPtrHash<T>, VertexPtrCompare<T>>;

  GraphIteratorBase(const Graph<T> &graph):
    graph_(graph), itr_(graph_.vertices_.begin()), current_pos_(0), end_pos_(graph_.vertices_.size())
  {}

  GraphIteratorBase(const Graph<T> &graph, size_t offset):
    graph_(graph), itr_(graph_.vertices_.begin()), current_pos_(offset), end_pos_(graph_.vertices_.size())
  {}

  virtual ~GraphIteratorBase() = default;

  virtual void increment()
  {
    current_pos_++;
  }
  virtual GraphIteratorBase* clone() = 0;

protected:
  friend struct GraphIterator<T>;

  Graph<T> graph_;
  VertexSet::const_iterator itr_;
  size_t current_pos_;
  const size_t end_pos_;
};

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

  GraphIterator(GraphIteratorBase<T> *base):
    base_(base)
  {}

  GraphIterator(const GraphIterator<T>& b):
    base_(b.base_->clone())
  {}

  // Prefix increment
  GraphIterator& operator++()
  {
    base_->increment(); return *this;
  }

  // Postfix increment
  GraphIterator operator++(int)
  {
    GraphIterator<T> tmp(*this);
    base_->increment();
    return tmp;
  }

  reference operator*() const { return *(base_->itr_); }
  pointer operator->() { return &(*(base_->itr_)); }
  bool operator== (const GraphIterator& rhs) { return base_->current_pos_ == rhs.base_->current_pos_; };
  bool operator!= (const GraphIterator& rhs) { return base_->current_pos_ != rhs.base_->current_pos_; };

protected:
  std::unique_ptr<GraphIteratorBase<T>> base_;
};


template<template <typename> typename G, typename T> requires Graphable<T>
struct DFSIterator;

template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedDirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedDirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  DFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  DFSIterator* clone() override { return new DFSIterator<UnweightedDirectedGraph, T>(*this); }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedDirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedDirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  DFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  DFSIterator* clone() override { return new DFSIterator<WeightedDirectedGraph, T>(*this); }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedUndirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedUndirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  DFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  DFSIterator* clone() override { return new DFSIterator<UnweightedUndirectedGraph, T>(*this); }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedUndirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedUndirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  DFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  DFSIterator* clone() override { return new DFSIterator<WeightedUndirectedGraph, T>(*this); }

private:
  std::vector<bool> visited_;
  std::stack<value_type> stack_;
};


template<template <typename> typename G, typename T> requires Graphable<T>
struct BFSIterator;

template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedDirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedDirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  BFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  BFSIterator* clone() override { return new BFSIterator<UnweightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedDirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedDirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  BFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  BFSIterator* clone() override { return new BFSIterator<WeightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedUndirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedUndirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  BFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  BFSIterator* clone() override { return new BFSIterator<UnweightedUndirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedUndirectedGraph, T> : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedUndirectedGraph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  BFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override { this->itr_++; GraphIteratorBase<T>::increment(); }
  BFSIterator* clone() override { return new BFSIterator<WeightedUndirectedGraph, T>(*this); }
};


} // namespace graph_lib