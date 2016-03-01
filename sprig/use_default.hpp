/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_USE_DEFAULT_HPP
#define SPRIG_USE_DEFAULT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

namespace sprig {
	//
	// use_default
	//
	struct use_default;

	//
	// is_use_default
	//
	template<typename T>
	struct is_use_default
		: public boost::is_same<T, use_default>
	{};

	//
	// select_default
	//
	template<typename T, typename Default>
	struct select_default
		: public boost::mpl::if_<
			is_use_default<T>,
			Default,
			T
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_USE_DEFAULT_HPP
