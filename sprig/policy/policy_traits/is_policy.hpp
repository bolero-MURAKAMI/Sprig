/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_HPP
#define SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/policy/policy.hpp>

namespace sprig {
	//
	// is_tagged_policy
	//
	template<typename T, typename Enable = void>
	struct is_tagged_policy
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_tagged_policy<
		T,
		typename boost::enable_if<
			boost::mpl::or_<
				typename boost::is_same<
					T,
					tagged_policy<
						typename T::policy_tag,
						typename T::policy
					>
				>::type,
				typename boost::is_base_and_derived<
					tagged_policy<
						typename T::policy_tag,
						typename T::policy
					>,
					T
				>::type
			>
		>::type
	>
		: public boost::mpl::true_
	{};

	//
	// is_self_tagged_policy
	//
	template<typename T, typename Enable = void>
	struct is_self_tagged_policy
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_self_tagged_policy<
		T,
		typename boost::enable_if<
			boost::is_base_and_derived<
				self_tagged_policy<
					typename T::policy_tag
				>,
				T
			>
		>::type
	>
		: public boost::mpl::true_
	{};

	//
	// is_policy
	//
	template<typename T, typename Enable = void>
	struct is_policy
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_policy<
		T,
		typename boost::enable_if<
			boost::mpl::or_<
				typename is_tagged_policy<T>::type,
				typename is_self_tagged_policy<T>::type
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_IS_POLIYCY_HPP
