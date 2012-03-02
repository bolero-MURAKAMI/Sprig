#ifndef SPRIG_SERIALIZATION_SPRIG_TREE_HPP
#define SPRIG_SERIALIZATION_SPRIG_TREE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/optional.hpp>
#include <sprig/tree.hpp>
#include <sprig/utility/serialization.hpp>
#include <sprig/serialization/boost/compressed_pair.hpp>
#include <sprig/serialization/sprig/utility.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	template<typename Archive, typename T, typename Traits>
	SPRIG_INLINE void serialize(
		Archive& ar,
		sprig::tree<T, Traits>& value,
		unsigned int const
		)
	{
		ar & boost::serialization::make_nvp("value", value.get());
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_SPRIG_TREE_HPP
