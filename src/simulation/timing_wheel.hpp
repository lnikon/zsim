#pragma once

#include "base_defs.hpp"
#include "gate.hpp"
#include "logic_value_defs.hpp"
#include "simulation_defs.hpp"

#include <memory>

namespace ns_simulation {
using namespace logic_value_type_ns;

struct event_t {
  event_t() = default;

  event_t(const logic_value_t newValue, ns_simulation::simulation_time_t time,
          gate_ns::GateSPtr gate)
      : m_newValue(newValue), m_time(time), m_gate(gate) {}

  event_t(ns_simulation::simulation_time_t time, gate_ns::GateSPtr gate)
      : m_time(time), m_gate(gate) {}

  event_t(const event_t &) = default;
  event_t &operator=(const event_t &other) = default;

  event_t(event_t &&) = default;
  event_t &operator=(event_t &&other) = default;

  ~event_t() = default;

  gate_ns::GateSPtr gate() const noexcept;

  logic_value_t m_newValue;
  ns_simulation::simulation_time_t m_time;
  gate_ns::GateSPtr m_gate;
};

using event_unique_ptr_t = std::unique_ptr<event_t>;
using event_shared_ptr_t = std::shared_ptr<event_t>;
using event_weak_ptr_t = std::weak_ptr<event_t>;
using event_shared_ptr_vec_t = std::vector<event_shared_ptr_t>;

struct TimingWheel {
  using events_list_t = std::vector<event_shared_ptr_vec_t>;
  using size_type_t = events_list_t::size_type;

  TimingWheel();

  ~TimingWheel() = default;

  TimingWheel(const TimingWheel &) = default;
  TimingWheel &operator=(const TimingWheel &other) = default;

  TimingWheel(TimingWheel &&) = default;

  TimingWheel &operator=(TimingWheel &&other) = default;

  void submit(event_shared_ptr_t event) noexcept;
  void submit(event_shared_ptr_t &&event) noexcept;
  void submit(const event_shared_ptr_vec_t &events) noexcept;
  void submit(event_shared_ptr_vec_t &&events) noexcept;
  event_shared_ptr_vec_t at(ns_simulation::simulation_time_t time) const
      noexcept;
  simulation_time_t length() const noexcept;

private:
  events_list_t m_events;

private:
  void extendCapacity(const size_type_t capacity);
};

using timing_wheel_unique_ptr_t = std::unique_ptr<TimingWheel>;
using timing_wheel_shared_ptr_t = std::shared_ptr<TimingWheel>;
using timing_wheel_weak_ptr_t = std::weak_ptr<TimingWheel>;

} // namespace ns_simulation
