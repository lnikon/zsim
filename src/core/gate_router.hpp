//#pragma once

//#include "base_defs.hpp"
//#include "net.hpp"

//#include <memory>

////namespace router_ns {

//struct GateNode;
//struct Router final
//{
//    using get_result_type = std::optional<NetSPtr>;

//    Router() = default;

//    void addNet(NetSPtr net);

//    get_result_type getNet(const IDBase::id_type& id, const NameBase::name_type& name);

//    get_result_type getNet(NodeBase net);

//    void send(LogicValue value);

//    void addRecipient(ReceiveBaseSPtr receiver);

//    void addReceiver(std::shared_ptr<GateNode> gate);

//    const ReceiveBaseSPtrVec &getRecipients() const;

//private:
//    /*
//     * Forms outgoing nets of the gate
//     */
//    NetSPtrVec          nets_{};

//    /*
//     * Incoming nets of the gate
//     */
//    ReceiveBaseSPtrVec  recipients_{};
//};

//using RouterSPtr = std::shared_ptr<Router>;
////} // namespace gate_router_ns
