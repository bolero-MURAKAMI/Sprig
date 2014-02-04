/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_WINDOWS_HPP
#define SPRIG_CONFIG_LIB_WINDOWS_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_MUST_NOMINMAX
#	if defined(_WINDEF_) && !defined(NOMINMAX)
#		error Error: undefined NOMINMAX. (Request: must define NOMINMAX.)
#	endif	// #if defined(_WINDEF_) && !defined(NOMINMAX)
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif	// #ifndef NOMINMAX
#endif	// #ifdef SPRIG_CONFIG_MUST_NOMINMAX

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/windows.hpp")
#	ifdef NOMINMAX
#		pragma message("    Defined: NOMINMAX.")
#	endif	// #ifdef NOMINMAX
#	ifdef WIN32_LEAN_AND_MEAN
#		pragma message("    Defined: WIN32_LEAN_AND_MEAN.")
#	endif	// #ifdef WIN32_LEAN_AND_MEAN
#	ifdef SPRIG_CONFIG_MUST_NOMINMAX
#		pragma message("    Request: must define NOMINMAX.")
#	endif	// #ifdef SPRIG_CONFIG_MUST_NOMINMAX
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#endif	// #ifndef SPRIG_CONFIG_LIB_WINDOWS_HPP
