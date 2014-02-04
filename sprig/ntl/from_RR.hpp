/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NTL_FROM_RR_HPP
#define SPRIG_NTL_FROM_RR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/external/ntl/rr.hpp>
#include <sprig/external/ntl/xdouble.hpp>
#include <sprig/external/ntl/quad_float.hpp>

namespace sprig {
	//
	// from_RR
	//
	// specialization from_RR: T == NTL::RR
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::RR>,
			NTL::RR
		>::type* = 0
		)
	{
		return target;
	}
	//
	// specialization from_RR: T == NTL::ZZ
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::ZZ>,
			NTL::ZZ
		>::type* = 0
		)
	{
		return NTL::to_ZZ(target);
	}
	//
	// specialization from_RR: T == NTL::xdouble
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::xdouble>,
			NTL::xdouble
		>::type* = 0
		)
	{
		return NTL::to_xdouble(target);
	}
	//
	// specialization from_RR: T == NTL::quad_float
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::quad_float>,
			NTL::quad_float
		>::type* = 0
		)
	{
		return NTL::to_quad_float(target);
	}
	//
	// specialization from_RR: T == int
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, int>,
			int
		>::type* = 0
		)
	{
		return NTL::to_int(target);
	}
	//
	// specialization from_RR: is_integral(T) && T != int
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::is_integral<T>,
				boost::mpl::not_<
					boost::is_same<typename boost::remove_const<T>::type, int>
				>
			>,
			int*
		>::type* = 0
		)
	{
		return NTL::to_long(target);
	}
	//
	// specialization from_RR: T == float
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, float>,
			float
		>::type* = 0
		)
	{
		return NTL::to_float(target);
	}
	//
	// specialization from_RR: is_float(T) && T != float
	//
	template<typename T>
	SPRIG_INLINE T from_RR(
		NTL::RR const& target,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::is_float<T>,
				boost::mpl::not_<
					boost::is_same<typename boost::remove_const<T>::type, float>
				>
			>,
			float*
		>::type* = 0
		)
	{
		return NTL::to_double(target);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_FROM_RR_HPP
