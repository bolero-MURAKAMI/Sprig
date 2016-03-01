/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_ZLIB_HPP
#define SPRIG_CONFIG_LIB_ZLIB_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/zlib.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_ZLIB_BINARY
#	if defined(_MT) && defined(_DLL)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT
#				define SPRIG_LIBCONFIG_ZLIB_BINARY SPRIG_LIBCONFIG_ZLIB_LIB_MT
#			endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_GD
#				define SPRIG_LIBCONFIG_ZLIB_BINARY SPRIG_LIBCONFIG_ZLIB_LIB_MT_GD
#			endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_GD
#		endif	// #ifdef NDEBUG
#	elif defined(_MT)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_S
#				define SPRIG_LIBCONFIG_ZLIB_BINARY SPRIG_LIBCONFIG_ZLIB_LIB_MT_S
#			endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_S
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_SGD
#				define SPRIG_LIBCONFIG_ZLIB_BINARY SPRIG_LIBCONFIG_ZLIB_LIB_MT_SGD
#			endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_LIB_MT_SGD
#		endif	// #ifdef NDEBUG
#	endif
#endif	// #ifndef SPRIG_LIBCONFIG_ZLIB_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_ZLIB_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ZLIB_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/zlib.hpp")
#	ifdef SPRIG_LIBCONFIG_ZLIB_BINARY
#		pragma message("    lib=" BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ZLIB_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ZLIB_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/zlib.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_ZLIB_HPP
