// Author: allen

#pragma once

namespace cicada::core {

class Timer {
pubic:
    Timer();
private:
    std::unique_ptr<Observer> _timer_observer;
};

} // namespace cicada::core
