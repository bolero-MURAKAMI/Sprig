#ifndef SPRIG_CONFIG_FORCEINLINE_HPP
#define SPRIG_CONFIG_FORCEINLINE_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/config/native_forceinline.hpp>

#ifndef SPRIG_CONFIG_NO_FORCEINLINE
#	ifdef SPRIG_HAS_NATIVE_FORCEINLINE
#		define SPRIG_FORCEINLINE SPRIG_NATIVE_FORCEINLINE
#	else	// #ifdef SPRIG_HAS_NATIVE_FORCEINLINE
#		define SPRIG_FORCEINLINE inline
#	endif	// #ifdef SPRIG_HAS_NATIVE_FORCEINLINE
#else	// #ifndef SPRIG_CONFIG_NO_FORCEINLINE
#	define SPRIG_FORCEINLINE
#endif	// #ifndef SPRIG_CONFIG_NO_FORCEINLINE

#endif	// #ifndef SPRIG_CONFIG_FORCEINLINE_HPP
