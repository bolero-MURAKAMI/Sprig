/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_PAIR_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_PAIR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/pair.hpp>
#include <boost/serialization/nvp.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::fusion::pair
	//
	template<typename Archive, typename T0, typename T1>
	SPRIG_INLINE void serialize(
		Archive& ar,
		boost::fusion::pair<T0, T1>& t,
		unsigned int const
		)
	{
		ar
			& boost::serialization::make_nvp("second", t.second)
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_PAIR_HPP
