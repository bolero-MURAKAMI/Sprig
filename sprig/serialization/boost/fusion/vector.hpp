/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/vector.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serialize_def.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_n_serialize_def.hpp>

//
// SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_N_ARGS_MAX
//
#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_N_ARGS_MAX
#	define SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_N_ARGS_MAX FUSION_MAX_VECTOR_SIZE
#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_N_ARGS_MAX

//
// boost::fusion::vector
// boost::fusion::vector[N]
//
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	FUSION_MAX_VECTOR_SIZE,
	boost::fusion::vector
	);
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF(
	SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_N_ARGS_MAX,
	boost::fusion::vector
	);

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_VECTOR_HPP
