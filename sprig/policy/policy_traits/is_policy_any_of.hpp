/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_ANY_OF_HPP
#define SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_ANY_OF_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>

namespace sprig {
	//
	// is_policy_any_of
	//
	template<typename Tags, typename T, typename Enable = void>
	struct is_policy_any_of
		: public boost::mpl::false_
	{};
	template<typename Tags, typename T>
	struct is_policy_any_of<
		Tags,
		T,
		typename boost::enable_if<
			typename boost::mpl::fold<
				Tags,
				boost::mpl::false_,
				boost::mpl::or_<
					boost::mpl::_1,
					is_policy_of<boost::mpl::_2, T>
				>
			>::type
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_ANY_OF_HPP
