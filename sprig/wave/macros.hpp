/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_WAVE_MACROS_HPP
#define SPRIG_WAVE_MACROS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/config.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <sprig/wave/config.hpp>
#include <sprig/wave/compiler/visualc.hpp>
#include <sprig/wave/compiler/gcc.hpp>
#include <sprig/wave/compiler/unknown.hpp>

//
//	: 行数チェック
//
#if SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_REPEAT
#	error SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_REPEAT
#endif	// #if SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_REPEAT
#if SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_SEQ
#	error SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_SEQ
#endif	// #if SPRIG_WAVE_MACROS_NUM > BOOST_PP_LIMIT_SEQ

//
// SPRIG_WAVE_MACROS_OPT
//
#define SPRIG_WAVE_MACROS_OPT(OPT) \
	BOOST_PP_SEQ_FOR_EACH( \
		SPRIG_WAVE_MACROS_INVOKE, \
		OPT, \
		BOOST_PP_REPEAT(SPRIG_WAVE_MACROS_NUM, SPRIG_WAVE_MACROS_ELEM_GEN, SPRIG_WAVE_MACROS_) \
		)
//
// SPRIG_WAVE_MACROS
// SPRIG_WAVE_MACROS_FULL
// SPRIG_WAVE_MACROS_MINIMUM
//
#define SPRIG_WAVE_MACROS() \
	SPRIG_WAVE_MACROS_OPT(SPRIG_WAVE_MACROS_OPT_DEFAULT)
#define SPRIG_WAVE_MACROS_FULL() \
	SPRIG_WAVE_MACROS_OPT(SPRIG_WAVE_MACROS_OPT_FULL)
#define SPRIG_WAVE_MACROS_MINIMUM() \
	SPRIG_WAVE_MACROS_OPT(SPRIG_WAVE_MACROS_OPT_MINIMUM)

namespace sprig {
	namespace wave {
		//
		// macros
		//
		SPRIG_INLINE char const* macros() {
			return SPRIG_WAVE_MACROS();
		}
	}	// namespace wave
}	// namespace sprig

#endif	// #ifndef SPRIG_WAVE_MACROS_HPP
