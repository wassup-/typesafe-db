#include "../../../../include/core/impl/linux/thread_impl.hpp"
#include "../../../../include/core/thread.hpp"
#include "../../../../include/assert.hpp"

#include <pthread.h>    // for pthread_create, pthread_join, pthread_cancel
#include <utility>		// for std::move

namespace fp { namespace impl {

    namespace {

        void pthreadcheck(int code)
        { FP_ASSERT(0 == code, "pthread error"); }
    }

    void* thread_impl::run(void* arg) {
        static_cast<fp::thread*>(arg)->run();
        return nullptr;
    }

    thread_impl::thread_impl(fp::thread* th)
    : m_handle()
    { pthreadcheck(pthread_create(&m_handle, nullptr, &thread_impl::run, th)); }

    void thread_impl::wait()
    { pthread_join(m_handle, nullptr); }

    void thread_impl::terminate()
    { pthread_cancel(m_handle); }
} }