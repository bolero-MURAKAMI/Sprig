/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_TRAITS_HPP
#define SPRIG_UCK_TRAITS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>

namespace sprig {
	namespace uck {
		//
		// traits
		//
		template<std::size_t sizeSizeN = 4, std::size_t intSizeN = 4>
		struct traits {
			static std::size_t const size_size = sizeSizeN;
			static std::size_t const int_size = intSizeN;
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_TRAITS_HPP
