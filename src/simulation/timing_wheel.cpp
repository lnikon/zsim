#include "timing_wheel.hpp"

#include <algorithm>
#include <iterator>

void ns_simulation::TimingWheel::submit(
    ns_simulation::event_shared_ptr_t event) noexcept {
  const auto time = event->m_time;
  extendCapacity(time);
  m_events[time].push_back(event);
}

void ns_simulation::TimingWheel::submit(
    ns_simulation::event_shared_ptr_t &&event) noexcept {
  const auto time = event->m_time;
  extendCapacity(time);
  m_events[time].push_back(std::move(event));
}

void ns_simulation::TimingWheel::submit(
    const ns_simulation::event_shared_ptr_vec_t &events) noexcept {
  auto maxIt = std::max_element(std::begin(events), std::end(events));
  if (maxIt == std::end(events)) {
    return;
  }

  const auto maxTime = (*maxIt)->m_time;
  extendCapacity(maxTime);

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
  extendCapacity(maxTime);

  std::for_each(std::begin(events), std::end(events),
                [&, this](auto event) { submit(std::move(event)); });
}

ns_simulation::event_shared_ptr_vec_t
ns_simulation::TimingWheel::at(ns_simulation::simulation_time_t time) const
    noexcept {
  if (time >= m_events.size()) {
    return event_shared_ptr_vec_t{};
  }

  return m_events[time];
}

void ns_simulation::TimingWheel::extendCapacity(
    const ns_simulation::TimingWheel::size_type_t capacity) {
  if (capacity > m_events.capacity()) {
    m_events.reserve(capacity + 1);
  }
}
