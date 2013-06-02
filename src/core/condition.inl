template<typename Rep, typename Period>
bool condition::timed_wait(std::chrono::duration<Rep, Period> t) {
    return _impl->timed_wait(t);
}