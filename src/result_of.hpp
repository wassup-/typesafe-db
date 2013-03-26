#ifndef _RESULT_OF_HPP
#define _RESULT_OF_HPP

#include <type_traits>		// for std::result_of

namespace fp {

    template<typename T> struct result_of {
        typedef typename T::type type;
    };

    template<typename TRet, typename... TArg> struct result_of<TRet(*)(TArg...) > {
        typedef TRet type;
    };

    template<typename TClass, typename TRet, typename... TArg> struct result_of<TRet(TClass::*)(TArg...)> {
        typedef TRet type;
    };

    template<typename Fn, typename... Arg> struct result_of<Fn(Arg...)> {
        typedef typename std::result_of < Fn(Arg...)>::type type;
    };
}

#endif