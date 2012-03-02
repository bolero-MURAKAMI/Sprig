#ifndef SPRIG_TYPE_TRAITS_IS_DEQUE_HPP
#define SPRIG_TYPE_TRAITS_IS_DEQUE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <deque>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_deque
	//
	template<typename T, typename Enable = void>
	struct is_deque
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_deque<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::deque<
					typename T::value_type,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_DEQUE_HPP
