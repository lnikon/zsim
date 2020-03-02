#include "netlist.hpp"
#include "filter.hpp"
#include "gate_router.hpp"

gate_ns::GateSPtr
netlist_ns::Netlist::findGate(NameBase::name_type_cref name) const {
  auto it = gates_.find(name);

  if (it != std::end(gates_)) {
    return it->second;
  }

  return nullptr;
}

net_ns::NetSPtr
netlist_ns::Netlist::findNet(NameBase::name_type_cref name) const {
  auto it = nets_.find(name);

  if (it != std::end(nets_)) {
    return it->second;
  }

  return nullptr;
}

gate_ns::GateSPtr netlist_ns::Netlist::addGate(NameBase::name_type_cref name,
                                               DelayBase::delay_type delay) {
  // Try to find and return the node, if it's already created
  auto gate = findGate(name);
  if (gate) {
    return gate;
  }

  // If find didn't succeed, then create new gate
  // and insert it into gates map
  gates_.emplace(name, gate_ns::make_shared(name, delay));

  return gates_[name];
}

gate_ns::GateSPtr netlist_ns::Netlist::addGate(gate_ns::GateSPtr gate) {
  gates_.emplace(gate->getName(), gate);

  return gates_[gate->getName()];
}

net_ns::NetSPtr netlist_ns::Netlist::addNet(NameBase::name_type_cref name,
                                            net_ns::NetType type,
                                            DelayBase::delay_type delay) {
  // Try to find and return the net, if it's already created
  auto net = findNet(name);
  if (net) {
    return net;
  }

  // If find didn't succeed, then create new net
  // and insert it into net map
  nets_.emplace(name, net_ns::make_shared(name, type, delay));

  return nets_[name];
}

/*
 * TODO: Do I need this function?
 */
void netlist_ns::Netlist::attachNet(NameBase::name_type_cref gateName,
                                    NameBase::name_type_cref netName,
                                    net_ns::NetType type,
                                    DelayBase::delay_type netDelay) {
  auto gate = addGate(gateName);
  auto net = addNet(netName, type, netDelay);

  //    gate->attachNet(net);
  net->addGate(gate);
}

net_ns::NetSPtrVec netlist_ns::Netlist::primaryInputs() const {
  auto inputNets = net_ns::NetSPtrVec{};
  zsim_algorithm_ns::filter(std::begin(nets_), std::end(nets_),
                            std::back_inserter(inputNets),
                            net_ns::IsPrimaryInputPerdicate{});
  return inputNets;
}

net_ns::NetSPtrVec netlist_ns::Netlist::primaryOutputs() const {
  auto outputNets = net_ns::NetSPtrVec{};
  zsim_algorithm_ns::filter(std::begin(nets_), std::end(nets_),
                            std::back_inserter(outputNets),
                            net_ns::IsPrimaryOutputPerdicate{});
  return outputNets;
}

LogicFunction<UserDefinedLogicFunctionType>
netlist_ns::Netlist::addCover(NameBase::name_type_cref coverOutputName,
                              TruthTableCRef truthTable) {
  so_covers_[coverOutputName] =
      LogicFunction<UserDefinedLogicFunctionType>{truthTable};

  return so_covers_[coverOutputName];
}
