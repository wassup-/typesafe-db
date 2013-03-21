#ifndef _MYSQL_RESULT_ITERATOR_HPP
#define _MYSQL_RESULT_ITERATOR_HPP

namespace fp {
    namespace mysql {
        namespace priv {
            struct result_iterator_impl;
        }

        struct basic_result;

        struct result_iterator {
        public:
            typedef result_iterator this_type;
            typedef typename std::iterator_traits<basic_row *> traits_type;

            typedef typename traits_type::value_type value_type;
            typedef typename traits_type::reference reference;
            typedef typename traits_type::pointer pointer;
            typedef typename traits_type::difference_type difference_type;
            typedef typename traits_type::iterator_category iterator_category;
        protected:
            priv::result_iterator_impl * m_impl;
        public:
            result_iterator(basic_result & res) : m_impl(0) { }
            ~result_iterator() { }

            result_iterator & operator ++() { return *this; }

            pointer operator ->() const { return 0; }

            reference operator *() const { return *operator->(); }
        };
    }
}

#endif