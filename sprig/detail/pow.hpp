/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DETAIL_POW_HPP
#define SPRIG_DETAIL_POW_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	namespace detail {
		template<typename T>
		SPRIG_INLINE T
		pow2(T const& x) {
			return x * x;
		}
		template<typename T>
		SPRIG_INLINE T
		pow3(T const& x) {
			return x * x * x;
		}
		template<typename T>
		SPRIG_INLINE T
		pow4(T const& x) {
			return x * x * x * x;
		}
		template<typename T>
		SPRIG_INLINE T
		pow5(T const& x) {
			return x * x * x * x * x;
		}
	}	// namespace detail
}	// namespace sprig

#endif	// #ifndef SPRIG_DETAIL_POW_HPP
