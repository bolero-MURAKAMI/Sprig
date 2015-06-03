/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CURVE_BEZIER_HPP
#define SPRIG_CURVE_BEZIER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/geometry/core/access.hpp>
#include <sprig/detail/pow.hpp>

namespace sprig {
	//
	// bezier
	//
	template<typename T, typename Point>
	SPRIG_INLINE Point
	bezier(T const& t, Point const& p0, Point const& p1, Point const& p2) {
		namespace bg = boost::geometry;
		using sprout::detail::pow2;
		return Point(
			pow2(1 - t) * bg::get<0>(p0)
				+ 2 * t * (1 - t) * bg::get<0>(p1)
				+ pow2(t) * bg::get<0>(p2)
				,
			pow2(1 - t) * bg::get<1>(p0)
				+ 2 * t * (1 - t) * bg::get<1>(p1)
				+ pow2(t) * bg::get<1>(p2)
			);
	}
	template<typename T, typename Point>
	SPRIG_INLINE Point
	bezier(T const& t, Point const& p0, Point const& p1, Point const& p2, Point const& p3) {
		namespace bg = boost::geometry;
		using sprout::detail::pow2;
		using sprout::detail::pow3;
		return Point(
			pow3(1 - t) * bg::get<0>(p0)
				+ 3 * t * pow2(1 - t) * bg::get<0>(p1)
				+ 3 * pow2(t) * (1 - t) * bg::get<0>(p2)
				+ pow3(t) * bg::get<0>(p3)
				,
			pow3(1 - t) * bg::get<1>(p0)
				+ 3 * t * pow2(1 - t) * bg::get<1>(p1)
				+ 3 * pow2(t) * (1 - t) * bg::get<1>(p2)
				+ pow3(t) * bg::get<1>(p3)
			);
	}
	template<typename T, typename Point>
	SPRIG_INLINE Point
	bezier(T const& t, Point const& p0, Point const& p1, Point const& p2, Point const& p3, Point const& p4) {
		namespace bg = boost::geometry;
		using sprout::detail::pow2;
		using sprout::detail::pow3;
		using sprout::detail::pow4;
		return Point(
			pow4(1 - t) * bg::get<0>(p0)
				+ 4 * t * pow3(1 - t) * bg::get<0>(p1)
				+ 6 * pow2(t) * pow2(1 - t) * bg::get<0>(p2)
				+ 4 * pow3(t) * (1 - t) * bg::get<0>(p3)
				+ pow4(t) * bg::get<0>(p4)
				,
			pow4(1 - t) * bg::get<1>(p0)
				+ 4 * t * pow3(1 - t) * bg::get<1>(p1)
				+ 6 * pow2(t) * pow2(1 - t) * bg::get<1>(p2)
				+ 4 * pow3(t) * (1 - t) * bg::get<1>(p3)
				+ pow4(t) * bg::get<1>(p4)
			);
	}
	template<typename T, typename Point>
	SPRIG_INLINE Point
	bezier(T const& t, Point const& p0, Point const& p1, Point const& p2, Point const& p3, Point const& p4, Point const& p5) {
		namespace bg = boost::geometry;
		using sprout::detail::pow2;
		using sprout::detail::pow3;
		using sprout::detail::pow4;
		using sprout::detail::pow5;
		return Point(
			pow5(1 - t) * bg::get<0>(p0)
				+ 5 * t * pow4(1 - t) * bg::get<0>(p1)
				+ 10 * pow2(t) * pow3(1 - t) * bg::get<0>(p2)
				+ 10 * pow3(t) * pow2(1 - t) * bg::get<0>(p3)
				+ 5 * pow4(t) * (1 - t) * bg::get<0>(p4)
				+ pow5(t) * bg::get<0>(p5)
				,
			pow5(1 - t) * bg::get<1>(p0)
				+ 5 * t * pow4(1 - t) * bg::get<1>(p1)
				+ 10 * pow2(t) * pow3(1 - t) * bg::get<1>(p2)
				+ 10 * pow3(t) * pow2(1 - t) * bg::get<1>(p3)
				+ 5 * pow4(t) * (1 - t) * bg::get<1>(p4)
				+ pow5(t) * bg::get<1>(p5)
			);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_CURVE_BEZIER_HPP
