#ifndef SPRIG_TYPE_TRAITS_IS_VECTOR_HPP
#define SPRIG_TYPE_TRAITS_IS_VECTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_vector
	//
	template<typename T, typename Enable = void>
	struct is_vector
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_vector<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				std::vector<
					typename T::value_type,
					typename T::allocator_type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_VECTOR_HPP
