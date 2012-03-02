#ifndef SPRIG_TYPE_TRAITS_IS_SET_HPP
#define SPRIG_TYPE_TRAITS_IS_SET_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <set>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_set
	//
	template<typename T, typename Enable = void>
	struct is_set
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_set<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::set<
					typename T::key_type,
					typename T::key_compare,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_multiset
	//
	template<typename T, typename Enable = void>
	struct is_multiset
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_multiset<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::multiset<
					typename T::key_type,
					typename T::key_compare,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_SET_HPP
