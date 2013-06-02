#ifndef META_CORE_HPP_
#define META_CORE_HPP_

#include <type_traits>

#include "../detail/config.h++"

namespace fp {
    //! Metafunction invocation
    template <typename T>
    using Invoke = typename T::type;

    //! Identity metafunction
    template <typename T>
    struct identity {
        using type = T;
    };

    //! Identity template alias
    template <typename T>
    using Identity = Invoke<identity<T>>;
    //! Deducible identity template alias
    template <typename T>
    using Alias = T;
    //! Not deducible identity template alias
    template <typename T>
    using NotDeducible = Identity<T>;

    //! Meta-boolean type with parameters for when dependent contexts are needed
    template <bool B, typename...>
    struct dependent_bool_type : std::integral_constant<bool, B> {};

    //! Boolean integral_constant alias
    template <bool B, typename... T>
    using Bool = Invoke<dependent_bool_type<B, T...>>;

    //! integral_constant alias
    template <typename T, T I>
    using Const = std::integral_constant<T, I>;

    //! Integer integral_constant alias
    template <int I>
    using Int = Const<decltype(I), I>;

    //! Constant void metafunction
    template <typename>
    struct void_ : identity<void> {};
    template <typename T>
    using Void = Invoke<void_<T>>;

    template <typename... T>
    struct count : Int<0> {};
    template <typename Head, typename... Tail>
    struct count<Head, Tail...> : Int<(Head::value? 1 : 0) + count<Tail...>::value> {};

    //! If-then-else metafunction
    template <typename Condition, typename Then, typename Else>
    using Conditional = Invoke<std::conditional<Condition::value, Then, Else>>;

    //! Logical negation metafunction
    template <typename T>
    using Not = Bool<!T::value>;

    //! Logical disjunction metafunction
    template <typename... T>
    struct Any : Bool<false> {};
    template <typename Head, typename... Tail>
    struct Any<Head, Tail...> : Conditional<Head, Bool<true>, Any<Tail...>> {};

    //! Logical conjunction metafunction
    template <typename... T>
    struct All : Bool<true> {};
    template <typename Head, typename... Tail>
    struct All<Head, Tail...> : Conditional<Head, All<Tail...>, Bool<false>> {};

    //! Minimum metafunction
    template <typename Head, typename... Tail>
    struct min : Head {};
    template <typename T, typename U, typename... Tail>
    struct min<T, U, Tail...> : min<Conditional<Bool<(T::value < U::value)>, T, U>, Tail...> {};

    //! Maximum metafunction
    template <typename Head, typename... Tail>
    struct max : Head {};
    template <typename T, typename U, typename... Tail>
    struct max<T, U, Tail...> : max<Conditional<Bool<(T::value > U::value)>, T, U>, Tail...> {};

    namespace meta_detail {
        enum class enabler { _ };
    } // namespace meta_detail
    //! Dummy for defaulting EnableIf
    constexpr auto _ = meta_detail::enabler::_;
    //! SFINAE enabler
    template <typename... T>
    using EnableIf = Invoke<std::enable_if<All<T...>::value, decltype(_)>>;
    //! SFINAE disabler
    template <typename... T>
    using DisableIf = Invoke<std::enable_if<Not<All<T...>>::value, decltype(_)>>;

    //! Marker for deducible template type parameters
    struct deduced;
} // namespace fp

#endif // META_CORE_HPP_