/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CSTDINT_HPP
#define SPRIG_CSTDINT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(__GNUC__)
#	include <stdint.h>
#elif defined(_MSC_VER)
#	include <crtdefs.h>
#endif

#include <boost/cstdint.hpp>

namespace sprig {
	using ::intptr_t;
	using ::uintptr_t;

	using boost::intmax_t;
	using boost::uintmax_t;

	using boost::int8_t;
	using boost::int_least8_t;
	using boost::int_fast8_t;
	using boost::uint8_t;
	using boost::uint_least8_t;
	using boost::uint_fast8_t;

	using boost::int16_t;
	using boost::int_least16_t;
	using boost::int_fast16_t;
	using boost::uint16_t;
	using boost::uint_least16_t;
	using boost::uint_fast16_t;

	using boost::int32_t;
	using boost::int_least32_t;
	using boost::int_fast32_t;
	using boost::uint32_t;
	using boost::uint_least32_t;
	using boost::uint_fast32_t;

	using boost::int64_t;
	using boost::int_least64_t;
	using boost::int_fast64_t;
	using boost::uint64_t;
	using boost::uint_least64_t;
	using boost::uint_fast64_t;
}	// namespace sprig

#endif	// #ifndef SPRIG_CSTDINT_HPP
