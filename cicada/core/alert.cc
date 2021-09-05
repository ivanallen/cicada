// Author: allen

#include "cicada/core/alert.h"

#include <glog/logging.h>

namespace cicada::core {

Alert::Alert(std::function<void()> cb, int64_t expire_ms) :
        _callback(std::move(cb)),
        _expire_ms(expire_ms) {
}

int64_t Alert::expire_ms() const {
    return _expire_ms;
}

void Alert::run() const {
    if (_callback) {
        _callback();
    }
}


} // namespace cicada::core
