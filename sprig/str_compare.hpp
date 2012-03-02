#ifndef SPRIG_STR_COMPARE_HPP
#define SPRIG_STR_COMPARE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <iosfwd>
#include <algorithm>
#include <boost/utility/enable_if.hpp>
#include <sprig/str_length.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>

namespace sprig {
	//
	// str_compare
	//
	template<typename Elem>
	SPRIG_INLINE int str_compare(
		Elem const* lhs,
		Elem const* rhs,
		typename boost::enable_if<
			sprig::is_c_str<Elem const*>
		>::type* = 0
		)
	{
		return std::char_traits<Elem>::compare(
			lhs,
			rhs,
			(std::min)(sprig::str_length(lhs), sprig::str_length(rhs))
			);
	}
	template<typename T>
	SPRIG_INLINE int str_compare(
		typename T::value_type const* lhs,
		T const& rhs,
		typename boost::enable_if<
			sprig::is_basic_string<T>
		>::type* = 0
		)
	{
		return -rhs.compare(lhs);
	}
	template<typename T>
	SPRIG_INLINE int str_compare(
		T const& lhs,
		typename T::value_type const* rhs,
		typename boost::enable_if<
			sprig::is_basic_string<T>
		>::type* = 0
		)
	{
		return lhs.compare(rhs);
	}
	template<typename T>
	SPRIG_INLINE int str_compare(
		T const& lhs,
		T const& rhs,
		typename boost::enable_if<
			sprig::is_basic_string<T>
		>::type* = 0
		)
	{
		return lhs.compare(rhs);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_STR_COMPARE_HPP
