#pragma once

#include "base_defs.hpp"
#include "logic_value_defs.hpp"
#include "simulation_defs.hpp"

namespace ns_simulation
{
    using namespace logic_value_type_ns;
    struct Event 
    {
        Event() = default;

        ~Event() = default;

        Event(const Event&) = default;
        Event& operator=(const Event& other) = default;

        Event(Event&&) = default;
        Event& operator=(Event&& other) = default;

        LogicValue m_newValue;
        ns_simulation::simulation_time_t m_time;
        NameBase::name_type m_gateName;
    };

    struct TimingWheel
    {
        TimingWheel()  = default;

        ~TimingWheel() = default;

        TimingWheel(const TimingWheel&) = default;
        TimingWheel& operator=(const TimingWheel& other)  = default;

        TimingWheel(TimingWheel&&) = default;

        TimingWheel& operator=(TimingWheel&& other) = default;
    };
}