#ifndef SPRIG_TYPE_TRAITS_IS_WCHAR_TYPE_HPP
#define SPRIG_TYPE_TRAITS_IS_WCHAR_TYPE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace sprig {
	//
	// is_wchar_type
	//
	template<typename T>
	struct is_wchar_type
		: public boost::is_same<typename boost::remove_cv<T>::type, wchar_t>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_WCHAR_TYPE_HPP
