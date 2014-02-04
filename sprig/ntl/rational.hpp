/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NTL_RATIONAL_HPP
#define SPRIG_NTL_RATIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/rational.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/external/ntl/rr.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>
#include <sprig/ntl/to_RR.hpp>
#include <sprig/ntl/significant.hpp>
#include <sprig/ntl/big_int.hpp>

namespace sprig {
	//
	// typedefs
	//
	typedef boost::rational<big_int> big_rational;

	//
	// to_rational
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<sprig::is_call_copy_param<T>, big_rational>::type
	to_rational(T const target) {
		NTL::RR value = to_RR(target);
		big_rational result(value.mantissa(), 1);
		if (value.exponent() >= 0) {
			result *= NTL::power(to_ZZ(2), value.exponent());
		} else {
			result /= NTL::power(to_ZZ(2), -value.exponent());
		}
		return result;
	}
	template<typename T>
	SPRIG_INLINE typename boost::disable_if<sprig::is_call_copy_param<T>, big_rational>::type
	to_rational(T const& target) {
		NTL::RR value = to_RR(target);
		big_rational result(value.mantissa(), 1);
		if (value.exponent() >= 0) {
			result *= NTL::power(to_ZZ(2), value.exponent());
		} else {
			result /= NTL::power(to_ZZ(2), -value.exponent());
		}
		return result;
	}

	//
	// to_rational_significant
	//
	// specialization to_rational_significant: is_integral(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_integral<T>,
		big_rational
	>::type
	to_rational_significant(T const target) {
		return big_rational(to_ZZ_full_significant(target));
	}
	//
	// specialization to_rational_significant: is_float(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_float<T>,
		big_rational
	>::type
	to_rational_significant(T const target) {
		return big_rational(to_ZZ_full_significant(target), significant<T>::digits10_ZZ());
	}
	//
	// specialization to_rational_significant: is_c_str(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_c_str<T>,
		big_rational
	>::type
	to_rational_significant(T const target) {
		return big_rational(
			to_ZZ_full_significant(target),
			NTL::power(to_ZZ(10), static_cast<long>(significant<T>::digits(target)))
			);
	}
	//
	// specialization to_rational_significant: is_basic_string(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_basic_string<T>,
		big_rational
	>::type
	to_rational_significant(T const& target) {
		return big_rational(
			to_ZZ_full_significant(target),
			NTL::power(to_ZZ(10), static_cast<long>(significant<T>::digits(target)))
			);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_RATIONAL_HPP
