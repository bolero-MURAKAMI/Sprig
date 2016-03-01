/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CONFIG_PRAGMA_ONCE_HPP
#define SPRIG_CONFIG_PRAGMA_ONCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	define SPRIG_HAS_PRAGMA_ONCE
#endif	// #if defined(_MSC_VER) && (_MSC_VER >= 1020)

#if defined(_MSC_VER) && (_MSC_VER >= 1020) && !defined(SPRIG_CONFIG_NO_PRAGMA_ONCE)
#	define SPRIG_USING_PRAGMA_ONCE
#endif	// #if defined(_MSC_VER) && (_MSC_VER >= 1020) && !defined(SPRIG_CONFIG_NO_PRAGMA_ONCE)

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#endif	// #ifndef SPRIG_CONFIG_PRAGMA_ONCE_HPP
