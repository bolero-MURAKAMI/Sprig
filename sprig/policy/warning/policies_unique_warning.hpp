#ifndef SPRIG_POLICY_POLICIES_UNIQUE_WARNING_HPP
#define SPRIG_POLICY_POLICIES_UNIQUE_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>
#include <sprig/policy/detail/policies_unique_check_impl.hpp>

//
// SPRIG_POLICYIES_UNIQUE_WARNING
//
#define SPRIG_POLICYIES_UNIQUE_WARNING(TAGS, TYPES) \
	SPRIG_POLICYIES_UNIQUE_CHECK_IMPL(TAGS, TYPES, SPRIG_POLICY_WARNING)

#endif	// #ifndef SPRIG_POLICY_POLICIES_UNIQUE_WARNING_HPP