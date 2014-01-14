#include "../../include/core/thread.hpp"
#include "../../include/unique_ptr.hpp"

namespace fp {

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
        using fp::run;
        run(_self);
    }
}