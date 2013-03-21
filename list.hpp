/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _BIND_LIST_H
#define _BIND_LIST_H

#include "placeholders.hpp"

namespace fp {
	template<typename> struct type { };
	struct unspecified { };

	template<typename, typename, typename> struct bind_t;

	template<typename R, typename F> struct result_traits {
		typedef R type;
	};

	template<typename F> struct result_traits<unspecified, F> {
		typedef typename F::result_type type;
	};

	template<typename T> struct value {
	private:
		T m_value;
	public:
		value(T const & v) : m_value(v) { }

		T & get() { return m_value; }
		T const & get() const { return m_value; }

		bool operator==(value const & v) const {
			return m_value == v.m_value;
		}
	};

	struct list0 {
	private:
	public:
		list0() { }


		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call();
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call();
		}
	};

	template<typename A1> struct list1 {
	private:
		A1 m_a1;
	public:
		list1(A1 a1) : m_a1(a1) { }

		A1 operator[](arg<1>) const { return m_a1; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1]);
		}
	};

	template<typename A1, typename A2> struct list2 {
	private:
		A1 m_a1;
		A2 m_a2;
	public:
		list2(A1 a1, A2 a2) : m_a1(a1), m_a2(a2) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2]);
		}
	};

	template<typename A1, typename A2, typename A3> struct list3 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
	public:
		list3(A1 a1, A2 a2, A3 a3) : m_a1(a1), m_a2(a2), m_a3(a3) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4> struct list4 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
	public:
		list4(A1 a1, A2 a2, A3 a3, A4 a4) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5> struct list5 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
	public:
		list5(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6> struct list6 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
	public:
		list6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7> struct list7 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
	public:
		list7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8> struct list8 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
	public:
		list8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9> struct list9 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
	public:
		list9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10> struct list10 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
	public:
		list10(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11> struct list11 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
	public:
		list11(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12> struct list12 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
	public:
		list12(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13> struct list13 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
	public:
		list13(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14> struct list14 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
	public:
		list14(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15> struct list15 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
	public:
		list15(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16> struct list16 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
	public:
		list16(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17> struct list17 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
	public:
		list17(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18> struct list18 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
	public:
		list18(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19> struct list19 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
	public:
		list19(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20> struct list20 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
	public:
		list20(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21> struct list21 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
	public:
		list21(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22> struct list22 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
	public:
		list22(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23> struct list23 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
	public:
		list23(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24> struct list24 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
	public:
		list24(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25> struct list25 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
	public:
		list25(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26> struct list26 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
	public:
		list26(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27> struct list27 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
	public:
		list27(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28> struct list28 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
	public:
		list28(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29> struct list29 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
	public:
		list29(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30> struct list30 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
	public:
		list30(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31> struct list31 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
	public:
		list31(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32> struct list32 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
	public:
		list32(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33> struct list33 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
	public:
		list33(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34> struct list34 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
	public:
		list34(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35> struct list35 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
	public:
		list35(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36> struct list36 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
	public:
		list36(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37> struct list37 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
	public:
		list37(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38> struct list38 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
	public:
		list38(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39> struct list39 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
	public:
		list39(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40> struct list40 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
	public:
		list40(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41> struct list41 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
	public:
		list41(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42> struct list42 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
	public:
		list42(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43> struct list43 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
	public:
		list43(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44> struct list44 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
	public:
		list44(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45> struct list45 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
	public:
		list45(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46> struct list46 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
	public:
		list46(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47> struct list47 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
	public:
		list47(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48> struct list48 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
	public:
		list48(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49> struct list49 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
	public:
		list49(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50> struct list50 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
	public:
		list50(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51> struct list51 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
	public:
		list51(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52> struct list52 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
	public:
		list52(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53> struct list53 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
	public:
		list53(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54> struct list54 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
	public:
		list54(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55> struct list55 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
	public:
		list55(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56> struct list56 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
	public:
		list56(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57> struct list57 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
	public:
		list57(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58> struct list58 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
	public:
		list58(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59> struct list59 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
	public:
		list59(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59, typename A60> struct list60 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
		A60 m_a60;
	public:
		list60(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59, A60 a60) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59), m_a60(a60) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }
		A60 operator[](arg<60>) const { return m_a60; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59, typename A60, typename A61> struct list61 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
		A60 m_a60;
		A61 m_a61;
	public:
		list61(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59, A60 a60, A61 a61) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59), m_a60(a60), m_a61(a61) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }
		A60 operator[](arg<60>) const { return m_a60; }
		A61 operator[](arg<61>) const { return m_a61; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59, typename A60, typename A61, typename A62> struct list62 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
		A60 m_a60;
		A61 m_a61;
		A62 m_a62;
	public:
		list62(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59, A60 a60, A61 a61, A62 a62) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59), m_a60(a60), m_a61(a61), m_a62(a62) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }
		A60 operator[](arg<60>) const { return m_a60; }
		A61 operator[](arg<61>) const { return m_a61; }
		A62 operator[](arg<62>) const { return m_a62; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59, typename A60, typename A61, typename A62, typename A63> struct list63 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
		A60 m_a60;
		A61 m_a61;
		A62 m_a62;
		A63 m_a63;
	public:
		list63(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59, A60 a60, A61 a61, A62 a62, A63 a63) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59), m_a60(a60), m_a61(a61), m_a62(a62), m_a63(a63) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }
		A60 operator[](arg<60>) const { return m_a60; }
		A61 operator[](arg<61>) const { return m_a61; }
		A62 operator[](arg<62>) const { return m_a62; }
		A63 operator[](arg<63>) const { return m_a63; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62], a[m_a63]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62], a[m_a63]);
		}
	};

	template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49, typename A50, typename A51, typename A52, typename A53, typename A54, typename A55, typename A56, typename A57, typename A58, typename A59, typename A60, typename A61, typename A62, typename A63, typename A64> struct list64 {
	private:
		A1 m_a1;
		A2 m_a2;
		A3 m_a3;
		A4 m_a4;
		A5 m_a5;
		A6 m_a6;
		A7 m_a7;
		A8 m_a8;
		A9 m_a9;
		A10 m_a10;
		A11 m_a11;
		A12 m_a12;
		A13 m_a13;
		A14 m_a14;
		A15 m_a15;
		A16 m_a16;
		A17 m_a17;
		A18 m_a18;
		A19 m_a19;
		A20 m_a20;
		A21 m_a21;
		A22 m_a22;
		A23 m_a23;
		A24 m_a24;
		A25 m_a25;
		A26 m_a26;
		A27 m_a27;
		A28 m_a28;
		A29 m_a29;
		A30 m_a30;
		A31 m_a31;
		A32 m_a32;
		A33 m_a33;
		A34 m_a34;
		A35 m_a35;
		A36 m_a36;
		A37 m_a37;
		A38 m_a38;
		A39 m_a39;
		A40 m_a40;
		A41 m_a41;
		A42 m_a42;
		A43 m_a43;
		A44 m_a44;
		A45 m_a45;
		A46 m_a46;
		A47 m_a47;
		A48 m_a48;
		A49 m_a49;
		A50 m_a50;
		A51 m_a51;
		A52 m_a52;
		A53 m_a53;
		A54 m_a54;
		A55 m_a55;
		A56 m_a56;
		A57 m_a57;
		A58 m_a58;
		A59 m_a59;
		A60 m_a60;
		A61 m_a61;
		A62 m_a62;
		A63 m_a63;
		A64 m_a64;
	public:
		list64(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49, A50 a50, A51 a51, A52 a52, A53 a53, A54 a54, A55 a55, A56 a56, A57 a57, A58 a58, A59 a59, A60 a60, A61 a61, A62 a62, A63 a63, A64 a64) : m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5), m_a6(a6), m_a7(a7), m_a8(a8), m_a9(a9), m_a10(a10), m_a11(a11), m_a12(a12), m_a13(a13), m_a14(a14), m_a15(a15), m_a16(a16), m_a17(a17), m_a18(a18), m_a19(a19), m_a20(a20), m_a21(a21), m_a22(a22), m_a23(a23), m_a24(a24), m_a25(a25), m_a26(a26), m_a27(a27), m_a28(a28), m_a29(a29), m_a30(a30), m_a31(a31), m_a32(a32), m_a33(a33), m_a34(a34), m_a35(a35), m_a36(a36), m_a37(a37), m_a38(a38), m_a39(a39), m_a40(a40), m_a41(a41), m_a42(a42), m_a43(a43), m_a44(a44), m_a45(a45), m_a46(a46), m_a47(a47), m_a48(a48), m_a49(a49), m_a50(a50), m_a51(a51), m_a52(a52), m_a53(a53), m_a54(a54), m_a55(a55), m_a56(a56), m_a57(a57), m_a58(a58), m_a59(a59), m_a60(a60), m_a61(a61), m_a62(a62), m_a63(a63), m_a64(a64) { }

		A1 operator[](arg<1>) const { return m_a1; }
		A2 operator[](arg<2>) const { return m_a2; }
		A3 operator[](arg<3>) const { return m_a3; }
		A4 operator[](arg<4>) const { return m_a4; }
		A5 operator[](arg<5>) const { return m_a5; }
		A6 operator[](arg<6>) const { return m_a6; }
		A7 operator[](arg<7>) const { return m_a7; }
		A8 operator[](arg<8>) const { return m_a8; }
		A9 operator[](arg<9>) const { return m_a9; }
		A10 operator[](arg<10>) const { return m_a10; }
		A11 operator[](arg<11>) const { return m_a11; }
		A12 operator[](arg<12>) const { return m_a12; }
		A13 operator[](arg<13>) const { return m_a13; }
		A14 operator[](arg<14>) const { return m_a14; }
		A15 operator[](arg<15>) const { return m_a15; }
		A16 operator[](arg<16>) const { return m_a16; }
		A17 operator[](arg<17>) const { return m_a17; }
		A18 operator[](arg<18>) const { return m_a18; }
		A19 operator[](arg<19>) const { return m_a19; }
		A20 operator[](arg<20>) const { return m_a20; }
		A21 operator[](arg<21>) const { return m_a21; }
		A22 operator[](arg<22>) const { return m_a22; }
		A23 operator[](arg<23>) const { return m_a23; }
		A24 operator[](arg<24>) const { return m_a24; }
		A25 operator[](arg<25>) const { return m_a25; }
		A26 operator[](arg<26>) const { return m_a26; }
		A27 operator[](arg<27>) const { return m_a27; }
		A28 operator[](arg<28>) const { return m_a28; }
		A29 operator[](arg<29>) const { return m_a29; }
		A30 operator[](arg<30>) const { return m_a30; }
		A31 operator[](arg<31>) const { return m_a31; }
		A32 operator[](arg<32>) const { return m_a32; }
		A33 operator[](arg<33>) const { return m_a33; }
		A34 operator[](arg<34>) const { return m_a34; }
		A35 operator[](arg<35>) const { return m_a35; }
		A36 operator[](arg<36>) const { return m_a36; }
		A37 operator[](arg<37>) const { return m_a37; }
		A38 operator[](arg<38>) const { return m_a38; }
		A39 operator[](arg<39>) const { return m_a39; }
		A40 operator[](arg<40>) const { return m_a40; }
		A41 operator[](arg<41>) const { return m_a41; }
		A42 operator[](arg<42>) const { return m_a42; }
		A43 operator[](arg<43>) const { return m_a43; }
		A44 operator[](arg<44>) const { return m_a44; }
		A45 operator[](arg<45>) const { return m_a45; }
		A46 operator[](arg<46>) const { return m_a46; }
		A47 operator[](arg<47>) const { return m_a47; }
		A48 operator[](arg<48>) const { return m_a48; }
		A49 operator[](arg<49>) const { return m_a49; }
		A50 operator[](arg<50>) const { return m_a50; }
		A51 operator[](arg<51>) const { return m_a51; }
		A52 operator[](arg<52>) const { return m_a52; }
		A53 operator[](arg<53>) const { return m_a53; }
		A54 operator[](arg<54>) const { return m_a54; }
		A55 operator[](arg<55>) const { return m_a55; }
		A56 operator[](arg<56>) const { return m_a56; }
		A57 operator[](arg<57>) const { return m_a57; }
		A58 operator[](arg<58>) const { return m_a58; }
		A59 operator[](arg<59>) const { return m_a59; }
		A60 operator[](arg<60>) const { return m_a60; }
		A61 operator[](arg<61>) const { return m_a61; }
		A62 operator[](arg<62>) const { return m_a62; }
		A63 operator[](arg<63>) const { return m_a63; }
		A64 operator[](arg<64>) const { return m_a64; }

		template<typename R, typename F, typename L> typename result_traits<R, F>::type operator[](bind_t<R,F,L> const & b) const { return b.eval(*this); }

		template<typename R, typename F, typename A> R operator()(type<R>, F const & f, A const & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62], a[m_a63], a[m_a64]);
		}
		template<typename F, typename A> void operator()(type<void>, F const & f, A & a) const {
			return f.call(a[m_a1], a[m_a2], a[m_a3], a[m_a4], a[m_a5], a[m_a6], a[m_a7], a[m_a8], a[m_a9], a[m_a10], a[m_a11], a[m_a12], a[m_a13], a[m_a14], a[m_a15], a[m_a16], a[m_a17], a[m_a18], a[m_a19], a[m_a20], a[m_a21], a[m_a22], a[m_a23], a[m_a24], a[m_a25], a[m_a26], a[m_a27], a[m_a28], a[m_a29], a[m_a30], a[m_a31], a[m_a32], a[m_a33], a[m_a34], a[m_a35], a[m_a36], a[m_a37], a[m_a38], a[m_a39], a[m_a40], a[m_a41], a[m_a42], a[m_a43], a[m_a44], a[m_a45], a[m_a46], a[m_a47], a[m_a48], a[m_a49], a[m_a50], a[m_a51], a[m_a52], a[m_a53], a[m_a54], a[m_a55], a[m_a56], a[m_a57], a[m_a58], a[m_a59], a[m_a60], a[m_a61], a[m_a62], a[m_a63], a[m_a64]);
		}
	};
}

#endif