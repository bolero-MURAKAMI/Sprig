/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_AS_VARIANT_HPP
#define SPRIG_KRKR_TJS_AS_VARIANT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/get_pointer.hpp>
#include <sprig/krkr/tjs/typedef.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// as_object_closure_variant
			//
			SPRIG_INLINE tTJSVariant as_object_closure_variant(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis) {
				return tTJSVariant(sprig::get_pointer(obj), sprig::get_pointer(objthis));
			}
			SPRIG_INLINE tTJSVariant as_object_closure_variant(sprig::krkr::tjs::object_type const& obj) {
				return sprig::krkr::tjs::as_object_closure_variant(obj, obj);
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_AS_VARIANT_HPP
