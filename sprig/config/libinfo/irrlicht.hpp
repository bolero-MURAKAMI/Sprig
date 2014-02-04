/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_IRRLICHT_HPP
#define SPRIG_CONFIG_LIBINFO_IRRLICHT_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_IRRLICHT)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <IrrCompileConfig.h>

#		pragma message("sprig/config/libinfo/irrlicht.hpp")
#		pragma message("    IRRLICHT_VERSION_MAJOR      = " BOOST_PP_STRINGIZE(IRRLICHT_VERSION_MAJOR))
#		pragma message("    IRRLICHT_VERSION_MINOR      = " BOOST_PP_STRINGIZE(IRRLICHT_VERSION_MINOR))
#		pragma message("    IRRLICHT_VERSION_REVISION   = " BOOST_PP_STRINGIZE(IRRLICHT_VERSION_REVISION))
#		pragma message("    IRRLICHT_SDK_VERSION        = " BOOST_PP_STRINGIZE(IRRLICHT_SDK_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_IRRLICHT)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_IRRLICHT_HPP
