#include "../../include/core/threadpool.hpp"
#include "../../include/core/thread.hpp"
#include "../../include/unique_ptr.hpp"
#include "../../include/assert.hpp"

#include <algorithm>    // for std::for_each, std::generate
#include <chrono>       // for std::chrono::*

namespace fp {

    struct threadpool;

    namespace {

        struct thread_generator {
            using thread_fn = void*(*)(void*);

            thread_generator(thread_fn fn, threadpool* pool)
            : fn_{fn}, pool_{pool}
            { FP_ASSERT(fn, "fn == null"); FP_ASSERT(pool, "threadpool == null"); }

            std::unique_ptr<thread> operator()() const
            { return fp::make_unique<thread>(fn_, static_cast<void*>(pool_)); }
        private:
            thread_fn fn_;
            threadpool* const pool_;
        };

        struct thread_starter {
            void operator()(const std::unique_ptr<thread>& th) const
            { FP_ASSERT(th, "thread == null"); th->start(); }
        };

        struct thread_waiter {
            void operator()(const std::unique_ptr<thread>& th) const
            { FP_ASSERT(th, "thread == null"); th->wait(); }
        };

        struct thread_terminater {
            void operator()(const std::unique_ptr<thread>& th) const
            { FP_ASSERT(th, "thread == null"); th->terminate(); }
        };
    }

    threadpool::threadpool(std::size_t sz, mode_e mode)
    : _threads(), _tasks(), _mutex(), _semaphore(0), _mode(mode), _run(true), _finish(false) {
        using std::begin; using std::end; using std::swap;
        // initialize a temporary container (in case something throws)
        std::vector<std::unique_ptr<thread>> threads;
        // allocate storage for our threads
        threads.resize(sz);
        // generate our threads
        std::generate(begin(threads), end(threads), thread_generator{&threadpool::task_runner, this});
        FP_ASSERT(threads.size() == sz, "vector.size != size");
        // start our threads
        std::for_each(begin(threads), end(threads), thread_starter{});
        FP_ASSERT(threads.size() == sz, "vector.size != size");
        // swap our containers
        swap(_threads, threads);
        FP_ASSERT(_threads.size() == sz, "vector.size != size");
    }

    threadpool::~threadpool() {
        using std::begin; using std::end;
        // give our threads a chance to finish on their own
        switch(_mode) {
            case mode_e::finish:
                _finish = true;
                break;
            default:
                _run = false;
                break;
        }
        // terminate our threads (forcefully)
        switch(_mode) {
            case mode_e::terminate:
                std::for_each(begin(_threads), end(_threads), thread_terminater{});
                break;
            default:
                std::for_each(begin(_threads), end(_threads), thread_waiter{});
                break;
        }
    }

    Runnable threadpool::pop() {
        if(!_run) {
            return nullptr;
        }
        // wait for an available task
        while (!_semaphore.timed_wait(std::chrono::milliseconds(500))) {
            if (_finish && _tasks.empty()) {
                return nullptr;
            }
        }
        FP_ASSERT(!_tasks.empty(), "tasks.empty() = true");
        // extract the first available task
        Runnable ret {};
        {
            lock_guard<mutex_t> l(_mutex);
            using std::swap;
            swap(ret, _tasks.front());
            _tasks.pop_front();
        }
        return ret;
    }

    std::size_t threadpool::size() const {
        return _threads.size();
    }

    std::size_t threadpool::remaining() const {
        return _tasks.size();
    }

    void* threadpool::task_runner(void* arg) {
        using fp::run;
        threadpool* const pool = static_cast<threadpool*>(arg);
        while (true) {
            // extract a task from the pool
            Runnable fn = pool->pop();
            if (!fn) { break; }
            // run the extracted task
            run(fn);
        }
        return nullptr;
    }
}