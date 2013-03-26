#ifndef _UPDATE_QUERY_IMPL_HPP
#define _UPDATE_QUERY_IMPL_HPP

#include "../record.hpp"

#include <sstream>      // for std::stringstream
#include <string>       // for std::string, std::to_string

namespace fp {
    namespace impl {
        struct update_query_impl;
        template<typename...> struct modifier_to_string;

        namespace update_modifiers {
            template<typename, int, typename> struct modifier;
        }

        template<typename> struct is_update_modifier {

            enum {
                value = false
            };
        };

        template<typename TDescriptor, int I, typename TGetter> struct is_update_modifier<update_modifiers::modifier<TDescriptor, I, TGetter> > {

            enum {
                value = true
            };
        };

        template<typename H, typename... T> struct modifier_to_string<H, T...> {
        protected:
            H m_head;
            modifier_to_string < T...> m_tail;
        public:

            modifier_to_string(H h, T... t) : m_head(h), m_tail(t...) {
            }

            void operator()(std::stringstream & ss) const {
                using std::to_string;
                ss << to_string(m_head) << ", ";
                m_tail(ss);
            }
        };

        template<typename H> struct modifier_to_string<H> {
        protected:
            H m_head;
        public:

            modifier_to_string(H h) : m_head(h) {
            }

            void operator()(std::stringstream & ss) const {
                using std::to_string;
                ss << to_string(m_head);
            }
        };

        struct update_query_impl {

            template<typename TDescriptor, typename... TModifiers >
            static std::string build_update_query(TModifiers... modifiers) {
                modifier_to_string < TModifiers...> mts(modifiers...);
                std::stringstream ss;
                ss << "UPDATE " << TDescriptor::table::name << " SET ";
                mts(ss);
                return ss.str();
            }
        };

        template<typename...> struct update_applier;

        template<typename H, typename... T> struct update_applier<H, T...> {
        protected:
            H m_head;
            update_applier < T...> m_tail;
        public:

            update_applier(H h, T... t) : m_head(h), m_tail(t...) {
            }

            template<typename TDescriptor, int... Fs>
            void operator()(fp::record<TDescriptor, Fs...> & rec) const {
                m_head(rec);
                m_tail(rec);
            }
        };

        template<typename H> struct update_applier<H> {
        protected:
            H m_head;
        public:

            update_applier(H h) : m_head(h) {
            }

            template<typename TDescriptor, int... Fs>
            void operator()(fp::record<TDescriptor, Fs...> & rec) const {
                m_head(rec);
            }
        };

        namespace update_modifiers {

            template<typename TDescriptor, int I> struct field_getter {
            public:

                template<int... Fs>
                auto operator()(fp::record<TDescriptor, Fs...> const & rec) const -> decltype(fp::get<I > (rec)) {
                    return fp::get<I > (rec);
                }

                friend std::string to_string(field_getter const &) {
                    return TDescriptor::template field<I>::name;
                }
            };

            template<typename TDescriptor, typename TValue> struct value_getter {
            protected:
                TValue m_value;
            public:

                value_getter() : m_value() {
                }

                value_getter(TValue v) : m_value(v) {
                }

                template<int... Fs >
                TValue const & operator()(fp::record<TDescriptor, Fs...> const & rec) const {
                    return m_value;
                }

                friend std::string to_string(value_getter const & g) {
                    using std::to_string;
                    return to_string(g.m_value);
                }
            };

            template<typename TDescriptor, int I, typename TGetter> struct modifier {
            protected:
                TGetter m_getter;
            public:

                modifier() : m_getter() {
                }

                modifier(TGetter g) : m_getter(g) {
                }

                template<int... Fs>
                void operator()(fp::record<TDescriptor, Fs...> & rec) const {
                    fp::get<I > (rec) = m_getter(rec);
                }

                friend std::string to_string(modifier const & m) {
                    using std::to_string;
                    return std::string(TDescriptor::template field<I>::name) + std::string(" = ") + to_string(m.m_getter);
                }
            };
        }
    }
}

#endif