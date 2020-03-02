#include "gate.hpp"
#include "filter.hpp"
#include "net.hpp"

gate_ns::GateNode::GateNode() : NodeBase{} {}

gate_ns::GateNode::GateNode(NameBase::name_type_cref name,
                            DelayBase::delay_type delay)
    : NodeBase{name, delay} {}

gate_ns::GateNode::GateNode(NameBase::name_type_cref name) : NodeBase{name} {}

gate_ns::GateNode &gate_ns::GateNode::operator=(gate_ns::GateNode &&other) {
  if (&other == this) {
    return *this;
  }

  return *this;
}

gate_ns::GateNode &
gate_ns::GateNode::operator=(const gate_ns::GateNode &other) {
  if (&other == this) {
    return *this;
  }

  return *this;
}

logic_value_type_ns::logic_value_t gate_ns::GateNode::run() {
  using namespace zsim_algorithm_ns;

  LogicValueVec logicValueVec;

  /*
   * Filter input nets
   */
  auto inputNets = net_ns::NetSPtrVec{};
  zsim_algorithm_ns::filter(std::begin(nets_), std::end(nets_),
                            std::back_inserter(inputNets), [](const auto &net) {
                              return net.bitmap_.get(
                                  net_ns::NetType::INPUT_NET);
                            });

  /*
   * Collect input values from recepients
   */
  std::transform(std::begin(inputNets), std::end(inputNets),
                 std::back_inserter(logicValueVec),
                 [](const auto &net) { return net->getValue(); });

  return run(logicValueVec);
}

logic_value_type_ns::logic_value_t
gate_ns::GateNode::run(logic_value_type_ns::LogicValueVecCRef input) {
  /*
   * Simulate current gate and receive it's response
   */
  value_ = fn_(input);

  /*
   * Filter output nets
   */
  auto outputNets = net_ns::NetSPtrVec{};
  zsim_algorithm_ns::filter(
      std::begin(nets_), std::end(nets_), std::back_inserter(outputNets),
      [](const auto &net) {
        return net.bitmap_.get(net_ns::NetType::OUTPUT_NET);
      });

  /*
   * Send current gate simulation result to all wires connected to it
   */
  for (auto net : outputNets) {
    net->receive(value_);
  }

  /** IMPLEMENT:
   * Add output change into timing wheel
   */

  /*
   * Return value of simulation result
   */
  return value_;
}

void gate_ns::GateNode::attachNet(net_ns::NetSPtr net, net_ns::NetType type) {
  net->setType(type);
  nets_.push_back(net);
}
