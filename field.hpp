#ifndef _FIELD_HPP
#define _FIELD_HPP

namespace fp {

    template<typename TDescriptor, int I> struct field {
        enum { index = I };
        typedef typename TDescriptor::template field<I>::type type;
        static char const * name;
    };
    template<typename TDescriptor, int I> char const * field<TDescriptor, I>::name = TDescriptor::template field<I>::name;
    
    template<typename TDescriptor, int I>
    char const * get_field_identifier() {
        return field<TDescriptor, I>::name;
    }
    template<typename TDescriptor, int I>
    char const * get_field_identifier(field<TDescriptor, I>) {
        return field<TDescriptor, I>::name;
    }
}

#endif