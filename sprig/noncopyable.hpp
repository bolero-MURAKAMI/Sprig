#ifndef SPRIG_NONCOPYABLE_HPP
#define SPRIG_NONCOPYABLE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	//
	// noncopyable
	//
	template<typename T>
	class noncopyable {
	protected:
		noncopyable() {}
		~noncopyable() {}
	private:
		noncopyable(noncopyable const&);
		noncopyable const& operator=(noncopyable const&);
	};
} // namespace sprig

#endif	// #ifndef SPRIG_NONCOPYABLE_HPP
