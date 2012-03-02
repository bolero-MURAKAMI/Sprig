#ifndef SPRIG_POLICY_IS_POLICY_WARNING_HPP
#define SPRIG_POLICY_IS_POLICY_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>
#include <sprig/policy/detail/is_policy_check_impl.hpp>

//
// SPRIG_IS_POLICY_WARNING
//
#define SPRIG_IS_POLICY_WARNING(TYPE) \
	SPRIG_IS_POLICY_CHECK_IMPL(TYPE, SPRIG_POLICY_WARNING)

#endif	// #ifndef SPRIG_POLICY_IS_POLICY_WARNING_HPP
