// Author: allen

#include "cicada/core/alert.h"

namespace cicada::core {
    
Alert::Alert(std::function<void()> cb, int expire_ms, int interval_ms) :
        _callback(std::move(cb)),
        _expire_ms(expire_ms) {
}

void Alert::run() const {
    if (_callback) {
        _callback();
    }
}


} // namespace cicada::core
