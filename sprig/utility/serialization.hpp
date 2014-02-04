/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_SERIALIZATION_HPP
#define SPRIG_UTILITY_SERIALIZATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/serialization.hpp>

#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#define SPRIG_SERIALIZATION_NAMESPACE_BEGIN \
	namespace boost { \
		namespace serialization {
#define SPRIG_SERIALIZATION_NAMESPACE_END \
		} \
	}
#else	// #ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#define SPRIG_SERIALIZATION_NAMESPACE_BEGIN
#define SPRIG_SERIALIZATION_NAMESPACE_END
#endif	// #ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP

namespace sprig {
	//
	// serialize_cast
	//
	template<typename T>
	SPRIG_INLINE T const& serialize_cast(T const& target) {
		return target;
	}
} // namespace sprig

#endif	// #ifndef SPRIG_UTILITY_SERIALIZATION_HPP
