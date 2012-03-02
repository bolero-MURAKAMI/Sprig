#ifndef SPRIG_CONFIG_LIB_FREETYPE_HPP
#define SPRIG_CONFIG_LIB_FREETYPE_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/freetype.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_FREETYPE_BINARY
#	ifdef SPRIG_LIBCONFIG_FREETYPE_LIB
#		define SPRIG_LIBCONFIG_FREETYPE_BINARY SPRIG_LIBCONFIG_FREETYPE_LIB
#	endif	// #ifdef SPRIG_LIBCONFIG_FREETYPE_LIB
#endif	// #ifndef SPRIG_LIBCONFIG_FREETYPE_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_FREETYPE_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_FREETYPE_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_FREETYPE_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/freetype.hpp")
#	ifdef SPRIG_LIBCONFIG_FREETYPE_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_FREETYPE_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_FREETYPE_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/yamlcpp.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_FREETYPE_HPP
