#ifndef SPRIG_CONFIG_PRAGMA_MESSAGE_HPP
#define SPRIG_CONFIG_PRAGMA_MESSAGE_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(_MSC_VER)
#	define SPRIG_HAS_PRAGMA_MESSAGE
#endif	// #if defined(_MSC_VER)

#endif	// #ifndef SPRIG_CONFIG_PRAGMA_MESSAGE_HPP
