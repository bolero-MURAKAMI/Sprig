/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CIN_ACQUIRE_HPP
#define SPRIG_CIN_ACQUIRE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iostream>
#include <boost/ref.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/acquire.hpp>
#include <sprig/list_acquire.hpp>

//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_DECL(NAME, USING_FUNC) \
	template<typename T> \
	SPRIG_INLINE bool NAME(T& arg) { \
		return USING_FUNC(arg, std::cin); \
	} \
	template<typename T> \
	SPRIG_INLINE bool NAME(T& arg, sprig::string_argument const& sa) { \
		std::cout << sa; \
		return USING_FUNC(arg, std::cin); \
	}
//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_EX_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_EX_DECL(NAME, USING_FUNC) \
	template<typename Action, typename T> \
	SPRIG_INLINE bool NAME(T& arg) { \
		return USING_FUNC<Action>(arg, std::cin); \
	} \
	template<typename Action, typename T> \
	SPRIG_INLINE bool NAME(T& arg, sprig::string_argument const& sa) { \
		std::cout << sa; \
		return USING_FUNC<Action>(arg, std::cin); \
	}
//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_DECL(NAME, USING_FUNC) \
	template<typename T> \
	SPRIG_INLINE void NAME(T& arg) { \
		while (!USING_FUNC(arg)) \
			; \
	} \
	template<typename T> \
	SPRIG_INLINE void NAME(T& arg, sprig::string_argument const& sa) { \
		while (!USING_FUNC(arg, sa)) \
			; \
	}
//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_EX_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_EX_DECL(NAME, USING_FUNC) \
	template<typename Action, typename T> \
	SPRIG_INLINE void NAME(T& arg) { \
		while (!USING_FUNC<Action>(arg)) \
			; \
	} \
	template<typename Action, typename T> \
	SPRIG_INLINE void NAME(T& arg, sprig::string_argument const& sa) { \
		while (!USING_FUNC<Action>(arg, sa)) \
			; \
	}
//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_DECL(NAME, USING_FUNC) \
	template<typename T, typename Predicate> \
	SPRIG_INLINE void NAME(T& arg, Predicate pred) { \
		T value; \
		do { \
			USING_FUNC(value); \
		} while (!pred(value)); \
		arg = value; \
	} \
	template<typename T, typename Predicate> \
	SPRIG_INLINE void NAME(T& arg, Predicate pred, sprig::string_argument const& sa) { \
		T value; \
		do { \
			USING_FUNC(value, sa); \
		} while (!pred(value)); \
		arg = value; \
	}
//
// SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_EX_DECL
//
#define SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_EX_DECL(NAME, USING_FUNC) \
	template<typename Action, typename T, typename Predicate> \
	SPRIG_INLINE void NAME(T& arg, Predicate pred) { \
		T value; \
		do { \
			USING_FUNC<Action>(value); \
		} while (!pred(value)); \
		arg = value; \
	} \
	template<typename Action, typename T, typename Predicate> \
	SPRIG_INLINE void NAME(T& arg, Predicate pred, sprig::string_argument const& sa) { \
		T value; \
		do { \
			USING_FUNC<Action>(value, sa); \
		} while (!pred(value)); \
		arg = value; \
	}
//
// SPRIG_CIN_ACQUIRE_DECL
//
#define SPRIG_CIN_ACQUIRE_DECL(NAME, REPEAT_NAME, UNTIL_NAME, USING_FUNC) \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_DECL(NAME, USING_FUNC); \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_DECL(REPEAT_NAME, NAME); \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_DECL(UNTIL_NAME, REPEAT_NAME);
//
// SPRIG_CIN_ACQUIRE_EX_DECL
//
#define SPRIG_CIN_ACQUIRE_EX_DECL(NAME, REPEAT_NAME, UNTIL_NAME, USING_FUNC) \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_EX_DECL(NAME, USING_FUNC); \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_REPEAT_EX_DECL(REPEAT_NAME, NAME); \
	SPRIG_CIN_ACQUIRE_CIN_ACQUIRE_UNTIL_EX_DECL(UNTIL_NAME, REPEAT_NAME);

namespace sprig {
	//
	// cin_acquire_any
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_acquire_any, cin_acquire_any_repeat, cin_acquire_any_repeat_until, acquire_any);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_acquire_any_ex, cin_acquire_any_repeat_ex, cin_acquire_any_repeat_until_ex, acquire_any_ex);
	//
	// cin_acquire_int
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_acquire_int, cin_acquire_int_repeat, cin_acquire_int_repeat_until, acquire_int);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_acquire_int_ex, cin_acquire_int_repeat_ex, cin_acquire_int_repeat_until_ex, acquire_int_ex);
	//
	// cin_acquire_uint
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_acquire_uint, cin_acquire_uint_repeat, cin_acquire_uint_repeat_until, acquire_uint);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_acquire_uint_ex, cin_acquire_uint_repeat_ex, cin_acquire_uint_repeat_until_ex, acquire_uint_ex);
	//
	// cin_acquire_real
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_acquire_real, cin_acquire_real_repeat, cin_acquire_real_repeat_until, acquire_real);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_acquire_real_ex, cin_acquire_real_repeat_ex, cin_acquire_real_repeat_until_ex, acquire_real_ex);
	//
	// cin_list_acquire_int
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_list_acquire_int, cin_list_acquire_int_repeat, cin_list_acquire_int_repeat_until, list_acquire_int);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_list_acquire_int_ex, cin_list_acquire_int_repeat_ex, cin_list_acquire_int_repeat_until_ex, list_acquire_int_ex);
	//
	// cin_list_acquire_uint
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_list_acquire_uint, cin_list_acquire_uint_repeat, cin_list_acquire_uint_repeat_until, list_acquire_uint);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_list_acquire_uint_ex, cin_list_acquire_uint_repeat_ex, cin_list_acquire_uint_repeat_until_ex, list_acquire_uint_ex);
	//
	// cin_list_acquire_real
	//
	SPRIG_CIN_ACQUIRE_DECL(cin_list_acquire_real, cin_list_acquire_real_repeat, cin_list_acquire_real_repeat_until, list_acquire_real);
	SPRIG_CIN_ACQUIRE_EX_DECL(cin_list_acquire_real_ex, cin_list_acquire_real_repeat_ex, cin_list_acquire_real_repeat_until_ex, list_acquire_real_ex);
}	// namespace sprig

#endif	// #ifndef SPRIG_CIN_ACQUIRE_HPP
