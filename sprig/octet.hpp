/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_OCTET_HPP
#define SPRIG_OCTET_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/assert.hpp>
#include <sprig/split_join.hpp>
#include <sprig/type_traits/is_boost_array.hpp>

namespace sprig {
	//
	// byte_of
	//
	template<typename T>
	struct byte_of
		: public boost::mpl::eval_if<
			boost::is_integral<T>,
			boost::mpl::identity<boost::uint8_t>,
			boost::range_value<T>
		>
	{};
	//
	// array_octet_of
	//
	template<typename T, typename Byte = typename sprig::byte_of<T>::type>
	struct array_octet_of
		: public boost::mpl::if_<
			boost::is_integral<T>,
			boost::array<Byte, sizeof(T)>,
			T
		>
	{
		BOOST_MPL_ASSERT((
			boost::mpl::or_<
				boost::is_integral<T>,
				sprig::is_boost_array<T>
			>
			));
	};
	//
	// to_octet
	//
	template<typename Octet, typename T>
	SPRIG_INLINE Octet to_octet(
		T t,
		typename boost::enable_if<
			boost::is_integral<T>
		>::type* = 0
		)
	{
		BOOST_MPL_ASSERT((boost::mpl::bool_<sizeof(T) == Octet::static_size>));
		Octet result;
		sprig::integer_split(t, boost::begin(result));
		return result;
	}
	template<typename Octet, typename T>
	SPRIG_INLINE Octet to_octet(
		T const& t,
		typename boost::enable_if<
			sprig::is_boost_array<T>
		>::type* = 0
		)
	{
		BOOST_MPL_ASSERT((boost::mpl::bool_<T::static_size == Octet::static_size>));
		return t;
	}
	//
	// to_array_octet
	//
	template<typename T>
	SPRIG_INLINE typename array_octet_of<T>::type to_array_octet(
		T t,
		typename boost::enable_if<
			boost::is_integral<T>
		>::type* = 0
		)
	{
		return to_octet<typename array_octet_of<T>::type>(t);
	}
	template<typename T>
	SPRIG_INLINE typename array_octet_of<T>::type to_array_octet(
		T const& t,
		typename boost::enable_if<
			sprig::is_boost_array<T>
		>::type* = 0
		)
	{
		return to_octet<typename array_octet_of<T>::type>(t);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_OCTET_HPP
