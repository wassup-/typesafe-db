#ifndef _UNIQUE_VALUE_HPP
#define _UNIQUE_VALUE_HPP

namespace fp {
	template<typename, int> struct field;
    template<typename> struct unique_value;

    template<typename TDescriptor, int I> struct unique_value<field<TDescriptor, I> > {
		enum { index = I };
	};
}

#endif