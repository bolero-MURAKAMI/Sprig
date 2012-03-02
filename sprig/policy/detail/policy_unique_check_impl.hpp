#ifndef SPRIG_POLICY_DETAIL_POLICY_UNIQUE_CHECK_IMPL_HPP
#define SPRIG_POLICY_DETAIL_POLICY_UNIQUE_CHECK_IMPL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <sprig/policy/policy_checks/policy_unique_check.hpp>

//
// SPRIG_POLICY_UNIQUE_CHECK_IMPL
//
#define SPRIG_POLICY_UNIQUE_CHECK_IMPL(TAG, TYPES, DELECTIVE) \
	DELECTIVE(( \
		sprig::policy_unique_check< \
			boost::mpl::identity<TAG>::type BOOST_PP_COMMA() \
			boost::mpl::identity<TYPES>::type \
		>::type \
		))

#endif	// #ifndef SPRIG_POLICY_DETAIL_POLICY_UNIQUE_CHECK_IMPL_HPP
