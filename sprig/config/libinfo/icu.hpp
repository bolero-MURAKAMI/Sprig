/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_ICU_HPP
#define SPRIG_CONFIG_LIBINFO_ICU_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_ICU)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <unicode/uvernum.h>

#		pragma message("sprig/config/libinfo/icu.hpp")
#		pragma message("    U_COPYRIGHT_STRING              = " BOOST_PP_STRINGIZE(U_COPYRIGHT_STRING))
#		pragma message("    U_ICU_VERSION_MAJOR_NUM         = " BOOST_PP_STRINGIZE(U_ICU_VERSION_MAJOR_NUM))
#		pragma message("    U_ICU_VERSION_MINOR_NUM         = " BOOST_PP_STRINGIZE(U_ICU_VERSION_MINOR_NUM))
#		pragma message("    U_ICU_VERSION_PATCHLEVEL_NUM    = " BOOST_PP_STRINGIZE(U_ICU_VERSION_PATCHLEVEL_NUM))
#		pragma message("    U_ICU_VERSION                   = " BOOST_PP_STRINGIZE(U_ICU_VERSION))
#		pragma message("    U_ICU_VERSION_SHORT             = " BOOST_PP_STRINGIZE(U_ICU_VERSION_SHORT))
#		pragma message("    U_ICU_DATA_VERSION              = " BOOST_PP_STRINGIZE(U_ICU_DATA_VERSION))
#		pragma message("    UCOL_RUNTIME_VERSION            = " BOOST_PP_STRINGIZE(UCOL_RUNTIME_VERSION))
#		pragma message("    UCOL_BUILDER_VERSION            = " BOOST_PP_STRINGIZE(UCOL_BUILDER_VERSION))
#		pragma message("    UCOL_TAILORINGS_VERSION         = " BOOST_PP_STRINGIZE(UCOL_TAILORINGS_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_ICU)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_ICU_HPP
