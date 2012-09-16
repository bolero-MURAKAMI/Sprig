#ifndef SPRIG_NUMERIC_CONVERSION_CONVERTER_POLICIES_HPP
#define SPRIG_NUMERIC_CONVERSION_CONVERTER_POLICIES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/numeric/conversion/converter.hpp>
#include <boost/numeric/conversion/converter_policies.hpp>

namespace sprig {
	namespace numeric {
		//
		// range_check_result
		//
		enum range_check_result {
			c_in_range,
			c_negative_overflow,
			c_positive_overflow,
			c_bit_overflow
		};
		//
		// to_range_check_result
		//
		SPRIG_INLINE range_check_result to_range_check_result(boost::numeric::range_check_result r) {
			return static_cast<range_check_result>(r);
		}
		//
		// range_check
		//
		template<typename To, typename From>
		SPRIG_INLINE range_check_result range_check(From from) {
			typedef boost::numeric::converter<To, From> converter_type;
			return to_range_check_result(converter_type::out_of_range(from));
		}

		//
		// bad_numeric_cast
		//
		class bad_numeric_cast
			: public boost::bad_numeric_cast
		{
		public:
			virtual char const* what() const throw() {
				return "bad numeric conversion: overflow";
			}
		};
		//
		// negative_overflow
		//
		class negative_overflow
			: public bad_numeric_cast
		{
		public:
			virtual char const* what() const throw() {
				return "bad numeric conversion: negative overflow";
			}
		};
		//
		// positive_overflow
		//
		class positive_overflow
			: public bad_numeric_cast
		{
		public:
			virtual char const* what() const throw() {
				return "bad numeric conversion: negative overflow";
			}
		};
		//
		// bit_overflow
		//
		class bit_overflow
			: public bad_numeric_cast
		{
		public:
			virtual char const* what() const throw() {
				return "bad numeric conversion: bit overflow";
			}
		};

		//
		// def_overflow_handler
		//
		struct def_overflow_handler {
		public:
			void operator()(range_check_result r) const {
				switch (r) {
				case c_negative_overflow:
					throw negative_overflow();
					break;
				case c_positive_overflow:
					throw positive_overflow();
					break;
				case c_bit_overflow:
					throw bit_overflow();
					break;
				}
			}
		};
		//
		// positive_silent_overflow_handler
		//
		struct positive_silent_overflow_handler {
		public:
			void operator()(range_check_result r) const {
				switch (r) {
				case c_negative_overflow:
					throw negative_overflow();
					break;
				case c_bit_overflow:
					throw bit_overflow();
					break;
				}
			}
		};
		//
		// silent_overflow_handler
		//
		struct silent_overflow_handler {
		public:
			void operator()(range_check_result) const {}
		};
	}	// namespace numeric
}	// namespace sprig

#endif	// #ifndef SPRIG_NUMERIC_CONVERSION_CONVERTER_POLICIES_HPP
