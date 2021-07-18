// Author: allen

#pragma once

#include <map>
#include "cicada/core/poller.h"

namespace cicada::core {

class PollPoller : public Poller {
public:
    std::vector<Observer*> poll(int timeout_ms) const override;

    void update(Observer* observer) override;

private:
    std::map<int, Observer*> _observers;
};

} // namespace cicada::core
