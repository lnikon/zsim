//#include "gate_router.hpp"
//#include "netlist.hpp"

//void Router::addNet(NetSPtr net)
//{
//    nets_.emplace_back(net);
//}

//Router::get_result_type Router::getNet(const IDBase::id_type &id, const NameBase::name_type &name)
//{
//    // Construct NodeBase object with given parameters to calculate to hash for
//    auto nodeBase = NodeBase(id, name);

//    return getNet(nodeBase);
//}

//Router::get_result_type Router::getNet(NodeBase net)
//{
//    get_result_type result = std::nullopt;

//    // Try to find node with a given base
//    auto netIt = std::find_if(std::begin(nets_), std::end(nets_), [net](const auto& nodeSPtr)
//    {
//        return static_cast<NodeBase>(*nodeSPtr) == net;
//    });

//    if(netIt != std::end(nets_))
//    {
//        result = *netIt;
//    }

//    return result;
//}

//void Router::send(logic_value_type_ns::LogicValue value)
//{
//    std::for_each(std::begin(nets_), std::end(nets_), [value](const auto netSPtr)
//    {
//        netSPtr->send(value);
//    });
//}

//void Router::addRecipient(ReceiveBaseSPtr receiver)
//{
//    recipients_.emplace_back(receiver);
//}

//void Router::addReceiver(std::shared_ptr<GateNode> gate)
//{
//    auto net = std::make_shared<Net>();

//    nets_.emplace_back(net);

////    gate->getRouter()->addRecipient(net);
//}

//const ReceiveBaseSPtrVec& Router::getRecipients() const
//{
//    return recipients_;
//}
