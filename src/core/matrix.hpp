/* 
 * File:   matrix.hpp
 * Author: tom
 *
 * Created on June 14, 2012, 9:25 PM
 */

#ifndef MATRIX_HPP
#define	MATRIX_HPP

#include <cstddef>      // for std::size_t
#include <iostream>     // for std::cout

namespace fp {
    namespace core {
        template<typename, std::size_t, std::size_t> struct matrix;

        template<typename T, std::size_t R, std::size_t C> struct matrix {
        public:
            typedef T value_type;
            typedef matrix<T, R, C> this_type;
            typedef T row[C];
            const static std::size_t ROWS = R;
            const static std::size_t COLS = C;
        private:
            template<typename, std::size_t, std::size_t> friend struct matrix;
        protected:
            T _data[R][C];
        public:

            matrix() : _data() {

            }

            template<typename M > matrix(M(&m)[R][C]) : _data() {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        _data[r][c] = static_cast<T> (m[r][c]);
                    }
                }
            }

            matrix(this_type const & m) : _data() {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        _data[r][c] = m._data[r][c];
                    }
                }
            }

            template<typename M > matrix(matrix<M, R, C> const & m) : _data() {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        _data[r][c] = static_cast<T> (m._data[r][c]);
                    }
                }
            }

            ~matrix() {

            }

            T & operator()(std::size_t r, std::size_t c) {
                return _data[r][c];
            }

            T operator()(std::size_t r, std::size_t c) const {
                return _data[r][c];
            }

            row & operator[](std::size_t r) {
                return _data[r];
            }

            row const & operator[](std::size_t r) const {
                return _data[r];
            }

            constexpr std::size_t rows() const {
                return R;
            }

            constexpr std::size_t columns() const {
                return C;
            }

            this_type & operator =(this_type const & m) {
                if (&m != this) {
                    for (std::size_t r = 0; r < R; ++r) {
                        for (std::size_t c = 0; c < C; ++c) {
                            m_data[r][c] = m.m_data[r][c];
                        }
                    }
                }
                return *this;
            }

            template<typename M > this_type & operator =(matrix<M, R, C> const & m) {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        m_data[r][c] = static_cast<T> (m.m_data[r][c]);
                    }
                }
                return *this;
            }

            this_type & operator =(T(&m)[R][C]) {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        m_data[r][c] = m[r][c];
                    }
                }
                return *this;
            }

            this_type & operator =(T * m) {
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        m_data[r][c] = m[r][c];
                    }
                }
                return *this;
            }

            matrix<T, C, R> transpose() const {
                matrix<T, C, R> ret;
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        ret.m_data[c][r] = m_data[r][c];
                    }
                }
                return ret;
            }

            template<typename M > matrix<M, R, C> as() const {
                matrix<M, R, C> ret;
                for (std::size_t r = 0; r < R; ++r) {
                    for (std::size_t c = 0; c < C; ++c) {
                        ret.m_data[r][c] = static_cast<M>(m_data[r][c]);
                    }
                }
                return ret;
            }
        };

        /**
         * Multiplication
         * @param l
         * @param r
         * @return matrix<T,R,C>
         */
        template<typename T, std::size_t R, std::size_t X, std::size_t C> inline matrix<T, R, C> operator*(matrix<T, R, X> const & l, matrix<T, X, C> const & r) {
            matrix<T, R, C> ret;
            for (std::size_t c_ = 0; c_ < C; ++c_) {
                for (std::size_t r_ = 0; r_ < R; ++r_) {
                    T v = T();
                    for (std::size_t x = 0; x < X; ++x) {
                        v += (l(r_, x) * r(x, c_));
                    }
                    ret(r_, c_) = v;
                }
            }
            return ret;
        }

        /**
         * Adding
         * @param l
         * @param r
         * @return matrix<T,R,C>
         */
        template<typename T, std::size_t R, std::size_t C> inline matrix<T, R, C> operator+(matrix<T, R, C> const & l, matrix<T, R, C> const & r) {
            matrix<T, R, C> ret;
            for (std::size_t c_ = 0; c_ < C; ++c_) {
                for (std::size_t r_ = 0; r_ < R; ++r_) {
                    ret(r_, c_) = (l(r_, c_) + r(r_, c_));
                }
            }
            return ret;
        }

        /**
         * Subtracting
         * @param l
         * @param r
         * @return matrix<T,R,C>
         */
        template<typename T, std::size_t R, std::size_t C> inline matrix<T, R, C> operator-(matrix<T, R, C> const & l, matrix<T, R, C> const & r) {
            matrix<T, R, C> ret;
            for (std::size_t c_ = 0; c_ < C; ++c_) {
                for (std::size_t r_ = 0; r_ < R; ++r_) {
                    ret(r_, c_) = (l(r_, c_) - r(r_, c_));
                }
            }
            return ret;
        }

        template<typename T, std::size_t R, std::size_t C> inline matrix<T, R, C> operator-(T l, matrix<T, R, C> const & r) {
            matrix<T, R, C> ret;
            for (std::size_t c_ = 0; c_ < C; ++c_) {
                for (std::size_t r_ = 0; r_ < R; ++r_) {
                    ret(r_, c_) = (l - r(r_, c_));
                }
            }
            return ret;
        }

        /**
         * Output to stream
         * @param s
         * @param m
         * @return std::ostream &
         */
        template<typename T, std::size_t R, std::size_t C> inline std::ostream & operator<<(std::ostream & s, matrix<T, R, C> const & m) {
            for (std::size_t r = 0; r < R; ++r) {
                if (r != 0) {
                    std::cout << '\n';
                }
                for (std::size_t c = 0; c < C; ++c) {
                    if (c != 0) {
                        std::cout << ' ';
                    }
                    std::cout << m(r, c);
                }
            }
            return s;
        }

        /**
         * Create a matrix
         * @param m
         * @return matrix<T,1,C>
         */
        template<typename T, std::size_t C> inline matrix<T, 1, C> make_matrix(T(&m)[C]) {
            matrix<T, 1, C> mx;
            for (std::size_t c = 0; c < C; ++c) mx(0, c) = m[c];
            return mx;
        }

        /**
         * Create a matrix
         * @param m
         * @return matrix<T,R,C>
         */
        template<typename T, std::size_t R, std::size_t C> inline matrix<T, R, C> make_matrix(T(&m)[R][C]) {
            return matrix<T, R, C > (m);
        }
    }
}

#endif	/* MATRIX_HPP */

