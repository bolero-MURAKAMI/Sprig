/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_FIXED_RANGE_HELPER_HPP
#define SPRIG_RANDOM_FIXED_RANGE_HELPER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	namespace random {
		namespace fixed_range_helper_detail {
			//
			// fixed_range_helper_impl
			//
			template<bool B, typename Engine>
			struct fixed_range_helper_impl {
			public:
				static bool const has_fixed_range = false;
			};
			template<typename Engine>
			struct fixed_range_helper_impl<true, Engine> {
			public:
				static bool const has_fixed_range = true;
				static typename Engine::result_type const min_value = Engine::min_value;
				static typename Engine::result_type const max_value = Engine::max_value;
			};
		}	// namespace random_adapter_detail
		//
		// fixed_range_helper
		//
		template<typename Engine>
		struct fixed_range_helper
			: public fixed_range_helper_detail::fixed_range_helper_impl<Engine::has_fixed_range, Engine>
		{};
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_FIXED_RANGE_HELPER_HPP
