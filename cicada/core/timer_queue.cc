// Author: allen

#include <sys/time.h>

#include <functional>

#include "cicada/core/timer_queue.h"
#include "cicada/core/event_loop.h"

#include <glog/logging.h>

namespace cicada::core {

TimerQueue::TimerQueue(EventLoop* loop) :
        _loop(loop),
        _observer(loop, _timer_fd.fd()) {
    _observer.set_read_callback(std::bind(&TimerQueue::handle_read, this));
}

void TimerQueue::add_alert(std::function<void()> cb, int timeout_ms) {
    struct timeval tp = { 0 };
    ::gettimeofday(&tp, nullptr);

    int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    int64_t expire_ms = now_ms + timeout_ms;

    auto it = _alerts.find(expire_ms);

    if (it != _alerts.end()) {
        return;
    }

    _alerts.insert(std::make_pair(expire_ms, std::make_unique<Alert>(std::move(cb), expire_ms)));

    auto first = _alerts.begin();

    _timer_fd.set_timeout(timeout_ms);
}

void TimerQueue::handle_read() {
    char c = 0;
    ::read(_timer_fd.fd(), &c, 1);
    struct timeval tp = { 0 };
    ::gettimeofday(&tp, nullptr);

    int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    for (auto it = _alerts.begin(); it != _alerts.end();) {

        if (it->first <= now_ms) {
            it->second->run();
            it = _alerts.erase(it);
            continue;
        }
        ++it;
    }
}


} // namespace cicada::core
