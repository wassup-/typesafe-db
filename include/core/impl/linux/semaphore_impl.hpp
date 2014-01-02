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
                unsigned long long const tm = std::chrono::duration_cast<std::chrono::microseconds>(t).count();
                timespec ts;
                ts.tv_sec = (tm / 1000000000);
                ts.tv_nsec = (tm % 1000000000);
                return (sem_timedwait(&m_handle, &ts) == 0);
            }

            int value();
        };
    }
}

#endif