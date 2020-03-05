#pragma once

#include "logic_function.hpp"
#include "id_generator.hpp"
#include "graph.hpp"

#include <set>
#include <string>
#include <functional>

namespace ns_netlist
{


using namespace logic_function_ns;


enum class InputNodeType {};
enum class OutputNodeType {};
enum class GateNodeType {};

struct IDBase
{
    using id_type       = id_generator_ns::IdGenerator::id_type;

    explicit IDBase(id_type id)
        : id_{id}
    { }

    IDBase() = default;
    virtual ~IDBase() = default;

    IDBase(const IDBase&) = default;
    IDBase& operator=(const IDBase&) = default;

    IDBase(IDBase&&) = default;
    IDBase& operator=(IDBase&&) = default;

    void setId(id_type id)
    {
        id_ = id;
    }

    auto getId() const -> id_type
    {
        return id_;
    }

    bool operator==(const IDBase& other)
    {
        return id_ == other.getId();
    }

protected:
    id_type id_{};
};

struct NameBase
{
    using name_type     = std::string;

    explicit NameBase(name_type name)
        : name_{name}
    { }

    NameBase() = default;
    virtual ~NameBase() = default;

    NameBase(const NameBase&) = default;
    NameBase& operator=(const NameBase&) = default;

    NameBase(NameBase&&) = default;
    NameBase& operator=(NameBase&&) = default;

    auto setName(const name_type& name)
    {
        name_ = name;
    }

    auto getName() const -> name_type
    {
        return name_;
    }

    bool operator==(const NameBase& other)
    {
        return name_ == other.getName();
    }

protected:
    name_type name_{};
};

struct DelayBase
{
    using delay_type = std::size_t;

    explicit DelayBase(delay_type delay)
        : delay_{delay}
    { }

    DelayBase() = default;
    virtual ~DelayBase() = default;

    DelayBase(const DelayBase&) = default;
    DelayBase& operator=(const DelayBase&) = default;

    DelayBase(DelayBase&&) = default;
    DelayBase& operator=(DelayBase&&) = default;

    auto setDelay(const delay_type& delay)
    {
        delay_ = delay;
    }

    auto getDelay() const -> delay_type
    {
        return delay_;
    }

    bool operator==(const DelayBase& other)
    {
        return delay_ == other.getDelay();
    }

protected:
    delay_type delay_{0};
};

struct HasLogicFunctionBase
{
    void setLogicFunction(LogicFunction<UserDefinedLogicFunctionType> logicFn)
    {
        fn_ = logicFn;
    }

protected:
    std::function<LogicValue(LogicValueVecCRef)> fn_{nullptr};
};

struct RunnableBase
{
    virtual ~RunnableBase() {}
    virtual LogicValue run(LogicValueVecCRef input) = 0;
};

// One to many relationship
struct SendBase
{
    virtual ~SendBase() {}
    virtual void send(LogicValue value) = 0;

protected:
    // Source type
    // Sink type
};

// One to many relationship
struct ReceiveBase
{
    virtual ~ReceiveBase() {}
    virtual void receive(LogicValue value) = 0;

protected:
    // Source type
    // Sink type
};

struct SimulateBase : HasLogicFunctionBase, RunnableBase, SendBase, ReceiveBase
{
};

// One to many relationship
struct PropogateBase
{
    virtual ~PropogateBase() {}
    virtual void propogate(LogicValue value) = 0;

protected:
    // Source type
    // Sink type
};


struct NodeBase : IDBase, NameBase, DelayBase
{
    using id_type       = IDBase::id_type;
    using name_type     = NameBase::name_type;
    using delay_type    = DelayBase::delay_type;

    NodeBase(id_type id, name_type name, delay_type delay)
        : IDBase(id),
          NameBase(name),
          DelayBase(delay)
    { }

    NodeBase() = default;
    virtual ~NodeBase() = default;

    NodeBase(const NodeBase&) = default;
    NodeBase& operator=(const NodeBase&) = default;

    NodeBase(NodeBase&&) = default;
    NodeBase& operator=(NodeBase&&) = default;

    bool operator==(const NodeBase& other)
    {
        return (static_cast<IDBase>(*this) == static_cast<IDBase>(other))
                && (static_cast<NameBase>(*this) == static_cast<NameBase>(other))
                && (static_cast<DelayBase>(*this) == static_cast<DelayBase>(other));
    }

    bool operator!=(const NodeBase& other)
    {
        return !(*this == other);
    }
};

struct GateNode : NodeBase, SimulateBase
{
    LogicValue run(LogicValueVecCRef input) override
    {
        return fn_(input);
    }
};

struct InputNode : NodeBase, ReceiveBase
{

};

struct OutputNode : NodeBase, SendBase
{

};

struct Net : NodeBase, PropogateBase
{

};

struct GenericNode : NodeBase, SimulateBase
{
    
};

//template <class LogicFunctionType, class NodeType>
//struct Node {};


//template <>
//struct Node<InputLogicFunctionType, InputNodeType> : NodeBase
//{
//    Node(NodeBase::name_type name, NodeBase::id_type id)
//        : NodeBase{name, id}
//    { }

//    Node() = default;
//    ~Node() = default;

//    Node(const Node&) = default;
//    Node& operator=(const Node&) = default;

//    Node(Node&&) = default;
//    Node& operator=(Node&&) = default;
//};
//using InputNode     = Node<InputLogicFunctionType, InputNodeType>;
//using InputNodeSPtr = std::shared_ptr<InputNode>;


//template <>
//struct Node<OutputLogicFunctionType, OutputNodeType> : NodeBase
//{
//    Node() = default;
//    ~Node() = default;

//    Node(const Node&) = default;
//    Node& operator=(const Node&) = default;

//    Node(Node&&) = default;
//    Node& operator=(Node&&) = default;
//};
//using OutputNode     = Node<OutputLogicFunctionType, OutputNodeType>;
//using OutputNodeSPtr = std::shared_ptr<OutputNode>;


//template <class LogicFunctionType>
//struct Node<LogicFunctionType, GateNodeType> : NodeBase
//{
//    Node() = default;
//    ~Node() = default;

//    Node(const Node&) = default;
//    Node& operator=(const Node&) = default;

//    Node(Node&&) = default;
//    Node& operator=(Node&&) = default;

//    void setLogicFunction(LogicFunction<LogicFunctionType> logicFn)
//    {
//        fn_ = logicFn;
//    }

//    template <class T>
//    LogicValue run(T&& input)
//    {
//        return fn_(input);
//    }

//private:
//    std::function<LogicValue(LogicValueVecCRef)> fn_{nullptr};
//};

//template <class LogicFunctionType>
//using GateNodeSPtr = std::shared_ptr<Node<LogicFunctionType, GateNodeType>>;


//struct Net : NodeBase
//{
//    Net(NodeBase::name_type name, NodeBase::id_type id)
//        : NodeBase{name, id} { }

//    Net() = default;
//    ~Net() = default;

//    Net(const Net&) = delete;
//    Net& operator=(const Net&) = delete;

//    Net(Net&&) = delete;
//    Net& operator=(Net&&) = delete;
//};
//using NetSPtr           = std::shared_ptr<Net>;
//using NetSPtrSet        = std::set<NetSPtr>;
//using NetSPtrSetRef     = std::set<NetSPtr>&;
//using NetSPtrSetCRef    = const NetSPtrSet&;

//using namespace graph_ns;
//struct Netlist final
//{
//    Netlist() {}
//    ~Netlist() {}

//    Netlist(const Netlist&) = delete;
//    Netlist& operator=(const Netlist&) = delete;

//    Netlist(Netlist&&) = delete;
//    Netlist& operator=(Netlist&&) = delete;

//    void addInput(const std::string& name, std::size_t id)
//    {
//        inputs_.addVertex(InputNode{name, id});

//        auto [netIt, ok] = addNet(name, id);
//        if(!ok)
//        {
//            return;
//            // throw an exception
//        }

//        inputs_.addEdge(InputNode{name, id}, *netIt, decltype (inputs_)::Direction::Output);
//    }

//    std::pair<NetSPtrSet::iterator, bool> addNet(const std::string& name, std::size_t id)
//    {
//        return nets_.emplace(std::make_shared<Net>(name, id));
//    }

//    Graph<InputNode,  NetSPtr>      inputs_;
//    Graph<OutputNode, NetSPtr>      outputs_;
//    NetSPtrSet                      nets_;
//};

//template <class LogicFunctionType, class NodeType>
//using NodeSPtr = std::shared_ptr<Node<LogicFunctionType, NodeType>>;





//using NetSPtr = std::shared_ptr<Net>;

} // namespace ns_netlist
