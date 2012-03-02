#ifndef SPRIG_SERIALIZATION_SPRIG_UTILITY_HPP
#define SPRIG_SERIALIZATION_SPRIG_UTILITY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/utility/utility.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	template<typename Archive>
	SPRIG_INLINE void serialize(
		Archive&,
		sprig::empty_class&,
		unsigned int const
		)
	{}
	template<typename Archive, typename T>
	SPRIG_INLINE void serialize(
		Archive&,
		sprig::empty_class_type_to<T>&,
		unsigned int const
		)
	{}
	template<typename Archive, int N>
	SPRIG_INLINE void serialize(
		Archive&,
		sprig::empty_class_enum<N>&,
		unsigned int const
		)
	{}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_SPRIG_UTILITY_HPP
