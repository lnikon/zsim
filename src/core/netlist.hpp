#pragma once

#include "base_defs.hpp"
#include "net.hpp"
#include "gate.hpp"
#include "logic_function.hpp"

#include <string>
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace netlist_ns
{

using namespace logic_function_ns;

struct Netlist
{
    gate_ns::GateSPtr   findGate(NameBase::name_type_cref name) const;

    net_ns::NetSPtr     findNet(NameBase::name_type_cref name) const;

    gate_ns::GateSPtr   addGate(NameBase::name_type_cref name,  DelayBase::delay_type delay = 0);
    gate_ns::GateSPtr   addGate(gate_ns::GateSPtr gate);

    net_ns::NetSPtr     addNet (NameBase::name_type_cref name,  net_ns::NetType type, DelayBase::delay_type delay = 0);

    void                attachNet(NameBase::name_type_cref gateName, net_ns::Net::name_type_cref netName, net_ns::NetType type, DelayBase::delay_type delay = 0);

    LogicFunction<UserDefinedLogicFunctionType>     addCover(NameBase::name_type_cref coverOutputName, TruthTableCRef truthTable);

private:
    /*
     * Values corresponds to .gate in model file
     */
    std::unordered_map<NameBase::name_type, gate_ns::GateSPtr> gates_;

    /*
     * Stores all nets existing in file
     */
    std::unordered_map<NameBase::name_type, net_ns::NetSPtr>   nets_;

    /*
     * Corresponding between so-cover and LogicFunction they perform.
     * Cover is determined by it's output net,
     * so that output net will be a key
     */
    std::unordered_map<NameBase::name_type, LogicFunction<UserDefinedLogicFunctionType>> so_covers_;
};

} // namespace netlist_ns
