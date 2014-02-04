/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_LIB_D3DX9_HPP
#define SPRIG_CONFIG_LIB_D3DX9_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "dxguid.lib")
#	if defined(NDEBUG) || defined(SPRIG_CONFIG_LIB_D3DX9_USING_RELEASE_BINARY)
#		pragma comment(lib, "d3dx9.lib")
#	else
#		pragma comment(lib, "d3dx9d.lib")
#	endif
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/dxsdk.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_D3DX9_HPP
