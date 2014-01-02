/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef UNIQUE_PTR_HPP_
#define UNIQUE_PTR_HPP_

#include "type_traits.hpp"      // for fp::Invoke

#include <memory>               // for std::unique_ptr
#include <type_traits>          // for std::is_array, std::remove_extent
#include <utility>              // for std::forward

namespace fp {

    namespace impl {

        template<typename T, typename... Args>
        inline std::unique_ptr<T> make_unique(std::true_type, Args&&... args) {
            static_assert(std::extent<T>::value == 0, "make_unique<T[N]>() is forbidden, please use make_unique<T[]>()");
            using U = Invoke<std::remove_extent<T>>;
            return std::unique_ptr<T>(new U[sizeof...(Args)] { std::forward<Args>(args)... });
        }

        template<typename T, typename... Args>
        inline std::unique_ptr<T> make_unique(std::false_type, Args&&... args) {
            return std::unique_ptr<T>(new T{ std::forward<Args>(args)... });
        }
    }

    template<typename T, typename... Args>
    inline std::unique_ptr<T> make_unique(Args&&... args) {
        return impl::make_unique(std::is_array<T>(), std::forward<Args>(args)...);
    }
}

#endif