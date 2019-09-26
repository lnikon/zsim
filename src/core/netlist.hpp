#pragma once

#include "logic_function.hpp"

#include <string>
#include <functional>

namespace netlist_ns
{

using namespace logic_function_ns;

template <class LogicFunctionType>
struct Gate
{
    Gate() = default;
    ~Gate() = default;

    Gate(const Gate&) = delete;
    Gate& operator=(const Gate&) = delete;

    Gate(Gate&&) = delete;
    Gate& operator=(Gate&&) = delete;

    void setLogicFunction(LogicFunction<LogicFunctionType> logicFn)
    {
        fn_ = logicFn;
    }

    template <class T>
    LogicValue run(T&& input)
    {
        return fn_(input);
    }

private:
    std::function<LogicValue(LogicValueVecCRef)> fn_{nullptr};
};


struct Net
{
    Net() = default;
    ~Net() = default;

    Net(const Net&) = delete;
    Net& operator=(const Net&) = delete;

    Net(Net&&) = delete;
    Net& operator=(Net&&) = delete;
};


struct Netlist final
{
    Netlist() = default;
    ~Netlist() = default;

    Netlist(const Netlist&) = delete;
    Netlist& operator=(const Netlist&) = delete;

    Netlist(Netlist&&) = delete;
    Netlist& operator=(Netlist&&) = delete;
};


} // namespace netlist_ns
