/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ENCODE_HEX_HPP
#define SPRIG_ENCODE_HEX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/array.hpp>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/split_literal.hpp>

namespace sprig {
	namespace encode_hex_detail {
		//
		// upper_table
		// lower_table
		//
		SPRIG_SPLIT_LITERAL_STRING_DECL(upper_table, "0123456789ABCDEF");
		SPRIG_SPLIT_LITERAL_STRING_DECL(lower_table, "0123456789abcdef");
		//
		// encode_high
		//
		template<typename Value, typename Char>
		SPRIG_INLINE Char encode_high(Value c, Char const* table) {
			return table[c >> 4 & 0x0F];
		}
		//
		// encode_low
		//
		template<typename Value, typename Char>
		SPRIG_INLINE Char encode_low(Value c, Char const* table) {
			return table[c & 0x0F];
		}
	}	// namespace encode_hex_detail
	//
	// encode_hex
	//
	template<typename Char, typename Range, typename OutputIterator>
	SPRIG_INLINE void encode_hex(
		Range const& range,
		OutputIterator out,
		bool lower = false,
		typename boost::enable_if<
			sprig::is_char_type<Char>
		>::type* = 0
		)
	{
		typedef Char char_type;
		typedef typename boost::range_value<Range>::type value_type;
		BOOST_MPL_ASSERT((sprig::is_char_type<value_type>));
		char_type const* table = lower
			? encode_hex_detail::lower_table::template get<char_type>()
			: encode_hex_detail::upper_table::template get<char_type>()
			;
		BOOST_FOREACH(value_type e, range) {
			*out++ = encode_hex_detail::encode_high(e, table);
			*out++ = encode_hex_detail::encode_low(e, table);
		}
	}
	template<typename Char, typename Range, typename OutputIterator>
	SPRIG_INLINE void encode_hex(
		Range const& range,
		OutputIterator out,
		bool lower = false,
		typename boost::enable_if<
			sprig::is_wchar_type<Char>
		>::type* = 0
		)
	{
		typedef Char char_type;
		typedef typename boost::range_value<Range>::type value_type;
		BOOST_MPL_ASSERT((sprig::is_char_type<value_type>));
		char_type const* table = lower
			? encode_hex_detail::lower_table::template get<char_type>()
			: encode_hex_detail::upper_table::template get<char_type>()
			;
		BOOST_FOREACH(value_type e, range) {
			*out++ = encode_hex_detail::encode_high(e, table);
			*out++ = encode_hex_detail::encode_low(e, table);
		}
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ENCODE_HEX_HPP
