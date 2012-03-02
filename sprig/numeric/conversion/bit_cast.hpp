#ifndef SPRIG_NUMERIC_CONVERSION_BIT_CAST_HPP
#define SPRIG_NUMERIC_CONVERSION_BIT_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/make_unsigned.hpp>
#include <sprig/numeric/conversion/converter_policies.hpp>

namespace sprig {
	namespace numeric {
		//
		// bit_cast
		//
		template<typename To, typename From, typename OverflowHandler>
		SPRIG_INLINE To bit_cast(From from, OverflowHandler handler) {
			typedef typename boost::make_unsigned<To>::type unsigned_to_type;
			typedef typename boost::make_unsigned<From>::type unsigned_from_type;
			To to = static_cast<To>(static_cast<unsigned_from_type>(from) & ~unsigned_to_type(0));
			handler(
				static_cast<unsigned_from_type>(from) ^ static_cast<unsigned_to_type>(to)
					? c_bit_overflow
					: c_in_range
				);
			return to;
		}
		template<typename To, typename From>
		SPRIG_INLINE To bit_cast(From from) {
			return bit_cast<To>(from, def_overflow_handler());
		}
		//
		// bit_silent_cast
		//
		template<typename To, typename From>
		SPRIG_INLINE To bit_silent_cast(From from) {
			return bit_cast<To>(from, silent_overflow_handler());
		}
	}	// namespace numeric
}	// namespace sprig

#endif	// #ifndef SPRIG_NUMERIC_CONVERSION_BIT_CAST_HPP
