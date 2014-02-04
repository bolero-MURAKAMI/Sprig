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
					iTJSDispatch2* that,
					iTJSDispatch2** result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					CreateNew(that, 0, 0, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE void FuncObjectCall(
					iTJSDispatch2* that,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					FuncCall(that, 0, 0, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE void MethodCall(
					iTJSDispatch2* that,
					tjs_char const* membername,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param
					)
				{
					FuncCall(that, 0, membername, 0, result, numparams, param, that);
				}
				SPRIG_INLINE tjs_int GetCount(iTJSDispatch2* that) {
					tjs_int result;
					return *GetCount(that, &result, 0, 0, 0);
				}
				SPRIG_INLINE void MethodCall(
					iTJSDispatch2* that,
					tjs_char const* membername,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					iTJSDispatch2* objthis
					)
				{
					FuncCall(that, 0, membername, 0, result, numparams, param, objthis);
				}
				SPRIG_INLINE tTJSVariant* MemberGet(
					iTJSDispatch2* that,
					tjs_char const* membername,
					tTJSVariant* result
					)
				{
					return PropGet(that, 0, membername, 0, result, that);
				}
				SPRIG_INLINE tTJSVariant* MemberGet(
					iTJSDispatch2* that,
					tjs_char const* membername,
					tTJSVariant* result,
					iTJSDispatch2* objthis
					)
				{
					return PropGet(that, 0, membername, 0, result, objthis);
				}
				SPRIG_INLINE bool IsInstanceObjectOf(iTJSDispatch2* that, tjs_char const* classname) {
					return IsInstanceOf(that, 0, 0, 0, classname, that);
				}
				SPRIG_INLINE bool IsInstanceObjectOfByNum(iTJSDispatch2* that, tjs_int num, tjs_char const* classname) {
					return IsInstanceOfByNum(that, 0, num, classname, that);
				}
				SPRIG_INLINE void AddMember(iTJSDispatch2* that, tjs_char const* name, tTJSVariant* member) {
					PropSet(that, TJS_MEMBERENSURE, name, 0, member, that);
				}
				SPRIG_INLINE void AddMemberByNum(iTJSDispatch2* that, tjs_int num, tTJSVariant* member) {
					PropSetByNum(that, TJS_MEMBERENSURE, num, member, that);
				}
				SPRIG_INLINE void AddMember(iTJSDispatch2* that, tjs_char const* name, iTJSDispatch2* member) {
					tTJSVariant var(member);
					member->Release();
					PropSet(that, TJS_MEMBERENSURE, name, 0, &var, that);
				}
				SPRIG_INLINE void AddMemberByNum(iTJSDispatch2* that, tjs_int num, iTJSDispatch2* member) {
					tTJSVariant var(member);
					member->Release();
					PropSetByNum(that, TJS_MEMBERENSURE, num, &var, that);
				}
				SPRIG_INLINE void AddMemberNoRelease(iTJSDispatch2* that, tjs_char const* name, iTJSDispatch2* member) {
					tTJSVariant var(member);
					PropSet(that, TJS_MEMBERENSURE, name, 0, &var, that);
				}
				SPRIG_INLINE void AddMemberByNumNoRelease(iTJSDispatch2* that, tjs_int num, iTJSDispatch2* member) {
					tTJSVariant var(member);
					PropSetByNum(that, TJS_MEMBERENSURE, num, &var, that);
				}
				SPRIG_INLINE iTJSDispatch2* GetMember(iTJSDispatch2* that, tjs_char const* name) {
					tTJSVariant var;
					return PropGet(that, TJS_IGNOREPROP, name, 0, &var, that)->AsObject();
				}
				SPRIG_INLINE iTJSDispatch2* GetMemberNoAddRef(iTJSDispatch2* that, tjs_char const* name) {
					tTJSVariant var;
					return PropGet(that, TJS_IGNOREPROP, name, 0, &var, that)->AsObjectNoAddRef();
				}
				SPRIG_INLINE iTJSDispatch2* GetMemberByNum(iTJSDispatch2* that, tjs_int num) {
					tTJSVariant var;
					return PropGetByNum(that, TJS_IGNOREPROP, num, &var, that)->AsObject();
				}
				SPRIG_INLINE iTJSDispatch2* GetMemberByNumNoAddRef(iTJSDispatch2* that, tjs_int num) {
					tTJSVariant var;
					return PropGetByNum(that, TJS_IGNOREPROP, num, &var, that)->AsObjectNoAddRef();
				}
				SPRIG_INLINE bool IsValidMember(iTJSDispatch2* that, tjs_char const* name) {
					return IsValid(that, TJS_IGNOREPROP, name, 0, that);
				}
				SPRIG_INLINE void DeleteMember(iTJSDispatch2* that, tjs_char const* name) {
					that->DeleteMember(0, name, 0, that);
				}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_SUGAR_WRAPPER_HPP
