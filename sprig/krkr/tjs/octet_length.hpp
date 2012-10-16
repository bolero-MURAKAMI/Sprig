#ifndef SPRIG_KRKR_TJS_OCTET_LENGTH_HPP
#define SPRIG_KRKR_TJS_OCTET_LENGTH_HPP

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
			// octet_length
			//
			SPRIG_INLINE tjs_uint octet_length(tTJSVariantOctet const* source) {
				return source ? source->GetLength()
					: 0
					;
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_OCTET_LENGTH_HPP
