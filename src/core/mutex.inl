template<typename Rep, typename Period>
bool mutex::timed_lock(std::chrono::duration<Rep, Period> t) {
    return _impl->timed_lock(t);
}