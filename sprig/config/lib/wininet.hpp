/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_WININET_HPP
#define SPRIG_CONFIG_LIB_WININET_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include <sprig/config/pragma_once.hpp>
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "wininet.lib")
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#endif	// #ifndef SPRIG_CONFIG_LIB_WININET_HPP
