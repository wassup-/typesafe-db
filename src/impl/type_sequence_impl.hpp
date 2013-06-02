#ifndef _TYPE_SEQUENCE_IMPL_HPP
#define _TYPE_SEQUENCE_IMPL_HPP

namespace fp {
    template<typename...>
    struct type_seq;

    namespace impl {
        template<typename, typename...>
        struct extend_impl;

        template<typename... S, typename... E>
        struct extend_impl<type_seq<S...>, E...> {
            using type = type_seq<S..., E...>;
        };
    }
}

#endif