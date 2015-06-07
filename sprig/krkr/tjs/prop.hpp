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
#include <sprig/krkr/tjs/typedef.hpp>
#include <sprig/krkr/tjs/error_wrapper.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// COMMENT: �I�u�W�F�N�g����v���p�e�B�̒l���擾����B
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* obj, tjs_char const* membername) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(obj, 0, membername, 0, &var, obj));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(sprig::krkr::tjs::object_type const& obj, tjs_char const* membername) {
				return GetPropValue<T>(sprig::get_pointer(obj), membername);
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* obj, iTJSDispatch2* objthis, tjs_char const* membername) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(obj, 0, membername, 0, &var, objthis));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tjs_char const* membername) {
				return GetPropValue<T>(sprig::get_pointer(obj), sprig::get_pointer(objthis), membername);
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(tTJSVariantClosure const& closure, tjs_char const* membername) {
				return GetPropValue<T>(closure.Object, closure.ObjThis, membername);
			}
			//
			// COMMENT: �v���p�e�B�I�u�W�F�N�g��ΏۂƂ��āA�I�u�W�F�N�g����v���p�e�B�̒l���擾����B
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* obj, iTJSDispatch2* objthis) {
				tTJSVariant var;
				return static_cast<T>(*PropGet(obj, 0, 0, 0, &var, objthis));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis) {
				return GetPropValue<T>(sprig::get_pointer(obj), sprig::get_pointer(objthis));
			}
			//
			// COMMENT: �����ɂ���āA�I�u�W�F�N�g����v���p�e�B�̒l���擾����B
			//
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* obj, tjs_int num) {
				tTJSVariant var;
				return static_cast<T>(*PropGetByNum(obj, 0, num, &var, obj));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(sprig::krkr::tjs::object_type const& obj, tjs_int num) {
				return GetPropValue<T>(sprig::get_pointer(obj), num);
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(iTJSDispatch2* obj, iTJSDispatch2* objthis, tjs_int num) {
				tTJSVariant var;
				return static_cast<T>(*PropGetByNum(obj, 0, num, &var, objthis));
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tjs_int num) {
				return GetPropValue<T>(sprig::get_pointer(obj), sprig::get_pointer(objthis), num);
			}
			template<typename T>
			SPRIG_INLINE T GetPropValue(tTJSVariantClosure const& closure, tjs_int num) {
				return GetPropValue<T>(closure.Object, closure.ObjThis, num);
			}

			//
			// COMMENT: �I�u�W�F�N�g�փv���p�e�B�̒l��ݒ肷��B
			//
			SPRIG_INLINE void SetPropValue(sprig::krkr::tjs::object_type const& obj, tjs_char const* membername, tTJSVariant const& var) {
				PropSet(sprig::get_pointer(obj), 0, membername, 0, &var, sprig::get_pointer(obj));
			}
			SPRIG_INLINE void SetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tjs_char const* membername, tTJSVariant const& var) {
				PropSet(sprig::get_pointer(obj), 0, membername, 0, &var, sprig::get_pointer(objthis));
			}
			SPRIG_INLINE void SetPropValue(tTJSVariantClosure const& closure, tjs_char const* membername, tTJSVariant const& var) {
				SetPropValue(closure.Object, closure.ObjThis, membername, var);
			}
			//
			// COMMENT: �v���p�e�B�I�u�W�F�N�g��ΏۂƂ��āA�I�u�W�F�N�g�փv���p�e�B�̒l��ݒ肷��B
			//
			SPRIG_INLINE void SetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tTJSVariant const& var) {
				PropSet(sprig::get_pointer(obj), 0, 0, 0, &var, sprig::get_pointer(objthis));
			}
			//
			// COMMENT: �����ɂ���āA�I�u�W�F�N�g�փv���p�e�B�̒l��ݒ肷��B
			//
			SPRIG_INLINE void SetPropValue(sprig::krkr::tjs::object_type const& obj, tjs_int num, tTJSVariant const& var) {
				PropSetByNum(sprig::get_pointer(obj), 0, num, &var, sprig::get_pointer(obj));
			}
			SPRIG_INLINE void SetPropValue(sprig::krkr::tjs::object_type const& obj, sprig::krkr::tjs::object_type const& objthis, tjs_int num, tTJSVariant const& var) {
				PropSetByNum(sprig::get_pointer(obj), 0, num, &var, sprig::get_pointer(objthis));
			}
			SPRIG_INLINE void SetPropValue(tTJSVariantClosure const& closure, tjs_int num, tTJSVariant const& var) {
				SetPropValue(closure.Object, closure.ObjThis, num, var);
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_PROP_HPP
