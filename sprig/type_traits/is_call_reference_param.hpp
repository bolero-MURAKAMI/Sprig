#ifndef SPRIG_TYPE_TRAITS_IS_CALL_REFERENCE_PARAM_HPP
#define SPRIG_TYPE_TRAITS_IS_CALL_REFERENCE_PARAM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/call_traits.hpp>
#include <boost/type_traits/is_reference.hpp>

namespace sprig {
	//
	// is_call_reference_param
	//
	template<typename T>
	struct is_call_reference_param
		: public boost::is_reference<
			typename boost::call_traits<T>::param_type
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_CALL_REFERENCE_PARAM_HPP
