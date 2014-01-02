/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

template<typename TType>
struct has_member {
protected:
	struct yes { char _unused; };
	struct no { yes _unused[2]; };

	struct BaseMixin {
		void operator()() { }
	};

	struct Base : TType, BaseMixin { };

	template<typename T, T> struct Helper { };
	template<typename U>
	static no deduce(U*, Helper<void(BaseMixin::*)(), &U::operator()>* = 0);
	static yes deduce(...);
public:
	constexpr static bool result = (sizeof(yes) == sizeof(deduce(static_cast<Base*>(nullptr))));
};

namespace detail {
	template<typename TType>
	struct void_exp_result { };

	template<typename TType, typename U>
	const U& operator,(const U&, void_exp_result<TType>);

	template<typename TType, typename U>
	U& operator,(U&, void_exp_result<TType>);

	template<typename TSrc, typename TDst>
	struct clone_constness {
		using type = TDst;
	};
	template<typename TSrc, typename TDst>
	struct clone_constness<const TSrc, TDst> {
		using type = const TDst;
	};
}

template<typename TType, typename TDetails>
struct is_call_possible {
protected:
	struct yes { char _unused; };
	struct no { yes _unused[2]; };

	struct derived : TType {
		using TType::operator();
		no operator()(...) const;
	};

	using derived_type = typename detail::clone_constness<TType, derived>::type;

	template<typename T, typename TDue>
	struct return_value_check {
		static yes deduce(TDue);
		static no deduce(...);
		static no deduce(no);
		static no deduce(detail::void_exp_result<TType>);
	};

	template<typename T>
	struct return_value_check<T, void> {
		static yes deduce(...);
		static no deduce(no);
	};

	template<bool Has, typename Fn>
	struct impl {
		constexpr bool value = false;
	};
	template<typename TArg, typename TRet>
	struct impl<true, TRet(TArg)> {
		constexpr static bool value = (sizeof(yes) == sizeof(return_value_check<TType, TRet>::deduce(static_cast<derived_type *>(nullptr)->operator()(*static_cast<TArg *>(nullptr)), detail::void_exp_result<TType>())));
	};
};