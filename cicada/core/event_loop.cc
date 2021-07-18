// Author: allen

#include "cicada/core/event_loop.h"

#include <cassert>

#include "cicada/core/observer.h"
#include "cicada/core/poller.h"

namespace cicada::core {

void EventLoop::loop() const {
    while (!_stop) {
        auto observers = _poller->poll(500);

        for (auto observer : observers) {
            observer->handle_events();
        }
    }
}

void EventLoop::update(Observer* observer) const {
    assert(_poller != nullptr);

    _poller->update(observer);
}

} // namespace cicada::core

