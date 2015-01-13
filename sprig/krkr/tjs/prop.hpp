/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_PROP_HPP
#define SPRIG_KRKR_TJS_PROP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/tjs/error_wrapper.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// COMMENT: オブジェクトからプロパティの値を取得する。
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* that, tjs_char const* membername) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(that, 0, membername, 0, &var, that));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* that, tjs_char const* membername, iTJSDispatch2* objthis) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(that, 0, membername, 0, &var, objthis));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(tTJSVariantClosure const& closure, tjs_char const* membername) {
				return GetPropValue<T>(closure.Object, membername, closure.ObjThis);
			}
			//
			// COMMENT: プロパティオブジェクトをthatとして、オブジェクトからプロパティの値を取得する。
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* that, iTJSDispatch2* objthis) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(that, 0, 0, 0, &var, objthis));
			}
			//
			// COMMENT: 序数によって、オブジェクトからプロパティの値を取得する。
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(tjs_int num, iTJSDispatch2* obj) {
				tTJSVariant var;
				return static_cast<T>(*PropGetByNum(obj, 0, num, &var, obj));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(tjs_int num, iTJSDispatch2* obj, iTJSDispatch2* objthis) {
				tTJSVariant var;
				return static_cast<T>(*PropGetByNum(obj, 0, num, &var, objthis));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(tjs_int num, tTJSVariantClosure const& closure) {
				return GetPropValue<T>(num, closure.Object, closure.ObjThis);
			}

			//
			// COMMENT: オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, iTJSDispatch2* that, tjs_char const* membername) {
				PropSet(that, 0, membername, 0, &var, that);
			}
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, iTJSDispatch2* that, tjs_char const* membername, iTJSDispatch2* objthis) {
				PropSet(that, 0, membername, 0, &var, objthis);
			}
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, tTJSVariantClosure const& closure, tjs_char const* membername) {
				SetPropValue(var, closure.Object, membername, closure.ObjThis);
			}
			//
			// COMMENT: プロパティオブジェクトをthatとして、オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, iTJSDispatch2* that, iTJSDispatch2* objthis) {
				PropSet(that, 0, 0, 0, &var, objthis);
			}
			//
			// COMMENT: 序数によって、オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, tjs_int num, iTJSDispatch2* obj) {
				PropSetByNum(obj, 0, num, &var, obj);
			}
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, tjs_int num, iTJSDispatch2* obj, iTJSDispatch2* objthis) {
				PropSetByNum(obj, 0, num, &var, objthis);
			}
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, tjs_int num, tTJSVariantClosure const& closure) {
				SetPropValue(var, num, closure.Object, closure.ObjThis);
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_PROP_HPP
