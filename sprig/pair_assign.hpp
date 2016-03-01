/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PAIR_ASSIGN_HPP
#define SPRIG_PAIR_ASSIGN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/utility/pair.hpp>

namespace sprig {
	//
	// pair_assign
	//
	template <typename Pair, typename T1, typename T2>
	SPRIG_INLINE void pair_assign(Pair& target, T1 const& v1, T2 const& v2) {
		sprig::first(target) = v1;
		sprig::second(target) = v2;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_PAIR_ASSIGN_HPP
