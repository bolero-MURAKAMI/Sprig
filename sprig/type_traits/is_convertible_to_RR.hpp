#ifndef SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_RR_HPP
#define SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_RR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/type_traits/is_convertible_to_ZZ.hpp>

namespace sprig {
	//
	// to_RR_convertion_traits
	//
	struct to_RR_convertion_traits
		: public to_ZZ_convertion_traits
	{};

	//
	// is_convertible_to_RR
	//
	template<typename T/*, typename Enable = void*/>
	struct is_convertible_to_RR
		: public is_convertible_to_ZZ<T>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_RR_HPP
