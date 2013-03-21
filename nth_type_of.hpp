#ifndef _NTH_TYPE_OF_H
#define _NTH_TYPE_OF_H

namespace fp {
    template<int, typename...> struct nth_type_of;

    template<int I, typename H, typename... T> struct nth_type_of<I, H, T...> {
        typedef typename nth_type_of < I - 1, T...>::type type;
    };

    template<typename H, typename... T> struct nth_type_of < 0, H, T...> {
        typedef H type;
    };

    template<int, typename> struct nth_type_of_seq;

    template<int I, typename... Ts> struct nth_type_of_seq<I, type_seq<Ts...> > {
        typedef typename nth_type_of<I, Ts...>::type type;
    };

    template<typename... T> struct first_type_of {
        typedef typename nth_type_of < 0, T...>::type type;
    };

    template<typename... T> struct last_type_of {
        typedef typename nth_type_of<sizeof...(T) - 1, T...>::type type;
    };
}

#endif