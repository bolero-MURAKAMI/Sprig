#ifndef SPRIG_TYPE_TRAITS_IS_PAIR_HPP
#define SPRIG_TYPE_TRAITS_IS_PAIR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_pair
	//
	template<typename T, typename Enable = void>
	struct is_pair
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_pair<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::pair<
					typename T::first_type,
					typename T::second_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_PAIR_HPP
