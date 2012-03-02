#ifndef SPRIG_SERIALIZATION_WINDOWS_HPP
#define SPRIG_SERIALIZATION_WINDOWS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <sprig/external/windows.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// POINT
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, POINT& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("x", v.x)
			& boost::serialization::make_nvp("y", v.y)
			;
	}
	//
	// SIZE
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, SIZE& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("cx", v.cx)
			& boost::serialization::make_nvp("cy", v.cy)
			;
	}
	//
	// RECT
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, RECT& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("left", v.left)
			& boost::serialization::make_nvp("top", v.top)
			& boost::serialization::make_nvp("right", v.right)
			& boost::serialization::make_nvp("bottom", v.bottom)
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_WINDOWS_HPP
