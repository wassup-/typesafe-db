#include "mutex_impl.hpp"

namespace fp {
    namespace impl {

        mutex_impl::mutex_impl() : m_handle() {
            pthread_mutex_init(&m_handle, 0);
        }

        mutex_impl::~mutex_impl() {
            pthread_mutex_destroy(&m_handle);
        }

        void mutex_impl::lock() {
            pthread_mutex_lock(&m_handle);
        }

        bool mutex_impl::try_lock() {
            return (0 == pthread_mutex_trylock(&m_handle));
        }

        void mutex_impl::unlock() {
            pthread_mutex_unlock(&m_handle);
        }
    }
}