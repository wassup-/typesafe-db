/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef MUTEX_IMPL_HPP
#define MUTEX_IMPL_HPP

#include <chrono>       // for std::chrono::*
#include <pthread.h>    // for pthread_mutex_t

namespace fp {
    namespace impl {

        struct mutex_impl {
        public:
            typedef mutex_impl this_type;
            typedef pthread_mutex_t native_type;
        protected:
            native_type m_handle;
        public:

            mutex_impl();
            ~mutex_impl();

            void lock();

            template<typename Rep, typename Period>
            bool timed_lock(std::chrono::duration<Rep, Period> t) {
                unsigned long long const tm = std::chrono::duration_cast<std::chrono::nanoseconds>(t).count();
                timespec ts;
                ts.tv_sec = (tm / 1000000000);
                ts.tv_nsec = (tm % 1000000000);
                return (pthread_mutex_timedlock(&m_handle, &ts) == 0);
            }

            bool try_lock();

            void unlock();

            native_type & handle() {
                return m_handle;
            }
        };
    }
}

#endif