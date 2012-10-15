#ifndef SPRIG_KRKR_TJS_OCTET_DATA_HPP
#define SPRIG_KRKR_TJS_OCTET_DATA_HPP

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
			// octet_data
			//
			namespace {
				SPRIG_INLINE tjs_uint8 const* octet_data(tTJSVariantOctet const* source) {
					return source ? source->GetData()
						: 0
						;
				}
			}	// anonymous-namespace
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_OCTET_DATA_HPP
