/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef LOCK_GUARD_HPP
#define LOCK_GUARD_HPP

#include "non_copyable.hpp"

namespace fp {

    template<typename Lock>
    struct lock_guard : non_copyable {
    protected:
        Lock& _lock;
    public:

        lock_guard(Lock& lock)
        : _lock(lock) {
            _lock.lock();
        }

        ~lock_guard() {
            _lock.unlock();
        }
    };

    template<typename Lock>
    lock_guard<Lock> lock(Lock& l) {
        return { l };
    }
}

#endif