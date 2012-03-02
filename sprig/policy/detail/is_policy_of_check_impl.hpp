#ifndef SPRIG_POLICY_DETAIL_IS_POLICY_OF_CHECK_IMPL_HPP
#define SPRIG_POLICY_DETAIL_IS_POLICY_OF_CHECK_IMPL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>

//
// SPRIG_IS_POLICY_OF_CHECK_IMPL
//
#define SPRIG_IS_POLICY_OF_CHECK_IMPL(TAG, TYPE, DELECTIVE) \
	DELECTIVE(( \
		sprig::is_policy_of< \
			boost::mpl::identity<TAG>::type BOOST_PP_COMMA() \
			boost::mpl::identity<TYPE>::type \
		> \
		))

#endif	// #ifndef SPRIG_POLICY_DETAIL_IS_POLICY_OF_CHECK_IMPL_HPP
