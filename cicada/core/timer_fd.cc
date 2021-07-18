// Author: allen

#include "cicada/core/timer_fd.h"

#include <poll.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdexcept>

#include "glog/logging.h"

namespace cicada::core {

TimerFd::TimerFd() {
    int r = ::pipe(_fds);
    if (r < 0) {
        char strerrbuf[1024];
        strerror_r(errno, strerrbuf, sizeof strerrbuf);
        throw std::runtime_error(strerrbuf);
    }

    r = ::pipe(_poll_fds);
    if (r < 0) {
        char strerrbuf[1024];
        strerror_r(errno, strerrbuf, sizeof strerrbuf);
        throw std::runtime_error(strerrbuf);
    }

    _timer_thread = std::thread([this]() {
        while (!_stop) {
            std::unique_lock<std::mutex> guard(_mutex);
           _running_cv.wait(guard, [this]{return _running || _stop;}); 
           guard.unlock();

           if (_stop) break;

           struct timeval tp = { 0 };
           ::gettimeofday(&tp, nullptr);

           int now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
           int timeout_ms = _expire_ms - now_ms;

           if (timeout_ms <= 0) {
               ::write(_fds[1], " ", 1);
               _running = false;
               continue;
           }

           struct pollfd pollfd = {_poll_fds[0], POLLIN, 0};
           int r = ::poll(&pollfd, 1, timeout_ms);
           if (r < 0) {
               char strerrbuf[1024];
               strerror_r(errno, strerrbuf, sizeof strerrbuf);
               throw std::runtime_error(strerrbuf);
           }
           if (r == 1) {
               char c = 0;
               ::read(_poll_fds[0], &c, 1);
               continue;
           }

           ::write(_fds[1], " ", 1);
           _running = false;
        }
    });
}

TimerFd::~TimerFd() {
    _stop = true;
    _running_cv.notify_one();
    ::write(_poll_fds[1], " ", 1);

    _timer_thread.join();
    ::close(_fds[0]);
    ::close(_fds[1]);
    ::close(_poll_fds[0]);
    ::close(_poll_fds[1]);
}

bool TimerFd::set_timeout(int timeout_ms) {
    assert(timeout_ms >= 0);

    struct timeval tp = { 0 };
    ::gettimeofday(&tp, nullptr);

    int64_t now_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    int64_t expire_ms = now_ms + timeout_ms;
    
    if (_running && expire_ms > _expire_ms) return false;

    // wakeup thread
    _expire_ms = expire_ms;
    ::write(_poll_fds[1], " ", 1);

    _running = true;
    _running_cv.notify_one();

    return true;
}

int TimerFd::fd() const {
    return _fds[0];
}


} // namespace cicada::core
