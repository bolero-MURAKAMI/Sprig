#ifndef SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_HEAD_TAIL_HPP
#define SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_HEAD_TAIL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/tuple/tuple.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <sprig/utility/serialization.hpp>

//
// SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX
//
#ifndef SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX
#	define SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX 10
#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX

//
// SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN
//
#define SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN(Z, N, D) \
	template<typename Archive, BOOST_PP_ENUM_PARAMS(N, typename T)> \
	void serialize( \
		Archive& ar, \
		boost::tuple<BOOST_PP_ENUM_PARAMS(N, T)>& t, \
		unsigned int const \
		) \
	{ \
		ar \
			& boost::serialization::make_nvp("head", t.head) \
			& boost::serialization::make_nvp("tail", t.tail) \
			; \
	}

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::tuples::cons
	//
	template<typename Archive, typename Head>
	void serialize(
		Archive& ar,
		boost::tuples::cons<Head, boost::tuples::null_type>& t,
		unsigned int const
		)
	{
		ar
			& boost::serialization::make_nvp("head", t.head)
			;
	}
	template<typename Archive, typename Head, typename Tail>
	void serialize(
		Archive& ar,
		boost::tuples::cons<Head, Tail>& t,
		unsigned int const
		)
	{
		ar
			& boost::serialization::make_nvp("head", t.head)
			& boost::serialization::make_nvp("tail", t.tail)
			;
	}
	//
	// boost::tuple
	//
	template<typename Archive>
	void serialize(
		Archive& ar,
		boost::tuple<>&,
		unsigned int const
		)
	{}
	template<typename Archive, typename T1>
	void serialize(
		Archive& ar,
		boost::tuple<T1>& t,
		unsigned int const
		)
	{
		ar
			& boost::serialization::make_nvp("head", t.head);
	}
	BOOST_PP_REPEAT_FROM_TO(
		2,
		BOOST_PP_INC(SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX),
		SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN,
		BOOST_PP_EMPTY()
		);
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_HEAD_TAIL_HPP
