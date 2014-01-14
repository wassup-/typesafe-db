/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include "../config.hpp"
#include "non_copyable.hpp"

#if defined(FP_SYSTEM_WINDOWS)
#include "impl/windows/semaphore_impl.hpp"
#elif defined(FP_SYSTEM_LINUX)
#include "impl/linux/semaphore_impl.hpp"
#endif

#include <algorithm>    // for std::swap
#include <chrono>       // for std::chrono::*
#include <memory>       // for std::unique_ptr

namespace fp {

    struct semaphore : non_copyable {
    public:
        using this_type = semaphore;

        enum mode_e {
            non_shared,
            shared,
        };
    protected:
        std::unique_ptr<impl::semaphore_impl> _impl;
    public:
        explicit semaphore(int = 0, mode_e = non_shared);

        friend void swap(semaphore& l, semaphore& r) {
            using std::swap;
            swap(l._impl, r._impl);
        }

        void wait();
        bool try_wait();
        
        template<typename Rep, typename Period>
        bool timed_wait(std::chrono::duration<Rep, Period>);

        void post();

        int value();
    };

#include "semaphore.inl"
}

#endif