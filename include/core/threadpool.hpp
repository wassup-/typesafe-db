#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "lock_guard.hpp"
#include "mutex.hpp"
#include "non_copyable.hpp"
#include "semaphore.hpp"
#include "../impl/functor_impl.hpp"

#include <cstddef>		// for std::size_t
#include <deque>		// for std::deque
#include <memory>               // for std::unique_ptr
#include <type_traits>          // for std::remove_reference

namespace fp {
    struct thread;

    struct threadpool : non_copyable {
    public:

        enum mode_e {
            wait = 0,
            terminate,
            finish
        };
    private:
        static void * task_runner(void *);
        using mutex_t = mutex;
        using semaphore_t = semaphore;
    protected:
        std::size_t const _size;
        thread ** _threads;
        mode_e _mode;
        volatile bool _run;
        volatile bool _finish;
        mutex_t _mutex;
        semaphore_t _semaphore;
        std::deque<impl::func_impl*> _tasks;

        std::unique_ptr<impl::func_impl> pop();
    public:
        explicit threadpool(std::size_t, mode_e = wait);
        ~threadpool();

        template<typename Fn> void push(Fn);
        template<typename C> void push(void(C::*)(), C *);
        template<typename Fn, typename... Arg> void push(Fn, Arg && ...);
        template<typename C, typename... Arg> void push(void(C::*)(Arg...), C *, Arg...);

        mode_e mode() const;
        void set_mode(mode_e);

        std::size_t size() const;
        std::size_t remaining() const;
    };

#include "threadpool.inl"
}

#endif