#ifndef SPRIG_CONFIG_LIB_D3D9_HPP
#define SPRIG_CONFIG_LIB_D3D9_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "dxguid.lib")
#	pragma comment(lib, "d3d9.lib")
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/dxsdk.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_D3D9_HPP
