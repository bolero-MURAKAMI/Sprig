/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_DXSDK_HPP
#define SPRIG_CONFIG_LIBINFO_DXSDK_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_DXSDK)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <dxsdkver.h>
#		include <boost/preprocessor/stringize.hpp>

#		pragma message("sprig/config/libinfo/dxsdk.hpp")
#		pragma message("    _DXSDK_BUILD_MAJOR      = " BOOST_PP_STRINGIZE(_DXSDK_BUILD_MAJOR))
#		pragma message("    _DXSDK_BUILD_MINOR      = " BOOST_PP_STRINGIZE(_DXSDK_BUILD_MINOR))
#		pragma message("    _DXSDK_PRODUCT_MAJOR    = " BOOST_PP_STRINGIZE(_DXSDK_PRODUCT_MAJOR))
#		pragma message("    _DXSDK_PRODUCT_MINOR    = " BOOST_PP_STRINGIZE(_DXSDK_PRODUCT_MINOR))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_DXSDK)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_DXSDK_HPP
