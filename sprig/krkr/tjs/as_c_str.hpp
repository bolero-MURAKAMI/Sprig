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
			SPRIG_INLINE tjs_char const* as_c_str(tTJSVariantString const* source) {
				tjs_char const* src = source->operator tjs_char const*();
				return src ? src
					: SPRIG_KRKR_TJS_W("")
					;
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_AS_C_STR_HPP
