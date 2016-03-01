/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ACCEPT_HPP
#define SPRIG_ACCEPT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/addressof.hpp>

namespace sprig {
	//
	// accept
	//
	template<typename T>
	SPRIG_INLINE T** accept(T*& p) {
		return boost::addressof(p);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ACCEPT_HPP
