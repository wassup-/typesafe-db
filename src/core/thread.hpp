#ifndef SYSTEM_THREAD_HPP
#define SYSTEM_THREAD_HPP

#include "../config.hpp"
#include "non_copyable.hpp"
#include "../impl/functor_impl.hpp"

#if defined(FP_SYSTEM_LINUX)
#include "impl/linux/thread_impl.hpp"
#elif defined(FP_SYSTEM_WINDOWS)
#include "impl/windows/thread_impl.hpp"
#elif defined(FP_SYSTEM_MACOS)
#include "impl/macos/thread_impl.hpp"
#endif

#include <algorithm>    // for std::swap
#include <chrono>       // for std::chrono::*
#include <memory>       // for std::unique_ptr

namespace fp {

    struct thread : non_copyable {
    protected:
        friend struct impl::thread_impl;
        std::unique_ptr<impl::thread_impl> _impl;
        std::unique_ptr<impl::func_impl> _fn;

        void run();
    public:
        template<typename Fn > thread(Fn);
        template<typename Fn, typename... Arg > thread(Fn, Arg && ...);

        template<typename C > thread(void(C::*)(), C *);
        template<typename C, typename... Arg > thread(void(C::*)(Arg...), C *, Arg...);

        thread(thread &&);

        ~thread();

        friend void swap(thread & l, thread & r) {
            using std::swap;
            swap(l._impl, r._impl);
            swap(l._fn, r._fn);
        }

        void start();

        void wait();

        void terminate();
    };

#include "thread.inl"

    namespace this_thread {

        template<typename Clock, typename Duration>
        inline void sleep_until(std::chrono::time_point<Clock, Duration> const & t) {
            sleep_for(t - Clock::now());
        }

        template<typename Rep, typename Period>
        inline void sleep_for(std::chrono::duration<Rep, Period> const & t) {
            std::chrono::seconds const secs = std::chrono::duration_cast<std::chrono::seconds > (t);
            std::chrono::nanoseconds const nsecs = std::chrono::duration_cast<std::chrono::nanoseconds > (t - secs);
            timespec ts = {secs.count(), nsecs.count()};
            while ((ts.tv_sec + ts.tv_nsec) > 0) {
                timespec remaining = {0, 0};
                if (0 != ::nanosleep(&ts, &remaining)) {
                    break;
                }
                ts.tv_sec = remaining.tv_sec;
                ts.tv_nsec = remaining.tv_nsec;
            }
        }
    }
}

#endif