/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_SPRIG_NTL_BIG_INT_HPP
#define SPRIG_SERIALIZATION_SPRIG_NTL_BIG_INT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/serialization/ntl/ZZ.hpp>
#include <sprig/ntl/big_int.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// sprig::big_int
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, sprig::big_int& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("ref", v.ref())
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_SPRIG_NTL_BIG_INT_HPP
