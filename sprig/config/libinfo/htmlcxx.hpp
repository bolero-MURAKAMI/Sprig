#ifndef SPRIG_CONFIG_LIBINFO_HTMLCXX_HPP
#define SPRIG_CONFIG_LIBINFO_HTMLCXX_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_HTMLCXX)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		pragma message("sprig/config/libinfo/htmlcxx.hpp")

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_HTMLCXX)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_HTMLCXX_HPP
