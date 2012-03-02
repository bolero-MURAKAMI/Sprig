#ifndef SPRIG_CONFIG_LIB_DXERR_HPP
#define SPRIG_CONFIG_LIB_DXERR_HPP

#ifdef SPRIG_CONFIG_LIB_USERCONFIG
#	include <sprig/config/pragma_once.hpp>
#endif	// #ifdef SPRIG_CONFIG_LIB_USERCONFIG

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/pragma_comment.hpp>

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "dxguid.lib")
#	pragma comment(lib, "DxErr.lib")
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#endif	// #ifdef SPRIG_CONFIG_LIB_AUTO_LINK

#include <sprig/config/libinfo/dxsdk.hpp>

#endif	// #ifndef SPRIG_CONFIG_LIB_DXERR_HPP
