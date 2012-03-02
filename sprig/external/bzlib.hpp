#ifndef SPRIG_EXTERNAL_BZLIB_HPP
#define SPRIG_EXTERNAL_BZLIB_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/config/lib/windows.hpp>
#include <sprig/config/lib/bzip2.hpp>

#include <rpc.h>
#include <rpcndr.h>
#include <bzlib.h>

#ifdef small
#	undef small
#endif

#endif	// #ifndef SPRIG_EXTERNAL_BZLIB_HPP
