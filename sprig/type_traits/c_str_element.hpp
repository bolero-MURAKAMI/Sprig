/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_C_STR_ELEMENT_HPP
#define SPRIG_TYPE_TRAITS_C_STR_ELEMENT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/void.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_c_str.hpp>

namespace sprig {
	//
	// c_str_element
	//
	template<typename T, typename Enable = void>
	struct c_str_element {};
	template<typename T>
	struct c_str_element<T, typename boost::enable_if<is_c_str<T> >::type>
		: public boost::mpl::if_<
			boost::is_pointer<T>,
			typename boost::remove_pointer<T>::type,
			typename boost::remove_bounds<T>::type
		>
	{};
	template<typename T>
	struct c_str_element<T, typename boost::disable_if<is_c_str<T> >::type>
		: public boost::mpl::identity<boost::mpl::void_>
	{};
	//
	// c_str_element_value
	//
	template<typename T>
	struct c_str_element_value
		: public boost::remove_cv<
			typename c_str_element<T>::type
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_C_STR_ELEMENT_HPP
