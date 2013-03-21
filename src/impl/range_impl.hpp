#ifndef _RANGE_IMPL_HPP
#define _RANGE_IMPL_HPP

namespace fp {
	template<int...> struct int_seq;
	
	namespace impl {
		template<int Min, int Max, int Cur, int... R> struct build_range_incr : build_range_incr<Min, Max, Cur + 1, Cur, R...> {
	    };

	    template<int Min, int Max, int... R> struct build_range_incr<Min, Max, Min, R...> : int_seq<Min, R...> {
	        typedef int_seq<Min, R...> type;
	    };

	    template<int Min, int Max, int Cur, int... R> struct build_range_decr : build_range_decr<Min, Max, Cur - 1, Cur, R...> {
	    };

	    template<int Min, int Max, int... R> struct build_range_decr<Min, Max, Min, R...> : int_seq<Min, R...> {
	        typedef int_seq<Min, R...> type;
	    };

        template<bool /* = false */, int Min, int Max> struct range_builder_impl {
            typedef typename build_range_incr<Min, Max, Max>::type type;
        };

        template<int Min, int Max> struct range_builder_impl<true, Min, Max> {
            typedef typename build_range_decr<Min, Max, Max>::type type;
        };
    }
}

#endif