#pragma once

#include "value_defs.hpp"

#include <iostream>

namespace logic_value_type_ns {

using namespace value_type_ns;

enum class logic_value_t : uint8_t {
  FALSE = 0,
  TRUE,
  DONT_CARE,
  HIGH_IMP,
  UNKOWN
};

using LogicValueVec = ValueVec<logic_value_t>;

using LogicValueVecRef = ValueVec<logic_value_t> &;

using LogicValueVecCRef = const ValueVec<logic_value_t> &;

using LogicValueMat = ValueVec<LogicValueVec>;

using LogicValueMatRef = ValueVec<LogicValueVec> &;

using LogicValueMatCRef = const ValueVec<LogicValueVec> &;

static std::string stringify(logic_value_t value) {
  auto result = std::string{"UNDEFINED"};
  if (value == logic_value_t::TRUE) {
    result = "LogicValue::LOW";
  } else if (value == logic_value_t::FALSE) {
    result = "LogicValue::HIGH";
  } else if (value == logic_value_t::HIGH_IMP) {
    result = "LogicValue::HIGH_IMP";
  } else if (value == logic_value_t::DONT_CARE) {
    result = "LogicValue::DONT_CARE";
  } else if (value == logic_value_t::UNKOWN) {
    result = "LogicValue::DONT_CARE";
  }
  return result;
}

static void print(logic_value_t value) {
  std::cout << stringify(value) << std::endl;
}

} // namespace logic_value_type_ns
