#ifndef SPRIG_POLICY_POLICY_TRAITS_GET_POLIYCY_HPP
#define SPRIG_POLICY_POLICY_TRAITS_GET_POLIYCY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/policy/policy_traits/is_policy.hpp>

namespace sprig {
	//
	// get_policy
	//
	template<typename T, typename Enable = void>
	struct get_policy
		: public boost::mpl::void_
	{};
	template<typename T>
	struct get_policy<
		T,
		typename boost::enable_if<is_tagged_policy<T> >::type
	>
		: public boost::mpl::identity<typename T::policy>
	{};
	template<typename T>
	struct get_policy<
		T,
		typename boost::enable_if<is_self_tagged_policy<T> >::type
	>
		: public boost::mpl::identity<T>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_GET_POLIYCY_HPP
