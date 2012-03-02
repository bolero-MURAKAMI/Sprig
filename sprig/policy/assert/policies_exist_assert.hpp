#ifndef SPRIG_POLICY_ASSERT_POLICIES_EXIST_ASSERT_HPP
#define SPRIG_POLICY_ASSERT_POLICIES_EXIST_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/assert/assert.hpp>
#include <sprig/policy/detail/policies_exist_check_impl.hpp>

//
// SPRIG_POLICYIES_EXIST_ASSERT
//
#define SPRIG_POLICYIES_EXIST_ASSERT(TAGS, TYPES) \
	SPRIG_POLICYIES_EXIST_CHECK_IMPL(TAGS, TYPES, SPRIG_POLICY_ASSERT)

#endif	// #ifndef SPRIG_POLICY_ASSERT_POLICIES_EXIST_ASSERT_HPP