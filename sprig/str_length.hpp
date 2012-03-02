#ifndef SPRIG_STR_LENGTH_HPP
#define SPRIG_STR_LENGTH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <iosfwd>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>

namespace sprig {
	//
	// str_length
	//
	template<typename Elem>
	SPRIG_INLINE std::size_t str_length(
		Elem const* str,
		typename boost::enable_if<
			sprig::is_c_str<Elem const*>
		>::type* = 0
		)
	{
		return std::char_traits<Elem>::length(str);
	}
	template<typename T>
	SPRIG_INLINE typename T::size_type str_length(
		T const& str,
		typename boost::enable_if<
			sprig::is_basic_string<T>
		>::type* = 0
		)
	{
		return str.size();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_STR_LENGTH_HPP
