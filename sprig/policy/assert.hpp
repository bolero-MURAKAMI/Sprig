/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_ASSERT_HPP
#define SPRIG_POLICY_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/assert/assert.hpp>

//
//	COMMENT: (TYPE)
//
#include <sprig/policy/assert/is_policy_assert.hpp>

//
//	COMMENT: (TAG, TYPE)
//
#include <sprig/policy/assert/is_policy_of_assert.hpp>

//
//	COMMENT: (TAGS, TYPE)
//
#include <sprig/policy/assert/is_policy_any_of_assert.hpp>

//
//	COMMENT: (TAG, TYPES)
//

#include <sprig/policy/assert/policy_unique_assert.hpp>
#include <sprig/policy/assert/policy_exist_assert.hpp>

//
//	COMMENT: (TAGS, TYPES)
//
#include <sprig/policy/assert/policies_requested_assert.hpp>
#include <sprig/policy/assert/policies_unique_assert.hpp>
#include <sprig/policy/assert/policies_exist_assert.hpp>

#endif	// #ifndef SPRIG_POLICY_ASSERT_HPP
