/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_ERROR_WRAPPER_HPP
#define SPRIG_KRKR_TJS_ERROR_WRAPPER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/macro/text.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
				SPRIG_INLINE void FuncCall(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->FuncCall(flag, membername, hint, result, numparams, param, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::FuncCall()"));
					}
				}
				SPRIG_INLINE tjs_int* GetCount(
					iTJSDispatch2* that,
					tjs_int *result,
					tjs_char const* membername,
					tjs_uint32* hint,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->GetCount(result, membername, hint, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::GetCount()"));
					}
					return result;
				}
				SPRIG_INLINE bool IsValid(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					iTJSDispatch2* objthis
					)
				{
					return that->IsValid(flag, membername, hint, objthis) == TJS_S_TRUE;
				}
				SPRIG_INLINE tTJSVariant* PropGet(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					tTJSVariant* result,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->PropGet(flag, membername, hint, result, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::PropGet()"));
					}
					return result;
				}
				SPRIG_INLINE tTJSVariant* PropGetByNum(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_int num,
					tTJSVariant* result,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->PropGetByNum(flag, num, result, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::PropGetByNum()"));
					}
					return result;
				}
				SPRIG_INLINE void PropSet(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					tTJSVariant const* param,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->PropSet(flag, membername, hint, param, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::PropSet()"));
					}
				}
				SPRIG_INLINE void PropSetByNum(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_int num,
					tTJSVariant const* param,
					iTJSDispatch2* objthis
					)
				{
					if (TJS_FAILED(that->PropSetByNum(flag, num, param, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::PropSetByNum()"));
					}
				}
				SPRIG_INLINE void CreateNew(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					iTJSDispatch2** result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					if (result == 0 || TJS_FAILED(that->CreateNew(flag, membername, hint, result, numparams, param, objthis))) {
						::TVPThrowExceptionMessage(SPRIG_KRKR_TJS_W("error in iTJSDispatch2::CreateNew()"));
					}
				}
				SPRIG_INLINE bool IsInstanceOf(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_char const* membername,
					tjs_uint32* hint,
					tjs_char const* classname,
					iTJSDispatch2* objthis
					)
				{
					return that->IsInstanceOf(flag, membername, hint, classname, objthis) == TJS_S_TRUE;
				}
				SPRIG_INLINE bool IsInstanceOfByNum(
					iTJSDispatch2* that,
					tjs_uint32 flag,
					tjs_int num,
					tjs_char const* classname,
					iTJSDispatch2* objthis
					)
				{
					return that->IsInstanceOfByNum(flag, num, classname, objthis) == TJS_S_TRUE;
				}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_ERROR_WRAPPER_HPP
