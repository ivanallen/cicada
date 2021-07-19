// Author: allen

#include "cicada/base/fd.h"

#include <fcntl.h>
#include <unistd.h>

#include "cicada/base/macro.h"

namespace cicada::base {


Fd::Fd(int fd) : _fd(fd) {
}

Fd::Fd() {
}

Fd::~Fd() {
    reset(-1);
}

void Fd::set_block() {
    int fd = _fd;
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags < 0) {
        CICADA_ABORT();
    }

    int r = fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);

    if (r < 0) {
        CICADA_ABORT();
    }
}

void Fd::set_nonblock() {
    int fd = _fd;
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags < 0) {
        CICADA_ABORT();
    }

    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    if (r < 0) {
        CICADA_ABORT();
    }
}

int Fd::value() const {
    return _fd;
}

int Fd::release() {
    int fd = _fd;
    _fd = -1;
    return fd;
}

void Fd::reset(int fd) {
    if (_fd >= 0) {
        ::close(_fd);
    }

    _fd = fd;
}

} // namespace cicada::base
