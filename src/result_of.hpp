#ifndef _RESULT_OF_HPP
#define _RESULT_OF_HPP

#include "type_traits.hpp"      // for Invoke
#include <type_traits>		// for std::result_of

namespace fp {

    namespace impl {
        template<typename>
        struct result_of;
        
        template<typename TRet, typename... TArg>
        struct result_of<TRet(*)(TArg...) > {
            using type = TRet;
        };

        template<typename TClass, typename TRet, typename... TArg>
        struct result_of<TRet(TClass::*)(TArg...)> {
            using type = TRet;
        };

        template<typename Fn, typename... Arg>
        struct result_of<Fn(Arg...)> {
            using type = Invoke < std::result_of < Fn(Arg...) >>;
        };
    }
    
    template<typename T>
    struct result_of : impl::result_of<T> { };
}

#endif