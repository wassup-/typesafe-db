/* 
 * File:   vector2.h
 * Author: tom
 *
 * Created on June 14, 2012, 7:41 PM
 */

#ifndef CORE_VECTOR2_HPP
#define	CORE_VECTOR2_HPP

#include <cmath>        // for std::sqrt
#include <iostream>     // for std::cout

namespace fp {
    namespace core {
        template<typename> class vector2;
        template<typename> class vector3;
        template<typename> class vector4;

        template<typename T> class vector2 {
        public:
            typedef T value_type;
            typedef vector2<T> this_type;
        private:
            template<typename> friend class vector2;
            template<typename> friend class vector3;
            template<typename> friend class vector4;
        protected:
            T _x;
            T _y;
        public:

            vector2() : _x(), _y() {

            }

            vector2(T x, T y) : _x(x), _y(y) {

            }

            vector2(vector2 const & v) : _x(v._x), _y(v._y) {

            }

            explicit vector2(T v[2]) : _x(v[0]), _y(v[1]) {

            }

            template<typename U>
            explicit vector2(vector2<U> const & v) : _x(v._x), _y(v._y) {

            }

            T & x() {
                return _x;
            }

            T x() const {
                return _x;
            }

            vector2 & x(T v) {
                _x = v;
                return *this;
            }

            T & y() {
                return _y;
            }

            T y() const {
                return _y;
            }

            vector2 & y(T v) {
                _y = v;
                return *this;
            }

            double length() const {
                return std::sqrt(dot(*this));
            }

            template<typename U>
            double dot(vector2<U> const & v) const {
                return ((_x * v._x) + (_y * v._y));
            }

            vector2 normalize() const {
                double len = length();
                if (len == 0.f) {
                    return vector2();
                } else {
                    return vector2(_x / len, _y / len);
                }
            }

            vector2 inverse() const {
                return vector2(-_x, -_y);
            }

            template<typename U>
            vector2 add(vector2<U> const & v) const {
                return vector2(_x + v._x, _y + v._y);
            }

            template<typename U>
            vector2 add(U v) const {
                return vector2(_x + v, _y + v);
            }

            template<typename U>
            vector2 sub(vector2<U> const & v) const {
                return vector2(_x - v._x, _y - v._y);
            }

            template<typename U>
            vector2 sub(U v) const {
                return vector2(_x - v, _y - v);
            }

            template<typename U>
            vector2 mul(vector2<U> const & v) const {
                return vector2(_x * v._x, _y * v._y);
            }

            template<typename U>
            vector2 mul(U v) const {
                return vector2(_x * v, _y * v);
            }

            template<typename U>
            vector2 div(vector2<U> const & v) const {
                return vector2(_x / v._x, _y / v._y);
            }

            template<typename U>
            vector2 div(U v) const {
                return vector2(_x / v, _y / v);
            }

            template<typename U>
            vector2<U> as() const {
                return vector3<U > (_x, _y);
            }

            vector2 & operator +=(vector2 const & v) {
                _x += v._x;
                _y += v._y;
                return *this;
            }

            vector2 & operator -=(vector2 const & v) {
                _x -= v._x;
                _y -= v._y;
                return *this;
            }

            vector2 & operator *=(vector2 const & v) {
                _x *= v._x;
                _y *= v._y;
                return *this;
            }

            vector2 & operator /=(vector2 const & v) {
                _x /= v._x;
                _y /= v._y;
                return *this;
            }

            bool operator ==(vector2 const & v) const {
                return (_x == v._x) && (_y == v._y);
            }

            bool operator !=(vector2 const & v) const {
                return (_x != v._x) || (_y != v._y);
            }

            template<typename U>
            friend bool operator ==(vector2 const & l, vector2<U> const & r) {
                return (l._x == r._x) && (l._y == r._y);
            }

            template<typename U>
            friend bool operator !=(vector2 const & l, vector2<U> const & r) {
                return (l._x != r._x) || (l._y != r._y);
            }

            friend vector2 operator-(vector2 const & v) {
                return v.inverse();
            }

            template<typename U>
            friend T operator %(vector2 const & l, vector2<U> const & r) {
                return l.dot(r);
            }

            template<typename U>
            friend vector2 operator+(vector2 const & l, vector2<U> const & r) {
                return l.add(r);
            }

            template<typename U>
            friend vector2 operator+(vector2 const & l, U v) {
                return l.add(v);
            }

            template<typename U>
            friend vector2 operator-(vector2 const & l, vector2<U> const & r) {
                return l.sub(r);
            }

            template<typename U>
            friend vector2 operator-(vector2 const & l, U v) {
                return l.sub(v);
            }

            template<typename U>
            friend vector2 operator*(vector2 const & l, vector2<U> const & r) {
                return l.mul(r);
            }

            template<typename U>
            friend vector2 operator*(vector2 const & l, U v) {
                return l.mul(v);
            }

            template<typename U>
            friend vector2 operator/(vector2 const & l, vector2<U> const & r) {
                return l.div(r);
            }

            template<typename U>
            friend vector2 operator/(vector2 const & l, U v) {
                return l.div(v);
            }
        };

        /**
         * Output to stream
         * @param s
         * @param v
         * @return std::ostream &
         */
        template<typename T>
        inline std::ostream & operator <<(std::ostream & s, vector2<T> const & v) {
            std::cout << "[" << v.x() << ", " << v.y() << "]";
            return s;
        }

        /**
         * Create a vector
         * @param v
         * @return vector2<T>
         */
        template<typename T>
        inline vector2<T> make_vector(T(&v)[2]) {
            return vector2<T > (v[0], v[1]);
        }

        /**
         * Create a vector
         * @param v
         * @return vector2<T>
         */
        template<typename T>
        inline vector2<T> make_vector(T x, T y) {
            return vector2<T > (x, y);
        }

        typedef vector2<int> vector2i;
        typedef vector2<float> vector2f;
        typedef vector2<double> vector2d;
    }
}

#endif	/* CORE_VECTOR2_HPP */