/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_CHECK_HPP
#define SPRIG_KRKR_MACRO_CHECK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>
#include <sprig/krkr/tjs/sugar_wrapper.hpp>

//
// SPRIG_KRKR_NUMPARAMS_EASY_CHECK
//
#define SPRIG_KRKR_NUMPARAMS_EASY_CHECK(NUM) \
	if (numparams < NUM) { \
		return TJS_E_BADPARAMCOUNT; \
	}
//
// SPRIG_KRKR_NUMPARAMS_CHECK
//
#define SPRIG_KRKR_NUMPARAMS_CHECK(NUM) \
	{ \
		SPRIG_KRKR_NUMPARAMS_EASY_CHECK(NUM); \
		for (tjs_int i = 0; i < NUM; ++i) { \
			if (param[i]->Type() == tvtVoid) \
				return TJS_E_BADPARAMCOUNT; \
		} \
	}
//
// SPRIG_KRKR_TYPE_CHECK
//
#define SPRIG_KRKR_TYPE_CHECK(INDEX, TYPE) \
	if (param[INDEX]->Type() != (TYPE)) { \
		return TJS_E_INVALIDPARAM; \
	}
//
// SPRIG_KRKR_TYPE_OR_VOID_CHECK
//
#define SPRIG_KRKR_TYPE_OR_VOID_CHECK(INDEX, TYPE) \
	if (param[INDEX]->Type() != (TYPE) \
		&& param[INDEX]->Type() != tvtVoid \
		) \
	{ \
		return TJS_E_INVALIDPARAM; \
	}
//
// SPRIG_KRKR_INSTANCEOF_CHECK
//
#define SPRIG_KRKR_INSTANCEOF_CHECK(INDEX, ENTRY_NAME) \
	if (param[INDEX]->Type() != tvtObject \
		|| !sprig::krkr::tjs::IsInstanceObjectOf( \
			param[INDEX]->AsObjectNoAddRef(), \
			SPRIG_KRKR_TJS_STRINGIZE(ENTRY_NAME) \
			) \
		) \
	{ \
		return TJS_E_INVALIDPARAM; \
	}
//
// SPRIG_KRKR_INSTANCEOF_OR_NULL_CHECK
//
#define SPRIG_KRKR_INSTANCEOF_OR_NULL_CHECK(INDEX, ENTRY_NAME) \
	if (param[INDEX]->Type() != tvtObject \
		|| param[INDEX]->AsObjectNoAddRef() \
		&& !sprig::krkr::tjs::IsInstanceObjectOf( \
			param[INDEX]->AsObjectNoAddRef(), \
			SPRIG_KRKR_TJS_STRINGIZE(ENTRY_NAME) \
			) \
		) \
	{ \
		return TJS_E_INVALIDPARAM; \
	}
//
// SPRIG_KRKR_PROP_INSTANCEOF_CHECK
//
#define SPRIG_KRKR_PROP_INSTANCEOF_CHECK(ENTRY_NAME) \
	if (param->Type() != tvtObject \
		|| !sprig::krkr::tjs::IsInstanceObjectOf( \
			param->AsObjectNoAddRef(), \
			SPRIG_KRKR_TJS_STRINGIZE(ENTRY_NAME) \
			) \
		) \
	{ \
		return TJS_E_INVALIDPARAM; \
	}
//
// SPRIG_KRKR_PROP_INSTANCEOF_OR_NULL_CHECK
//
#define SPRIG_KRKR_PROP_INSTANCEOF_OR_NULL_CHECK(ENTRY_NAME) \
	if (param->Type() != tvtObject \
		|| param->AsObjectNoAddRef() \
		&& !sprig::krkr::tjs::IsInstanceObjectOf( \
			param->AsObjectNoAddRef(), \
			SPRIG_KRKR_TJS_STRINGIZE(ENTRY_NAME) \
			) \
		) \
	{ \
		return TJS_E_INVALIDPARAM; \
	}

#endif	// #ifndef SPRIG_KRKR_MACRO_CHECK_HPP
