/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_STR_CAST_HPP
#define SPRIG_KRKR_TJS_STR_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/str_cast.hpp>

namespace sprig {
	//
	// specialization str_cast_traits
	//
	template<typename T>
	struct str_cast_traits<
		T,
		typename boost::enable_if<
			boost::is_same<T, tTJSString>
		>::type
	> {
		typedef tjs_char value_type;
		static value_type const* c_str(T const& str) {
			return str.c_str();
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_STR_CAST_HPP
