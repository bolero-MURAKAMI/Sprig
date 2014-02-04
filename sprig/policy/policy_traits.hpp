/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_HPP
#define SPRIG_POLICY_POLICY_TRAITS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

//
//	COMMENT: ポリシー判定
//
#include <sprig/policy/policy_traits/is_policy.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>
#include <sprig/policy/policy_traits/is_policy_any_of.hpp>
#include <sprig/policy/policy_traits/is_policy_unique.hpp>
#include <sprig/policy/policy_traits/is_policy_exist.hpp>

//
//	COMMENT: ポリシー取得
//
#include <sprig/policy/policy_traits/get_policy.hpp>
#include <sprig/policy/policy_traits/get_policy_tag.hpp>
#include <sprig/policy/policy_traits/select_policy.hpp>
#include <sprig/policy/policy_traits/collect_policy.hpp>

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_HPP
