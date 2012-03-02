#ifndef SPRIG_KRKR_TJS_INSTANCE_HPP
#define SPRIG_KRKR_TJS_INSTANCE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// create_tjs_native_instance
			//
			// COMMENT: 指定された型のインスタンスを生成して返す。
			//
			template<typename T>
			SPRIG_INLINE iTJSNativeInstance* TJS_INTF_METHOD create_tjs_native_instance() {
				return new T();
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_INSTANCE_HPP
