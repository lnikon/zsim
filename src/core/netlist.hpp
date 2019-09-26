#pragma once

#include "logic_function.hpp"
#include "id_generator.hpp"

#include <string>
#include <functional>

namespace netlist_ns
{

using namespace logic_function_ns;

template <class LogicFunctionType>
struct Node
{
    using id_type = id_generator_ns::IdGenerator::id_type;

    Node() = default;
    virtual ~Node() = default;

    Node(const Node&) = default;
    Node& operator=(const Node&) = default;

    Node(Node&&) = default;
    Node& operator=(Node&&) = default;

    void setId(id_type id)
    {
        id_ = id;
    }

    auto getId() const
    {
        return id_;
    }

protected:
    id_type id_{};
};

template <class LogicFunctionType>
struct Gate : Node<LogicFunctionType>
{
    Gate() = default;
    ~Gate() = default;

    Gate(const Gate&) = default;
    Gate& operator=(const Gate&) = default;

    Gate(Gate&&) = default;
    Gate& operator=(Gate&&) = default;

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
