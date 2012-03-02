#ifndef SPRIG_NUMERIC_CONVERSION_POSITIVE_OVERFLOW_CAST_HPP
#define SPRIG_NUMERIC_CONVERSION_POSITIVE_OVERFLOW_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <limits>
#include <sprig/numeric/conversion/converter_policies.hpp>

namespace sprig {
	namespace numeric {
		//
		// positive_overflow_cast
		//
		template<typename To, typename From, typename OverflowHandler>
		SPRIG_INLINE To positive_overflow_cast(From from, OverflowHandler handler) {
			range_check_result r = range_check<To>(from);
			handler(r);
			return r == c_positive_overflow
				? std::numeric_limits<To>::max()
				: static_cast<To>(from)
				;
		}
		template<typename To, typename From>
		SPRIG_INLINE To positive_overflow_cast(From from) {
			return positive_overflow_cast<To>(from, positive_silent_overflow_handler());
		}
	}	// namespace numeric
}	// namespace sprig

#endif	// #ifndef SPRIG_NUMERIC_CONVERSION_POSITIVE_OVERFLOW_CAST_HPP
