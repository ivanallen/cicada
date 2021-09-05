#include "unistd.h"
#include <iostream>
#include <string_view>

#include "cicada/core/event_loop.h"
#include "cicada/core/timer_queue.h"

void alert(cicada::core::TimerQueue& timer_queue, int index) {
    std::cout << "Alert " << index << std::endl;
    timer_queue.add_alert([&timer_queue, index]() {
        alert(timer_queue, index+1);
    }, 200 + index);
}

int main() {
    std::string_view welcome = "Hello cicada!";
    std::cout << welcome << std::endl;

    cicada::core::EventLoop loop;
    cicada::core::TimerQueue timer_queue(&loop);

    timer_queue.add_alert([&timer_queue]() {
        alert(timer_queue, 0);
    }, 1000);

    loop.loop();
    return 0;
}
