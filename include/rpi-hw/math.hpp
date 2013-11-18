/* 
    Title --- math.hpp

    Copyright (C) 2013 Giacomo Trudu - wicker25[at]gmail[dot]com

    This file is part of Rpi-hw.

    Rpi-hw is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation version 3 of the License.

    Rpi-hw is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Rpi-hw. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _RPI_HW_MATH_HPP_
#define _RPI_HW_MATH_HPP_

#include <cmath>

namespace rpihw { // Begin main namespace

/*!
	@namespace rpihw::math
	@brief Namespace of the mathematical functions.
*/
namespace math { // Begin math namespace

//! Pi, the ratio of a circle's circumference to its diameter.
const double PI = M_PI;

//! The infinity constant.
const double INF = INFINITY;

//! The natural logarithm of 2.
const double LOG2 = 0.6931471;

//! Returns the absolute value of `x`.
template < typename T >
inline T abs( T x ) { return (x > 0) ? x : -x; }

//! Returns the nearest integer not greater than `x`.
template < typename T >
inline T floor( T x ) { return static_cast< T >( std::floor( (double) x ) ); }

//! Returns the nearest integer not less than `x`.
template < typename T >
inline T ceil( T x ) { return static_cast< T >( std::ceil( (double) x ) ); }

//! Returns the nearest integer to `x`.
template < typename T >
inline T round( T x ) { return (x > 0.0) ? math::floor( x + 0.5 ) : math::floor( x - 0.5 ); }

//! Returns the lesser of `x` and `y`
template < typename T >
inline T min( T x, T y ) { return (x < y) ? x : y; }

//! Returns the greater of `x` and `y`
template < typename T >
inline T max( T x, T y ) { return (x > y) ? x : y; }

//! Returns `x` between `y` and `z`
template < typename T >
inline T between( T x, T y, T z ) { return (x < y) ? y : ( (x > z) ? z : x ); }

//! Returns the sign of `x`
template < typename T >
inline T sign( T x ) { return (x == 0) ? 0 : ( (x > 0) ? 1 : -1 ); }

//! Returns -1 if `x` is less than `y`; 1 if `x` is greater than `y`, and 0 if they are equal 
template < typename T >
inline T cmp( T x, T y ) { return (x == y) ? 0 : ( (x > y) ? 1 : -1 ); }

//! Returns `x` raised to the power `y`
template < typename T >
inline T pow( T x, T y ) { return std::pow( (double) x, (double) y ); }

//! Returns the square of `x`
template < typename T >
inline T square( T x ) { return (x * x); }

//! Returns the cube of `x`
template < typename T >
inline T cube( T x ) { return (x * x * x); }

//! Returns the square root of `x`
template < typename T >
inline T sqrt( T x ) { return static_cast< T >( std::sqrt( x ) ); }

//! Returns the natural logarithm of `x`
template < typename T >
inline T log( T x ) { return static_cast< T >( std::log( x ) ); }

//! Returns the base-2 logarithm of `x`
template < typename T >
inline T log2( T x ) { return static_cast< T >( math::log( (double) x ) / LOG2 ); }

//! Returns the angle `x` expressed in radians
template < typename T >
inline T rad( T x ) { return x * PI / 180.0; }

//! Returns the angle `x` expressed in degrees
template < typename T >
inline T deg( T x ) { return x * 180.0 / PI; }

//! Returns the sine of an angle of `x` radians 
template < typename T >
inline T sin( T x ) { return static_cast< T >( std::sin( (double) x ) ); }

//! Returns the cosine of an angle of `x` radians
template < typename T >
inline T cos( T x ) { return static_cast< T >( std::cos( (double) x ) ); }

//! Returns the tangent of an angle of `x` radians
template < typename T >
inline T tan( T x ) { return static_cast< T >( std::tan( (double) x ) ); }

//! Returns the arctangent of `x`, expressed in radians 
template < typename T >
inline T atan( T x ) { return static_cast< T >( std::atan( (double) x ) ); }

/* FAST CALCULATIONS */

//! Returns the base-2 logarithm of `x`
inline size_t fast_log2( size_t x ) {

	asm( "clz %1, %0" : "=r" (x) : "r" (x) );
	return ( 31 - x );
}

//! Returns 2 raised to the power `x`
inline size_t fast_pow2( size_t x ) { return 1 << x; }

} // End of math namespace

} // End of main namespace

#endif /* _RPI_HW_MATH_HPP_ */
