/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SEMAPHORE_IMPL_HPP
#define SEMAPHORE_IMPL_HPP

#include <semaphore.h>          // for sem_t
#include <chrono>               // for std::chrono::*

namespace fp {
    namespace impl {

        struct semaphore_impl {
        protected:
            sem_t m_handle;
        public:

            semaphore_impl(int, bool);
            ~semaphore_impl();

            void wait();

            void post();

            bool try_wait();

            template<typename Rep, typename Period>
            bool timed_wait(std::chrono::duration<Rep, Period> t) {
                timespec ts;
                const auto secs = std::chrono::duration_cast<std::chrono::seconds>(t);
                const auto nsecs = std::chrono::duration_cast<std::chrono::nanoseconds>(t - secs);
                ts.tv_sec = secs.count();
                ts.tv_nsec = nsecs.count();
                return (sem_timedwait(&m_handle, &ts) == 0);
            }

            int value();
        };
    }
}

#endif