/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_IS_CONST_REFERENCE_HPP
#define SPRIG_TYPE_TRAITS_IS_CONST_REFERENCE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace sprig {
	//
	// is_const_reference
	//
	template<typename T>
	struct is_const_reference
		: public boost::mpl::and_<
			boost::is_reference<T>,
			boost::is_const<
				typename boost::remove_reference<T>::type
			>
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_CONST_REFERENCE_HPP
