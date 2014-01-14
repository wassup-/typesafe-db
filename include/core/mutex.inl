/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

template<typename Rep, typename Period>
bool mutex::timed_lock(std::chrono::duration<Rep, Period> t) {
    return _impl->timed_lock(t);
}