#include "../../include/core/threadpool.hpp"
#include "../../include/core/thread.hpp"

#include <chrono>       // for std::chrono::*
#include <iostream>

namespace fp {

    threadpool::threadpool(std::size_t sz, mode_e mode)
    : _size(sz), _threads(new thread*[sz]), _mode(mode), _run(true), _finish(false), _mutex(), _semaphore(0), _tasks() {
        for(std::size_t i = 0; i < _size; ++i) {
            _threads[i] = new thread(&threadpool::task_runner, this);
            _threads[i]->start();
        }
    }

    threadpool::~threadpool() {
        if(finish == _mode) {
            _finish = true;
        } else {
            _run = false;
        }
        for(std::size_t i = 0; i < _size; ++i) {
            const std::unique_ptr<thread> th(_threads[i]);
            if (terminate == _mode) {
                th->terminate();
            } else {
                th->wait();
            }
        }
        delete[] _threads;
        for(std::deque<impl::func_impl*>::iterator it = _tasks.begin(); it != _tasks.end(); ++it) {
            delete *it;
        }
    }

    std::unique_ptr<impl::func_impl> threadpool::pop() {
        if (!_run) {
            return nullptr;
        }
        while (!_semaphore.timed_wait(std::chrono::milliseconds(500))) {
            if (_finish && _tasks.empty()) {
                return nullptr;
            } else {
                continue;
            }
        }
        impl::func_impl* ret = nullptr;
        {
            lock_guard<mutex_t> l(_mutex);
            ret = _tasks.front();
            _tasks.pop_front();
        }
        return std::unique_ptr<impl::func_impl>(ret);
    }

    std::size_t threadpool::size() const {
        return _size;
    }

    std::size_t threadpool::remaining() const {
        return _tasks.size();
    }

    void * threadpool::task_runner(void * arg) {
        threadpool* pool = static_cast<threadpool*>(arg);
        while (true) {
            const std::unique_ptr<impl::func_impl> fn = pool->pop();
            if (!fn) {
                break;
            }
            fn->run();
        }
        return nullptr;
    }
}