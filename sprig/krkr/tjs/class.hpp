#ifndef SPRIG_KRKR_TJS_CLASS_HPP
#define SPRIG_KRKR_TJS_CLASS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/tmp/eval_assert.hpp>
#include <sprig/krkr/tjs/intrusive_ptr.hpp>
#include <sprig/krkr/macro/text.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			namespace {
				//
				// COMMENT: 吉里吉里の（グローバル空間の）クラスオブジェクトを取得する。
				//
				SPRIG_INLINE iTJSDispatch2* GetTJSClass(tjs_char const* name) {
					iTJSDispatch2* result;
					tTJSVariant var;
					::TVPExecuteExpression(name, &var);
					if (!(result = var.AsObject()))
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in sprig::krkr::tjs::GetTJSClass()"));
					return result;
				}
				SPRIG_INLINE iTJSDispatch2* GetTJSClassNoAddRef(tjs_char const* name) {
					iTJSDispatch2* result;
					tTJSVariant var;
					::TVPExecuteExpression(name, &var);
					if (!(result = var.AsObjectNoAddRef()))
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in sprig::krkr::tjs::GetTJSClassNoAddRef()"));
					return result;
				}
			}	// anonymous-namespace
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_CLASS_HPP
