/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_BOOST_HPP
#define SPRIG_CONFIG_LIBINFO_BOOST_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_BOOST)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/version.hpp>
#		include <boost/config.hpp>
#		include <boost/preprocessor/stringize.hpp>

#		pragma message("sprig/config/libinfo/boost.hpp")
#		pragma message("    BOOST_VERSION   = " BOOST_PP_STRINGIZE(BOOST_VERSION))
#		pragma message("    BOOST_COMPILER  = " BOOST_PP_STRINGIZE(BOOST_COMPILER))
#		pragma message("    BOOST_STDLIB    = " BOOST_PP_STRINGIZE(BOOST_STDLIB))
#		pragma message("    BOOST_PLATFORM  = " BOOST_PP_STRINGIZE(BOOST_PLATFORM))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_BOOST)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_BOOST_HPP
