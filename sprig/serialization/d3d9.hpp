/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_D3D9_HPP
#define SPRIG_SERIALIZATION_D3D9_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <sprig/external/d3d9.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// D3DVERTEXBUFFER_DESC
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DVERTEXBUFFER_DESC& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("Format", v.Format)
			& boost::serialization::make_nvp("Type", v.Type)
			& boost::serialization::make_nvp("Usage", v.Usage)
			& boost::serialization::make_nvp("Pool", v.Pool)
			& boost::serialization::make_nvp("Size", v.Size)
			& boost::serialization::make_nvp("FVF", v.FVF)
			;
	}
	//
	// D3DINDEXBUFFER_DESC
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DINDEXBUFFER_DESC& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("Format", v.Format)
			& boost::serialization::make_nvp("Type", v.Type)
			& boost::serialization::make_nvp("Usage", v.Usage)
			& boost::serialization::make_nvp("Pool", v.Pool)
			& boost::serialization::make_nvp("Size", v.Size)
			;
	}
	//
	// D3DSURFACE_DESC
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DSURFACE_DESC& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("Format", v.Format)
			& boost::serialization::make_nvp("Type", v.Type)
			& boost::serialization::make_nvp("Usage", v.Usage)
			& boost::serialization::make_nvp("Pool", v.Pool)
			& boost::serialization::make_nvp("MultiSampleType", v.MultiSampleType)
			& boost::serialization::make_nvp("MultiSampleQuality", v.MultiSampleQuality)
			& boost::serialization::make_nvp("Width", v.Width)
			& boost::serialization::make_nvp("Height", v.Height)
			;
	}
	//
	// D3DVOLUME_DESC
	//
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, D3DVOLUME_DESC& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("Format", v.Format)
			& boost::serialization::make_nvp("Type", v.Type)
			& boost::serialization::make_nvp("Usage", v.Usage)
			& boost::serialization::make_nvp("Pool", v.Pool)
			& boost::serialization::make_nvp("Width", v.Width)
			& boost::serialization::make_nvp("Height", v.Height)
			& boost::serialization::make_nvp("Depth", v.Depth)
			;
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_D3D9_HPP
