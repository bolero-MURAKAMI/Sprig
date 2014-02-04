/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_OF_HPP
#define SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_OF_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/policy/policy.hpp>

namespace sprig {
	//
	// is_policy_of
	//
	template<typename Tag, typename T, typename Enable = void>
	struct is_policy_of
		: public boost::mpl::false_
	{};
	template<typename Tag, typename T>
	struct is_policy_of<
		Tag,
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				tagged_policy<
					Tag,
					typename T::policy
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	template<typename Tag, typename T>
	struct is_policy_of<
		Tag,
		T,
		typename boost::enable_if<
			boost::is_base_and_derived<
				tagged_policy<
					Tag,
					typename T::policy
				>,
				T
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	template<typename Tag, typename T>
	struct is_policy_of<
		Tag,
		T,
		typename boost::enable_if<
			boost::is_base_and_derived<
				self_tagged_policy<Tag>,
				T
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_OF_HPP
