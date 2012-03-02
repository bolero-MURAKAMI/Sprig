#ifndef SPRIG_CONFIG_INLINE_HPP
#define SPRIG_CONFIG_INLINE_HPP

#include <sprig/config/pragma_once.hpp>
#include <sprig/config/forceinline.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifndef SPRIG_CONFIG_NO_INLINE
#	ifdef SPRIG_CONFIG_FORCE_INLINE
#		define SPRIG_INLINE SPRIG_FORCEINLINE
#	else	// #ifdef SPRIG_CONFIG_FORCE_INLINE
#		define SPRIG_INLINE inline
#	endif	// #ifdef SPRIG_CONFIG_FORCE_INLINE
#else	// #ifndef SPRIG_CONFIG_NO_INLINE
#	define SPRIG_INLINE
#endif	// #ifndef SPRIG_CONFIG_NO_INLINE

#endif	// #ifndef SPRIG_CONFIG_INLINE_HPP
