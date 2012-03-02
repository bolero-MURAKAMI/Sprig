#ifndef SPRIG_POLICY_ASSERT_POLICY_UNIQUE_ASSERT_HPP
#define SPRIG_POLICY_ASSERT_POLICY_UNIQUE_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/assert/assert.hpp>
#include <sprig/policy/detail/policy_unique_check_impl.hpp>

//
// SPRIG_POLICY_UNIQUE_ASSERT
//
#define SPRIG_POLICY_UNIQUE_ASSERT(TAG, TYPES) \
	SPRIG_POLICY_UNIQUE_CHECK_IMPL(TAG, TYPES, SPRIG_POLICY_ASSERT)

#endif	// #ifndef SPRIG_POLICY_ASSERT_POLICY_UNIQUE_ASSERT_HPP