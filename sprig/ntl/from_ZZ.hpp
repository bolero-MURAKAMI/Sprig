#ifndef SPRIG_NTL_FROM_ZZ_HPP
#define SPRIG_NTL_FROM_ZZ_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
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
	// from_ZZ
	//
	// specialization from_ZZ: T == NTL::ZZ
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::ZZ>
		>::type* = 0
		)
	{
		return target;
	}
	//
	// specialization from_ZZ: T == NTL::RR
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::RR>
		>::type* = 0
		)
	{
		return NTL::to_RR(target);
	}
	//
	// specialization from_ZZ: T == NTL::xdouble
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::xdouble>
		>::type* = 0
		)
	{
		return NTL::to_xdouble(target);
	}
	//
	// specialization from_ZZ: T == NTL::quad_float
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, NTL::quad_float>
		>::type* = 0
		)
	{
		return NTL::to_quad_float(target);
	}
	//
	// specialization from_ZZ: T == int
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, int>
		>::type* = 0
		)
	{
		return NTL::to_int(target);
	}
	//
	// specialization from_ZZ: is_signed(T) && T != int
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::is_signed<T>,
				boost::mpl::not_<
					boost::is_same<typename boost::remove_const<T>::type, int>
				>
			>
		>::type* = 0
		)
	{
		return NTL::to_long(target);
	}
	//
	// specialization from_ZZ: T == unsigned int
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, unsigned int>
		>::type* = 0
		)
	{
		return NTL::to_uint(target);
	}
	//
	// specialization from_ZZ: is_unsigned(T) && T != unsigned int
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::is_unsigned<T>,
				boost::mpl::not_<
					boost::is_same<typename boost::remove_const<T>::type, unsigned int>
				>
			>
		>::type* = 0
		)
	{
		return NTL::to_ulong(target);
	}
	//
	// specialization from_ZZ: T == float
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::is_same<typename boost::remove_const<T>::type, float>
		>::type* = 0
		)
	{
		return NTL::to_float(target);
	}
	//
	// specialization from_ZZ: is_float(T) && T != float
	//
	template<typename T>
	SPRIG_INLINE T from_ZZ(
		NTL::ZZ const& target,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::is_float<T>,
				boost::mpl::not_<
					boost::is_same<typename boost::remove_const<T>::type, float>
				>
			>
		>::type* = 0
		)
	{
		return NTL::to_double(target);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_FROM_ZZ_HPP
