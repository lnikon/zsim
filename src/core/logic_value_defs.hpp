#pragma once

#include "value_defs.hpp"

#include <iostream>

namespace logic_value_type_ns {

using namespace value_type_ns;

enum class LogicValue : uint8_t  { FALSE = 0, TRUE, DONT_CARE, HIGH_IMP, UNKOWN };

using LogicValueVec     = ValueVec<LogicValue>;

using LogicValueVecRef  = ValueVec<LogicValue>&;

using LogicValueVecCRef = const ValueVec<LogicValue>&;

using LogicValueMat     = ValueVec<LogicValueVec>;

using LogicValueMatRef  = ValueVec<LogicValueVec>&;

using LogicValueMatCRef = const ValueVec<LogicValueVec>&;

static std::string stringify(LogicValue value)
{
    auto result = std::string{"UNDEFINED"};
    if(value == LogicValue::TRUE)
    {
        result = "LogicValue::LOW";
    }
    else if(value == LogicValue::FALSE)
    {
        result = "LogicValue::HIGH";
    }
    else if(value == LogicValue::HIGH_IMP)
    {
        result = "LogicValue::HIGH_IMP";
    }
    else if(value == LogicValue::DONT_CARE)
    {
        result = "LogicValue::DONT_CARE";
    }
    else if(value == LogicValue::UNKOWN)
    {
        result = "LogicValue::DONT_CARE";
    }
    return result;
}

static void print(LogicValue value)
{
    std::cout << stringify(value) << std::endl;
}

} // namespace logic_value_type_ns
