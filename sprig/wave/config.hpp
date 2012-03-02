#ifndef SPRIG_WAVE_CONFIG_HPP
#define SPRIG_WAVE_CONFIG_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/config.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/control/if.hpp>

//
// SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT
//	: デフォルトの区切りの桁数
//
#ifndef SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT
#	define SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT 79
#endif	// #ifndef SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT

//
// SPRIG_WAVE_MACROS_CONFIG_PUT_NDEF
//	: 定義されないマクロもコメントとして出力するか
//
#ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_NDEF
#	define SPRIG_WAVE_MACROS_CONFIG_PUT_NDEF 1
#endif	// #ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_NDEF
//
// SPRIG_WAVE_MACROS_CONFIG_PUT_REM
//	: コメントを出力するか
//
#ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_REM
#	define SPRIG_WAVE_MACROS_CONFIG_PUT_REM 1
#endif	// #ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_REM
//
// SPRIG_WAVE_MACROS_CONFIG_PUT_SEP
//	: 区切りの桁数
//
#ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_SEP
#	define SPRIG_WAVE_MACROS_CONFIG_PUT_SEP SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT
#endif	// #ifndef SPRIG_WAVE_MACROS_CONFIG_PUT_SEP

//
// SPRIG_WAVE_MACROS_VERSION
// SPRIG_WAVE_MACROS_VERSION_MAJOR
// SPRIG_WAVE_MACROS_VERSION_MINOR
// SPRIG_WAVE_MACROS_VERSION_SUBMINOR
//	: バージョン
//
#define SPRIG_WAVE_MACROS_VERSION 0x000100
#define SPRIG_WAVE_MACROS_VERSION_MAJOR 0
#define SPRIG_WAVE_MACROS_VERSION_MINOR 1
#define SPRIG_WAVE_MACROS_VERSION_SUBMINOR 0
//
// SPRIG_WAVE_MACROS_VERSION_STRING
//	: バージョン文字列
//
#define SPRIG_WAVE_MACROS_VERSION_STRING() \
	BOOST_PP_STRINGIZE(SPRIG_WAVE_MACROS_VERSION_MAJOR.SPRIG_WAVE_MACROS_VERSION_MINOR.SPRIG_WAVE_MACROS_VERSION_SUBMINOR)

//
// SPRIG_WAVE_MACROS_OPT_DEFAULT
// SPRIG_WAVE_MACROS_OPT_FULL
// SPRIG_WAVE_MACROS_OPT_MINIMUM
//	: 既定の生成オプション
//
#define SPRIG_WAVE_MACROS_OPT_DEFAULT \
	(SPRIG_WAVE_MACROS_CONFIG_PUT_NDEF) \
	(SPRIG_WAVE_MACROS_CONFIG_PUT_REM) \
	(SPRIG_WAVE_MACROS_CONFIG_PUT_SEP)
#define SPRIG_WAVE_MACROS_OPT_FULL \
	(1) \
	(1) \
	(SPRIG_WAVE_MACROS_CONFIG_SEP_DEFAULT)
#define SPRIG_WAVE_MACROS_OPT_MINIMUM \
	(0) \
	(0) \
	(0)

//
// SPRIG_WAVE_MACROS_GETOPT
//	: オプション抽出
//
#define SPRIG_WAVE_MACROS_GETOPT(I, OPT) \
	BOOST_PP_SEQ_ELEM(I, OPT)

//
// SPRIG_WAVE_MACROS_SEP_GEN
// SPRIG_WAVE_MACROS_ELEM_GEN
// SPRIG_WAVE_MACROS_INVOKE
//
#define SPRIG_WAVE_MACROS_SEP_GEN(z, n, d) d
#define SPRIG_WAVE_MACROS_ELEM_GEN(z, n, d) (BOOST_PP_CAT(d, n))
#define SPRIG_WAVE_MACROS_INVOKE(r, d, e) e(d)

//
// SPRIG_WAVE_MACROS_DEF
// SPRIG_WAVE_MACROS_NDEF
//	: マクロ定義生成
//
#define SPRIG_WAVE_MACROS_DEF(OPT, MACRO) \
		"    macro = "#MACRO"\n"
#define SPRIG_WAVE_MACROS_NDEF(OPT, MACRO) \
	BOOST_PP_IF( \
		SPRIG_WAVE_MACROS_GETOPT(0, OPT), \
		"#   macro = "#MACRO"\n", \
		"" \
		)
//
// SPRIG_WAVE_MACROS_DEFV
// SPRIG_WAVE_MACROS_NDEFV
//	: 値付きマクロ定義生成
//
#define SPRIG_WAVE_MACROS_DEFV(OPT, MACRO) \
	"    macro = "#MACRO"="BOOST_PP_STRINGIZE(MACRO)"\n"
#define SPRIG_WAVE_MACROS_NDEFV(OPT, MACRO) \
	BOOST_PP_IF( \
		SPRIG_WAVE_MACROS_GETOPT(0, OPT), \
		"#   macro = "#MACRO"=(undefined)""\n", \
		"" \
		)
//
// SPRIG_WAVE_MACROS_DEFF
// SPRIG_WAVE_MACROS_NDEFF
//	: 関数マクロ定義生成
//
#define SPRIG_WAVE_MACROS_DEFF(OPT, MACRO, FUNC) \
	"    macro = "#MACRO"="#FUNC"\n"
#define SPRIG_WAVE_MACROS_NDEFF(OPT, MACRO, FUNC) \
	BOOST_PP_IF( \
		SPRIG_WAVE_MACROS_GETOPT(0, OPT), \
		"#   macro = "#MACRO"=(undefined)""\n", \
		"" \
		)
//
// SPRIG_WAVE_MACROS_DEFP
// SPRIG_WAVE_MACROS_NDEFP
//	: 疑似マクロ定義生成
//
#define SPRIG_WAVE_MACROS_DEFP(OPT, MACRO) \
	"    macro = "#MACRO"="#MACRO"\n"
#define SPRIG_WAVE_MACROS_NDEFP(OPT, MACRO) \
	BOOST_PP_IF( \
		SPRIG_WAVE_MACROS_GETOPT(0, OPT), \
		"#   macro = "#MACRO"=(undefined)""\n", \
		"" \
		)
//
// SPRIG_WAVE_MACROS_REM
//	: コメント生成
//
#define SPRIG_WAVE_MACROS_REM(OPT, TEXT) \
	BOOST_PP_IF( \
		SPRIG_WAVE_MACROS_GETOPT(1, OPT), \
		"# "TEXT"\n", \
		"" \
		)
//
// SPRIG_WAVE_MACROS_SEP
//	: 区切り生成
//
#define SPRIG_WAVE_MACROS_SEP(OPT, CHAR) \
	BOOST_PP_IF( \
		BOOST_PP_GREATER(SPRIG_WAVE_MACROS_GETOPT(2, OPT), 0), \
		"#"BOOST_PP_REPEAT(BOOST_PP_DEC(SPRIG_WAVE_MACROS_GETOPT(2, OPT)), SPRIG_WAVE_MACROS_SEP_GEN, CHAR)"\n", \
		"" \
		)

//
// SPRIG_WAVE_VISUALC
// SPRIG_WAVE_GCC
// SPRIG_WAVE_UNKNOWN
//	: コンパイラ分岐
//
#if defined(BOOST_MSVC)
#	define SPRIG_WAVE_VISUALC
#elif defined(__GNUC__)
#	define SPRIG_WAVE_GCC
#else
#	define SPRIG_WAVE_UNKNOWN
#endif

#endif	// #ifndef SPRIG_WAVE_CONFIG_HPP
