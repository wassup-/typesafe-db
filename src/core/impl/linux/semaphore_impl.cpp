#include "semaphore_impl.hpp"

namespace fp {
    namespace impl {

        semaphore_impl::semaphore_impl(int v, bool s) : m_handle() {
            sem_init(&m_handle, ((s) ? 1 : 0), v);
        }

        semaphore_impl::~semaphore_impl() {
            sem_destroy(&m_handle);
        }

        void semaphore_impl::wait() {
            sem_wait(&m_handle);
        }

        void semaphore_impl::post() {
            sem_post(&m_handle);
        }

        bool semaphore_impl::try_wait() {
            return (0 == sem_trywait(&m_handle));
        }

        int semaphore_impl::value() {
            int ret = 0;
            sem_getvalue(&m_handle, &ret);
            return ret;
        }
    }
}