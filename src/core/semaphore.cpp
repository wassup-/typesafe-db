#include "../../include/core/semaphore.hpp"

namespace fp {

    semaphore::semaphore(int v, mode_e mode)
    : _impl(new impl::semaphore_impl(v, (shared == mode))) {
    }

    semaphore::~semaphore() {
    }

    void semaphore::wait() {
        _impl->wait();
    }

    void semaphore::post() {
        _impl->post();
    }

    bool semaphore::try_wait() {
        return _impl->try_wait();
    }

    int semaphore::value() {
        return _impl->value();
    }
}