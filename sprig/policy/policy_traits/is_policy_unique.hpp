/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_UNIQUE_HPP
#define SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_UNIQUE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/bool.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>

namespace sprig {
	//
	// is_policy_unique
	//
	template<typename Tag, typename Types>
	struct is_policy_unique
		: public boost::mpl::bool_<
			boost::mpl::count_if<
				Types,
				is_policy_of<Tag, boost::mpl::_1>
			>::value <= 1
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_UNIQUE_HPP
