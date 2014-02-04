/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
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
