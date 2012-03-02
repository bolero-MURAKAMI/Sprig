#ifndef SPRIG_SERIALIZATION_SPRIG_UBLAS_MATRIX_HPP
#define SPRIG_SERIALIZATION_SPRIG_UBLAS_MATRIX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <sprig/ublas/matrix.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// scaling_2d
	//
	template <typename Archive, typename T>
	SPRIG_INLINE void serialize(Archive& ar, sprig::ublas::scaling_2d<T>& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("_0", v.get<0>())
			& boost::serialization::make_nvp("_1", v.get<1>())
			;
	}
	//
	// rotation_2d
	//
	template <typename Archive, typename T>
	SPRIG_INLINE void serialize(Archive& ar, sprig::ublas::rotation_2d<T>& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("_0", v.get<0>())
			;
	}
	//
	// scaling_2d
	//
	template <typename Archive, typename T>
	SPRIG_INLINE void serialize(Archive& ar, sprig::ublas::translation_2d<T>& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("_0", v.get<0>())
			& boost::serialization::make_nvp("_1", v.get<1>())
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_SPRIG_UBLAS_MATRIX_HPP
