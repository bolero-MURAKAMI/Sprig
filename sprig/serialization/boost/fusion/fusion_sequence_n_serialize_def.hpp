#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/for_each.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serializer.hpp>

//
// SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_GEN
//
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_GEN(Z, N, D_CLASS_TEMPLATE) \
	template<typename Archive, BOOST_PP_ENUM_PARAMS(N, typename T)> \
	SPRIG_INLINE void serialize( \
		Archive& ar, \
		BOOST_PP_CAT(D_CLASS_TEMPLATE, N)<BOOST_PP_ENUM_PARAMS(N, T)>& t, \
		unsigned int const \
		) \
	{ \
		boost::fusion::for_each(t, sprig::serialization::make_fusion_sequence_serializer(ar)); \
	}

//
// SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF
//
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF(N, CLASS_TEMPLATE) \
	SPRIG_SERIALIZATION_NAMESPACE_BEGIN \
		template<typename Archive> \
		void serialize( \
			Archive& ar, \
			BOOST_PP_CAT(CLASS_TEMPLATE, 0)<>& t, \
			unsigned int const \
			) \
		{} \
		BOOST_PP_REPEAT_FROM_TO( \
			1, \
			BOOST_PP_INC(N), \
			SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_GEN, \
			CLASS_TEMPLATE \
			); \
	SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_N_SERIALIZE_DEF_HPP
