#ifndef SPRIG_MATH_HPP
#define SPRIG_MATH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cmath>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// integer_digits
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			typename boost::is_arithmetic<T>::type,
			typename is_call_copy_param<T>::type
		>,
		std::size_t
	>::type
	integer_digits(T const t) {
		return static_cast<std::size_t>(std::ceil(std::log10(t)));
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			typename boost::is_arithmetic<T>::type,
			typename boost::mpl::not_<typename is_call_copy_param<T>::type>::type
		>,
		std::size_t
	>::type
	integer_digits(T const& t) {
		return static_cast<std::size_t>(std::ceil(std::log10(t)));
	}
	//
	// numeric_abs
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<sprig::is_call_copy_param<T>, T>::type
	numeric_abs(T const t) {
		return t < 0 ? -t : t;
	}
	template<typename T>
	SPRIG_INLINE typename boost::disable_if<sprig::is_call_copy_param<T>, T>::type
	numeric_abs(T const& t) {
		return t < 0 ? -t : t;
	}
} // namespace sprig

#endif	// #ifndef SPRIG_MATH_HPP
