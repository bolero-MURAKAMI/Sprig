/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_RATIONAL_HPP
#define SPRIG_UTILITY_RATIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/rational.hpp>
#include <sprig/cast_converter.hpp>

namespace sprig {
	namespace rational_detail {
		//
		// rational_arrange_digit_impl
		//
		template<typename IntType>
		SPRIG_INLINE IntType rational_arrange_digit_impl(
			IntType const& denom,
			IntType const& n,
			IntType const& current,
			IntType const& current_digit
			)
		{
			return (current % denom != 0)
				? rational_arrange_digit_impl(denom, n, current * n, current_digit + 1)
				: current_digit
				;
		}
		//
		// rational_arrange_factor_impl
		//
		template<typename IntType>
		SPRIG_INLINE IntType rational_arrange_factor_impl(
			IntType const& denom,
			IntType const& n,
			IntType const& current
			)
		{
			return (current % denom != 0)
				? rational_arrange_factor_impl(denom, n, current * n)
				: current
				;
		}
	}	// namespace rational_detail
	//
	// rational_cast
	//
	template<typename To, typename Converter, typename IntType>
	SPRIG_INLINE To rational_cast(boost::rational<IntType> const& from, Converter conv) {
		return conv(from.numerator()) / conv(from.denominator());
	}
	//
	// rational_converter_cast
	//
	template<typename Tag, typename To, typename IntType>
	SPRIG_INLINE To rational_converter_cast(boost::rational<IntType> const& from) {
		return sprig::converter_cast<Tag, To>(from.numerator()) / sprig::converter_cast<Tag, To>(from.denominator());
	}
	//
	// rational_arrange_digit
	//
	template<typename IntType>
	SPRIG_INLINE IntType rational_arrange_digit(
		boost::rational<IntType> const& v,
		IntType const& n = 10
		)
	{
		return rational_detail::rational_arrange_digit_impl<IntType>(v.denominator(), n, 1, 0);
	}
	//
	// rational_arrange_factor
	//
	template<typename IntType>
	SPRIG_INLINE IntType rational_arrange_factor(
		boost::rational<IntType> const& v,
		IntType const& n = 10
		)
	{
		return rational_detail::rational_arrange_factor_impl<IntType>(v.denominator(), n, 1);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_RATIONAL_HPP
