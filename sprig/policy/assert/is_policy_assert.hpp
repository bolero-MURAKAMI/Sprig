#ifndef SPRIG_POLICY_ASSERT_IS_POLICY_ASSERT_HPP
#define SPRIG_POLICY_ASSERT_IS_POLICY_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/assert/assert.hpp>
#include <sprig/policy/detail/is_policy_check_impl.hpp>

//
// SPRIG_IS_POLICY_ASSERT
//
#define SPRIG_IS_POLICY_ASSERT(TYPE) \
	SPRIG_IS_POLICY_CHECK_IMPL(TYPE, SPRIG_POLICY_ASSERT)

#endif	// #ifndef SPRIG_POLICY_ASSERT_IS_POLICY_ASSERT_HPP
