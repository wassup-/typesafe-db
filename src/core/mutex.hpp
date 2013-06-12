#ifndef MUTEX_HPP
#define MUTEX_HPP

#include "../config.hpp"
#include "non_copyable.hpp"

#if defined(FP_SYSTEM_WINDOWS)
#include "impl/windows/mutex_impl.hpp"
#elif defined(FP_SYSTEM_LINUX)
#include "impl/linux/mutex_impl.hpp"
#endif

#include <chrono>       // for std::chrono::*
#include <memory>       // for std::unique_ptr
#include <utility>      // for std::swap

namespace fp {

    struct mutex : non_copyable {
    public:
        using this_type = mutex;
        using native_type = impl::mutex_impl::native_type;
    protected:
        std::unique_ptr<impl::mutex_impl> _impl;
    public:
        mutex();
        mutex(mutex &&);

        friend void swap(mutex & l, mutex & r) {
            using std::swap;
            swap(l._impl, r._impl);
        }

        void lock();
        bool try_lock();
        
        template<typename Rep, typename Period>
        bool timed_lock(std::chrono::duration<Rep, Period>);

        void unlock();

        native_type & handle() {
            return _impl->handle();
        }
    };

#include "mutex.inl"
}

#endif