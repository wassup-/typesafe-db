#ifndef _ARG_PLACEHOLDERS_H
#define _ARG_PLACEHOLDERS_H

namespace fp {
	template<int> struct arg { };

	template<int L, int R> bool operator==(arg<L> const &, arg<R> const &) {
		return false;
	}
	template<int I> bool operator==(arg<I> const &, arg<I> const &) {
		return true;
	}

	namespace placeholders {
		static arg<1> const _1;
		static arg<2> const _2;
		static arg<3> const _3;
		static arg<4> const _4;
		static arg<5> const _5;
		static arg<6> const _6;
		static arg<7> const _7;
		static arg<8> const _8;
		static arg<9> const _9;
	}
}

#endif