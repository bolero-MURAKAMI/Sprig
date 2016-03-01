/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_EXPAT_HPP
#define SPRIG_CONFIG_LIBINFO_EXPAT_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_EXPAT)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <expat.h>

#		pragma message("sprig/config/libinfo/expat.hpp")
#		pragma message("    XML_MAJOR_VERSION   = " BOOST_PP_STRINGIZE(XML_MAJOR_VERSION))
#		pragma message("    XML_MINOR_VERSION   = " BOOST_PP_STRINGIZE(XML_MINOR_VERSION))
#		pragma message("    XML_MICRO_VERSION   = " BOOST_PP_STRINGIZE(XML_MICRO_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_EXPAT)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_EXPAT_HPP
