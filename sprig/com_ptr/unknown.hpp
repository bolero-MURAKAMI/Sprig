/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_COM_PTR_UNKNOWN_HPP
#define SPRIG_COM_PTR_UNKNOWN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/unknwn.hpp>
#include <sprig/com_ptr.hpp>

namespace {
	//
	// com_ptr_add_ref
	//
	SPRIG_INLINE void com_ptr_add_ref(IUnknown* ptr) {
		ptr->AddRef();
	}
	//
	// com_ptr_release
	//
	SPRIG_INLINE void com_ptr_release(IUnknown* ptr) {
		ptr->Release();
	}
}	// anonymous-namespace

#endif	// #ifndef SPRIG_COM_PTR_UNKNOWN_HPP
