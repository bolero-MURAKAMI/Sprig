#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_LIST_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_LIST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/list.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serialize_def.hpp>

//
// boost::fusion::list
//
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	FUSION_MAX_LIST_SIZE,
	boost::fusion::list
	);

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_LIST_HPP
