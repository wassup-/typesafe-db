#include "condition.hpp"

namespace fp {

    condition::condition(mutex & mtx)
    : _impl(new impl::condition_impl(mtx.handle())) {
    }

    condition::condition(condition && c)
    : _impl(nullptr) {
        swap(*this, c);
    }

    condition::~condition() {
    }

    void condition::wait() {
        _impl->wait();
    }

    void condition::post() {
        _impl->post();
    }

    void condition::post_all() {
        _impl->post_all();
    }
}