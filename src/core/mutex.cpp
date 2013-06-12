#include "../../include/core/mutex.hpp"

namespace fp {

    mutex::mutex()
    : _impl(new impl::mutex_impl()) {
    }

    mutex::mutex(mutex && mtx)
    : _impl(nullptr) {
        swap(*this, mtx);
    }

    void mutex::lock() {
        _impl->lock();
    }

    bool mutex::try_lock() {
        return _impl->try_lock();
    }

    void mutex::unlock() {
        _impl->unlock();
    }
}