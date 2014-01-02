/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "../config.hpp"
#include "mutex.hpp"
#include "non_copyable.hpp"

#if defined(FP_SYSTEM_WINDOWS)
#include "impl/windows/condition_impl.hpp"
#elif defined(FP_SYSTEM_LINUX)
#include "impl/linux/condition_impl.hpp"
#endif

#include <algorithm>    // for std::swap
#include <chrono>       // for std::chrono::*
#include <memory>       // for std::unique_ptr

namespace fp {

    struct condition : non_copyable {
    public:
        using this_type = condition;
    protected:
        std::unique_ptr<impl::condition_impl> _impl;
    public:
        condition(mutex&);
        condition(condition&&);
        ~condition();

        friend void swap(condition& l, condition& r) {
            using std::swap;
            swap(l._impl, r._impl);
        }

        void wait();
        
        template<typename Rep, typename Period>
        bool timed_wait(std::chrono::duration<Rep, Period>);

        void post();
        void post_all();
    };

#include "condition.inl"
}

#endif