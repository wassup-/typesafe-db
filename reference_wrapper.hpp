#ifndef _REF_WRAPPER_H
#define _REF_WRAPPER_H

namespace fp {
	template<typename T> struct remove_reference {
		typedef T type;
	};
	template<typename T> struct remove_reference<T&> {
		typedef T type;
	};
	template<typename T> struct remove_pointer {
		typedef T type;
	};
	template<typename T> struct remove_pointer<T*> {
		typedef T type;
	};
	template<typename T> struct remove_const {
		typedef T type;
	};
	template<typename T> struct remove_const<T const> {
		typedef T type;
	};

	template<typename T> struct ref_wrapper_traits {
		typedef T value_type;
		typedef T & reference;
		typedef T * pointer;
	};

	template<typename T> struct ref_wrapper_traits<T const> {
		typedef T value_type;
		typedef T const & reference;
		typedef T const * pointer;	
	};

	template<typename T> struct reference_wrapper {
	public:
		typedef reference_wrapper<T> this_type;
		typedef typename ref_wrapper_traits<typename remove_reference<T>::type>::value_type value_type;
		typedef typename ref_wrapper_traits<typename remove_reference<T>::type>::reference reference;
		typedef typename ref_wrapper_traits<typename remove_reference<T>::type>::pointer pointer;
	protected:
		pointer m_ptr;
	public:
		reference_wrapper(reference ref) : m_ptr(&ref) { }

		reference_wrapper(reference_wrapper const & ref) : m_ptr(ref.m_ptr) { }

		operator reference() const {
			return *m_ptr;
		}

		pointer operator&() const {
			return m_ptr;
		}

		reference_wrapper & operator=(reference_wrapper const & ref) {
			m_ptr = ref.m_ptr;
			return *this;
		}

		bool operator==(reference_wrapper const & ref) const {
			return (m_ptr == ref.m_ptr);
		}

		bool operator!=(reference_wrapper const & ref) const {
			return (m_ptr != ref.m_ptr);
		}

		reference get() const { return *m_ptr; }
	};

	template<typename T> T & get(reference_wrapper<T> const & r) {
		return r.get();
	}

	template<typename T> reference_wrapper<T> ref(T & r) {
		return reference_wrapper<T>(r);
	}

	template<typename T> reference_wrapper<T const> cref(T const & r) {
		return reference_wrapper<T const>(r);
	}
}

#endif