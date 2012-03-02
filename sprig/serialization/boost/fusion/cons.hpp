#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_CONS_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_CONS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/cons.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serialize_def.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::fusion::nil
	//
	template<typename Archive>
	void serialize(
		Archive& ar,
		boost::fusion::nil&,
		unsigned int const
		)
	{}
SPRIG_SERIALIZATION_NAMESPACE_END

//
// boost::fusion::cons
//
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	1,
	boost::fusion::cons
	);
SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(
	2,
	boost::fusion::cons
	);

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_CONS_HPP
