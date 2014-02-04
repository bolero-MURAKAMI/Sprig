/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/for_each.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/serialization/boost/fusion/fusion_sequence_serializer.hpp>

//
// SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF
//
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF(N, CLASS_TEMPLATE) \
	SPRIG_SERIALIZATION_NAMESPACE_BEGIN \
		template<typename Archive, BOOST_PP_ENUM_PARAMS(N, typename T)> \
		void serialize( \
			Archive& ar, \
			CLASS_TEMPLATE<BOOST_PP_ENUM_PARAMS(N, T)>& t, \
			unsigned int const \
			) \
		{ \
			boost::fusion::for_each(t, sprig::serialization::make_fusion_sequence_serializer(ar)); \
		} \
	SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZE_DEF_HPP
