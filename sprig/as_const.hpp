#ifndef SPRIG_AS_CONST_HPP
#define SPRIG_AS_CONST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	//
	// as_const
	//
	template<typename T>
	T const& as_const(T const& t) {
		return t;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_AS_CONST_HPP
