
#pragma once
#include <vector>
#include <memory>

enum class Operations { False, True, Variable, Not, And, Or, Xor};

template <typename T>
using ISimplifier = std::shared_ptr<T> (*)(const std::shared_ptr<T> &);

template <typename T>
using IBoolTreeBuilder = std::shared_ptr<T> (*)(const Operations, const std::vector<std::shared_ptr<T>> &);

