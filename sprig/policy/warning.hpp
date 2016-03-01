/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_WARNING_HPP
#define SPRIG_POLICY_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>

//
//	COMMENT: (TYPE)
//
#include <sprig/policy/warning/is_policy_warning.hpp>

//
//	COMMENT: (TAG, TYPE)
//
#include <sprig/policy/warning/is_policy_of_warning.hpp>

//
//	COMMENT: (TAGS, TYPE)
//
#include <sprig/policy/warning/is_policy_any_of_warning.hpp>

//
//	COMMENT: (TAG, TYPES)
//

#include <sprig/policy/warning/policy_unique_warning.hpp>
#include <sprig/policy/warning/policy_exist_warning.hpp>

//
//	COMMENT: (TAGS, TYPES)
//
#include <sprig/policy/warning/policies_requested_warning.hpp>
#include <sprig/policy/warning/policies_unique_warning.hpp>
#include <sprig/policy/warning/policies_exist_warning.hpp>

#endif	// #ifndef SPRIG_POLICY_WARNING_HPP
