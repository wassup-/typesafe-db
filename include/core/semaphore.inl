template<typename Rep, typename Period>
bool semaphore::timed_wait(std::chrono::duration<Rep, Period> t) {
    return _impl->timed_wait(t);
}