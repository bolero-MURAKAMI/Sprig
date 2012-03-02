#ifndef SPRIG_ACCEPT_HPP
#define SPRIG_ACCEPT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/addressof.hpp>

namespace sprig {
	//
	// accept
	//
	template<typename T>
	SPRIG_INLINE T** accept(T*& p) {
		return boost::addressof(p);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ACCEPT_HPP
