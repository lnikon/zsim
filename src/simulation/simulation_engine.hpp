#pragma once

#include "netlist.hpp"
#include "timing_wheel.hpp"

using SignalValue = std::pair<ns_simulation::simulation_time_t, logic_value_t>;
using SignalValues = std::vector<SignalValue>;
using SignalsValues = std::unordered_map<std::string, SignalValues>;

namespace ns_simulation {

// struct PrimaryInputs {
//  explicit PrimaryInputs(ns_netlist::Netlist);

//  PrimaryInputs(const PrimaryInputs &) = default;
//  PrimaryInputs &operator=(const PrimaryInputs &) = default;

//  PrimaryInputs(PrimaryInputs &&) = default;
//  PrimaryInputs &operator=(PrimaryInputs &&) = default;

//  ~PrimaryInputs() = default;

// private:
//  std::unordered_map<std::string, logic_value_t> m_values;
//};

using PrimaryInputs = std::unordered_map<std::string, logic_value_t>;
using PrimaryOutputs = std::unordered_map<std::string, logic_value_t>;

class SimulationEngine {
public:
  explicit SimulationEngine(ns_netlist::Netlist);

  SimulationEngine(const SimulationEngine &) = default;
  SimulationEngine &operator=(const SimulationEngine &) = default;

  SimulationEngine(SimulationEngine &&) = default;
  SimulationEngine &operator=(SimulationEngine &&) = default;

  ~SimulationEngine() = default;

  void simulate(PrimaryInputs primaryInputs);
  SignalsValues getSimulationResults() const;

private:
  ns_netlist::Netlist m_netlist;
  ns_simulation::TimingWheel m_timingWheel;
  SignalsValues m_sv;
};

} // namespace ns_simulation
