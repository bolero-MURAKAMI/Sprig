/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_IS_C_STR_HPP
#define SPRIG_TYPE_TRAITS_IS_C_STR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>

namespace sprig {
	//
	// is_c_str_pointer
	//
	template<typename T>
	struct is_c_str_pointer
		: public boost::mpl::and_<
			boost::is_pointer<T>,
			boost::mpl::or_<
				sprig::is_char_type<typename boost::remove_pointer<T>::type>,
				sprig::is_wchar_type<typename boost::remove_pointer<T>::type>
			>
		>
	{};
	//
	// is_c_str_array
	//
	template<typename T>
	struct is_c_str_array
		: public boost::mpl::and_<
			boost::is_array<T>,
			boost::mpl::or_<
				sprig::is_char_type<typename boost::remove_bounds<T>::type>,
				sprig::is_wchar_type<typename boost::remove_bounds<T>::type>
			>
		>
	{};
	//
	// is_c_str
	//
	template<typename T>
	struct is_c_str
		: public boost::mpl::or_<
			is_c_str_pointer<T>,
			is_c_str_array<T>
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_C_STR_HPP
