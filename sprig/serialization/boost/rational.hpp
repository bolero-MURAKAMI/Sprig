/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_BOOST_RATIONAL_HPP
#define SPRIG_SERIALIZATION_BOOST_RATIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/rational.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// boost::rational
	//
	template<typename Archive, typename Int>
	SPRIG_INLINE void save(Archive& ar, boost::rational<Int> const& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("numerator", v.numerator())
			& boost::serialization::make_nvp("denominator", v.denominator())
			;
	}
	template<typename Archive, typename Int>
	SPRIG_INLINE void load(Archive& ar, boost::rational<Int>& v, unsigned int const) {
		Int numerator;
		Int denominator;
		ar
			& boost::serialization::make_nvp("numerator", numerator)
			& boost::serialization::make_nvp("denominator", denominator)
			;
		v.assign(numerator, denominator);
	}
	template<typename Archive, typename Int>
	SPRIG_INLINE void serialize(Archive& ar, boost::rational<Int>& v, unsigned int const version) {
		boost::serialization::split_free(ar, v, version);
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_RATIONAL_HPP
