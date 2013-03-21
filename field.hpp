#ifndef _FIELD_HPP
#define _FIELD_HPP

namespace fp {

    template<typename TDescriptor, int I> struct field {
        enum { index = I };
    };
}

#endif