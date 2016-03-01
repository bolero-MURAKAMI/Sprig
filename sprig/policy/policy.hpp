/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_HPP
#define SPRIG_POLICY_POLICY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	//
	// tagged_policy
	//
	template<typename Tag, typename T>
	struct tagged_policy {
	public:
		typedef Tag policy_tag;
		typedef T policy;
	};

	//
	// self_tagged_policy
	//
	template<typename Tag>
	struct self_tagged_policy {
	public:
		typedef Tag policy_tag;
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_HPP
