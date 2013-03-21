#ifndef _PRIMARY_KEY_HPP
#define _PRIMARY_KEY_HPP

namespace fp {
	template<typename, int> struct field;
    template<typename> struct primary_key;

    template<typename TDescriptor, int I> struct primary_key<field<TDescriptor, I> > {
        enum { index = I };
    };
}

#endif