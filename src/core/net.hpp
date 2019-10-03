#pragma once

#include "base_defs.hpp"

#include <set>
#include <array>
#include <memory>

// Forward declaration for gate
namespace gate_ns {
struct GateNode;
using GateSPtr      = std::shared_ptr<GateNode>;
using GateSPtrVec   = std::set<GateSPtr>;
using GateSPtrSet   = std::set<GateSPtr>;

} // namespace gate_ns

namespace net_ns {

enum class NetType : uint32_t { INPUT_NET = 0, OUTPUT_NET, IO_NET, HYPEREDGE, INTERNAL_NET, UNDEFINED, ENUM_END};

struct NetTypeBitmap final
{
    /*
     * Don't mark this constructor as explicit to make possbiel construction of bitmap from a single value
     */
    NetTypeBitmap(NetType type);

    NetTypeBitmap() = default;
    ~NetTypeBitmap() = default;
    NetTypeBitmap(const NetTypeBitmap&) = default;
    NetTypeBitmap& operator=(NetTypeBitmap&) = default;

    void set(NetType type);
    void unset(NetType type);
    bool get(NetType type) const;
    void reset();

private:
    std::array<bool, static_cast<uint32_t>(NetType::ENUM_END)> bitmap_;
};

struct Net final : NodeBase, SendBase, ReceiveBase
{
    Net();

    Net(name_type_cref name, NetType type, delay_type delay);

    Net(name_type_cref name, delay_type delay);
    Net(name_type_cref name, NetType type);

    explicit Net(name_type_cref name);

    ~Net() override = default;

    Net(const Net&) = default;
    Net& operator=(const Net& other);

    Net(Net&&) = default;
    Net& operator=(Net&& other);

    void            setType(NetType type);
    bool            getType(NetType type) const;
    NetTypeBitmap   getTypeBitmap() const;

    void addGate(gate_ns::GateSPtr gate);

private:
    gate_ns::GateSPtrVec gates_;
    NetType              type_{NetType::UNDEFINED};
    NetTypeBitmap        bitmap_{};

    void reset();
};

using NetSPtr = std::shared_ptr<Net>;
using NetSPtrVec = std::vector<NetSPtr>;
using NetSPtrSet = std::set<NetSPtr>;

template <class... Args>
auto make_unique(Args&&... args)
{
    return std::make_unique<Net>(std::forward<Args>(args)...);
}

template <class... Args>
auto make_shared(Args&&... args)
{
    return std::make_shared<Net>(std::forward<Args>(args)...);
}

} // namespace net_ns
