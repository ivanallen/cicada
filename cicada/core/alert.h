// Author: allen

#pragma once

#include <functional>

namespace cicada::core {

class Alert {
public:
    Alert(std::function<void()> cb, int64_t expire_ms);

    void run() const;

    int64_t expire_ms() const;

private:
    std::function<void()> _callback;
    int64_t _expire_ms = 0;
};

} // namespace cicada::core
