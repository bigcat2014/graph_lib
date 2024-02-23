#pragma once


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
} // namespace graph_lib