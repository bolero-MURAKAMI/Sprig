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
#include <sprig/get_pointer.hpp>
#include <sprig/krkr/tjs/typedef.hpp>
#include <sprig/krkr/tjs/error_wrapper.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
				SPRIG_INLINE sprig::krkr::tjs::object_type CreateNewObject(
					sprig::krkr::tjs::object_type const& obj,
					tjs_int numparams,
					tTJSVariant** param,
					sprig::krkr::tjs::object_type const& objthis
					)
				{
					iTJSDispatch2* result = 0;
					CreateNew(sprig::get_pointer(obj), 0, 0, 0, &result, numparams, param, sprig::get_pointer(objthis));
					return sprig::krkr::tjs::object_type(result, false);
				}
				SPRIG_INLINE tTJSVariant* FuncObjectCall(
					sprig::krkr::tjs::object_type const& obj,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param,
					sprig::krkr::tjs::object_type const& objthis
					)
				{
					FuncCall(sprig::get_pointer(obj), 0, 0, 0, result, numparams, param, sprig::get_pointer(objthis));
					return result;
				}
				SPRIG_INLINE tTJSVariant FuncObjectCall(
					sprig::krkr::tjs::object_type const& obj,
					tjs_int numparams,
					tTJSVariant** param,
					sprig::krkr::tjs::object_type const& objthis
					)
				{
					tTJSVariant result;
					return *FuncObjectCall(obj, &result, numparams, param, objthis);
				}
				SPRIG_INLINE tTJSVariant* MethodCall(
					sprig::krkr::tjs::object_type const& obj,
					tjs_char const* membername,
					tTJSVariant* result,
					tjs_int numparams,
					tTJSVariant** param
					)
				{
					FuncCall(sprig::get_pointer(obj), 0, membername, 0, result, numparams, param, sprig::get_pointer(obj));
					return result;
				}
				SPRIG_INLINE tTJSVariant MethodCall(
					sprig::krkr::tjs::object_type const& obj,
					tjs_char const* membername,
					tjs_int numparams,
					tTJSVariant** param
					)
				{
					tTJSVariant result;
					return *MethodCall(obj, membername, &result, numparams, param);
				}
				SPRIG_INLINE tjs_int GetCount(sprig::krkr::tjs::object_type const& obj) {
					tjs_int result;
					return *GetCount(sprig::get_pointer(obj), &result, 0, 0, 0);
				}
				SPRIG_INLINE tTJSVariant GetMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* membername) {
					tTJSVariant result;
					return *PropGet(sprig::get_pointer(obj), 0, membername, 0, &result, sprig::get_pointer(obj));
				}
				SPRIG_INLINE tTJSVariant GetMember(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tjs_char const* membername) {
					tTJSVariant result;
					return *PropGet(sprig::get_pointer(obj), 0, membername, 0, &result, sprig::get_pointer(objthis));
				}
				SPRIG_INLINE bool IsInstanceObjectOf(sprig::krkr::tjs::object_type const& obj, tjs_char const* classname) {
					return IsInstanceOf(sprig::get_pointer(obj), 0, 0, 0, classname, sprig::get_pointer(obj));
				}
				SPRIG_INLINE bool IsInstanceObjectOf(sprig::krkr::tjs::object_type const& obj, tjs_int num, tjs_char const* classname) {
					return IsInstanceOfByNum(sprig::get_pointer(obj), 0, num, classname, sprig::get_pointer(obj));
				}
				SPRIG_INLINE void AddMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* name, tTJSVariant const& member) {
					PropSet(sprig::get_pointer(obj), TJS_MEMBERENSURE, name, 0, &member, sprig::get_pointer(obj));
				}
				SPRIG_INLINE void AddMember(sprig::krkr::tjs::object_type const& obj, tjs_int num, tTJSVariant const& member) {
					PropSetByNum(sprig::get_pointer(obj), TJS_MEMBERENSURE, num, &member, sprig::get_pointer(obj));
				}
				SPRIG_INLINE void AddNewMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* name, sprig::krkr::tjs::object_type const& member) {
					tTJSVariant var(sprig::get_pointer(member));
					member->Release();
					PropSet(sprig::get_pointer(obj), TJS_MEMBERENSURE, name, 0, &var, sprig::get_pointer(obj));
				}
				SPRIG_INLINE void AddNewMember(sprig::krkr::tjs::object_type const& obj, tjs_int num, sprig::krkr::tjs::object_type const& member) {
					tTJSVariant var(sprig::get_pointer(member));
					member->Release();
					PropSetByNum(sprig::get_pointer(obj), TJS_MEMBERENSURE, num, &var, sprig::get_pointer(obj));
				}
				SPRIG_INLINE tTJSVariant GetClassMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* name) {
					tTJSVariant var;
					return *PropGet(sprig::get_pointer(obj), TJS_IGNOREPROP, name, 0, &var, sprig::get_pointer(obj));
				}
				SPRIG_INLINE tTJSVariant GetClassMember(sprig::krkr::tjs::object_type const& obj, tjs_int num) {
					tTJSVariant var;
					return *PropGetByNum(sprig::get_pointer(obj), TJS_IGNOREPROP, num, &var, sprig::get_pointer(obj));
				}
				SPRIG_INLINE bool IsValidMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* name) {
					return IsValid(sprig::get_pointer(obj), TJS_IGNOREPROP, name, 0, sprig::get_pointer(obj));
				}
				SPRIG_INLINE void DeleteMember(sprig::krkr::tjs::object_type const& obj, tjs_char const* name) {
					obj->DeleteMember(0, name, 0, sprig::get_pointer(obj));
				}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_SUGAR_WRAPPER_HPP
