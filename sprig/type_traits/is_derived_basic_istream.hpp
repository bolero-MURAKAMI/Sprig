#ifndef SPRIG_TYPE_TRAITS_IS_DERIVED_BASIC_ISTREAM_HPP
#define SPRIG_TYPE_TRAITS_IS_DERIVED_BASIC_ISTREAM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_derived_basic_istream
	//
	template<typename T, typename Enable = void>
	struct is_derived_basic_istream
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_derived_basic_istream<
		T,
		typename boost::enable_if<
			boost::is_base_and_derived<
				std::basic_istream<
					typename T::char_type,
					typename T::traits_type
				>,
				T
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_DERIVED_BASIC_ISTREAM_HPP
