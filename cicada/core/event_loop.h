// Author: allen

#pragma once
#include <memory>

#include "cicada/core/poller.h"

namespace cicada::core {

class Observer;
class EventLoop {
public:
    EventLoop();

    void update(Observer* observer) const;
    void loop() const;

private:
    std::unique_ptr<Poller> _poller;
    bool _stop = false;
};

} // namespace cicada::core
