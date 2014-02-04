/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
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
