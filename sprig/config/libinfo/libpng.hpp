#ifndef SPRIG_CONFIG_LIBINFO_LIBPNG_HPP
#define SPRIG_CONFIG_LIBINFO_LIBPNG_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBPNG)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <png.h>

#		pragma message("sprig/config/libinfo/libpng.hpp")
#		pragma message("    PNG_LIBPNG_VER_STRING       = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_STRING))
#		pragma message("    PNG_HEADER_VERSION_STRING   = " BOOST_PP_STRINGIZE(PNG_HEADER_VERSION_STRING))
#		pragma message("    PNG_LIBPNG_VER_SONUM        = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_SONUM))
#		pragma message("    PNG_LIBPNG_VER_DLLNUM       = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_DLLNUM))
#		pragma message("    PNG_LIBPNG_VER_MAJOR        = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_MAJOR))
#		pragma message("    PNG_LIBPNG_VER_MINOR        = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_MINOR))
#		pragma message("    PNG_LIBPNG_VER_RELEASE      = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_RELEASE))
#		pragma message("    PNG_LIBPNG_VER_BUILD        = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER_BUILD))
#		pragma message("    PNG_LIBPNG_VER              = " BOOST_PP_STRINGIZE(PNG_LIBPNG_VER))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBPNG)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_LIBPNG_HPP
