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
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* that, tjs_char const* membername, iTJSDispatch2* obj) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(that, 0, membername, 0, &var, obj));
			}
			//
			// COMMENT: プロパティオブジェクトをthatとして、オブジェクトからプロパティの値を取得する。
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* that, iTJSDispatch2* obj) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(that, 0, 0, 0, &var, obj));
			}
			//
			// COMMENT: 序数によって、オブジェクトからプロパティの値を取得する。
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(tjs_int num, iTJSDispatch2* obj) {
				tTJSVariant var;
				return static_cast<T>(*PropGetByNum(obj, 0, num, &var, obj));
			}

			//
			// COMMENT: オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, iTJSDispatch2* that, tjs_char const* membername, iTJSDispatch2* obj) {
				PropSet(that, 0, membername, 0, &var, obj);
			}
			//
			// COMMENT: プロパティオブジェクトをthatとして、オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, iTJSDispatch2* that, iTJSDispatch2* obj) {
				PropSet(that, 0, 0, 0, &var, obj);
			}
			//
			// COMMENT: 序数によって、オブジェクトへプロパティの値を設定する。
			//
			SPRIG_INLINE void SetPropValue(tTJSVariant const& var, tjs_int num, iTJSDispatch2* obj) {
				PropSetByNum(obj, 0, num, &var, obj);
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_PROP_HPP
