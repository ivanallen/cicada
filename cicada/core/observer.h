// Author: allen

#pragma once

#include <functional>

// Observer regist events into event loop.
namespace cicada::core {

class EventLoop;
class Observer {
public:
    friend class EventLoop;

    using ReadCallback = std::function<void()>;
    using WriteCallback = std::function<void()>;
    using ErrorCallback = std::function<void()>;

    explicit Observer(EventLoop* loop, int fd);

    void set_read_callback(ReadCallback cb);
    void set_write_callback(WriteCallback cb);
    void set_error_callback(ErrorCallback cb);

    void enable_read();
    void enable_write();
    void enable_error();
    void enable_all();

    void disable_read();
    void disable_write();
    void disable_error();
    void disable_all();

    int fd() const;
    int events() const;
    void set_revents(int revents);

    void update();
    void handle_events() const;

public:
    static const int kNoneEvent = 0;
    static const int kReadEvent = 1;
    static const int kWriteEvent = 1 << 1;
    static const int kErrorEvent = 1 << 2;

private:
    EventLoop* _loop = nullptr;
    int _fd = -1;
    int _events = 0;
    int _revents = 0;
    ReadCallback _read_callback;
    WriteCallback _write_callback;
    ErrorCallback _error_callback;
};

} // namespace cicada::core
