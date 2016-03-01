/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_OPENSSL_HPP
#define SPRIG_CONFIG_LIBINFO_OPENSSL_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_OPENSSL)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <openssl/opensslv.h>

#		pragma message("sprig/config/libinfo/openssl.hpp")
#		pragma message("    OPENSSL_VERSION_NUMBER  = " BOOST_PP_STRINGIZE(OPENSSL_VERSION_NUMBER))
#		pragma message("    OPENSSL_VERSION_TEXT    = " BOOST_PP_STRINGIZE(OPENSSL_VERSION_TEXT))
#		pragma message("    OPENSSL_VERSION_PTEXT   = " BOOST_PP_STRINGIZE(OPENSSL_VERSION_PTEXT))
#		pragma message("    SHLIB_VERSION_HISTORY   = " BOOST_PP_STRINGIZE(SHLIB_VERSION_HISTORY))
#		pragma message("    SHLIB_VERSION_NUMBER    = " BOOST_PP_STRINGIZE(SHLIB_VERSION_NUMBER))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_OPENSSL)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_OPENSSL_HPP
