/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_NATIVE_FORCEINLINE_HPP
#define SPRIG_CONFIG_NATIVE_FORCEINLINE_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(_MSC_VER) || defined(__GNUC__)
#	define SPRIG_HAS_NATIVE_FORCEINLINE
#	if defined(_MSC_VER)
#		define SPRIG_NATIVE_FORCEINLINE __forceinline
#	elif defined(__GNUC__)
#		define SPRIG_NATIVE_FORCEINLINE __attribute__((always_inline))
#	endif
#endif	// #if defined(_MSC_VER) || defined(__GNUC__)

#endif	// #ifndef SPRIG_CONFIG_NATIVE_FORCEINLINE_HPP
