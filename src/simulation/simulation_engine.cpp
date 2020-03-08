#include "simulation_engine.hpp"

ns_simulation::SimulationEngine::SimulationEngine(ns_netlist::Netlist netlist)
    : m_netlist{netlist}, m_timingWheel{} {}

void ns_simulation::SimulationEngine::simulate(
    ns_simulation::PrimaryInputs primaryInputValues) {
  // 1. Initialize primary inputs - O(n*logn)
  for (const auto &[name, value] : primaryInputValues) {
    auto net = m_netlist.findNet(name);
    if (net) {
      net->setValue(value);
    }
  }

  // 2. Get primary inputs
  auto primaryInputs = m_netlist.primaryInputs();

  // 3. Fill event list with gates attached to primary inputs.
  // No two events with same gate can coexists, so we need this
  // lambda to perform that check
  auto containsEventWithGateEqualTo = [](auto events, auto gate) {
    auto eventIt = std::find_if(
        std::begin(events), std::end(events),
        [gate](auto currentEvent) { return currentEvent->gate() == gate; });
    return eventIt != std::end(events);
  };

  // Starting creating the events.
  // For each net, go over gates attached to it,
  // for each gate, if event with that gate doesn't already exists,
  // then create new event from that gate and current simulation time,
  // push created event into initial events list
  constexpr const simulation_time_t startTime = 0;
  event_shared_ptr_vec_t initialEvents;
  for (auto net : primaryInputs) {
    auto gates = net->gates();
    for (auto gate : gates) {
      if (!containsEventWithGateEqualTo(initialEvents, gate)) {
        initialEvents.emplace_back(std::make_shared<event_t>(startTime, gate));
      }
    }
  }

  // Submit created initial events list into timing wheel
  TimingWheel timingWheel;
  timingWheel.submit(initialEvents);

  // 4. Start actual simulation
}
