/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _UPDATE_QUERY_IMPL_HPP
#define _UPDATE_QUERY_IMPL_HPP

#include "../record.hpp"
#include "../stringutil.hpp"

#include <iostream>     // for std::ostream
#include <string>       // for std::string, std::to_string

#define FP_RETURNS(x) -> decltype(x) { return x; }

namespace fp { namespace impl {
    struct update_query_impl;
    
    namespace update_modifiers {
        
        template<typename, typename>
        struct modifier;
    }

    template<typename>
    struct is_update_modifier : std::false_type { };

    template<typename TField, typename TGetter>
    struct is_update_modifier<update_modifiers::modifier<TField, TGetter>> : is_field<TField> { };

    struct update_query_impl {

        template<typename TDescriptor, typename... TUpdate>
        static std::string build_update_query(TUpdate... modifiers) {
            using std::to_string;
            return stringutils::concatenate(
                "UPDATE ",
                TDescriptor::table::name,
                " SET ",
                stringutils::implode(", ", to_string(modifiers)...)
            );
        }
    };

    template<typename...>
    struct update_applier;

    template<typename H, typename... T>
    struct update_applier<H, T...> {
    protected:
        H head_;
        update_applier<T...> tail_;
    public:

        update_applier(H h, T... t)
        : head_(h), tail_(t...)
        { }

        template<typename... Fs>
        void operator()(fp::record<Fs...>& rec) const {
            head_(rec);
            tail_(rec);
        }
    };

    template<typename H>
    struct update_applier<H> {
    protected:
        H head_;
    public:

        update_applier(H h)
        : head_(h)
        { }

        template<typename... Fs>
        void operator()(fp::record<Fs...>& rec) const {
            head_(rec);
        }
    };

    namespace update_modifiers {

        template<typename TField>
        struct field_getter {
        public:
            using descriptor_type = DescriptorOf<TField>;
        public:

            template<typename... Fs>
            Invoke<TField> operator()(const fp::record<Fs...>& rec) const {
                return get<TField>(rec);
            }

            friend std::string to_string(const field_getter&) {
                using std::to_string;
                return to_string(TField());
            }
        };
        
        template<typename TLeft, typename TRight>
        struct field_add {
        public:
            using descriptor_type = DescriptorOf<TRight>;
            using type = Invoke<TRight>;
        protected:
            type value_;
        public:

            field_add() = default;

            field_add(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TLeft>(rec) + get<TRight>(rec))

            friend std::string to_string(const field_add& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TLeft()), " + ", to_string(TRight()));
            }
        };
        
        template<typename TLeft, typename TRight>
        struct field_sub {
        public:
            using descriptor_type = DescriptorOf<TRight>;
            using type = Invoke<TRight>;
        protected:
            type value_;
        public:

            field_sub() = default;

            field_sub(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TLeft>(rec) - get<TRight>(rec))

            friend std::string to_string(const field_sub& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TLeft()), " - ", to_string(TRight()));
            }
        };
        
        template<typename TLeft, typename TRight>
        struct field_mul {
        public:
            using descriptor_type = DescriptorOf<TRight>;
            using type = Invoke<TRight>;
        protected:
            type value_;
        public:

            field_mul() = default;

            field_mul(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TLeft>(rec) * get<TRight>(rec))

            friend std::string to_string(const field_mul& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TLeft()), " * ", to_string(TRight()));
            }
        };
        
        template<typename TLeft, typename TRight>
        struct field_div {
        public:
            using descriptor_type = DescriptorOf<TRight>;
            using type = Invoke<TRight>;
        protected:
            type value_;
        public:

            field_div() = default;

            field_div(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TLeft>(rec) / get<TRight>(rec))

            friend std::string to_string(const field_div& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TLeft()), " / ", to_string(TRight()));
            }
        };

        template<typename TField>
        struct value_getter {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            type value_;
        public:

            value_getter() = default;

            value_getter(type v)
            : value_(v)
            { }

            template<typename... Fs >
            const type& operator()(const fp::record<Fs...>& rec) const {
                return value_;
            }

            friend std::string to_string(const value_getter& g) {
                using std::to_string;
                return to_string(g.value_);
            }
        };
        
        template<typename TField>
        struct value_add {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            type value_;
        public:

            value_add() = default;

            value_add(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TField>(rec) + value_)

            friend std::string to_string(const value_add& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TField()), " + ", to_string(g.value_));
            }
        };
        
        template<typename TField>
        struct value_sub {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            type value_;
        public:

            value_sub() = default;

            value_sub(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TField>(rec) - value_)

            friend std::string to_string(const value_sub& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TField()), " - ", to_string(g.value_));
            }
        };
        
        template<typename TField>
        struct value_mul {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            type value_;
        public:

            value_mul() = default;

            value_mul(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TField>(rec) * value_)

            friend std::string to_string(const value_mul& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TField()), " * ", to_string(g.value_));
            }
        };
        
        template<typename TField>
        struct value_div {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            type value_;
        public:

            value_div() = default;

            value_div(type v)
            : value_(v)
            { }

            template<typename... Fs >
            auto operator()(const fp::record<Fs...>& rec) const
            FP_RETURNS(get<TField>(rec) / value_)

            friend std::string to_string(const value_div& g) {
                using std::to_string;
                return stringutils::concatenate(to_string(TField()), " / ", to_string(g.value_));
            }
        };

        template<typename TField, typename TValue>
        struct modifier {
        public:
            using descriptor_type = DescriptorOf<TField>;
            using type = Invoke<TField>;
        protected:
            TValue value_;
        public:

            modifier() = default;

            modifier(TValue v)
            : value_(v)
            { }

            template<typename... Fs>
            void operator()(fp::record<Fs...>& rec) const {
                get<TField>(rec) = value_(rec);
            }

            friend std::string to_string(const modifier& m) {
                using std::to_string;
                return stringutils::concatenate(to_string(TField()), " = (", to_string(m.value_), ")");
            }
        };
    }
} }

#undef FP_RETURNS

#endif