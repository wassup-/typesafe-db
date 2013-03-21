#include <cmath>
#include <limits>
#include <type_traits>

namespace fp {
	template<typename T> struct comparer {
		static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type eq(T l, T r, int ulp = 1) {
			return (std::abs(l - r) <= (std::numeric_limits<T>::epsilon() * std::max(std::abs(l), std::abs(r)) * ulp));
		}

		static typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type eq(T l, T r) {
			return (l == r);
		}

		static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type lt(T l, T r, int ulp = 1) {
			return (l < r);
		}

		static typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type lt(T l, T r) {
			return (l < r);
		}

		static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type gt(T l, T r, int ulp = 1) {
			return (l > r);
		}

		static typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type gt(T l, T r) {
			return (l > r);
		}

		static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type lte(T l, T r, int ulp = 1) {
			return (l <= r);
		}

		static typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type lte(T l, T r) {
			return (l <= r);
		}

		static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type gte(T l, T r, int ulp = 1) {
			return (l >= r);
		}

		static typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type gte(T l, T r) {
			return (l >= r);
		}
	};
}