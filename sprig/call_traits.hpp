/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CALL_TRAITS_HPP
#define SPRIG_CALL_TRAITS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/call_traits.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/if.hpp>

namespace sprig {
	//
	// call_traits
	//
	template<typename T>
	struct call_traits {
		typedef typename boost::call_traits<T>::value_type value_type;
		typedef typename boost::call_traits<T>::reference reference;
		typedef typename boost::call_traits<T>::const_reference const_reference;
		typedef typename boost::call_traits<T>::param_type param_type;
		typedef typename boost::mpl::if_<
			typename boost::is_reference<param_type>::type,
			const_reference,
			value_type
		>::type getter_type;
	};
	template<>
	struct call_traits<void> {
		typedef void value_type;
		typedef void reference;
		typedef void const_reference;
		typedef void param_type;
		typedef void getter_type;
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CALL_TRAITS_HPP
