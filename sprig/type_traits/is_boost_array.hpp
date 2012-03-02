#ifndef SPRIG_TYPE_TRAITS_IS_BOOST_ARRAY_HPP
#define SPRIG_TYPE_TRAITS_IS_BOOST_ARRAY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_boost_array
	//
	template<typename T, typename Enable = void>
	struct is_boost_array
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_boost_array<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				boost::array<
					typename T::value_type,
					T::static_size
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_BOOST_ARRAY_HPP
