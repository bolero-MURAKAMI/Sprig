#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_DEQUE_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_DEQUE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/deque.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serialize_def.hpp>

//
// boost::fusion::deque
//
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	FUSION_MAX_DEQUE_SIZE,
	boost::fusion::deque
	);

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_DEQUE_HPP
