#ifndef SPRIG_SERIALIZATION_NTL_ZZ_HPP
#define SPRIG_SERIALIZATION_NTL_ZZ_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/lexical_cast.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// NTL::ZZ
	//
	template <typename Archive>
	SPRIG_INLINE void save(Archive& ar, NTL::ZZ const& v, unsigned int const) {
		std::string str(boost::lexical_cast<std::string>(v));
		ar
			& boost::serialization::make_nvp("str", str)
			;
	}
	template <typename Archive>
	SPRIG_INLINE void load(Archive& ar, NTL::ZZ& v, unsigned int const) {
		std::string str;
		ar
			& boost::serialization::make_nvp("str", str)
			;
		v = NTL::to_ZZ(str.c_str());
	}
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, NTL::ZZ& v, unsigned int const version) {
		boost::serialization::split_free(ar, v, version);
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_NTL_ZZ_HPP
