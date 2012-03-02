#ifndef SPRIG_POLICY_POLICY_UNIQUE_WARNING_HPP
#define SPRIG_POLICY_POLICY_UNIQUE_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>
#include <sprig/policy/detail/policy_unique_check_impl.hpp>

//
// SPRIG_POLICY_UNIQUE_WARNING
//
#define SPRIG_POLICY_UNIQUE_WARNING(TAG, TYPES) \
	SPRIG_POLICY_UNIQUE_CHECK_IMPL(TAG, TYPES, SPRIG_POLICY_WARNING)

#endif	// #ifndef SPRIG_POLICY_POLICY_UNIQUE_WARNING_HPP
