#include "../../../../include/core/impl/linux/thread_impl.hpp"
#include "../../../../include/core/thread.hpp"

#include <cassert>		// for assert
#include <pthread.h>            // for pthread_create, pthread_join, pthread_cancel
#include <utility>		// for std::move

namespace fp {
    namespace impl {

        namespace {

            void pthreadcheck(int code) {
                assert(0 == code);
            }
        }

        void * thread_impl::run(void * arg) {
            fp::thread * th = static_cast<fp::thread *> (arg);
            th->run();
            return nullptr;
        }

        thread_impl::thread_impl(fp::thread * th) : m_handle() {
            pthreadcheck(pthread_create(&m_handle, nullptr, &thread_impl::run, th));
        }

        thread_impl::thread_impl(thread_impl && impl) : m_handle(std::move(impl.m_handle)) {
        }

        void thread_impl::wait() {
            pthread_join(m_handle, nullptr);
        }

        void thread_impl::terminate() {
            pthread_cancel(m_handle);
        }
    }
}