/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_PAIR_HPP
#define SPRIG_UTILITY_PAIR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/compressed_pair.hpp>
#include <boost/tuple/tuple.hpp>

namespace sprig {
	//
	// first
	//
	template<typename T1, typename T2>
	SPRIG_INLINE T1& first(std::pair<T1, T2>& value) {
		return value.first;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T1 const& first(std::pair<T1, T2> const& value) {
		return value.first;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T1& first(boost::compressed_pair<T1, T2>& value) {
		return value.first();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T1 const& first(boost::compressed_pair<T1, T2> const& value) {
		return value.first();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T1& first(boost::tuple<T1, T2>& value) {
		return value.template get<0>();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T1 const& first(boost::tuple<T1, T2> const& value) {
		return value.template get<0>();
	}
	//
	// second
	//
	template<typename T1, typename T2>
	SPRIG_INLINE T2& second(std::pair<T1, T2>& value) {
		return value.second;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T2 const& second(std::pair<T1, T2> const& value) {
		return value.second;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T2& second(boost::compressed_pair<T1, T2>& value) {
		return value.second();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T2 const& second(boost::compressed_pair<T1, T2> const& value) {
		return value.second();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T2& second(boost::tuple<T1, T2>& value) {
		return value.template get<1>();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE T2 const& second(boost::tuple<T1, T2> const& value) {
		return value.template get<1>();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_PAIR_HPP
