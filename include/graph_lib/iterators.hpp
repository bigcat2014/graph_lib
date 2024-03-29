#pragma once

#include <queue>
#include <iterator>
#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>

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
    graph_(graph), itr_(graph_.vertices_.begin()), end_itr_(graph_.vertices_.end()), current_value_(*graph_.vertices_.begin()), current_pos_(0), end_pos_(graph_.vertices_.size())
  {}

  GraphIteratorBase(const Graph<T> &graph, size_t offset):
    graph_(graph), current_pos_(offset), end_pos_(graph_.vertices_.size())
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
  VertexSet::const_iterator end_itr_;
  size_t current_pos_;
  const size_t end_pos_;

  value_type current_value_;
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

  reference operator*() const { return base_->current_value_; }
  pointer operator->() { return &(base_->current_value_); }
  bool operator== (const GraphIterator& rhs) { return base_->current_pos_ == rhs.base_->current_pos_; };
  bool operator!= (const GraphIterator& rhs) { return base_->current_pos_ != rhs.base_->current_pos_; };

protected:
  std::unique_ptr<GraphIteratorBase<T>> base_;
};


template<typename T> requires Graphable<T> 
struct BasicGraphIterator : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BasicGraphIterator(const Graph<T> &graph):
    GraphIteratorBase<T>(graph)
  {}

  BasicGraphIterator(const Graph<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override
  {
    GraphIteratorBase<T>::increment();
    this->itr_++;
    if (this->current_pos_ < this->end_pos_) { this->current_value_ = *(this->itr_); }
  }

  BasicGraphIterator* clone() override { return new BasicGraphIterator(*this); }
};


template<template <typename U> requires Graphable<U> typename G, typename T> requires Graphable<T>
struct DFSIteratorBase : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIteratorBase(const G<T> &graph):
    GraphIteratorBase<T>(graph)
  {
    visitVertex(this->current_value_);
  }

  DFSIteratorBase(const G<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override
  {
    GraphIteratorBase<T>::increment();
    if (this->current_pos_ >= this->end_pos_) { return; }

    if (stack_.empty())
    {
      unsigned count = 0;
      do
      {
        const auto vertex = *(++this->itr_);
        count = visited_.count(vertex);
      } while (count != 0);
      if (this->itr_ != this->end_itr_) { stack_.push(*this->itr_); }
    }

    this->current_value_ = stack_.top();
    stack_.pop();

    visitVertex(this->current_value_);
  }

private:
  std::unordered_map<value_type, bool, VertexPtrHash<T>, VertexPtrCompare<T>> visited_;
  std::stack<value_type> stack_;

  void visitVertex(value_type vertex)
  {
    const auto val = visited_.find(vertex);
    if (val == visited_.end() || !(*val).second)
    {
      visited_[vertex] = true;
    }
    for(auto& edge : (*vertex).adj)
    {
      auto adj_vertex = (*edge).vertex;
      const auto val2 = visited_.find(adj_vertex);
      if (val2 == visited_.end() || !(*val2).second)
      {
        stack_.push(adj_vertex);
      }
    }
  }
};

template<template <typename> typename G, typename T> requires Graphable<T>
struct DFSIterator;
template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedDirectedGraph, T> : public DFSIteratorBase<UnweightedDirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedDirectedGraph<T> &graph):
    DFSIteratorBase<UnweightedDirectedGraph, T>(graph)
  {}

  DFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    DFSIteratorBase<UnweightedDirectedGraph, T>(graph, offset)
  {}

  DFSIterator* clone() override { return new DFSIterator<UnweightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedDirectedGraph, T> : public DFSIteratorBase<WeightedDirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedDirectedGraph<T> &graph):
    DFSIteratorBase<WeightedDirectedGraph, T>(graph)
  {}

  DFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    DFSIteratorBase<WeightedDirectedGraph, T>(graph, offset)
  {}

  DFSIterator* clone() override { return new DFSIterator<WeightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct DFSIterator<UnweightedUndirectedGraph, T> : public DFSIteratorBase<UnweightedUndirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const UnweightedUndirectedGraph<T> &graph):
    DFSIteratorBase<UnweightedUndirectedGraph, T>(graph)
  {}

  DFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    DFSIteratorBase<UnweightedUndirectedGraph, T>(graph, offset)
  {}

  DFSIterator* clone() override { return new DFSIterator<UnweightedUndirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct DFSIterator<WeightedUndirectedGraph, T> : public DFSIteratorBase<WeightedUndirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  DFSIterator(const WeightedUndirectedGraph<T> &graph):
    DFSIteratorBase<WeightedUndirectedGraph, T>(graph)
  {}

  DFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    DFSIteratorBase<WeightedUndirectedGraph, T>(graph, offset)
  {}

  DFSIterator* clone() override { return new DFSIterator<WeightedUndirectedGraph, T>(*this); }
};


template<template <typename U> requires Graphable<U> typename G, typename T> requires Graphable<T>
struct BFSIteratorBase : public GraphIteratorBase<T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIteratorBase(const G<T> &graph):
    GraphIteratorBase<T>(graph)
  {
    visitVertex(this->current_value_);
  }

  BFSIteratorBase(const G<T> &graph, size_t offset):
    GraphIteratorBase<T>(graph, offset)
  {}

  void increment() override
  {
    GraphIteratorBase<T>::increment();
    if (this->current_pos_ >= this->end_pos_) { return; }

    if (queue_.empty())
    {
      unsigned count = 0;
      do
      {
        const auto vertex = *(++this->itr_);
        count = visited_.count(vertex);
      } while (count != 0);
      if (this->itr_ != this->end_itr_) { queue_.push(*this->itr_); }
    }

    this->current_value_ = queue_.front();
    queue_.pop();

    visitVertex(this->current_value_);
  }

private:
  std::unordered_map<value_type, bool, VertexPtrHash<T>, VertexPtrCompare<T>> visited_;
  std::queue<value_type> queue_;

  void visitVertex(value_type vertex)
  {
    const auto val = visited_.find(vertex);
    if (val == visited_.end() || !(*val).second)
    {
      visited_[vertex] = true;
    }
    for(auto& edge : (*vertex).adj)
    {
      auto adj_vertex = (*edge).vertex;
      const auto val2 = visited_.find(adj_vertex);
      if (val2 == visited_.end() || !(*val2).second)
      {
        queue_.push(adj_vertex);
      }
    }
  }
};

template<template <typename> typename G, typename T> requires Graphable<T>
struct BFSIterator;
template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedDirectedGraph, T> : public BFSIteratorBase<UnweightedDirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedDirectedGraph<T> &graph):
    BFSIteratorBase<UnweightedDirectedGraph, T>(graph)
  {}

  BFSIterator(const UnweightedDirectedGraph<T> &graph, size_t offset):
    BFSIteratorBase<UnweightedDirectedGraph, T>(graph, offset)
  {}

  BFSIterator* clone() override { return new BFSIterator<UnweightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedDirectedGraph, T> : public BFSIteratorBase<WeightedDirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedDirectedGraph<T> &graph):
    BFSIteratorBase<WeightedDirectedGraph, T>(graph)
  {}

  BFSIterator(const WeightedDirectedGraph<T> &graph, size_t offset):
    BFSIteratorBase<WeightedDirectedGraph, T>(graph, offset)
  {}

  BFSIterator* clone() override { return new BFSIterator<WeightedDirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<UnweightedUndirectedGraph, T> : public BFSIteratorBase<UnweightedUndirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const UnweightedUndirectedGraph<T> &graph):
    BFSIteratorBase<UnweightedUndirectedGraph, T>(graph)
  {}

  BFSIterator(const UnweightedUndirectedGraph<T> &graph, size_t offset):
    BFSIteratorBase<UnweightedUndirectedGraph, T>(graph, offset)
  {}

  BFSIterator* clone() override { return new BFSIterator<UnweightedUndirectedGraph, T>(*this); }
};

template<typename T> requires Graphable<T> 
struct BFSIterator<WeightedUndirectedGraph, T> : public BFSIteratorBase<WeightedUndirectedGraph, T>
{
  using iterator_category = std::input_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::shared_ptr<Vertex<T>>;
  using pointer           = value_type const*;
  using reference         = value_type const&;

  BFSIterator(const WeightedUndirectedGraph<T> &graph):
    BFSIteratorBase<WeightedUndirectedGraph, T>(graph)
  {}

  BFSIterator(const WeightedUndirectedGraph<T> &graph, size_t offset):
    BFSIteratorBase<WeightedUndirectedGraph, T>(graph, offset)
  {}

  BFSIterator* clone() override { return new BFSIterator<WeightedUndirectedGraph, T>(*this); }
};

} // namespace graph_lib