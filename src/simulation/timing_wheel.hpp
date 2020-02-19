#pragma once

namespace ns_simulation
{
    struct Event 
    {
        Event();

        ~Event() override = default;

        Event(const Event&) = default;
        Event& operator=(const Event& other);

        Event(Event&&) = default;
        Event& operator=(Event&& other);
    };

    struct TimingWheel
    {
        TimingWheel();

        ~TimingWheel() override = default;

        TimingWheel(const TimingWheel&) = default;
        TimingWheel& operator=(const TimingWheel& other);

        TimingWheel(TimingWheel&&) = default;
        TimingWheel& operator=(TimingWheel&& other);
    };
}