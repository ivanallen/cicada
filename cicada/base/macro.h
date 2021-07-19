// Author: allen

#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

#include <stdexcept>

#define CICADA_ABORT() \
    do { \
        char strerrbuf[1024]; \
        ::strerror_r(errno, strerrbuf, sizeof strerrbuf); \
        throw std::runtime_error(strerrbuf); \
    } while(0)
