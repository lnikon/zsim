#pragma once

#include "value_defs.hpp"

namespace logic_value_type_ns {

using namespace value_type_ns;

enum class LogicValue   { LOW = 0, HIGH, DONT_CARE, HIGH_IMP };

using LogicValueVec     = ValueVec<LogicValue>;

using LogicValueVecRef  = ValueVec<LogicValue>&;

using LogicValueVecCRef = const ValueVec<LogicValue>&;

using LogicValueMat     = ValueVec<LogicValueVec>;

using LogicValueMatRef  = ValueVec<LogicValueVec>&;

using LogicValueMatCRef = const ValueVec<LogicValueVec>&;

} // namespace logic_value_type_ns
