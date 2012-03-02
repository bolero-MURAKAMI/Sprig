#ifndef SPRIG_POLICY_DETAIL_IS_POLICY_CHECK_IMPL_HPP
#define SPRIG_POLICY_DETAIL_IS_POLICY_CHECK_IMPL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <sprig/policy/policy_traits/is_policy.hpp>

//
// SPRIG_IS_POLICY_CHECK_IMPL
//
#define SPRIG_IS_POLICY_CHECK_IMPL(TYPE, DELECTIVE) \
	DELECTIVE((sprig::is_policy<boost::mpl::identity<TYPE>::type>))

#endif	// #ifndef SPRIG_POLICY_DETAIL_IS_POLICY_CHECK_IMPL_HPP
