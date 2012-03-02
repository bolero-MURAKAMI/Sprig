#ifndef SPRIG_TYPE_TRAITS_IS_MAP_HPP
#define SPRIG_TYPE_TRAITS_IS_MAP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <map>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_map
	//
	template<typename T, typename Enable = void>
	struct is_map
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_map<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::map<
					typename T::key_type,
					typename T::mapped_type,
					typename T::key_compare,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_multimap
	//
	template<typename T, typename Enable = void>
	struct is_multimap
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_multimap<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::multimap<
					typename T::key_type,
					typename T::mapped_type,
					typename T::key_compare,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_MAP_HPP
