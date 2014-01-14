/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SYSTEM_THREAD_HPP
#define SYSTEM_THREAD_HPP

#include "../config.hpp"
#include "non_copyable.hpp"
#include "runnable.hpp"
#include "../impl/functor_impl.hpp"

#if defined(FP_SYSTEM_LINUX)
#include "impl/linux/thread_impl.hpp"
#elif defined(FP_SYSTEM_WINDOWS)
#include "impl/windows/thread_impl.hpp"
#elif defined(FP_SYSTEM_MACOS)
#include "impl/macos/thread_impl.hpp"
#endif

#include <algorithm>    // for std::swap
#include <chrono>       // for std::chrono::*
#include <memory>       // for std::unique_ptr

namespace fp {

    class thread : non_copyable {
    public:
        template<typename Fn>
        thread(Fn);

        template<typename Fn, typename... Arg>
        thread(Fn, Arg&&...);

        template<typename C>
        thread(void(C::*)(), C*);

        template<typename C, typename... Arg>
        thread(void(C::*)(Arg...), C*, Arg...);

        ~thread();

        void start();

        void wait();

        void terminate();
    private:
        friend struct impl::thread_impl;
        std::unique_ptr<impl::thread_impl> _impl;
        const Runnable _self;

        void run();
    };

#include "thread.inl"
}

#endif