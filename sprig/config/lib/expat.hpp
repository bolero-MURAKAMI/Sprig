/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_EXPAT_HPP
#define SPRIG_CONFIG_LIB_EXPAT_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/expat.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_EXPAT_BINARY
#	if !defined(UNICODE)
#		if !defined(_MT)
#			ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB
#			else	// #ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_D
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_D
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_D
#			endif	// #ifdef NDEBUG
#		else	// #if !defined(_MT)
#			ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_MT
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_MT
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_MT
#			else	// #ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_MT_D
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_MT_D
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_MT_D
#			endif	// #ifdef NDEBUG
#		endif	// #if !defined(_MT)
#	else	// #if !defined(UNICODE)
#		if !defined(_MT)
#			ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_W
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W
#			else	// #ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_D
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_W_D
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_D
#			endif	// #ifdef NDEBUG
#		else	// #if !defined(_MT)
#			ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_MT
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_W_MT
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_MT
#			else	// #ifdef NDEBUG
#				ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_MT_D
#					define SPRIG_LIBCONFIG_EXPAT_BINARY SPRIG_LIBCONFIG_EXPAT_LIB_W_MT_D
#				endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_LIB_W_MT_D
#			endif	// #ifdef NDEBUG
#		endif	// #if !defined(_MT)
#	endif	// #if !defined(UNICODE)
#endif	// #ifndef SPRIG_LIBCONFIG_EXPAT_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_EXPAT_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_EXPAT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/expat.hpp")
#	ifdef SPRIG_LIBCONFIG_EXPAT_BINARY
#		pragma message("    lib=" BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_EXPAT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_EXPAT_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/expat.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_EXPAT_HPP
