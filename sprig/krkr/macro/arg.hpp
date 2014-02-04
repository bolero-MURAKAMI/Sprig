/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_ARG_HPP
#define SPRIG_KRKR_MACRO_ARG_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <sprig/external/tp_stub.hpp>

//
// SPRIG_KRKR_ARG[_DEFAULT]
//
#define SPRIG_KRKR_ARG(INDEX) \
	(param[INDEX])
#define SPRIG_KRKR_ARG_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG(INDEX) \
			: DEFAULT_ARG \
		)

//
// SPRIG_KRKR_ARG_TYPE
//
#define SPRIG_KRKR_ARG_TYPE(INDEX) \
	(SPRIG_KRKR_ARG(INDEX)->Type())

//
// SPRIG_KRKR_ENABLE_ARG
//
#define SPRIG_KRKR_ENABLE_ARG(INDEX) \
	( \
		numparams >= BOOST_PP_INC(INDEX) \
		&& SPRIG_KRKR_ARG_TYPE(INDEX) != tvtVoid \
		)

//
// SPRIG_KRKR_ARG_[VARIANT|OBJECT|CLOSURE|STRING|OCTET|BOOL|INTERMEDIATE][_DEFAULT]
//
#define SPRIG_KRKR_ARG_VARIANT(INDEX) \
	(*param[INDEX])
#define SPRIG_KRKR_ARG_VARIANT_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_VARIANT(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_OBJECT(INDEX) \
	(param[INDEX]->AsObjectNoAddRef())
#define SPRIG_KRKR_ARG_OBJECT_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_OBJECT(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_CLOSURE(INDEX) \
	(param[INDEX]->AsObjectClosureNoAddRef())
#define SPRIG_KRKR_ARG_CLOSURE_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_CLOSURE(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_STRING(INDEX) \
	(param[INDEX]->AsStringNoAddRef())
#define SPRIG_KRKR_ARG_STRING_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_STRING(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_OCTET(INDEX) \
	(param[INDEX]->AsOctetNoAddRef())
#define SPRIG_KRKR_ARG_OCTET_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_OCTET(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_BOOL(INDEX) \
	( \
		param[INDEX]->operator bool() \
		)
#define SPRIG_KRKR_ARG_BOOL_DEFAULT(INDEX, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_BOOL(INDEX) \
			: DEFAULT_ARG \
		)
#define SPRIG_KRKR_ARG_INTERMEDIATE(INDEX, VARIANT_TYPE, INTERMEDIATE_TYPE) \
	( \
		static_cast<INTERMEDIATE_TYPE>(static_cast<VARIANT_TYPE>(*param[INDEX])) \
		)
#define SPRIG_KRKR_ARG_INTERMEDIATE_DEFAULT(INDEX, VARIANT_TYPE, INTERMEDIATE_TYPE, DEFAULT_ARG) \
	( \
		SPRIG_KRKR_ENABLE_ARG(INDEX) \
			? SPRIG_KRKR_ARG_INTERMEDIATE(INDEX, VARIANT_TYPE, INTERMEDIATE_TYPE) \
			: DEFAULT_ARG \
		)

#endif	// #ifndef SPRIG_KRKR_MACRO_ARG_HPP
