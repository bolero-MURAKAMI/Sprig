/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_SPRIG_PRIORITY_MAP_HPP
#define SPRIG_SERIALIZATION_SPRIG_PRIORITY_MAP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <sprig/priority_map.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	template <typename Archive, typename Key, typename Priority, typename Mapped>
	SPRIG_INLINE void save(Archive& ar, sprig::priority_map_element<Key, Priority, Mapped> const& v, unsigned int const) {
		ar
			& boost::serialization::make_nvp("key", v.get_key())
			& boost::serialization::make_nvp("priority", v.get_priority())
			& boost::serialization::make_nvp("mapped", v.get_mapped())
			;
	}
	template <typename Archive, typename Key, typename Priority, typename Mapped>
	SPRIG_INLINE void load(Archive& ar, sprig::priority_map_element<Key, Priority, Mapped>& v, unsigned int const) {
		typedef sprig::priority_map_element<Key, Priority, Mapped> value_type;
		typename value_type::key_type key;
		typename value_type::priority_type priority;
		typename value_type::mapped_type mapped;
		ar
			& boost::serialization::make_nvp("key", key)
			& boost::serialization::make_nvp("priority", priority)
			& boost::serialization::make_nvp("mapped", mapped)
			;
		v.set_key(key);
		v.set_priority(priority);
		v.set_mapped(mapped);
	}
	template <typename Archive, typename Key, typename Priority, typename Mapped>
	SPRIG_INLINE void serialize(Archive& ar, sprig::priority_map_element<Key, Priority, Mapped>& v, unsigned int const version) {
		boost::serialization::split_free(ar, v, version);
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_SPRIG_PRIORITY_MAP_HPP
