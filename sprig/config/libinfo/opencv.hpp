/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIBINFO_OPENCV_HPP
#define SPRIG_CONFIG_LIBINFO_OPENCV_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_OPENCV)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <opencv2/core/version.hpp>

#		pragma message("sprig/config/libinfo/opencv.hpp")
#		pragma message("    CV_MAJOR_VERSION    = " BOOST_PP_STRINGIZE(CV_MAJOR_VERSION))
#		pragma message("    CV_MINOR_VERSION    = " BOOST_PP_STRINGIZE(CV_MINOR_VERSION))
#		pragma message("    CV_SUBMINOR_VERSION = " BOOST_PP_STRINGIZE(CV_SUBMINOR_VERSION))
#		pragma message("    CV_VERSION          = " BOOST_PP_STRINGIZE(CV_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_OPENCV)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_OPENCV_HPP
