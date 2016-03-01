/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_OPENSSL_HPP
#define SPRIG_CONFIG_LIB_OPENSSL_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/openssl.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY
#	if defined(_MT) && defined(_DLL)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD
#				define SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD_D
#				define SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD_D
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MD_D
#		endif	// #ifdef NDEBUG
#	elif defined(_MT)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT
#				define SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT_D
#				define SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT_D
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_LIB_MT_D
#		endif	// #ifdef NDEBUG
#	endif
#endif	// #ifndef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY

#ifndef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY
#	if defined(_MT) && defined(_DLL)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD
#				define SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD_D
#				define SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD_D
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MD_D
#		endif	// #ifdef NDEBUG
#	elif defined(_MT)
#		ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT
#				define SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT
#		else	// #ifdef NDEBUG
#			ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT_D
#				define SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT_D
#			endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_LIB_MT_D
#		endif	// #ifdef NDEBUG
#	endif
#endif	// #ifndef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY
#	ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/openssl.hpp")
#	ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY
#		pragma message("    lib=" BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_LIBEAY_BINARY
#	ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY
#		pragma message("    lib=" BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_OPENSSL_SSLEAY_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/openssl.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_OPENSSL_HPP
