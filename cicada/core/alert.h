// Author: allen

#pragma once

#include <functional>

namespace cicada::core {
    
class Alert {
public:
    Alert(std::function<void()> cb, int expire_ms, int interval_ms);

    void run() const;

private:
    std::function<void()> _callback;
    int _expire_ms = 0;
    int _interval_ms = 0;
};

} // namespace cicada::core
