#ifndef CONDITION_IMPL_HPP
#define CONDITION_IMPL_HPP

#include "../../mutex.hpp"

#include <pthread.h>            // for pthread_cond_t, pthread_mutex_t
#include <chrono>               // for std::chrono::*

namespace fp {
    namespace impl {

        struct condition_impl {
        protected:
            pthread_cond_t m_handle;
            pthread_mutex_t & m_mutex;
        public:

            condition_impl(pthread_mutex_t &);
            ~condition_impl();

            void wait();

            void post();
            void post_all();

            template<typename Rep, typename Period>
            bool timed_wait(std::chrono::duration<Rep, Period> t) {
                unsigned long long const tm = std::chrono::duration_cast<std::chrono::microseconds>(t).count();
                timespec ts;
                ts.tv_sec = (tm / 1000000);
                ts.tv_nsec = (tm % 1000000);
                return (pthread_cond_timedwait(&m_handle, &m_mutex, &ts) == 0);
            }
        };
    }
}

#endif