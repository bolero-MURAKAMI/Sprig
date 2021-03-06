/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_TEXT_HPP
#define SPRIG_KRKR_MACRO_TEXT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/preprocessor/stringize.hpp>
#include <sprig/external/tp_stub.hpp>

//
// SPRIG_KRKR_TJS_W
// SPRIG_KRKR_TJS_N
//
#define SPRIG_KRKR_TJS_W(TEXT) \
	TJS_W(TEXT)
#define SPRIG_KRKR_TJS_N(TEXT) \
	TJS_N(TEXT)

//
// SPRIG_KRKR_TJS_STRINGIZE
//
#define SPRIG_KRKR_TJS_STRINGIZE(TEXT) \
	SPRIG_KRKR_TJS_STRINGIZE_I(BOOST_PP_STRINGIZE(TEXT))
#define SPRIG_KRKR_TJS_STRINGIZE_I(TEXT) \
	SPRIG_KRKR_TJS_W(TEXT)

#endif	// #ifndef SPRIG_KRKR_MACRO_TEXT_HPP
