/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "lock_guard.hpp"
#include "mutex.hpp"
#include "non_copyable.hpp"
#include "runnable.hpp"
#include "semaphore.hpp"
#include "../impl/functor_impl.hpp"

#include <cstddef>		// for std::size_t
#include <deque>		// for std::deque
#include <memory>       // for std::unique_ptr
#include <type_traits>  // for std::remove_reference
#include <vector>       // for std::vector

namespace fp {

    class thread;

    struct threadpool : non_copyable {
    public:
        enum class mode_e {
            wait = 0,
            terminate,
            finish
        };
    public:
        explicit threadpool(std::size_t, mode_e = mode_e::wait);
        ~threadpool();

        template<typename Fn> void push(Fn);
        template<typename C> void push(void(C::*)(), C*);
        template<typename Fn, typename... Arg> void push(Fn, Arg&& ...);
        template<typename C, typename... Arg> void push(void(C::*)(Arg...), C*, Arg...);

        mode_e mode() const;
        void set_mode(mode_e);

        std::size_t size() const;
        std::size_t remaining() const;
    private:
        static void* task_runner(void*);
    protected:
        using mutex_t = mutex;
        using semaphore_t = semaphore;

        std::vector<std::unique_ptr<thread>> _threads;
        std::deque<Runnable> _tasks;
        mutex_t _mutex;
        semaphore_t _semaphore;
        mode_e _mode;
        volatile bool _run;
        volatile bool _finish;

        Runnable pop();
    };

#include "threadpool.inl"
}

#endif