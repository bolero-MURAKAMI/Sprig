/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_LIBJPEG_HPP
#define SPRIG_CONFIG_LIBINFO_LIBJPEG_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBJPEG)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <jversion.h>
#		include <jpeglib.h>

#		pragma message("sprig/config/libinfo/libjpeg.hpp")
#		pragma message("    JVERSION            = " BOOST_PP_STRINGIZE(JVERSION))
#		pragma message("    JCOPYRIGHT          = " BOOST_PP_STRINGIZE(JCOPYRIGHT))
#		pragma message("    JPEG_LIB_VERSION    = " BOOST_PP_STRINGIZE(JPEG_LIB_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBJPEG)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_LIBJPEG_HPP
