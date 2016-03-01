/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_AS_C_STR_HPP
#define SPRIG_KRKR_TJS_AS_C_STR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/macro/text.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// as_c_str
			//
			SPRIG_INLINE tjs_nchar const* as_c_str(tjs_nchar const* source) {
				return source ? source
					: SPRIG_KRKR_TJS_N("")
					;
			}
			SPRIG_INLINE tjs_char const* as_c_str(tjs_char const* source) {
				return source ? source
					: SPRIG_KRKR_TJS_W("")
					;
			}
			SPRIG_INLINE tjs_char const* as_c_str(tTJSVariantString const* source) {
				tjs_char const* src = source->operator tjs_char const*();
				return sprig::krkr::tjs::as_c_str(
					source ? source->operator tjs_char const*()
						: 0
					);
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_AS_C_STR_HPP
