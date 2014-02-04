/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NUMERIC_CONVERSION_OVERFLOW_CAST_HPP
#define SPRIG_NUMERIC_CONVERSION_OVERFLOW_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <limits>
#include <sprig/numeric/conversion/converter_policies.hpp>

namespace sprig {
	namespace numeric {
		//
		// overflow_cast
		//
		template<typename To, typename From, typename OverflowHandler>
		SPRIG_INLINE To overflow_cast(From from, OverflowHandler handler) {
			range_check_result r = range_check<To>(from);
			handler(r);
			return r == c_positive_overflow
				? std::numeric_limits<To>::max()
				: r == c_negative_overflow
					? std::numeric_limits<To>::min()
					: static_cast<To>(from)
				;
		}
		template<typename To, typename From>
		SPRIG_INLINE To overflow_cast(From from) {
			return overflow_cast<To>(from, silent_overflow_handler());
		}
	}	// namespace numeric
}	// namespace sprig

#endif	// #ifndef SPRIG_NUMERIC_CONVERSION_OVERFLOW_CAST_HPP
