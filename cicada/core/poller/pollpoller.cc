// Author: allen

#include "cicada/core/poller/pollpoller.h"

#include <poll.h>
#include <cassert>
#include <utility> // for make_pair

#include "cicada/core/observer.h"

#include <glog/logging.h>

namespace cicada::core {

std::vector<Observer*> PollPoller::poll(int timeout_ms) const {
    std::vector<Observer*> res;

    std::vector<struct pollfd> fds;
    fds.reserve(_observers.size());


    for (auto [fd, observer] : _observers) {
        int events = observer->events();
        short evts = 0;
        evts |= (events & Observer::kReadEvent) ? POLLIN : 0;
        evts |= (events & Observer::kWriteEvent) ? POLLOUT : 0;
        fds.emplace_back();
        auto& back = fds.back();
        back.fd = fd;
        back.events = evts;
        back.revents = 0;
    }

    nfds_t nfds = fds.size();
    int count = ::poll(&fds[0], nfds, timeout_ms);

    for (int i = 0; i < count; ++i) {
        auto& item = fds[i];
        auto iter = _observers.find(item.fd);
        assert(iter != _observers.end());
        auto observer = iter->second;

        int revents = 0;
        revents |= (item.revents & POLLIN) ? Observer::kReadEvent : 0;
        revents |= (item.revents & POLLOUT) ? Observer::kWriteEvent : 0;
        revents |= (item.revents & POLLERR) ? Observer::kErrorEvent : 0;
        observer->set_revents(revents);
        res.emplace_back(observer);
    }

    return res;
}

void PollPoller::update(Observer* observer) {
    int fd = observer->fd();
    auto [iter, ok] = _observers.insert(std::make_pair(fd, observer));

    assert(ok);
}

} // namespace cicada::core
