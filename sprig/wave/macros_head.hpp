#ifndef SPRIG_WAVE_MACROS_HEAD_HPP
#define SPRIG_WAVE_MACROS_HEAD_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/config.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <sprig/wave/config.hpp>

//
// SPRIG_WAVE_MACROS_HEAD_[N]
//
#define SPRIG_WAVE_MACROS_HEAD_0(OPT) \
	SPRIG_WAVE_MACROS_SEP(OPT, "*")
#define SPRIG_WAVE_MACROS_HEAD_1(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "これは sprig/wave/macros.hpp によって自動生成されたマクロ定義群です")
#define SPRIG_WAVE_MACROS_HEAD_2(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "sprig/wave/macros.hpp のコンパイルされたプロジェクト環境を反映しています")
#define SPRIG_WAVE_MACROS_HEAD_3(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "")
#define SPRIG_WAVE_MACROS_HEAD_4(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "Version  : "SPRIG_WAVE_MACROS_VERSION_STRING())
#define SPRIG_WAVE_MACROS_HEAD_5(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "Compiler : "BOOST_COMPILER)
#define SPRIG_WAVE_MACROS_HEAD_6(OPT)  \
	SPRIG_WAVE_MACROS_REM(OPT, "Date&Time: "__DATE__" "__TIME__)
#define SPRIG_WAVE_MACROS_HEAD_7(OPT)  \
		\
	SPRIG_WAVE_MACROS_SEP(OPT, "*")
//
// SPRIG_WAVE_MACROS_HEAD_NUM
//
#define SPRIG_WAVE_MACROS_HEAD_NUM 8

//
//	: 行数チェック
//
#if SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_REPEAT
#	error SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_REPEAT
#endif	// #if SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_REPEAT
#if SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_SEQ
#	error SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_SEQ
#endif	// #if SPRIG_WAVE_MACROS_HEAD_NUM > BOOST_PP_LIMIT_SEQ

//
// SPRIG_WAVE_MACROS_HEAD
//
#define SPRIG_WAVE_MACROS_HEAD() \
	BOOST_PP_SEQ_FOR_EACH( \
		SPRIG_WAVE_MACROS_INVOKE, \
		SPRIG_WAVE_MACROS_OPT_FULL, \
		BOOST_PP_REPEAT(SPRIG_WAVE_MACROS_HEAD_NUM, SPRIG_WAVE_MACROS_ELEM_GEN, SPRIG_WAVE_MACROS_HEAD_) \
		)

namespace sprig {
	namespace wave {
		//
		// macros_head
		//
		SPRIG_INLINE char const* macros_head() {
			return SPRIG_WAVE_MACROS_HEAD();
		}
	}	// namespace wave
}	// namespace sprig

#endif	// #ifndef SPRIG_WAVE_MACROS_HEAD_HPP
