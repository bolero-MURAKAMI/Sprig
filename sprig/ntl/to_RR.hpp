/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NTL_TO_RR_HPP
#define SPRIG_NTL_TO_RR_HPP

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
#include <sprig/external/ntl/rr.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/c_str_element.hpp>
#include <sprig/type_traits/is_basic_string.hpp>
#include <sprig/type_traits/is_convertible_to_RR.hpp>

namespace sprig {
	//
	// to_RR
	//
	// specialization to_RR: T == NTL::RR
	//
	template<typename T>
	typename boost::enable_if<
		boost::is_same<T, NTL::RR>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return target;
	}
	//
	// specialization to_RR: is_convertible_to_RR(T) && T != NTL::RR
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_convertible_to_RR<T>,
			boost::mpl::not_<boost::is_same<T, NTL::RR> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(target);
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_convertible_to_RR<T>,
			boost::mpl::not_<boost::is_same<T, NTL::RR> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(target);
	}
	//
	// specialization to_RR: is_signed(T) && !is_convertible_to_RR(T)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_signed<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_signed>(target));
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_signed<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_signed>(target));
	}
	//
	// specialization to_RR: is_unsigned(T) && !is_convertible_to_RR(T)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_unsigned<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_unsigned>(target));
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_unsigned<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_unsigned>(target));
	}
	//
	// specialization to_RR: is_float(T) && !is_convertible_to_RR(T)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_float<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_float>(target));
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::is_float<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(static_cast<to_RR_convertion_traits::max_float>(target));
	}
	//
	// specialization to_RR: is_c_str(T) && !is_convertible_to_RR(T)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_c_str<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_c_str<T>,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
	//
	// specialization to_RR: T == std::basic_string<T::value_type, T::traits_type, T::allocator_type> && is_convertible_to_RR(T::value_type const*)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			is_convertible_to_RR<typename T::value_type const*>,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(target.c_str());
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			is_convertible_to_RR<typename T::value_type const*>,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(target.c_str());
	}
	//
	// specialization to_RR: T == std::basic_string<T::value_type, T::traits_type, T::allocator_type> && !is_convertible_to_RR(T::value_type const*)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			boost::mpl::not_<is_convertible_to_RR<typename T::value_type const*> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			is_basic_string<T>,
			boost::mpl::not_<is_convertible_to_RR<typename T::value_type const*> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
	//
	// specialization to_RR: !is_arithmetic(T) && !is_c_str(T) && T == std::basic_string<T::value_type, T::traits_type, T::allocator_type> && !is_convertible_to_RR(T)
	//
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::not_<boost::is_arithmetic<T> >,
			boost::mpl::not_<is_c_str<T> >,
			boost::mpl::not_<is_basic_string<T> >,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			is_call_copy_param<T>
		>,
		NTL::RR
	>::type
	to_RR(T const target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
	template<typename T>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::not_<boost::is_arithmetic<T> >,
			boost::mpl::not_<is_c_str<T> >,
			boost::mpl::not_<is_basic_string<T> >,
			boost::mpl::not_<is_convertible_to_RR<T> >,
			boost::mpl::not_<is_call_copy_param<T> >
		>,
		NTL::RR
	>::type
	to_RR(T const& target) {
		return NTL::to_RR(str_cast<std::string>(target).c_str());
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_TO_RR_HPP
