/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
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
			// COMMENT: �w�肳�ꂽ�^�̃C���X�^���X�𐶐����ĕԂ��B
			//
			template<typename T>
			SPRIG_INLINE iTJSNativeInstance* TJS_INTF_METHOD create_tjs_native_instance() {
				return new T();
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_INSTANCE_HPP
