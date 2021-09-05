// Author: allen

#include "cicada/core/timer_fd.h"

#include <poll.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdexcept>

#include "glog/logging.h"

#include "cicada/base/macro.h"

namespace cicada::core {

TimerFd::TimerFd() {
    int fds[2] = { 0 };
    int r = ::pipe(fds);
    if (r < 0) {
        CICADA_ABORT();
    }

    _in_fd.reset(fds[0]);
    _out_fd.reset(fds[1]);

    _out_fd.set_nonblock();

    _timer_thread = std::thread([this]() {
        while (!_stop) {
            std::unique_lock<std::mutex> guard(_mutex);
            _running_cv.wait(guard, [this]() {
                return _expire_ms > 0 || _stop;
            });

            if (_expire_ms == 0 && _stop) {
                break;
            }

            struct timeval tp = { 0 };
            ::gettimeofday(&tp, nullptr);

            int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
            int64_t expire_ms = _expire_ms;

            int timeout_ms = 0;

            if (expire_ms > now_ms) {
                timeout_ms = static_cast<int>(expire_ms - now_ms);
            } else {
                ::write(_out_fd.value(), " ", 1);
                _expire_ms = 0;
                continue;
            }

            int r = ::poll(NULL, 0, timeout_ms);

            if (r < 0) {
                CICADA_ABORT();
            }

            ::write(_out_fd.value(), " ", 1);
            _expire_ms = 0;
        }
    });
}

TimerFd::~TimerFd() {
    _stop = true;
    _running_cv.notify_one();
    _timer_thread.join();
}

void TimerFd::set_timeout(int timeout_ms) {
    assert(timeout_ms >= 0);

    struct timeval tp = { 0 };
    ::gettimeofday(&tp, nullptr);

    int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    int64_t expire_ms = now_ms + timeout_ms;

    // wakeup thread
    std::lock_guard<std::mutex> guard(_mutex);
    _expire_ms = expire_ms;
    _running_cv.notify_one();
}

int TimerFd::fd() const {
    return _in_fd.value();
}


} // namespace cicada::core
