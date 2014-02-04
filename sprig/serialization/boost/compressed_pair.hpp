/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_COMPRESSED_PAIR_HPP
#define SPRIG_SERIALIZATION_BOOST_COMPRESSED_PAIR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/compressed_pair.hpp>
#include <boost/serialization/nvp.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::compressed_pair
	//
	template<typename Archive, typename T0, typename T1>
	SPRIG_INLINE void serialize(
		Archive& ar,
		boost::compressed_pair<T0, T1>& value,
		unsigned int const
		)
	{
		ar
			& boost::serialization::make_nvp("first", value.first())
			& boost::serialization::make_nvp("second", value.second())
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_COMPRESSED_PAIR_HPP
