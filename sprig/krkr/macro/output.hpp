/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_OUTPUT_HPP
#define SPRIG_KRKR_MACRO_OUTPUT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/comparison/greater_equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/tjs/output.hpp>
#include <sprig/krkr/macro/log_level.hpp>

//
// SPRIG_KRKR_LOG_LEVEL
//
#ifndef SPRIG_KRKR_LOG_LEVEL
#	ifdef NDEBUG
#		define SPRIG_KRKR_LOG_LEVEL SPRIG_KRKR_LOG_LEVEL_NOTIFICATION
#	else	// #ifdef NDEBUG
#		define SPRIG_KRKR_LOG_LEVEL SPRIG_KRKR_LOG_LEVEL_NORMAL
#	endif	// #ifdef NDEBUG
#endif	// #ifndef SPRIG_KRKR_LOG_LEVEL

//
// SPRIG_KRKR_LOG_LEVEL_SWITCH
//
#define SPRIG_KRKR_LOG_LEVEL_SWITCH(MACRO, LEVEL) \
	BOOST_PP_IF( \
		BOOST_PP_GREATER_EQUAL(LEVEL, SPRIG_KRKR_LOG_LEVEL), \
		MACRO, \
		BOOST_PP_EMPTY() \
		)

//
// SPRIG_KRKR_SECTION
// SPRIG_KRKR_OUTPUT
// SPRIG_KRKR_OUTPUT_VALUE
//
#ifndef SPRIG_KRKR_NDEBUG
#	define SPRIG_KRKR_SECTION(NAME, LEVEL) \
		SPRIG_KRKR_LOG_LEVEL_SWITCH( \
			sprig::krkr::tjs::section BOOST_PP_CAT(sprig_krkr_tjs_section_, __LINE__)(NAME), \
			LEVEL \
			)
#	define SPRIG_KRKR_OUTPUT(MESSAGE, LEVEL) \
		SPRIG_KRKR_LOG_LEVEL_SWITCH( \
			sprig::krkr::tjs::output(MESSAGE), \
			LEVEL \
			)
#	define SPRIG_KRKR_OUTPUT_VALUE(NAME, CONTENTS, LEVEL) \
		SPRIG_KRKR_LOG_LEVEL_SWITCH( \
			sprig::krkr::tjs::output_value(NAME, CONTENTS), \
			LEVEL \
			)
#	define SPRIG_KRKR_OUTPUT_COMMENT(COMMENT, LEVEL) \
		SPRIG_KRKR_LOG_LEVEL_SWITCH( \
			sprig::krkr::tjs::output_comment(COMMENT), \
			LEVEL \
			)
#else	// #ifndef SPRIG_KRKR_NDEBUG
#	define SPRIG_KRKR_SECTION(NAME)
#	define SPRIG_KRKR_OUTPUT(MESSAGE)
#	define SPRIG_KRKR_OUTPUT_VALUE(NAME, CONTENTS)
#	define SPRIG_KRKR_OUTPUT_COMMENT(COMMENT)
#endif	// #ifndef SPRIG_KRKR_NDEBUG

#endif	// #ifndef SPRIG_KRKR_MACRO_OUTPUT_HPP
