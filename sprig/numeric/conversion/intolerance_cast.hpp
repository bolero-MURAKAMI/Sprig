/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NUMERIC_CONVERSION_INTOLERANCE_CAST_HPP
#define SPRIG_NUMERIC_CONVERSION_INTOLERANCE_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/numeric/conversion/converter_policies.hpp>

namespace sprig {
	namespace numeric {
		//
		// intolerance_cast
		//
		template<typename To, typename From, typename OverflowHandler>
		SPRIG_INLINE To intolerance_cast(From from, OverflowHandler handler) {
			handler(range_check<To>(from));
			return static_cast<To>(from);
		}
		template<typename To, typename From>
		SPRIG_INLINE To intolerance_cast(From from) {
			return intolerance_cast<To>(from, def_overflow_handler());
		}
	}	// namespace numeric
}	// namespace sprig

#endif	// #ifndef SPRIG_NUMERIC_CONVERSION_INTOLERANCE_CAST_HPP
