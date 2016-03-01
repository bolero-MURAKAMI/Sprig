/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_EXIST_WARNING_HPP
#define SPRIG_POLICY_POLICY_EXIST_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/policy/warning/warning.hpp>
#include <sprig/policy/detail/policy_exist_check_impl.hpp>

//
// SPRIG_POLICY_EXIST_WARNING
//
#define SPRIG_POLICY_EXIST_WARNING(TAG, TYPES) \
	SPRIG_POLICY_EXIST_CHECK_IMPL(TAG, TYPES, SPRIG_POLICY_WARNING)

#endif	// #ifndef SPRIG_POLICY_POLICY_EXIST_WARNING_HPP
