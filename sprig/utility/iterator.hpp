/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_ITERATOR_HPP
#define SPRIG_UTILITY_ITERATOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iterator>

namespace sprig {
	//
	// get_advance
	//
	template<typename T, typename differenceT>
	SPRIG_INLINE T get_advance(T it, differenceT n) {
		std::advance(it, n);
		return it;
	};
	//
	// result_advanced
	//
	template<typename T, typename differenceT>
	SPRIG_INLINE T& result_advanced(T& it, differenceT n) {
		std::advance(it, n);
		return it;
	};
	//
	// result_never_advanced
	//
	template<typename T, typename differenceT>
	SPRIG_INLINE T result_never_advanced(T& it, differenceT n) {
		T temp_it = it;
		std::advance(it, n);
		return temp_it;
	};
} // namespace sprig

#endif	// #ifndef SPRIG_UTILITY_ITERATOR_HPP
