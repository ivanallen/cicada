// Author: allen

#include "cicada/core/observer.h"

#include <cassert>

#include "cicada/core/event_loop.h"

#include "glog/logging.h"

namespace cicada::core {

Observer::Observer(EventLoop* loop, int fd) :
        _loop(loop),
        _fd(fd) {
    enable_all();
}

void Observer::set_read_callback(ReadCallback cb) {
    _read_callback = std::move(cb);
}

void Observer::set_write_callback(WriteCallback cb) {
    _write_callback = std::move(cb);
}

void Observer::set_error_callback(ErrorCallback cb) {
    _error_callback = std::move(cb);
}

void Observer::enable_read() {
    _events |= kReadEvent;
    update();
}

void Observer::enable_write() {
    _events |= kWriteEvent;
    update();
}

void Observer::enable_error() {
    _events |= kErrorEvent;
    update();
}

void Observer::enable_all() {
    _events |= (kReadEvent | kWriteEvent | kErrorEvent);
    update();
}

void Observer::disable_read() {
    _events &= ~kReadEvent;
    update();
}

void Observer::disable_write() {
    _events &= ~kWriteEvent;
    update();
}

void Observer::disable_error() {
    _events &= ~kErrorEvent;
    update();
}

void Observer::disable_all() {
    _events = kNoneEvent;
    update();
}

int Observer::fd() const {
    return _fd;
}

int Observer::events() const {
    return _events;
}

void Observer::set_revents(int revents) {
    _revents = revents;
}

void Observer::update() {
    assert(_loop != nullptr);

    _loop->update(this);
}

void Observer::handle_events() const {
    int revents = _revents;

    if (_read_callback && (revents & kReadEvent)) {
        _read_callback();
    }

    if (_write_callback && (revents & kWriteEvent)) {
        _write_callback();
    }

    if (_error_callback && (revents & kWriteEvent)) {
        _error_callback();
    }
}

} // namespace cicada::core
