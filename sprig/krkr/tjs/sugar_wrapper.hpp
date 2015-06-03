/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_SUGAR_WRAPPER_HPP
#define SPRIG_KRKR_TJS_SUGAR_WRAPPER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/tjs/error_wrapper.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
				SPRIG_INLINE void CreateNewObject(
					iTJSDispatch2* obj,
					iTJSDispatch2** result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					CreateNew(obj, 0, 0, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE iTJSDispatch2* CreateNewObject(
					iTJSDispatch2* obj,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					iTJSDispatch2* result = 0;
					CreateNewObject(obj, &result, numparams, param, objthis);
					return result;
				}
				SPRIG_INLINE void FuncObjectCall(
					iTJSDispatch2* obj,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					FuncCall(obj, 0, 0, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE void MethodCall(
					iTJSDispatch2* obj,
					tjs_char const* membername,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param
					)
				{
					FuncCall(obj, 0, membername, 0, result, numparams, param, obj);
				}
				SPRIG_INLINE void MethodCall(
					iTJSDispatch2* obj,
					tjs_char const* membername,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					FuncCall(obj, 0, membername, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE tjs_int GetCount(iTJSDispatch2* obj) {
					tjs_int result;
					return *GetCount(obj, &result, 0, 0, 0);
				}
				SPRIG_INLINE tTJSVariant GetMember(iTJSDispatch2* obj, tjs_char const* membername) {
					tTJSVariant result;
					return *PropGet(obj, 0, membername, 0, &result, obj);
				}
				SPRIG_INLINE tTJSVariant GetMember(iTJSDispatch2* obj, iTJSDispatch2* objthis, tjs_char const* membername) {
					tTJSVariant result;
					return *PropGet(obj, 0, membername, 0, &result, objthis);
				}
				SPRIG_INLINE bool IsInstanceObjectOf(iTJSDispatch2* obj, tjs_char const* classname) {
					return IsInstanceOf(obj, 0, 0, 0, classname, obj);
				}
				SPRIG_INLINE bool IsInstanceObjectOf(iTJSDispatch2* obj, tjs_int num, tjs_char const* classname) {
					return IsInstanceOfByNum(obj, 0, num, classname, obj);
				}
				SPRIG_INLINE void AddMember(iTJSDispatch2* obj, tjs_char const* name, tTJSVariant const& member) {
					PropSet(obj, TJS_MEMBERENSURE, name, 0, &member, obj);
				}
				SPRIG_INLINE void AddMember(iTJSDispatch2* obj, tjs_int num, tTJSVariant const& member) {
					PropSetByNum(obj, TJS_MEMBERENSURE, num, &member, obj);
				}
				SPRIG_INLINE void AddNewMember(iTJSDispatch2* obj, tjs_char const* name, iTJSDispatch2* member) {
					tTJSVariant var(member);
					member->Release();
					PropSet(obj, TJS_MEMBERENSURE, name, 0, &var, obj);
				}
				SPRIG_INLINE void AddNewMember(iTJSDispatch2* obj, tjs_int num, iTJSDispatch2* member) {
					tTJSVariant var(member);
					member->Release();
					PropSetByNum(obj, TJS_MEMBERENSURE, num, &var, obj);
				}
				SPRIG_INLINE tTJSVariant GetClassMember(iTJSDispatch2* obj, tjs_char const* name) {
					tTJSVariant var;
					return *PropGet(obj, TJS_IGNOREPROP, name, 0, &var, obj);
				}
				SPRIG_INLINE tTJSVariant GetClassMember(iTJSDispatch2* obj, tjs_int num) {
					tTJSVariant var;
					return *PropGetByNum(obj, TJS_IGNOREPROP, num, &var, obj);
				}
				SPRIG_INLINE bool IsValidMember(iTJSDispatch2* obj, tjs_char const* name) {
					return IsValid(obj, TJS_IGNOREPROP, name, 0, obj);
				}
				SPRIG_INLINE void DeleteMember(iTJSDispatch2* obj, tjs_char const* name) {
					obj->DeleteMember(0, name, 0, obj);
				}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_SUGAR_WRAPPER_HPP
