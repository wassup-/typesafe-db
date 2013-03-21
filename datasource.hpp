/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _DATASOURCE_HPP
#define _DATASOURCE_HPP

#include "record.hpp"

namespace fp {
    template<typename> struct datasource;
    template<typename> struct record_loader;

    /*template<int, typename T, typename Src> T get(datasource<Src> &);
    template<int, typename T, typename Src> T get(datasource<Src> const &);

    template<typename Src> struct datasource {

        template<typename T > T get(int i) {
            return static_cast<Src *> (this)->get<T > (i);
        }

        template<typename T > T get(int i) const {
            return static_cast<Src const *> (this)->get<T > (i);
        }
    };

    template<typename TDescriptor, int... Is> struct record_loader<record<TDescriptor, int_seq<Is...> > > {

        template<typename Src> static record <TDescriptor, int_seq < Is...> > load(datasource<Src> & src) {
            return record < TDescriptor, int_seq < Is...> >(src.template get<Ts > (Is)...);
        }
    };

    template<typename TRecord, typename Src> TRecord load_record(datasource<Src> & src) {
        return record_loader<TRecord>::load(src);
    }

    template<int I, typename T, typename Src> T get(datasource<Src> & src) {
        return src.get<T > (I);
    }

    template<int I, typename T, typename Src> T get(datasource<Src> const & src) {
        return src.get<T > (I);
    }*/
}

#endif