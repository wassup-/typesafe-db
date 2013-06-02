#include "condition_impl.hpp"

namespace fp {
    namespace impl {

        condition_impl::condition_impl(pthread_mutex_t & mtx) : m_handle(), m_mutex(mtx) {
            pthread_cond_init(&m_handle, 0);
        }

        condition_impl::~condition_impl() {
            pthread_cond_destroy(&m_handle);
        }

        void condition_impl::wait() {
            pthread_cond_wait(&m_handle, &m_mutex);
        }

        void condition_impl::post() {
            pthread_cond_signal(&m_handle);
        }

        void condition_impl::post_all() {
            pthread_cond_broadcast(&m_handle);
        }
    }
}