/* 
 * File:   vector4.hpp
 * Author: tom
 *
 * Created on June 14, 2012, 7:42 PM
 */

#ifndef CORE_VECTOR4_HPP
#define	CORE_VECTOR4_HPP

#include <cmath>        // for std::sqrt
#include <iostream>     // for std::cout

namespace fp {
    namespace core {
        template<typename> class vector2;
        template<typename> class vector3;
        template<typename> class vector4;

        template<typename T> class vector4 {
        public:
            typedef T value_type;
            typedef vector4<T> this_type;
        private:
            template<typename> friend class vector2;
            template<typename> friend class vector3;
            template<typename> friend class vector4;
        protected:
            T _x;
            T _y;
            T _z;
            T _w;
        public:

            vector4() : _x(), _y(), _z(), _w() {

            }

            vector4(T x, T y, T z, T w) : _x(x), _y(y), _z(z), _w(w) {

            }

            vector4(vector4 const & v) : _x(v._x), _y(v._y), _z(v._z), _w(v._w) {

            }

            explicit vector4(T v[4]) : _x(v[0]), _y(v[1]), _z(v[2]), _w(v[3]) {

            }

            template<typename U>
            explicit vector4(vector4<U> const & v) : _x(v._x), _y(v._y), _z(v._z), _w(v._w) {

            }

            T & x() {
                return _x;
            }

            T x() const {
                return _x;
            }

            vector4 & x(T v) {
                _x = v;
                return *this;
            }

            T & y() {
                return _y;
            }

            T y() const {
                return _y;
            }

            vector4 & y(T v) {
                _y = v;
                return *this;
            }

            T & z() {
                return _z;
            }

            T z() const {
                return _z;
            }

            vector4 & z(T v) {
                _z = v;
                return *this;
            }

            T & w() {
                return _w;
            }

            T w() const {
                return _w;
            }

            vector4 & w(T v) {
                _w = v;
                return *this;
            }

            double length() const {
                return std::sqrt(dot(*this));
            }

            template<typename U>
            double dot(vector4<U> const & v) const {
                return ((_x * v._x) + (_y * v._y) + (_z * v._z) + (_w * v._w));
            }

            vector4 normalize() const {
                double len = length();
                if (len == 0.f) {
                    return vector4();
                } else {
                    return vector4(_x / len, _y / len, _z / len, _w / len);
                }
            }

            vector4 inverse() const {
                return vector4(-_x, -_y, -_z, -_w);
            }

            template<typename U>
            vector4 add(vector4<U> const & v) const {
                return vector4(_x + v._x, _y + v._y, _z + v._z, _w + v._w);
            }

            template<typename U>
            vector4 sub(vector4<U> const & v) const {
                return vector4(_x - v._x, _y - v._y, _z - v._z, _w - v._w);
            }

            template<typename U>
            vector4 mul(vector4<U> const & v) const {
                return vector4(_x * v._x, _y * v._y, _z * v._z, _w * v._w);
            }

            template<typename U>
            vector4 div(vector4<U> const & v) const {
                return vector4(_x / v._x, _y / v._y, _z / v._z, _w / v._w);
            }

            template<typename U>
            vector4<U> as() const {
                return vector4<U > (_x, _y, _z, _w);
            }

            vector4 & operator +=(vector4 const & v) {
                _x += v._x;
                _y += v._y;
                _z += v._z;
                _w += v._w;
                return *this;
            }

            vector4 & operator -=(vector4 const & v) {
                _x -= v._x;
                _y -= v._y;
                _z -= v._z;
                _w -= v._w;
                return *this;
            }

            vector4 & operator *=(vector4 const & v) {
                _x *= v._x;
                _y *= v._y;
                _z *= v._z;
                _w *= v._w;
                return *this;
            }

            vector4 & operator /=(vector4 const & v) {
                _x /= v._x;
                _y /= v._y;
                _z /= v._z;
                _w /= v._w;
                return *this;
            }

            template<typename U>
            friend bool operator==(vector4 const & l, vector4<U> const & r) {
                return (l._x == r._x) && (l._y == r._y) && (l._z == r._z) && (l._w == r._w);
            }

            template<typename U>
            friend bool operator!=(vector4 const & l, vector4<U> const & r) {
                return (l._x != r._x) || (l._y != r._y) || (l._z != r._z) || (l._w != r._w);
            }

            friend vector4 operator-(vector4 const & v) {
                return v.inverse();
            }

            template<typename U>
            friend T operator %(vector4 const & l, vector4<U> const & r) {
                return l.dot(r);
            }

            template<typename U>
            friend vector4 operator+(vector4 const & l, vector4<U> const & r) {
                return l.add(r);
            }

            template<typename U>
            friend vector4 operator+(vector4 const & l, U v) {
                return l.add(v);
            }

            template<typename U>
            friend vector4 operator+(U v, vector4 const & r) {
                return r.add(v);
            }

            template<typename U>
            friend vector4 operator-(vector4 const & l, vector4<U> const & r) {
                return l.sub(r);
            }

            template<typename U>
            friend vector4 operator-(vector4 const & l, U v) {
                return l.sub(v);
            }

            template<typename U>
            friend vector4 operator-(U v, vector4 const & r) {
                return vector4(v - r._x, v - r._y, v - r._z, v - r._w);
            }

            template<typename U>
            friend vector4 operator*(vector4 const & l, vector4<U> const & r) {
                return l.mul(r);
            }

            template<typename U>
            friend vector4 operator*(vector4 const & l, U v) {
                return l.mul(v);
            }

            template<typename U>
            friend vector4 operator*(U v, vector4 const & r) {
                return r.mul(v);
            }

            template<typename U>
            friend vector4 operator/(vector4 const & l, vector4<U> const & r) {
                return l.div(r);
            }

            template<typename U>
            friend vector4 operator/(vector4 const & l, U v) {
                return l.div(v);
            }

            template<typename U>
            friend vector4 operator/(U v, vector4 const & r) {
                return vector4(v / r._x, v / r._y, v / r._z, v / r._w);
            }
        };

        /**
         * Output to stream
         * @param s
         * @param v
         * @return std::ostream &
         */
        template<typename T>
        inline std::ostream & operator <<(std::ostream & s, vector4<T> const & v) {
            std::cout << "[" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << "]";
            return s;
        }

        /**
         * Create a vector
         * @param v
         * @return vector4<T>
         */
        template<typename T>
        inline vector4<T> make_vector(T(&v)[4]) {
            return vector3<T > (v[0], v[1], v[2], v[3]);
        }

        /**
         * Create a vector
         * @param v
         * @return vector3<T>
         */
        template<typename T>
        inline vector4<T> make_vector(T x, T y, T z, T w) {
            return vector4<T > (x, y, z, w);
        }

        typedef vector4<int> vector4i;
        typedef vector4<float> vector4f;
        typedef vector4<double> vector4d;
    }
}

#endif	/* CORE_VECTOR4_HPP */