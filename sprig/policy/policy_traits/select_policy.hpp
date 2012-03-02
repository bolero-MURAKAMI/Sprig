#ifndef SPRIG_POLICY_POLICY_TRAITS_SELECT_POLIYCY_HPP
#define SPRIG_POLICY_POLICY_TRAITS_SELECT_POLIYCY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <sprig/policy/policy.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>
#include <sprig/policy/policy_traits/get_policy.hpp>

namespace sprig {
	//
	// select_policy
	//
	template<
		typename Sequence,
		typename Tag,
		typename Default = boost::mpl::void_
	>
	struct select_policy
		: public get_policy<
			typename boost::mpl::eval_if<
				typename boost::mpl::count_if<
					Sequence,
					is_policy_of<Tag, boost::mpl::_1>
				>::type,
				typename boost::mpl::deref<
					boost::mpl::find_if<
						Sequence,
						is_policy_of<Tag, boost::mpl::_1>
					>
				>::type,
				boost::mpl::identity<tagged_policy<Tag, Default> >
			>::type
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_SELECT_POLIYCY_HPP
