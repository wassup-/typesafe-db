#ifndef LOCK_GUARD_HPP
#define LOCK_GUARD_HPP

#include "non_copyable.hpp"

namespace fp {

    template<typename Lock> struct lock_guard : non_copyable {
    protected:
        Lock & _lock;
    public:

        lock_guard(Lock & lock) : _lock(lock) {
            _lock.lock();
        }

        ~lock_guard() {
            _lock.unlock();
        }
    };
}

#endif