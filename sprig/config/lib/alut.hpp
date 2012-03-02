#ifndef SPRIG_CONFIG_LIB_ALUT_HPP
#define SPRIG_CONFIG_LIB_ALUT_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/alut.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/config/lib/openal.hpp>

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_ALUT_BINARY
#	define SPRIG_LIBCONFIG_ALUT_BINARY SPRIG_LIBCONFIG_ALUT_LIB
#endif	// #ifndef SPRIG_LIBCONFIG_ALUT_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_ALUT_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ALUT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ALUT_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/alut.hpp")
#	ifdef SPRIG_LIBCONFIG_ALUT_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ALUT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ALUT_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/alut.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_ALUT_HPP