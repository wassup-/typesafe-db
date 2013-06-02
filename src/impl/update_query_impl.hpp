#ifndef _UPDATE_QUERY_IMPL_HPP
#define _UPDATE_QUERY_IMPL_HPP

#include "../record.hpp"

#include <iostream>     // for std::ostream
#include <sstream>      // for std::ostringstream
#include <string>       // for std::string, std::to_string

namespace fp {
    namespace impl {
        struct update_query_impl;
        
        template<typename...>
        struct modifier_to_string;

        namespace update_modifiers {
            
            template<typename, typename>
            struct modifier;
        }

        template<typename>
        struct is_update_modifier {

            enum {
                value = false
            };
        };

        template<typename TField, typename TGetter>
        struct is_update_modifier<update_modifiers::modifier<TField, TGetter>> {

            enum {
                value = is_field<TField>::value
            };
        };

        template<typename H, typename... T>
        struct modifier_to_string<H, T...> {
        protected:
            H _head;
            modifier_to_string<T...> _tail;
        public:

            modifier_to_string(H h, T... t)
            : _head(h), _tail(t...) {
            }

            void operator()(std::ostream & ss) const {
                using std::to_string;
                ss << to_string(_head) << ", ";
                _tail(ss);
            }
        };

        template<typename H>
        struct modifier_to_string<H> {
        protected:
            H _head;
        public:

            modifier_to_string(H h)
            : _head(h) {
            }

            void operator()(std::ostream & ss) const {
                using std::to_string;
                ss << to_string(_head);
            }
        };

        struct update_query_impl {

            template<typename TDescriptor, typename... TUpdate>
            static std::string build_update_query(TUpdate... modifiers) {
                modifier_to_string < TUpdate...> mts(modifiers...);
                std::ostringstream ss;
                ss << "UPDATE " << TDescriptor::table::name << " SET ";
                mts(ss);
                return ss.str();
            }
        };

        template<typename...>
        struct update_applier;

        template<typename H, typename... T>
        struct update_applier<H, T...> {
        protected:
            H _head;
            update_applier<T...> _tail;
        public:

            update_applier(H h, T... t)
            : _head(h), _tail(t...) {
            }

            template<typename... Fs>
            void operator()(fp::record<Fs...> & rec) const {
                _head(rec);
                _tail(rec);
            }
        };

        template<typename H>
        struct update_applier<H> {
        protected:
            H _head;
        public:

            update_applier(H h)
            : _head(h) {
            }

            template<typename... Fs>
            void operator()(fp::record<Fs...> & rec) const {
                _head(rec);
            }
        };

        namespace update_modifiers {

            template<typename TField>
            struct field_getter {
            public:
                using descriptor_type = DescriptorOf<TField>;
            public:

                template<typename... Fs>
                Invoke<TField> operator()(fp::record<Fs...> const & rec) const {
                    return get<TField>(rec);
                }

                friend std::string to_string(field_getter const &) {
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
                type _value;
            public:

                field_add()
                : _value() {
                }

                field_add(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return (get<TLeft>(rec) + get<TRight>(rec));
                }

                friend std::string to_string(field_add const & g) {
                    using std::to_string;
                    return to_string(TLeft()) + " + " + to_string(TRight());
                }
            };
            
            template<typename TLeft, typename TRight>
            struct field_sub {
            public:
                using descriptor_type = DescriptorOf<TRight>;
                using type = Invoke<TRight>;
            protected:
                type _value;
            public:

                field_sub()
                : _value() {
                }

                field_sub(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return (get<TLeft>(rec) - get<TRight>(rec));
                }

                friend std::string to_string(field_sub const & g) {
                    using std::to_string;
                    return to_string(TLeft()) + " - " + to_string(TRight());
                }
            };
            
            template<typename TLeft, typename TRight>
            struct field_mul {
            public:
                using descriptor_type = DescriptorOf<TRight>;
                using type = Invoke<TRight>;
            protected:
                type _value;
            public:

                field_mul()
                : _value() {
                }

                field_mul(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return (get<TLeft>(rec) * get<TRight>(rec));
                }

                friend std::string to_string(field_mul const & g) {
                    using std::to_string;
                    return to_string(TLeft()) + " * " + to_string(TRight());
                }
            };
            
            template<typename TLeft, typename TRight>
            struct field_div {
            public:
                using descriptor_type = DescriptorOf<TRight>;
                using type = Invoke<TRight>;
            protected:
                type _value;
            public:

                field_div()
                : _value() {
                }

                field_div(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return (get<TLeft>(rec) / get<TRight>(rec));
                }

                friend std::string to_string(field_div const & g) {
                    using std::to_string;
                    return to_string(TLeft()) + " / " + to_string(TRight());
                }
            };

            template<typename TField>
            struct value_getter {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                type _value;
            public:

                value_getter()
                : _value() {
                }

                value_getter(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type const & operator()(fp::record<Fs...> const & rec) const {
                    return _value;
                }

                friend std::string to_string(value_getter const & g) {
                    using std::to_string;
                    return to_string(g._value);
                }
            };
            
            template<typename TField>
            struct value_add {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                type _value;
            public:

                value_add()
                : _value() {
                }

                value_add(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return get<TField>(rec) + _value;
                }

                friend std::string to_string(value_add const & g) {
                    using std::to_string;
                    return to_string(TField()) + " + " + to_string(g._value);
                }
            };
            
            template<typename TField>
            struct value_sub {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                type _value;
            public:

                value_sub()
                : _value() {
                }

                value_sub(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return get<TField>(rec) - _value;
                }

                friend std::string to_string(value_sub const & g) {
                    using std::to_string;
                    return to_string(TField()) + " - " + to_string(g._value);
                }
            };
            
            template<typename TField>
            struct value_mul {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                type _value;
            public:

                value_mul()
                : _value() {
                }

                value_mul(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return get<TField>(rec) * _value;
                }

                friend std::string to_string(value_mul const & g) {
                    using std::to_string;
                    return to_string(TField()) + " * " + to_string(g._value);
                }
            };
            
            template<typename TField>
            struct value_div {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                type _value;
            public:

                value_div()
                : _value() {
                }

                value_div(type v)
                : _value(v) {
                }

                template<typename... Fs >
                type operator()(fp::record<Fs...> const & rec) const {
                    return get<TField>(rec) / _value;
                }

                friend std::string to_string(value_div const & g) {
                    using std::to_string;
                    return to_string(TField()) + " / " + to_string(g._value);
                }
            };

            template<typename TField, typename TValue>
            struct modifier {
            public:
                using descriptor_type = DescriptorOf<TField>;
                using type = Invoke<TField>;
            protected:
                TValue _value;
            public:

                modifier()
                : _value() {
                }

                modifier(TValue v)
                : _value(v) {
                }

                template<typename... Fs>
                void operator()(fp::record<Fs...> & rec) const {
                    get<TField> (rec) = _value(rec);
                }

                friend std::string to_string(modifier const & m) {
                    using std::to_string;
                    return to_string(TField()) + std::string(" = (") + to_string(m._value) + ")";
                }
            };
        }
    }
}

#endif