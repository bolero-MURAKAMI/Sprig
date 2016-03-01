/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CURVE_CATMULL_ROM_SPLINE_HPP
#define SPRIG_CURVE_CATMULL_ROM_SPLINE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/geometry/core/access.hpp>
#include <sprig/detail/pow.hpp>

namespace sprig {
	//
	// catmull_rom_spline
	//
	template<typename T, typename Point>
	SPRIG_INLINE Point
	catmull_rom_spline(T const& t, Point const& p0, Point const& p1, Point const& p2, Point const& p3) {
		namespace bg = boost::geometry;
		using sprig::detail::pow2;
		using sprig::detail::pow3;
		return value_type(
			(-bg::get<0>(p0) + 3 * bg::get<0>(p1) - 3 * bg::get<0>(p2) + bg::get<0>(p3)) / 2 * pow3(t)
				+ (2 * bg::get<0>(p0) - 5 * bg::get<0>(p1) + 4 * bg::get<0>(p2) - bg::get<0>(p3) / 2 * pow2(t)
				+ (-bg::get<0>(p0) + bg::get<0>(p2)) / 2 * t
				+ bg::get<0>(p1)
				,
			(-bg::get<1>(p0) + 3 * bg::get<1>(p1) - 3 * bg::get<1>(p2) + bg::get<1>(p3)) / 2 * pow3(t)
				+ (2 * bg::get<1>(p0) - 5 * bg::get<1>(p1) + 4 * bg::get<1>(p2) - bg::get<1>(p3)) / 2 * pow2(t)
				+ (-bg::get<1>(p0) + bg::get<1>(p2)) / 2 * t
				+ bg::get<1>(p1)
			);
	}
	//
	// catmull_rom_spline_start
	//
	template<typename T, typename Point>
	SPRIG_INLINE Point
	catmull_rom_spline_start(T const& t, Point const& p0, Point const& p1, Point const& p2) {
		namespace bg = boost::geometry;
		using sprig::detail::pow2;
		return value_type(
			(bg::get<0>(p0) - 2 * bg::get<0>(p1) + bg::get<0>(p2)) / 2 * pow2(t)
				+ (-3 * bg::get<0>(p0) + 4 * bg::get<0>(p1) - bg::get<0>(p2)) / 2 * t
				+ bg::get<0>(p0)
				,
			(bg::get<1>(p0) - 2 * bg::get<1>(p1) + bg::get<1>(p2)) / 2 * pow2(t)
				+ (-3 * bg::get<1>(p0) + 4 * bg::get<1>(p1) - bg::get<1>(p2)) / 2 * t
				+ bg::get<1>(p0)
			);
	}
	//
	// catmull_rom_spline_end
	//
	template<typename T, typename Point>
	SPRIG_INLINE Point
	catmull_rom_spline_end(T const& t, Point const& p0, Point const& p1, Point const& p2) {
		namespace bg = boost::geometry;
		using sprig::detail::pow2;
		return value_type(
			(bg::get<0>(p0) - 2 * bg::get<0>(p1) + bg::get<0>(p2)) / 2 * pow2(t)
				+ (-bg::get<0>(p0) + bg::get<0>(p2)) / 2 * t
				+ bg::get<0>(p1)
				,
			(bg::get<1>(p0) - 2 * bg::get<1>(p1) + bg::get<1>(p2)) / 2 * pow2(t)
				+ (-bg::get<1>(p0) + bg::get<1>(p2)) / 2 * t
				+ bg::get<1>(p1)
			);
	}

	//
	// catmull_rom_spline_f
	//
	template<typename Point>
	struct catmull_rom_spline_f {
	public:
		typedef Point result_type;
	private:
		Point p0_;
		Point p1_;
		Point p2_;
		Point p3_;
	public:
		catmull_rom_spline_f(Point const& p0, Point const& p1, Point const& p2, Point const& p3)
			: p0_(p0), p1_(p1), p2_(p2), p3_(p3)
		{}
		template<typename T>
		Point operator()(T const& t) const {
			return sprig::catmull_rom_spline(t, p0_, p1_, p2_, p3_);
		}
	};
	//
	// catmull_rom_spline_start_f
	//
	template<typename Point>
	struct catmull_rom_spline_start_f {
	public:
		typedef Point result_type;
	private:
		Point p0_;
		Point p1_;
		Point p2_;
	public:
		catmull_rom_spline_start_f(Point const& p0, Point const& p1, Point const& p2)
			: p0_(p0), p1_(p1), p2_(p2)
		{}
		template<typename T>
		Point operator()(T const& t) const {
			return sprig::catmull_rom_spline_start(t, p0_, p1_, p2_);
		}
	};
	//
	// catmull_rom_spline_end_f
	//
	template<typename Point>
	struct catmull_rom_spline_end_f {
	public:
		typedef Point result_type;
	private:
		Point p0_;
		Point p1_;
		Point p2_;
	public:
		catmull_rom_spline_end_f(Point const& p0, Point const& p1, Point const& p2)
			: p0_(p0), p1_(p1), p2_(p2)
		{}
		template<typename T>
		Point operator()(T const& t) const {
			return sprig::catmull_rom_spline_end(t, p0_, p1_, p2_);
		}
	};

	//
	// make_catmull_rom_spline
	//
	template<typename Point>
	SPRIG_INLINE sprig::catmull_rom_spline_f<Point>
	make_catmull_rom_spline(Point const& p0, Point const& p1, Point const& p2, Point const& p3) {
		return sprig::catmull_rom_spline_f<Point>(p0, p1, p2, p3);
	}
	//
	// make_catmull_rom_spline_start
	//
	template<typename Point>
	SPRIG_INLINE sprig::catmull_rom_spline_start_f<Point>
	make_catmull_rom_spline_start(Point const& p0, Point const& p1, Point const& p2) {
		return sprig::catmull_rom_spline_start_f<Point>(p0, p1, p2);
	}
	//
	// make_catmull_rom_spline_end
	//
	template<typename Point>
	SPRIG_INLINE sprig::catmull_rom_spline_end_f<Point>
	make_catmull_rom_spline_end(Point const& p0, Point const& p1, Point const& p2) {
		return sprig::catmull_rom_spline_end_f<Point>(p0, p1, p2);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_CURVE_CATMULL_ROM_SPLINE_HPP
