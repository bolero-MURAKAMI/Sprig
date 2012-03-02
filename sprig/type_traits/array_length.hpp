#ifndef SPRIG_TYPE_TRAITS_ARRAY_LENGTH_HPP
#define SPRIG_TYPE_TRAITS_ARRAY_LENGTH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_bounds.hpp>

namespace sprig {
	//
	// array_length
	//
	template<typename T>
	struct array_length
		: public boost::mpl::size_t<
			sizeof(T) / sizeof(typename boost::remove_bounds<T>::type)
		>
	{
		BOOST_MPL_ASSERT((boost::is_array<T>));
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_ARRAY_LENGTH_HPP
