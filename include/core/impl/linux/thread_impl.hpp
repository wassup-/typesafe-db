/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SYSTEM_THREAD_IMPL_HPP
#define SYSTEM_THREAD_IMPL_HPP

#include <pthread.h>            // for pthread_t

namespace fp {
    struct thread;

    namespace impl {

        struct thread_impl {
        protected:
            pthread_t m_handle;

            static void * run(void *);
        public:
            thread_impl(fp::thread *);
            thread_impl(thread_impl &&);

            void wait();
            void terminate();
        };
    }
}

#endif