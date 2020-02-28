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

    LogicFunction(const LogicFunction&) = default;
    LogicFunction& operator=(const LogicFunction&) = default;

    LogicFunction(LogicFunction&&) = default;
    LogicFunction& operator=(LogicFunction&&) = default;

    LogicFunction(TruthTableCRef truthTable)
        : truthTable_{truthTable}
    {

    }

    LogicFunction(TruthTable&& truthTable)
        : truthTable_{std::move(truthTable)}
    {

    }

    logic_value_t operator()(LogicValueVecCRef inputs)
    {
        logic_value_t result = logic_value_t::DONT_CARE;
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
        truthTable_.addCover(LogicValueVec{logic_value_t::FALSE,  logic_value_t::FALSE},  logic_value_t::FALSE);
        truthTable_.addCover(LogicValueVec{logic_value_t::FALSE,  logic_value_t::TRUE},   logic_value_t::FALSE);
        truthTable_.addCover(LogicValueVec{logic_value_t::TRUE,   logic_value_t::FALSE},  logic_value_t::FALSE);
        truthTable_.addCover(LogicValueVec{logic_value_t::TRUE,   logic_value_t::TRUE},   logic_value_t::TRUE);
    }
};

} // namespace logic_function_ns
