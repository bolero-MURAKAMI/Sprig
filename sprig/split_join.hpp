/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SPLIT_JOIN_HPP
#define SPRIG_SPLIT_JOIN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <climits>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/endian.hpp>

namespace sprig {
	//
	// integer_split
	//
	template<typename IntType, typename OutputIterator>
	void integer_split(
		IntType t,
		OutputIterator out,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 1)>
		>::type* = 0
		)
	{
		*out = static_cast<unsigned char>(t);
	}
	template<typename IntType, typename OutputIterator>
	void integer_split(
		IntType t,
		OutputIterator out,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 2)>
		>::type* = 0
		)
	{
		*out = static_cast<unsigned char>((t >> CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>(t & UCHAR_MAX);
	}
	template<typename IntType, typename OutputIterator>
	void integer_split(
		IntType t,
		OutputIterator out,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 4)>
		>::type* = 0
		)
	{
		*out = static_cast<unsigned char>((t >> 3 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 2 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>(t & UCHAR_MAX);
	}
	template<typename IntType, typename OutputIterator>
	void integer_split(
		IntType t,
		OutputIterator out,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 8)>
		>::type* = 0
		)
	{
		*out = static_cast<unsigned char>((t >> 7 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 6 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 5 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 4 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 3 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> 2 * CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>((t >> CHAR_BIT) & UCHAR_MAX);
		*++out = static_cast<unsigned char>(t & UCHAR_MAX);
	}
	//
	// integer_join
	//
	template<typename IntType, typename InputIterator>
	IntType integer_join(
		InputIterator in,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 1)>
		>::type* = 0
		)
	{
		return static_cast<IntType>(*in) & UCHAR_MAX;
	}
	template<typename IntType, typename InputIterator>
	IntType integer_join(
		InputIterator in,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 2)>
		>::type* = 0
		)
	{
		static IntType const uchar_max = UCHAR_MAX;
		IntType t1 = *in;
		IntType t2 = *++in;
		return (t1 << CHAR_BIT) & (uchar_max << CHAR_BIT)
			| t2 & uchar_max
			;
	}
	template<typename IntType, typename InputIterator>
	IntType integer_join(
		InputIterator in,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 4)>
		>::type* = 0
		)
	{
		static IntType const uchar_max = UCHAR_MAX;
		IntType t1 = *in;
		IntType t2 = *++in;
		IntType t3 = *++in;
		IntType t4 = *++in;
		return (t1 << 3 * CHAR_BIT) & (uchar_max << 3 * CHAR_BIT)
			| (t2 << 2 * CHAR_BIT) & (uchar_max << 2 * CHAR_BIT)
			| (t3 << CHAR_BIT) & (uchar_max << CHAR_BIT)
			| t4 & uchar_max
			;
	}
	template<typename IntType, typename InputIterator>
	IntType integer_join(
		InputIterator in,
		typename boost::enable_if<
			boost::mpl::bool_<(sizeof(IntType) == 8)>
		>::type* = 0
		)
	{
		static IntType const uchar_max = UCHAR_MAX;
		IntType t1 = *in;
		IntType t2 = *++in;
		IntType t3 = *++in;
		IntType t4 = *++in;
		IntType t5 = *++in;
		IntType t6 = *++in;
		IntType t7 = *++in;
		IntType t8 = *++in;
		return (t1 << 7 * CHAR_BIT) & (uchar_max << 7 * CHAR_BIT)
			| (t2 << 6 * CHAR_BIT) & (uchar_max << 6 * CHAR_BIT)
			| (t3 << 5 * CHAR_BIT) & (uchar_max << 5 * CHAR_BIT)
			| (t4 << 4 * CHAR_BIT) & (uchar_max << 4 * CHAR_BIT)
			| (t5 << 3 * CHAR_BIT) & (uchar_max << 3 * CHAR_BIT)
			| (t6 << 2 * CHAR_BIT) & (uchar_max << 2 * CHAR_BIT)
			| (t7 << CHAR_BIT) & (uchar_max << CHAR_BIT)
			| t8 & uchar_max
			;
	}
	//
	// float_split
	//
	template<typename FloatType, typename OutputIterator>
	void float_split(
		FloatType const& t,
		OutputIterator out
		)
	{
		typedef unsigned char const* pointer;
		pointer p = reinterpret_cast<pointer>(&t);
		if (sprig::is_little_endian()) {
			for (pointer i = p + sizeof(FloatType) - 1, last = p - 1; i != last; --i) {
				*out = *i;
				++out;
			}
		} else {
			for (pointer i = p, last = p + sizeof(FloatType); i != last; ++i) {
				*out = *i;
				++out;
			}
		}
	}
	//
	// float_join
	//
	template<typename FloatType, typename InputIterator>
	FloatType float_join(
		InputIterator in
		)
	{
		typedef unsigned char* pointer;
		FloatType result;
		pointer p = reinterpret_cast<pointer>(&result);
		if (sprig::is_little_endian()) {
			for (pointer i = p + sizeof(FloatType) - 1, last = p - 1; i != last; --i) {
				*i = *in;
				++in;
			}
		} else {
			for (pointer i = p, last = p + sizeof(FloatType); i != last; ++i) {
				*i = *in;
				++in;
			}
		}
		return result;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_SPLIT_JOIN_HPP
