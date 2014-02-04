/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_INLINE_HPP
#define SPRIG_CONFIG_INLINE_HPP

#include <sprig/config/pragma_once.hpp>
#include <sprig/config/forceinline.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifndef SPRIG_CONFIG_NO_INLINE
#	ifdef SPRIG_CONFIG_FORCE_INLINE
#		define SPRIG_INLINE SPRIG_FORCEINLINE
#	else	// #ifdef SPRIG_CONFIG_FORCE_INLINE
#		define SPRIG_INLINE inline
#	endif	// #ifdef SPRIG_CONFIG_FORCE_INLINE
#else	// #ifndef SPRIG_CONFIG_NO_INLINE
#	define SPRIG_INLINE
#endif	// #ifndef SPRIG_CONFIG_NO_INLINE

#endif	// #ifndef SPRIG_CONFIG_INLINE_HPP
