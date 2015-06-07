/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_ESCAPE_C_HPP
#define SPRIG_KRKR_TJS_ESCAPE_C_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/tjs/as_c_str.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// escape_c
			//
			SPRIG_INLINE tTJSString escape_c(tTJSString const& source) {
				tTJSString result;
				source.EscapeC(result);
				return result;
			}
			SPRIG_INLINE tTJSString escape_c(tjs_char const* source) {
				sprig::krkr::tjs::escape_c(tTJSString(source));
			}
			SPRIG_INLINE tTJSString escape_c(tTJSVariantString const* source) {
				sprig::krkr::tjs::escape_c(sprig::krkr::tjs::as_c_str(source));
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_ESCAPE_C_HPP
