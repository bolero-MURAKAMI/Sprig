/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICIES_REQUESTED_WARNING_HPP
#define SPRIG_POLICY_POLICIES_REQUESTED_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>
#include <sprig/policy/detail/policies_requested_check_impl.hpp>

//
// SPRIG_POLICYIES_REQUESTED_WARNING
//
#define SPRIG_POLICYIES_REQUESTED_WARNING(TAGS, TYPES) \
	SPRIG_POLICYIES_REQUESTED_CHECK_IMPL(TAGS, TYPES, SPRIG_POLICY_WARNING)

#endif	// #ifndef SPRIG_POLICY_POLICIES_REQUESTED_WARNING_HPP
