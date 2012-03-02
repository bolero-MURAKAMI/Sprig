#ifndef SPRIG_CONFIG_LIBINFO_DEVIL_HPP
#define SPRIG_CONFIG_LIBINFO_DEVIL_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_DEVIL)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <IL/il.h>

#		pragma message("sprig/config/libinfo/devil.hpp")
#		pragma message("    IL_VERSION  = " BOOST_PP_STRINGIZE(IL_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_DEVIL)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_DEVIL_HPP
