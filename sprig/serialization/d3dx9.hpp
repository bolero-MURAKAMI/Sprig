/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_D3DX9_HPP
#define SPRIG_SERIALIZATION_D3DX9_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <sprig/external/d3dx9.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// D3DXVECTOR2
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DXVECTOR2& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("x", v.x)
			& boost::serialization::make_nvp("y", v.y)
			;
	}
	//
	// D3DXVECTOR3
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DXVECTOR3& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("x", v.x)
			& boost::serialization::make_nvp("y", v.y)
			& boost::serialization::make_nvp("z", v.z)
			;
	}
	//
	// D3DXVECTOR4
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DXVECTOR4& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("x", v.x)
			& boost::serialization::make_nvp("y", v.y)
			& boost::serialization::make_nvp("z", v.z)
			& boost::serialization::make_nvp("w", v.w)
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_D3DX9_HPP
