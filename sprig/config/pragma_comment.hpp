#ifndef SPRIG_CONFIG_PRAGMA_COMMENT_HPP
#define SPRIG_CONFIG_PRAGMA_COMMENT_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(_MSC_VER) || defined(__BORLANDC__)
#	define SPRIG_HAS_PRAGMA_COMMENT
#endif	// #if defined(_MSC_VER) || defined(__BORLANDC__)

#endif	// #ifndef SPRIG_CONFIG_PRAGMA_COMMENT_HPP
