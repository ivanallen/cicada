// Author: allen

#pragma once

namespace cicada::core {

class Observer;
class Poller;
class EventLoop {
public:
    EventLoop();

    void update(Observer* observer) const;
    void loop() const;

private:
    Poller* _poller;
    bool _stop = false;
};

} // namespace cicada::core
