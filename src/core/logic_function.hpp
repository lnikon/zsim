#pragma once

#include "truth_table.hpp"

namespace logic_function_ns
{

using namespace truth_table_ns;

enum class And2LogicFunctionType {};
enum class UserDefinedLogicFunctionType {};
enum class InputLogicFunctionType {};
enum class OutputLogicFunctionType {};

template <class LogicFunctionType>
struct LogicFunction;

template <>
struct LogicFunction<InputLogicFunctionType>
{

};

template <>
struct LogicFunction<OutputLogicFunctionType>
{

};

template <>
struct LogicFunction<UserDefinedLogicFunctionType>
{
    LogicFunction() = default;

    LogicFunction(const LogicFunction&) = delete;
    LogicFunction& operator=(const LogicFunction&) = delete;

    LogicFunction(LogicFunction&&) = delete;
    LogicFunction& operator=(LogicFunction&&) = delete;

    template <class T>
    LogicFunction(T&& truthTable)
        : truthTable_{std::forward<T>(truthTable)}
    { }

    LogicValue operator()(LogicValueVecCRef inputs)
    {
        LogicValue result = LogicValue::DONT_CARE;
        if(const auto [ok, value] = truthTable_.match(inputs); ok)
        {
            result = value;
        }

        return result;
    }

    protected:
    TruthTable truthTable_{};
};


template <>
struct LogicFunction<And2LogicFunctionType> : LogicFunction<UserDefinedLogicFunctionType>
{
    LogicFunction(TruthTableCRef truthTable) = delete;

    LogicFunction()
        :  LogicFunction<UserDefinedLogicFunctionType>()
    {
        truthTable_.addCover(LogicValueVec{LogicValue::LOW,  LogicValue::LOW},  LogicValue::LOW);
        truthTable_.addCover(LogicValueVec{LogicValue::LOW,  LogicValue::HIGH}, LogicValue::LOW);
        truthTable_.addCover(LogicValueVec{LogicValue::HIGH, LogicValue::LOW},  LogicValue::LOW);
        truthTable_.addCover(LogicValueVec{LogicValue::HIGH, LogicValue::HIGH}, LogicValue::HIGH);
    }
};

} // namespace logic_function_ns
