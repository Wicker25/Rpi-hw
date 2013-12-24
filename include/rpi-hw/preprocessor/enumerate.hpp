/* 
    Title --- enumerate.hpp

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


#ifndef _RPI_HW_ENUMERATE_HPP_
#define _RPI_HW_ENUMERATE_HPP_

//! Generates a comma-separated list of enumerated expressions.
#define __ENUM( expr, from, to )	__ENUM_ ## from ## _ ## to ( expr )

//! Generates a comma-separated list of parameters.
#define __ENUM_PARAMS( type, prefix, from, to )		__ENUM( type prefix, from, to )


// All repeat macros
#define __ENUM_0_0( expr )		expr ## 0
#define __ENUM_0_1( expr )		__ENUM_0_0( expr ), expr ## 1
#define __ENUM_0_2( expr )		__ENUM_0_1( expr ), expr ## 2
#define __ENUM_0_3( expr )		__ENUM_0_2( expr ), expr ## 3
#define __ENUM_0_4( expr )		__ENUM_0_3( expr ), expr ## 4
#define __ENUM_0_5( expr )		__ENUM_0_4( expr ), expr ## 5
#define __ENUM_0_6( expr )		__ENUM_0_5( expr ), expr ## 6
#define __ENUM_0_7( expr )		__ENUM_0_6( expr ), expr ## 7
#define __ENUM_0_8( expr )		__ENUM_0_7( expr ), expr ## 8
#define __ENUM_0_9( expr )		__ENUM_0_8( expr ), expr ## 9
#define __ENUM_0_10( expr )		__ENUM_0_9( expr ), expr ## 10
#define __ENUM_0_11( expr )		__ENUM_0_10( expr ), expr ## 11
#define __ENUM_0_12( expr )		__ENUM_0_11( expr ), expr ## 12
#define __ENUM_0_13( expr )		__ENUM_0_12( expr ), expr ## 13
#define __ENUM_0_14( expr )		__ENUM_0_13( expr ), expr ## 14
#define __ENUM_0_15( expr )		__ENUM_0_14( expr ), expr ## 15
#define __ENUM_0_16( expr )		__ENUM_0_15( expr ), expr ## 16
#define __ENUM_0_17( expr )		__ENUM_0_16( expr ), expr ## 17
#define __ENUM_0_18( expr )		__ENUM_0_17( expr ), expr ## 18
#define __ENUM_0_19( expr )		__ENUM_0_18( expr ), expr ## 19
#define __ENUM_0_20( expr )		__ENUM_0_19( expr ), expr ## 20

#define __ENUM_1_1( expr )		expr ## 1
#define __ENUM_1_2( expr )		__ENUM_1_1( expr ), expr ## 2
#define __ENUM_1_3( expr )		__ENUM_1_2( expr ), expr ## 3
#define __ENUM_1_4( expr )		__ENUM_1_3( expr ), expr ## 4
#define __ENUM_1_5( expr )		__ENUM_1_4( expr ), expr ## 5
#define __ENUM_1_6( expr )		__ENUM_1_5( expr ), expr ## 6
#define __ENUM_1_7( expr )		__ENUM_1_6( expr ), expr ## 7
#define __ENUM_1_8( expr )		__ENUM_1_7( expr ), expr ## 8
#define __ENUM_1_9( expr )		__ENUM_1_8( expr ), expr ## 9
#define __ENUM_1_10( expr )		__ENUM_1_9( expr ), expr ## 10
#define __ENUM_1_11( expr )		__ENUM_1_10( expr ), expr ## 11
#define __ENUM_1_12( expr )		__ENUM_1_11( expr ), expr ## 12
#define __ENUM_1_13( expr )		__ENUM_1_12( expr ), expr ## 13
#define __ENUM_1_14( expr )		__ENUM_1_13( expr ), expr ## 14
#define __ENUM_1_15( expr )		__ENUM_1_14( expr ), expr ## 15
#define __ENUM_1_16( expr )		__ENUM_1_15( expr ), expr ## 16
#define __ENUM_1_17( expr )		__ENUM_1_16( expr ), expr ## 17
#define __ENUM_1_18( expr )		__ENUM_1_17( expr ), expr ## 18
#define __ENUM_1_19( expr )		__ENUM_1_18( expr ), expr ## 19
#define __ENUM_1_20( expr )		__ENUM_1_19( expr ), expr ## 20

#define __ENUM_2_2( expr )		expr ## 2
#define __ENUM_2_3( expr )		__ENUM_2_2( expr ), expr ## 3
#define __ENUM_2_4( expr )		__ENUM_2_3( expr ), expr ## 4
#define __ENUM_2_5( expr )		__ENUM_2_4( expr ), expr ## 5
#define __ENUM_2_6( expr )		__ENUM_2_5( expr ), expr ## 6
#define __ENUM_2_7( expr )		__ENUM_2_6( expr ), expr ## 7
#define __ENUM_2_8( expr )		__ENUM_2_7( expr ), expr ## 8
#define __ENUM_2_9( expr )		__ENUM_2_8( expr ), expr ## 9
#define __ENUM_2_10( expr )		__ENUM_2_9( expr ), expr ## 10
#define __ENUM_2_11( expr )		__ENUM_2_10( expr ), expr ## 11
#define __ENUM_2_12( expr )		__ENUM_2_11( expr ), expr ## 12
#define __ENUM_2_13( expr )		__ENUM_2_12( expr ), expr ## 13
#define __ENUM_2_14( expr )		__ENUM_2_13( expr ), expr ## 14
#define __ENUM_2_15( expr )		__ENUM_2_14( expr ), expr ## 15
#define __ENUM_2_16( expr )		__ENUM_2_15( expr ), expr ## 16
#define __ENUM_2_17( expr )		__ENUM_2_16( expr ), expr ## 17
#define __ENUM_2_18( expr )		__ENUM_2_17( expr ), expr ## 18
#define __ENUM_2_19( expr )		__ENUM_2_18( expr ), expr ## 19
#define __ENUM_2_20( expr )		__ENUM_2_19( expr ), expr ## 20

#define __ENUM_3_3( expr )		expr ## 3
#define __ENUM_3_4( expr )		__ENUM_3_3( expr ), expr ## 4
#define __ENUM_3_5( expr )		__ENUM_3_4( expr ), expr ## 5
#define __ENUM_3_6( expr )		__ENUM_3_5( expr ), expr ## 6
#define __ENUM_3_7( expr )		__ENUM_3_6( expr ), expr ## 7
#define __ENUM_3_8( expr )		__ENUM_3_7( expr ), expr ## 8
#define __ENUM_3_9( expr )		__ENUM_3_8( expr ), expr ## 9
#define __ENUM_3_10( expr )		__ENUM_3_9( expr ), expr ## 10
#define __ENUM_3_11( expr )		__ENUM_3_10( expr ), expr ## 11
#define __ENUM_3_12( expr )		__ENUM_3_11( expr ), expr ## 12
#define __ENUM_3_13( expr )		__ENUM_3_12( expr ), expr ## 13
#define __ENUM_3_14( expr )		__ENUM_3_13( expr ), expr ## 14
#define __ENUM_3_15( expr )		__ENUM_3_14( expr ), expr ## 15
#define __ENUM_3_16( expr )		__ENUM_3_15( expr ), expr ## 16
#define __ENUM_3_17( expr )		__ENUM_3_16( expr ), expr ## 17
#define __ENUM_3_18( expr )		__ENUM_3_17( expr ), expr ## 18
#define __ENUM_3_19( expr )		__ENUM_3_18( expr ), expr ## 19
#define __ENUM_3_20( expr )		__ENUM_3_19( expr ), expr ## 20

#define __ENUM_4_4( expr )		expr ## 4
#define __ENUM_4_5( expr )		__ENUM_4_4( expr ), expr ## 5
#define __ENUM_4_6( expr )		__ENUM_4_5( expr ), expr ## 6
#define __ENUM_4_7( expr )		__ENUM_4_6( expr ), expr ## 7
#define __ENUM_4_8( expr )		__ENUM_4_7( expr ), expr ## 8
#define __ENUM_4_9( expr )		__ENUM_4_8( expr ), expr ## 9
#define __ENUM_4_10( expr )		__ENUM_4_9( expr ), expr ## 10
#define __ENUM_4_11( expr )		__ENUM_4_10( expr ), expr ## 11
#define __ENUM_4_12( expr )		__ENUM_4_11( expr ), expr ## 12
#define __ENUM_4_13( expr )		__ENUM_4_12( expr ), expr ## 13
#define __ENUM_4_14( expr )		__ENUM_4_13( expr ), expr ## 14
#define __ENUM_4_15( expr )		__ENUM_4_14( expr ), expr ## 15
#define __ENUM_4_16( expr )		__ENUM_4_15( expr ), expr ## 16
#define __ENUM_4_17( expr )		__ENUM_4_16( expr ), expr ## 17
#define __ENUM_4_18( expr )		__ENUM_4_17( expr ), expr ## 18
#define __ENUM_4_19( expr )		__ENUM_4_18( expr ), expr ## 19
#define __ENUM_4_20( expr )		__ENUM_4_19( expr ), expr ## 20

#define __ENUM_5_5( expr )		expr ## 5
#define __ENUM_5_6( expr )		__ENUM_5_5( expr ), expr ## 6
#define __ENUM_5_7( expr )		__ENUM_5_6( expr ), expr ## 7
#define __ENUM_5_8( expr )		__ENUM_5_7( expr ), expr ## 8
#define __ENUM_5_9( expr )		__ENUM_5_8( expr ), expr ## 9
#define __ENUM_5_10( expr )		__ENUM_5_9( expr ), expr ## 10
#define __ENUM_5_11( expr )		__ENUM_5_10( expr ), expr ## 11
#define __ENUM_5_12( expr )		__ENUM_5_11( expr ), expr ## 12
#define __ENUM_5_13( expr )		__ENUM_5_12( expr ), expr ## 13
#define __ENUM_5_14( expr )		__ENUM_5_13( expr ), expr ## 14
#define __ENUM_5_15( expr )		__ENUM_5_14( expr ), expr ## 15
#define __ENUM_5_16( expr )		__ENUM_5_15( expr ), expr ## 16
#define __ENUM_5_17( expr )		__ENUM_5_16( expr ), expr ## 17
#define __ENUM_5_18( expr )		__ENUM_5_17( expr ), expr ## 18
#define __ENUM_5_19( expr )		__ENUM_5_18( expr ), expr ## 19
#define __ENUM_5_20( expr )		__ENUM_5_19( expr ), expr ## 20

#define __ENUM_6_6( expr )		expr ## 6
#define __ENUM_6_7( expr )		__ENUM_6_6( expr ), expr ## 7
#define __ENUM_6_8( expr )		__ENUM_6_7( expr ), expr ## 8
#define __ENUM_6_9( expr )		__ENUM_6_8( expr ), expr ## 9
#define __ENUM_6_10( expr )		__ENUM_6_9( expr ), expr ## 10
#define __ENUM_6_11( expr )		__ENUM_6_10( expr ), expr ## 11
#define __ENUM_6_12( expr )		__ENUM_6_11( expr ), expr ## 12
#define __ENUM_6_13( expr )		__ENUM_6_12( expr ), expr ## 13
#define __ENUM_6_14( expr )		__ENUM_6_13( expr ), expr ## 14
#define __ENUM_6_15( expr )		__ENUM_6_14( expr ), expr ## 15
#define __ENUM_6_16( expr )		__ENUM_6_15( expr ), expr ## 16
#define __ENUM_6_17( expr )		__ENUM_6_16( expr ), expr ## 17
#define __ENUM_6_18( expr )		__ENUM_6_17( expr ), expr ## 18
#define __ENUM_6_19( expr )		__ENUM_6_18( expr ), expr ## 19
#define __ENUM_6_20( expr )		__ENUM_6_19( expr ), expr ## 20

#define __ENUM_7_7( expr )		expr ## 7
#define __ENUM_7_8( expr )		__ENUM_7_7( expr ), expr ## 8
#define __ENUM_7_9( expr )		__ENUM_7_8( expr ), expr ## 9
#define __ENUM_7_10( expr )		__ENUM_7_9( expr ), expr ## 10
#define __ENUM_7_11( expr )		__ENUM_7_10( expr ), expr ## 11
#define __ENUM_7_12( expr )		__ENUM_7_11( expr ), expr ## 12
#define __ENUM_7_13( expr )		__ENUM_7_12( expr ), expr ## 13
#define __ENUM_7_14( expr )		__ENUM_7_13( expr ), expr ## 14
#define __ENUM_7_15( expr )		__ENUM_7_14( expr ), expr ## 15
#define __ENUM_7_16( expr )		__ENUM_7_15( expr ), expr ## 16
#define __ENUM_7_17( expr )		__ENUM_7_16( expr ), expr ## 17
#define __ENUM_7_18( expr )		__ENUM_7_17( expr ), expr ## 18
#define __ENUM_7_19( expr )		__ENUM_7_18( expr ), expr ## 19
#define __ENUM_7_20( expr )		__ENUM_7_19( expr ), expr ## 20

#define __ENUM_8_8( expr )		expr ## 8
#define __ENUM_8_9( expr )		__ENUM_8_8( expr ), expr ## 9
#define __ENUM_8_10( expr )		__ENUM_8_9( expr ), expr ## 10
#define __ENUM_8_11( expr )		__ENUM_8_10( expr ), expr ## 11
#define __ENUM_8_12( expr )		__ENUM_8_11( expr ), expr ## 12
#define __ENUM_8_13( expr )		__ENUM_8_12( expr ), expr ## 13
#define __ENUM_8_14( expr )		__ENUM_8_13( expr ), expr ## 14
#define __ENUM_8_15( expr )		__ENUM_8_14( expr ), expr ## 15
#define __ENUM_8_16( expr )		__ENUM_8_15( expr ), expr ## 16
#define __ENUM_8_17( expr )		__ENUM_8_16( expr ), expr ## 17
#define __ENUM_8_18( expr )		__ENUM_8_17( expr ), expr ## 18
#define __ENUM_8_19( expr )		__ENUM_8_18( expr ), expr ## 19
#define __ENUM_8_20( expr )		__ENUM_8_19( expr ), expr ## 20

#define __ENUM_9_9( expr )		expr ## 9
#define __ENUM_9_10( expr )		__ENUM_9_9( expr ), expr ## 10
#define __ENUM_9_11( expr )		__ENUM_9_10( expr ), expr ## 11
#define __ENUM_9_12( expr )		__ENUM_9_11( expr ), expr ## 12
#define __ENUM_9_13( expr )		__ENUM_9_12( expr ), expr ## 13
#define __ENUM_9_14( expr )		__ENUM_9_13( expr ), expr ## 14
#define __ENUM_9_15( expr )		__ENUM_9_14( expr ), expr ## 15
#define __ENUM_9_16( expr )		__ENUM_9_15( expr ), expr ## 16
#define __ENUM_9_17( expr )		__ENUM_9_16( expr ), expr ## 17
#define __ENUM_9_18( expr )		__ENUM_9_17( expr ), expr ## 18
#define __ENUM_9_19( expr )		__ENUM_9_18( expr ), expr ## 19
#define __ENUM_9_20( expr )		__ENUM_9_19( expr ), expr ## 20

#define __ENUM_10_10( expr )	expr ## 10
#define __ENUM_10_11( expr )	__ENUM_10_10( expr ), expr ## 11
#define __ENUM_10_12( expr )	__ENUM_10_11( expr ), expr ## 12
#define __ENUM_10_13( expr )	__ENUM_10_12( expr ), expr ## 13
#define __ENUM_10_14( expr )	__ENUM_10_13( expr ), expr ## 14
#define __ENUM_10_15( expr )	__ENUM_10_14( expr ), expr ## 15
#define __ENUM_10_16( expr )	__ENUM_10_15( expr ), expr ## 16
#define __ENUM_10_17( expr )	__ENUM_10_16( expr ), expr ## 17
#define __ENUM_10_18( expr )	__ENUM_10_17( expr ), expr ## 18
#define __ENUM_10_19( expr )	__ENUM_10_18( expr ), expr ## 19
#define __ENUM_10_20( expr )	__ENUM_10_19( expr ), expr ## 20

#define __ENUM_11_11( expr )	expr ## 11
#define __ENUM_11_12( expr )	__ENUM_11_11( expr ), expr ## 12
#define __ENUM_11_13( expr )	__ENUM_11_12( expr ), expr ## 13
#define __ENUM_11_14( expr )	__ENUM_11_13( expr ), expr ## 14
#define __ENUM_11_15( expr )	__ENUM_11_14( expr ), expr ## 15
#define __ENUM_11_16( expr )	__ENUM_11_15( expr ), expr ## 16
#define __ENUM_11_17( expr )	__ENUM_11_16( expr ), expr ## 17
#define __ENUM_11_18( expr )	__ENUM_11_17( expr ), expr ## 18
#define __ENUM_11_19( expr )	__ENUM_11_18( expr ), expr ## 19
#define __ENUM_11_20( expr )	__ENUM_11_19( expr ), expr ## 20

#define __ENUM_12_12( expr )	expr ## 12
#define __ENUM_12_13( expr )	__ENUM_12_12( expr ), expr ## 13
#define __ENUM_12_14( expr )	__ENUM_12_13( expr ), expr ## 14
#define __ENUM_12_15( expr )	__ENUM_12_14( expr ), expr ## 15
#define __ENUM_12_16( expr )	__ENUM_12_15( expr ), expr ## 16
#define __ENUM_12_17( expr )	__ENUM_12_16( expr ), expr ## 17
#define __ENUM_12_18( expr )	__ENUM_12_17( expr ), expr ## 18
#define __ENUM_12_19( expr )	__ENUM_12_18( expr ), expr ## 19
#define __ENUM_12_20( expr )	__ENUM_12_19( expr ), expr ## 20

#define __ENUM_13_13( expr )	expr ## 13
#define __ENUM_13_14( expr )	__ENUM_13_13( expr ), expr ## 14
#define __ENUM_13_15( expr )	__ENUM_13_14( expr ), expr ## 15
#define __ENUM_13_16( expr )	__ENUM_13_15( expr ), expr ## 16
#define __ENUM_13_17( expr )	__ENUM_13_16( expr ), expr ## 17
#define __ENUM_13_18( expr )	__ENUM_13_17( expr ), expr ## 18
#define __ENUM_13_19( expr )	__ENUM_13_18( expr ), expr ## 19
#define __ENUM_13_20( expr )	__ENUM_13_19( expr ), expr ## 20

#define __ENUM_14_14( expr )	expr ## 14
#define __ENUM_14_15( expr )	__ENUM_14_14( expr ), expr ## 15
#define __ENUM_14_16( expr )	__ENUM_14_15( expr ), expr ## 16
#define __ENUM_14_17( expr )	__ENUM_14_16( expr ), expr ## 17
#define __ENUM_14_18( expr )	__ENUM_14_17( expr ), expr ## 18
#define __ENUM_14_19( expr )	__ENUM_14_18( expr ), expr ## 19
#define __ENUM_14_20( expr )	__ENUM_14_19( expr ), expr ## 20

#define __ENUM_15_15( expr )	expr ## 15
#define __ENUM_15_16( expr )	__ENUM_15_15( expr ), expr ## 16
#define __ENUM_15_17( expr )	__ENUM_15_16( expr ), expr ## 17
#define __ENUM_15_18( expr )	__ENUM_15_17( expr ), expr ## 18
#define __ENUM_15_19( expr )	__ENUM_15_18( expr ), expr ## 19
#define __ENUM_15_20( expr )	__ENUM_15_19( expr ), expr ## 20

#define __ENUM_16_16( expr )	expr ## 16
#define __ENUM_16_17( expr )	__ENUM_16_16( expr ), expr ## 17
#define __ENUM_16_18( expr )	__ENUM_16_17( expr ), expr ## 18
#define __ENUM_16_19( expr )	__ENUM_16_18( expr ), expr ## 19
#define __ENUM_16_20( expr )	__ENUM_16_19( expr ), expr ## 20

#define __ENUM_17_17( expr )	expr ## 17
#define __ENUM_17_18( expr )	__ENUM_17_17( expr ), expr ## 18
#define __ENUM_17_19( expr )	__ENUM_17_18( expr ), expr ## 19
#define __ENUM_17_20( expr )	__ENUM_17_19( expr ), expr ## 20

#define __ENUM_18_18( expr )	expr ## 18
#define __ENUM_18_19( expr )	__ENUM_18_18( expr ), expr ## 19
#define __ENUM_18_20( expr )	__ENUM_18_19( expr ), expr ## 20

#define __ENUM_19_19( expr )	expr ## 19
#define __ENUM_19_20( expr )	__ENUM_19_19( expr ), expr ## 20

#define __ENUM_20_20( expr )	expr ## 20

#endif /* _RPI_HW_ENUMERATE_HPP_ */
