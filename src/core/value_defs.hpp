#pragma once

#include <vector>

namespace value_type_ns
{

template <class ValueType>
using ValueVec     = std::vector<ValueType>;

template <class ValueType>
using ValueVecRef  = std::vector<ValueType>&;

template <class ValueType>
using ValueVecCRef = const std::vector<ValueType>&;

template <class ValueType>
using ValueMat     = std::vector<ValueVec<ValueType>>;

template <class ValueType>
using ValueMatRef  = std::vector<ValueVec<ValueType>>&;

template <class ValueType>
using ValueMatCRef = const std::vector<ValueVec<ValueType>>&;

} // namespace value_type_ns
