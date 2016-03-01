/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_C_STR_HPP
#define SPRIG_C_STR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>

namespace sprig {
	//
	// c_str
	//
	template<typename Elem>
	SPRIG_INLINE Elem const* c_str(
		Elem const* str,
		typename boost::enable_if<
			sprig::is_c_str<Elem const*>
		>::type* = 0
		)
	{
		return str;
	}
	template<typename T>
	SPRIG_INLINE typename T::value_type const* c_str(
		T const& str,
		typename boost::enable_if<
			sprig::is_basic_string<T>
		>::type* = 0
		)
	{
		return str.c_str();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_C_STR_HPP
