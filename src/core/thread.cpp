#include "../../include/core/thread.hpp"

namespace fp {

    thread::thread(thread&& th)
    : _impl(nullptr), _fn(nullptr) {
        swap(*this, th);
    }

    thread::~thread() {
        if (_impl) {
            _impl->wait();
        }
    }

    void thread::start() {
        if (_impl) {
            _impl->wait();
        }
        _impl.reset(new impl::thread_impl(this));
    }

    void thread::wait() {
        if (_impl) {
            _impl->wait();
            _impl.reset(nullptr);
        }
    }

    void thread::terminate() {
        if (_impl) {
            _impl->terminate();
            _impl.reset(nullptr);
        }
    }

    void thread::run() {
        _fn->run();
    }
}