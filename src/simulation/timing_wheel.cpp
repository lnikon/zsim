#include "timing_wheel.hpp"

#include <algorithm>
#include <iterator>

ns_simulation::TimingWheel::TimingWheel() {
  constexpr const decltype(m_events)::size_type magic_number = 10;
  m_events.resize(magic_number);
}

void ns_simulation::TimingWheel::submit(
    ns_simulation::event_shared_ptr_t event) noexcept {
  const auto time = event->m_time;
  //  extendCapacity(time + 1);
  m_events[time].push_back(event);
}

void ns_simulation::TimingWheel::submit(
    ns_simulation::event_shared_ptr_t &&event) noexcept {
  const auto time = event->m_time;
  extendCapacity(time + 1);
  m_events[time].push_back(std::move(event));
}

void ns_simulation::TimingWheel::submit(
    const ns_simulation::event_shared_ptr_vec_t &events) noexcept {
  auto maxIt = std::max_element(std::begin(events), std::end(events));
  if (maxIt == std::end(events)) {
    return;
  }

  const auto maxTime = (*maxIt)->m_time;
  extendCapacity(maxTime + 1);

  std::for_each(std::begin(events), std::end(events),
                [&, this](auto event) { submit(event); });
}

void ns_simulation::TimingWheel::submit(
    ns_simulation::event_shared_ptr_vec_t &&events) noexcept {
  auto maxIt = std::max_element(std::begin(events), std::end(events));
  if (maxIt == std::end(events)) {
    return;
  }

  const auto maxTime = (*maxIt)->m_time;
  extendCapacity(maxTime + 1);

  std::for_each(std::begin(events), std::end(events),
                [&, this](auto event) { submit(event); });
}

ns_simulation::event_shared_ptr_vec_t
ns_simulation::TimingWheel::at(ns_simulation::simulation_time_t time) const
    noexcept {
  if (time >= m_events.size()) {
    return event_shared_ptr_vec_t{};
  }

  return m_events[time];
}

ns_simulation::simulation_time_t ns_simulation::TimingWheel::length() const
    noexcept {
  return static_cast<ns_simulation::simulation_time_t>(m_events.size());
}

void ns_simulation::TimingWheel::extendCapacity(
    const ns_simulation::TimingWheel::size_type_t capacity) {
  if (capacity == 0) {
    return;
  }
  if (capacity > m_events.capacity()) {
    m_events.reserve(capacity + 1);
  }
}

gate_ns::GateSPtr ns_simulation::event_t::gate() const noexcept {
  return m_gate;
}
