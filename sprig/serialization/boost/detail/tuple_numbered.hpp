/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_NUMBERED_HPP
#define SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_NUMBERED_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/tuple/tuple.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
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
// SPRIG_SERIALIZATION_BOOST_TUPLE_ARCHIVE_GEN
// SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN
//
#define SPRIG_SERIALIZATION_BOOST_TUPLE_ARCHIVE_GEN(Z, N, D) \
	& boost::serialization::make_nvp(BOOST_PP_STRINGIZE(BOOST_PP_CAT(_, N)), t.get<N>())
#define SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN(Z, N, D) \
	template<typename Archive, BOOST_PP_ENUM_PARAMS(N, typename T)> \
	SPRIG_INLINE void serialize( \
		Archive& ar, \
		boost::tuple<BOOST_PP_ENUM_PARAMS(N, T)>& t, \
		unsigned int const, \
		typename boost::enable_if_c< \
			boost::tuples::length<boost::tuple<BOOST_PP_ENUM_PARAMS(N, T)> >::value == N \
		>::type* = 0 \
		) \
	{ \
		ar \
			BOOST_PP_REPEAT(N, SPRIG_SERIALIZATION_BOOST_TUPLE_ARCHIVE_GEN, BOOST_PP_EMPTY()) \
			; \
	}

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::tuple
	//
	template<typename Archive>
	void serialize(
		Archive& ar,
		boost::tuple<>& t,
		unsigned int const
		)
	{}
	BOOST_PP_REPEAT_FROM_TO(
		1,
		BOOST_PP_INC(SPRIG_SERIALIZATION_BOOST_TUPLE_ARGS_MAX),
		SPRIG_SERIALIZATION_BOOST_TUPLE_SERIALIZE_GEN,
		BOOST_PP_EMPTY()
		);
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_DETAIL_TUPLE_NUMBERED_HPP
