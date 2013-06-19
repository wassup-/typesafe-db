/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CONTAINER_TRAITS_HPP
#define CONTAINER_TRAITS_HPP

namespace std {
    template<typename, typename> struct vector;
    template<typename, typename> struct deque;
    template<typename, typename, typename> struct basic_string;
    template<typename, typename> struct list;
    template<typename, typename> struct forward_list;
    template<typename, typename, typename> struct set;
    template<typename, typename, typename, typename> struct unordered_set;
    template<typename, typename, typename> struct multiset;
    template<typename, typename, typename, typename> struct unordered_multiset;
    template<typename, typename, typename, typename> struct map;
    template<typename, typename, typename, typename, typename> struct unordered_map;
    template<typename, typename, typename, typename> struct multimap;
    template<typename, typename, typename, typename, typename> struct unordered_multimap;
}

namespace fp {

    template<typename> struct container_traits;

    struct vectorlike_tag { };

    struct listlike_tag { };

    struct associative_tag { };

    template<typename T, typename A>
    struct container_traits<std::vector<T, A> > {
        typedef vectorlike_tag category;
    };

    template<typename T, typename A>
    struct container_traits<std::deque<T, A> > {
        typedef vectorlike_tag category;
    };

    template<typename C, typename T, typename A>
    struct container_traits<std::basic_string<C, T, A> > {
        typedef vectorlike_tag category;
    };

    template<typename T, typename A>
    struct container_traits<std::list<T, A> > {
        typedef listlike_tag category;
    };

    template<typename T, typename A>
    struct container_traits<std::forward_list<T, A> > {
        typedef listlike_tag category;
    };

    template<typename T, typename C, typename A>
    struct container_traits<std::set<T, C, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename H, typename P, typename A>
    struct container_traits<std::unordered_set<K, H, P, A> > {
        typedef associative_tag category;
    };

    template<typename T, typename C, typename A>
    struct container_traits<std::multiset<T, C, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename H, typename P, typename A>
    struct container_traits<std::unordered_multiset<K, H, P, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename T, typename C, typename A>
    struct container_traits<std::map<K, T, C, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename T, typename H, typename P, typename A>
    struct container_traits<std::unordered_map<K, T, H, P, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename T, typename C, typename A>
    struct container_traits<std::multimap<K, T, C, A> > {
        typedef associative_tag category;
    };

    template<typename K, typename T, typename H, typename P, typename A>
    struct container_traits<std::unordered_multimap<K, T, H, P, A> > {
        typedef associative_tag category;
    };
}

#endif