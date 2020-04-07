#pragma once

#include "base_defs.hpp"
#include "net.hpp"

#include <memory>
#include <set>

namespace gate_ns {

struct NetWrapper {
  NetWrapper() { bitmap_.reset(); }

  ~NetWrapper() = default;
  NetWrapper(const NetWrapper &) = default;
  NetWrapper &operator=(NetWrapper &) = default;

  NetWrapper(net_ns::NetSPtr net) : net_{net} {}

  NetWrapper(net_ns::NetSPtr net, net_ns::NetTypeBitmap bitmap)
      : net_{net}, bitmap_{bitmap} {}

  net_ns::NetSPtr net_;
  net_ns::NetTypeBitmap bitmap_;
};
using NetWrapperVec = std::vector<NetWrapper>;

struct GateNode final : NodeBase, SimulateBase {
  GateNode();

  GateNode(name_type_cref name, delay_type delay);

  GateNode(name_type_cref name);

  ~GateNode() override = default;

  GateNode(const GateNode &) = default;
  GateNode &operator=(const GateNode &other);

  GateNode(GateNode &&) = default;
  GateNode &operator=(GateNode &&other);

  logic_value_t run() override;
  logic_value_t run(LogicValueVecCRef input) override;

  void attachNet(net_ns::NetSPtr net, net_ns::NetType type);

  net_ns::NetSPtrVec outputNets() const noexcept;

  inline bool operator==(const GateNode &rhs) const noexcept;

private:
  net_ns::NetSPtrVec nets_{};
};

using GateSPtr = std::shared_ptr<GateNode>;
using GateSPtrSet = std::set<GateSPtr>;

template <class... Args> auto make_unique(Args &&... args) {
  return std::make_unique<GateNode>(std::forward<Args>(args)...);
}

template <class... Args> auto make_shared(Args &&... args) {
  return std::make_shared<GateNode>(std::forward<Args>(args)...);
}

} // namespace gate_ns
