/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_ALUT_HPP
#define SPRIG_CONFIG_LIBINFO_ALUT_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_ALUT)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <AL/alut.h>

#		pragma message("sprig/config/libinfo/alut.hpp")
#		pragma message("    ALUT_API_MAJOR_VERSION  = " BOOST_PP_STRINGIZE(ALUT_API_MAJOR_VERSION))
#		pragma message("    ALUT_API_MINOR_VERSION  = " BOOST_PP_STRINGIZE(ALUT_API_MINOR_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_ALUT)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_ALUT_HPP
