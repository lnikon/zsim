#pragma once

#include "netlist.hpp"
#include "timing_wheel.hpp"

namespace ns_simulation 
{

class SimulationEngine
{
    public:
    SimulationEngine() = default;

    SimulationEngine(const SimulationEngine&) = default;
    SimulationEngine& operator=(const SimulationEngine&) = default;

    SimulationEngine(SimulationEngine&&) = default;
    SimulationEngine& operator=(SimulationEngine&&) = default;

    ~SimulationEngine() = default;

    private:
    ns_netlist::Netlist m_netlist;
    ns_simulation::TimingWheel m_timingWheel;
};

}