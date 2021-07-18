// Author: allen

#pragma once

#include <vector>

namespace cicada::core {

class Observer;

class Poller {
public:
    // poll obsever has events
    virtual std::vector<Observer*> poll(int timeout_ms) const = 0;

    // update observer's events on poller
    virtual void update(Observer* observer) = 0;
};

} // namespace cicada::core
