/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_MAP_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_MAP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/map.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serialize_def.hpp>

//
// boost::fusion::map
//
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	FUSION_MAX_MAP_SIZE,
	boost::fusion::map
	);

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_MAP_HPP
