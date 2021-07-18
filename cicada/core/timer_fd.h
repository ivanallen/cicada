// Author: allen

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace cicada::core {

class TimerFd {
public:
    TimerFd();
    ~TimerFd();

    bool set_timeout(int timeout_ms);
    int fd() const;
private:
    int _fds[2] = { 0 };
    int _poll_fds[2] = { 0 };
    std::thread _timer_thread;
    std::condition_variable _running_cv;
    std::mutex _mutex;
    std::atomic<bool> _running = false;
    std::atomic<bool> _stop = false;
    std::atomic<int64_t> _expire_ms = 0;
};

} // namespace cicada::core
