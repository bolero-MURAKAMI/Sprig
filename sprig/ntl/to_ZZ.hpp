/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NTL_TO_ZZ_HPP
#define SPRIG_NTL_TO_ZZ_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>
#include <sprig/type_traits/c_str_element.hpp>
#include <sprig/type_traits/is_convertible_to_ZZ.hpp>

namespace sprig {
	//
	// to_ZZ
	//
	// specialization to_ZZ: T == NTL::ZZ
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_same<T, NTL::ZZ>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return target;
	}
	//
	// specialization to_ZZ: is_convertible_to_ZZ(T) && T != NTL::ZZ
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_convertible_to_ZZ<T>,
			boost::mpl::not_<boost::is_same<T, NTL::ZZ> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(target);
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_convertible_to_ZZ<T>,
			boost::mpl::not_<boost::is_same<T, NTL::ZZ> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(target);
	}
	//
	// specialization to_ZZ: is_signed(T) && !is_convertible_to_ZZ(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_signed<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_signed>(target));
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_signed<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_signed>(target));
	}
	//
	// specialization to_ZZ: is_unsigned(T) && !is_convertible_to_ZZ(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_unsigned<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_unsigned>(target));
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_unsigned<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_unsigned>(target));
	}
	//
	// specialization to_ZZ: is_float(T) && !is_convertible_to_ZZ(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_float<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_float>(target));
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::is_float<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(static_cast<to_ZZ_convertion_traits::max_float>(target));
	}
	//
	// specialization to_ZZ: is_c_str(T) && !is_convertible_to_ZZ(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_c_str<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_c_str<T>,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			typename boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
	//
	// specialization to_ZZ: is_basic_string(T) && is_convertible_to_ZZ(T::value_type const*)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			is_convertible_to_ZZ<typename T::value_type const*>,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(target.c_str());
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			is_convertible_to_ZZ<typename T::value_type const*>,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(target.c_str());
	}
	//
	// specialization to_ZZ: is_basic_string(T) && !is_convertible_to_ZZ(T::value_type const*)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			boost::mpl::not_<is_convertible_to_ZZ<typename T::value_type const*> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			boost::mpl::not_<is_convertible_to_ZZ<typename T::value_type const*> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
	//
	// specialization to_ZZ: !is_arithmetic(T) && !is_c_str(T) && !is_basic_string(T) && !is_convertible_to_ZZ(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::not_<boost::is_arithmetic<T> >,
			boost::mpl::not_<is_c_str<T> >,
			boost::mpl::not_<is_basic_string<T> >,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			is_call_copy_param<T>
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::not_<boost::is_arithmetic<T> >,
			boost::mpl::not_<is_c_str<T> >,
			boost::mpl::not_<is_basic_string<T> >,
			boost::mpl::not_<is_convertible_to_ZZ<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::ZZ
	>::type
	to_ZZ(T const& target) {
		return NTL::to_ZZ(str_cast<std::string>(target).c_str());
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_TO_ZZ_HPP
