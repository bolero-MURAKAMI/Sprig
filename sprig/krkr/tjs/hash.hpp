/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_HASH_HPP
#define SPRIG_KRKR_TJS_HASH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/functional/hash/hash.hpp>
#include <sprig/external/tp_stub.hpp>

//
// hash_value
//
static std::size_t hash_value(tTJSString const& target) {
	return boost::hash_range(target.c_str(), target.c_str() + target.length());
}

#endif	// #ifndef SPRIG_KRKR_TJS_HASH_HPP
