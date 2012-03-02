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
