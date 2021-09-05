// Author: allen

#pragma once

#include <map>
#include <memory>

#include "cicada/core/alert.h"
#include "cicada/core/observer.h"
#include "cicada/core/timer_fd.h"

namespace cicada::core {

class EventLoop;

class TimerQueue {
public:
    TimerQueue(EventLoop* loop);
    void add_alert(std::function<void()> cb, int timeout_ms);
    void handle_read();
private:
    std::map<uint64_t, std::unique_ptr<Alert>> _alerts;
    TimerFd _timer_fd;
    EventLoop* _loop;
    Observer _observer;
};

} // namespace cicada::core
