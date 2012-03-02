#ifndef SPRIG_CONFIG_LIB_ICU_HPP
#define SPRIG_CONFIG_LIB_ICU_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include "../../../config/libconfig/icu.hpp"
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#ifndef SPRIG_LIBCONFIG_ICU_DT_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_DT_LIB
#		define SPRIG_LIBCONFIG_ICU_DT_BINARY SPRIG_LIBCONFIG_ICU_DT_LIB
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_DT_LIB
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_DT_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_UC_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_UC_LIB
#			define SPRIG_LIBCONFIG_ICU_UC_BINARY SPRIG_LIBCONFIG_ICU_UC_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_UC_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_UC_LIB_D
#			define SPRIG_LIBCONFIG_ICU_UC_BINARY SPRIG_LIBCONFIG_ICU_UC_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_UC_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_UC_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_IN_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_IN_LIB
#			define SPRIG_LIBCONFIG_ICU_IN_BINARY SPRIG_LIBCONFIG_ICU_IN_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_IN_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_IN_LIB_D
#			define SPRIG_LIBCONFIG_ICU_IN_BINARY SPRIG_LIBCONFIG_ICU_IN_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_IN_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_IN_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_LE_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_LE_LIB
#			define SPRIG_LIBCONFIG_ICU_LE_BINARY SPRIG_LIBCONFIG_ICU_LE_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_LE_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_LE_LIB_D
#			define SPRIG_LIBCONFIG_ICU_LE_BINARY SPRIG_LIBCONFIG_ICU_LE_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_LE_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_LE_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_LX_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_LX_LIB
#			define SPRIG_LIBCONFIG_ICU_LX_BINARY SPRIG_LIBCONFIG_ICU_LX_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_LX_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_LX_LIB_D
#			define SPRIG_LIBCONFIG_ICU_LX_BINARY SPRIG_LIBCONFIG_ICU_LX_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_LX_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_LX_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_IO_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_IO_LIB
#			define SPRIG_LIBCONFIG_ICU_IO_BINARY SPRIG_LIBCONFIG_ICU_IO_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_IO_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_IO_LIB_D
#			define SPRIG_LIBCONFIG_ICU_IO_BINARY SPRIG_LIBCONFIG_ICU_IO_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_IO_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_IO_BINARY

#ifndef SPRIG_LIBCONFIG_ICU_TU_BINARY
#	ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_TU_LIB
#			define SPRIG_LIBCONFIG_ICU_TU_BINARY SPRIG_LIBCONFIG_ICU_TU_LIB
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_TU_LIB
#	else	// #ifdef NDEBUG
#		ifdef SPRIG_LIBCONFIG_ICU_TU_LIB_D
#			define SPRIG_LIBCONFIG_ICU_TU_BINARY SPRIG_LIBCONFIG_ICU_TU_LIB_D
#		endif	// #ifdef SPRIG_LIBCONFIG_ICU_TU_LIB_D
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_LIBCONFIG_ICU_TU_BINARY

#include <boost/preprocessor/stringize.hpp>
#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	ifdef SPRIG_LIBCONFIG_ICU_DT_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_DT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_DT_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_UC_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_UC_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_UC_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_IN_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_IN_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_IN_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_LE_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_LE_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_LE_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_LX_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_LX_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_LX_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_IO_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_IO_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_IO_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_TU_BINARY
#		pragma comment(lib, BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_TU_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_TU_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/config/pragma_message.hpp>

#ifdef SPRIG_HAS_PRAGMA_MESSAGE
#	pragma message("sprig/config/lib/icu.hpp")
#	ifdef SPRIG_LIBCONFIG_ICU_DT_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_DT_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_DT_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_UC_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_UC_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_UC_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_IN_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_IN_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_IN_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_LE_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_LE_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_LE_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_LX_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_LX_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_LX_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_IO_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_IO_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_IO_BINARY
#	ifdef SPRIG_LIBCONFIG_ICU_TU_BINARY
#		pragma message("    lib="BOOST_PP_STRINGIZE(SPRIG_LIBCONFIG_ICU_TU_BINARY))
#	endif	// #ifdef SPRIG_LIBCONFIG_ICU_TU_BINARY
#endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/icu.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_ICU_HPP