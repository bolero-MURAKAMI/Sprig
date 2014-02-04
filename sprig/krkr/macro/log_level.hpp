/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_LOG_LEVEL_HPP
#define SPRIG_KRKR_MACRO_LOG_LEVEL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

//
// SPRIG_KRKR_LOG_LEVEL_NORMAL
// SPRIG_KRKR_LOG_LEVEL_NOTIFICATION
// SPRIG_KRKR_LOG_LEVEL_WARNING
// SPRIG_KRKR_LOG_LEVEL_ERROR
// SPRIG_KRKR_LOG_LEVEL_CRITICAL
//
#define SPRIG_KRKR_LOG_LEVEL_NORMAL 1
#define SPRIG_KRKR_LOG_LEVEL_NOTIFICATION 2
#define SPRIG_KRKR_LOG_LEVEL_WARNING 3
#define SPRIG_KRKR_LOG_LEVEL_ERROR 4
#define SPRIG_KRKR_LOG_LEVEL_CRITICAL 5

//
// SPRIG_KRKR_LOG_LEVEL_IMPORTANT
// SPRIG_KRKR_LOG_LEVEL_REQUIRED
//
#define SPRIG_KRKR_LOG_LEVEL_IMPORTANT 3
#define SPRIG_KRKR_LOG_LEVEL_REQUIRED 5

#endif	// #ifndef SPRIG_KRKR_MACRO_LOG_LEVEL_HPP
