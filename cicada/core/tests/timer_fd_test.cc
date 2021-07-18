#include "gtest/gtest.h"

#include <unistd.h>
#include <iostream>

#include "cicada/core/timer_fd.h"

using namespace cicada::core;

TEST(timer_fd_test, timer_fd_test) {
    TimerFd timer_fd;
    char c = 0;
    int r = 0;

    EXPECT_TRUE(timer_fd.set_timeout(100));
    EXPECT_FALSE(timer_fd.set_timeout(200));
    r = ::read(timer_fd.fd(), &c, 1);
    EXPECT_EQ(r, 1);
    EXPECT_EQ(c, ' ');

    EXPECT_TRUE(timer_fd.set_timeout(100));
    EXPECT_FALSE(timer_fd.set_timeout(200));
    r = ::read(timer_fd.fd(), &c, 1);
    EXPECT_EQ(r, 1);
    EXPECT_EQ(c, ' ');
}

