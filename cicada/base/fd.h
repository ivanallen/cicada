// Author: allen

#include "cicada/base/noncopyable.h"

namespace cicada::base {

class Fd : noncopyable {
public:
    explicit Fd(int fd);
    Fd();
    ~Fd();

    int value() const;
    void set_block();
    void set_nonblock();

    // release ownership
    int release();

    void reset(int fd);
private:
    int _fd = -1;
};


} // namespace cicada::base
