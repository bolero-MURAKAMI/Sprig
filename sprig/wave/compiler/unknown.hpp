#ifndef SPRIG_WAVE_COMPILER_UNKNOWN_HPP
#define SPRIG_WAVE_COMPILER_UNKNOWN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/wave/config.hpp>

#ifdef SPRIG_WAVE_UNKNOWN

	//
	// SPRIG_WAVE_MACROS_[N]
	//
#	define SPRIG_WAVE_MACROS_0(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")
#	define SPRIG_WAVE_MACROS_1(OPT) SPRIG_WAVE_MACROS_REM(OPT, "(Unknown)")
#	define SPRIG_WAVE_MACROS_2(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")
	//
	// SPRIG_WAVE_MACROS_NUM
	//
#	define SPRIG_WAVE_MACROS_NUM 3

#endif	// #ifdef SPRIG_WAVE_UNKNOWN

#endif	// #ifndef SPRIG_WAVE_COMPILER_UNKNOWN_HPP
