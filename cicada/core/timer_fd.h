// Author: allen

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "cicada/base/fd.h"

namespace cicada::core {

class TimerFd {
public:
    TimerFd();
    ~TimerFd();

    void set_timeout(int timeout_ms);
    int fd() const;
private:
    base::Fd _in_fd; // block
    base::Fd _out_fd; // nonblock

    std::thread _timer_thread;
    std::condition_variable _running_cv;
    std::mutex _mutex;
    std::atomic<bool> _stop = false;
    int64_t _expire_ms = 0;
};

} // namespace cicada::core
