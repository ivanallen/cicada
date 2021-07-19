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

    int poll_fds[2] = { 0 };
    r = ::pipe(poll_fds);
    if (r < 0) {
        CICADA_ABORT();
    }

    _poll_in_fd.reset(poll_fds[0]);
    _poll_out_fd.reset(poll_fds[1]);

    _poll_in_fd.set_nonblock();
    _poll_out_fd.set_nonblock();

    _timer_thread = std::thread([this]() {
        while (!_stop) {
           struct timeval tp = { 0 };
           ::gettimeofday(&tp, nullptr);

           int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
           int64_t expire_ms = _expire_ms; // get value from atomic

           int timeout_ms = 0;

           if (expire_ms == 0) {
               timeout_ms = -1;
           } else if (expire_ms > now_ms) {
               timeout_ms = static_cast<int>(expire_ms - now_ms);
           } else {
               ::write(_out_fd.value(), " ", 1);
               continue;
           }

           struct pollfd pollfd = {_poll_in_fd.value(), POLLIN, 0};
           int r = ::poll(&pollfd, 1, timeout_ms);

           if (r < 0) {
               CICADA_ABORT();
           }

           if (r == 1) {
               char c = 0;
               ::read(_poll_in_fd.value(), &c, 1);
               continue;
           }

           ::write(_out_fd.value()," ", 1);
        }
    });
}

TimerFd::~TimerFd() {
    _stop = true;
    ::write(_poll_out_fd.value(), " ", 1);

    _timer_thread.join();
}

void TimerFd::set_timeout(int timeout_ms) {
    assert(timeout_ms >= 0);

    struct timeval tp = { 0 };
    ::gettimeofday(&tp, nullptr);

    uint64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    uint64_t expire_ms = now_ms + timeout_ms;
    
    // wakeup thread
    _expire_ms = expire_ms;
    ::write(_poll_out_fd.value(), " ", 1);
}

int TimerFd::fd() const {
    return _in_fd.value();
}


} // namespace cicada::core
