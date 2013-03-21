#ifndef _RECORD_HPP
#define _RECORD_HPP

#include "int_sequence.hpp"
#include "field.hpp"
#include "nth_type_of.hpp"
#include "type_sequence.hpp"

#include <string>
#include <tuple>

namespace fp {

    /**
     * This type represents a record
     * the first typename represents a descriptor 
     * the second typename represents an int sequence (template<int...> struct int_seq)
     * the int sequence is needed to do the mapping between field indices
     */
    template<typename TDescriptor, int... Indices> struct record {
    public:
        typedef type_seq<typename TDescriptor::template field<Indices>::type...> types;
        static int const SIZE = sizeof...(Indices);
    protected:
        std::tuple<typename TDescriptor::template field<Indices>::type...> m_values;
    public:
        record() : m_values() { }
        record(typename TDescriptor::template field<Indices>::type && ... ts) : m_values(std::forward<typename TDescriptor::template field<Indices>::type > (ts)...) { }
        record(record const & rec) : m_values(rec.m_values) { }

        int size() const {
            return SIZE;
        }

        template<int I>
        typename TDescriptor::template field<I>::type & get() {
            return std::get<index_of<I, Indices...>::value>(m_values);
        }

        template<int I>
        typename TDescriptor::template field<I>::type const & get() const {
            return std::get<index_of<I, Indices...>::value>(m_values);
        }
    };

    template<int I, typename TDescriptor, int... Is>
    auto get(record<TDescriptor, Is...> & r) -> decltype(r.template get<I>()) {
        return r.template get<I>();
    }

    template<int I, typename TDescriptor, int... Is>
    auto get(record<TDescriptor, Is...> const & r) -> decltype(r.template get<I>()) {
        return r.template get<I>();
    }

    template<typename F, typename TDescriptor, int... Is>
    auto get(record<TDescriptor, Is...> & r) -> decltype(r.template get<F::index>()) {
        return r.template get<F::index>();
    }

    template<typename F, typename TDescriptor, int... Is>
    auto get(record<TDescriptor, Is...> const & r) -> decltype(r.template get<F::index>()) {
        return r.template get<F::index>();
    }

    template<typename TDescriptor, int I, int... Is>
    auto get(record<TDescriptor, Is...> & r, field<TDescriptor, I>) -> decltype(r.template get<I>()) {
        return r.template get<I>();
    }

    template<typename TDescriptor, int I, int... Is>
    auto get(record<TDescriptor, Is...> const & r, field<TDescriptor, I>) -> decltype(r.template get<I>()) {
        return r.template get<I>();
    }
}

#endif