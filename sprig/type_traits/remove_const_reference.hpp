#ifndef SPRIG_TYPE_TRAITS_REMOVE_CONST_REFERENCE_HPP
#define SPRIG_TYPE_TRAITS_REMOVE_CONST_REFERENCE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace sprig {
	//
	// remove_const_reference
	//
	template<typename T>
	struct remove_const_reference
		: public boost::remove_const<
			typename boost::remove_reference<T>::type
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_REMOVE_CONST_REFERENCE_HPP
