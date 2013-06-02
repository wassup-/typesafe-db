/* 
 * File:   vector3.hpp
 * Author: tom
 *
 * Created on June 14, 2012, 7:41 PM
 */

#ifndef CORE_VECTOR3_HPP
#define	CORE_VECTOR3_HPP

#include <cmath>        // for std::sqrt
#include <iostream>     // for std::cout

namespace fp {
    namespace core {
        template<typename> class vector2;
        template<typename> class vector3;
        template<typename> class vector4;

        template<typename T> class vector3 {
        public:
            typedef T value_type;
            typedef vector3<T> this_type;
        private:
            template<typename> friend class vector2;
            template<typename> friend class vector3;
            template<typename> friend class vector4;
        protected:
            T _x;
            T _y;
            T _z;
        public:

            vector3() : _x(), _y(), _z() {

            }

            vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {

            }

            vector3(vector3 const & v) : _x(v._x), _y(v._y), _z(v._z) {

            }

            explicit vector3(T v[3]) : _x(v[0]), _y(v[1]), _z(v[2]) {

            }

            template<typename U>
            explicit vector3(vector3<U> const & v) : _x(v._x), _y(v._y), _z(v._z) {

            }

            T & x() {
                return _x;
            }

            T x() const {
                return _x;
            }

            vector3 & x(T v) {
                _x = v;
                return *this;
            }

            T & y() {
                return _y;
            }

            T y() const {
                return _y;
            }

            vector3 & y(T v) {
                _y = v;
                return *this;
            }

            T & z() {
                return _z;
            }

            T z() const {
                return _z;
            }

            vector3 & z(T v) {
                _z = v;
                return *this;
            }

            double length() const {
                return std::sqrt(dot(*this));
            }

            template<typename U>
            double dot(vector3<U> const & v) const {
                return ((_x * v._x) + (_y * v._y) + (_z * v._z));
            }

            vector3 normalize() const {
                double len = length();
                if (len == 0.f) {
                    return vector3();
                } else {
                    return vector3(_x / len, _y / len, _z / len);
                }
            }

            vector3 inverse() const {
                return vector3(-_x, -_y, -_z);
            }

            template<typename U>
            vector3 cross(vector3<U> const & v) const {
                return vector3((_y * v._z) - (_z * v._y), (_z * v._x) - (_x * v._z), (_x * v._y) - (_y * v._x));
            }

            template<typename U>
            vector3 add(vector3<U> const & v) const {
                return vector3(_x + v._x, _y + v._y, _z + v._z);
            }

            template<typename U>
            vector3 add(U v) const {
                return vector3(_x + v, _y + v, _z + v);
            }

            template<typename U>
            vector3 sub(vector3<U> const & v) const {
                return vector3(_x - v._x, _y - v._y, _z - v._z);
            }

            template<typename U>
            vector3 sub(U v) const {
                return vector3(_x - v, _y - v, _z - v);
            }

            template<typename U>
            vector3 mul(vector3<U> const & v) const {
                return vector3(_x * v._x, _y * v._y, _z * v._z);
            }

            template<typename U>
            vector3 mul(U v) const {
                return vector3(_x * v, _y * v, _z * v);
            }

            template<typename U>
            vector3 div(vector3<U> const & v) const {
                return vector3(_x / v._x, _y / v._y, _z / v._z);
            }

            template<typename U>
            vector3 div(U v) const {
                return vector3(_x / v, _y / v, _z / v);
            }

            template<typename U>
            vector3<U> as() const {
                return vector3<U > (_x, _y, _z);
            }

            vector3 & operator +=(vector3 const & v) {
                _x += v._x;
                _y += v._y;
                _z += v._z;
                return *this;
            }

            vector3 & operator -=(vector3 const & v) {
                _x -= v._x;
                _y -= v._y;
                _z -= v._z;
                return *this;
            }

            vector3 & operator *=(vector3 const & v) {
                _x *= v._x;
                _y *= v._y;
                _z *= v._z;
                return *this;
            }

            vector3 & operator /=(vector3 const & v) {
                _x /= v._x;
                _y /= v._y;
                _z /= v._z;
                return *this;
            }

            template<typename U>
            bool operator==(vector3<U> const & r) const {
                return (_x == r._x) && (_y == r._y) && (_z == r._z);
            }

            template<typename U>
            bool operator!=(vector3<U> const & r) const {
                return (_x != r._x) || (_y != r._y) || (_z != r._z);
            }

            friend vector3 operator-(vector3 const & v) {
                return v.inverse();
            }

            template<typename U>
            friend T operator %(vector3 const & l, vector3<U> const & r) {
                return l.dot(r);
            }

            template<typename U>
            friend vector3 operator+(vector3 const & l, vector3<U> const & r) {
                return l.add(r);
            }

            template<typename U>
            friend vector3 operator+(vector3 const & l, U v) {
                return l.add(v);
            }

            template<typename U>
            friend vector3 operator+(U v, vector3 const & r) {
                return r.add(v);
            }

            template<typename U>
            friend vector3 operator-(vector3 const & l, vector3<U> const & r) {
                return l.sub(r);
            }

            template<typename U>
            friend vector3 operator-(vector3 const & l, U v) {
                return l.sub(v);
            }

            template<typename U>
            friend vector3 operator-(U v, vector3 const & r) {
                return vector3(v - r._x, v - r._y, v - r._z);
            }

            template<typename U>
            friend vector3 operator*(vector3 const & l, vector3<U> const & r) {
                return l.mul(r);
            }

            template<typename U>
            friend vector3 operator*(vector3 const & l, U v) {
                return l.mul(v);
            }

            template<typename U>
            friend vector3 operator*(U v, vector3 const & r) {
                return r.mul(v);
            }

            template<typename U>
            friend vector3 operator/(vector3 const & l, vector3<U> const & r) {
                return l.div(r);
            }

            template<typename U>
            friend vector3 operator/(vector3 const & l, U v) {
                return l.div(v);
            }

            template<typename U>
            friend vector3 operator/(U v, vector3 const & r) {
                return vector3(v / r._x, v / r._y, v / r._z);
            }
        };

        /**
         * Output to stream
         * @param s
         * @param v
         * @return std::ostream &
         */
        template<typename T>
        inline std::ostream & operator <<(std::ostream & s, vector3<T> const & v) {
            std::cout << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]";
            return s;
        }

        /**
         * Create a vector
         * @param v
         * @return vector3<T>
         */
        template<typename T>
        inline vector3<T> make_vector(T(&v)[3]) {
            return vector3<T > (v[0], v[1], v[2]);
        }

        /**
         * Create a vector
         * @param v
         * @return vector3<T>
         */
        template<typename T>
        inline vector3<T> make_vector(T x, T y, T z) {
            return vector3<T > (x, y, z);
        }

        template<typename T>
        inline vector3<T> rotate(vector3<T> const & l, vector3<T> const & r) {
            T x = l.x();
            T y = l.y();
            T z = l.z();

            x += (l.x() * std::cos(r.y()) + l.z() * std::sin(r.y()));
            z += (-l.x() * std::sin(r.y()) + l.z() * std::cos(r.y()));

            y += (l.y() * std::cos(r.x()) - l.z() * std::sin(r.x()));
            z += (l.y() * std::sin(r.x()) + l.z() * std::cos(r.x()));

            x += (l.x() * std::cos(r.z()) - l.y() * std::sin(r.z()));
            z += (l.x() * std::sin(r.z()) + l.y() * std::cos(r.z()));

            return vector3<T > (x, y, z);
        }

        typedef vector3<int> vector3i;
        typedef vector3<float> vector3f;
        typedef vector3<double> vector3d;
    }
}

#endif	/* CORE_VECTOR3_HPP */