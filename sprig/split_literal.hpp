/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SPLIT_LITERAL_HPP
#define SPRIG_SPLIT_LITERAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>

namespace sprig {
	//
	// literal_string_tag
	// literal_char_tag
	//
	struct literal_string_tag {};
	struct literal_char_tag {};
}	// namespace sprig

//
// SPRIG_SPLIT_LITERAL_STRING_DECL
//
#define SPRIG_SPLIT_LITERAL_STRING_DECL(NAME, LIT) \
	struct NAME : public sprig::literal_string_tag { \
	public: \
		/* get */ \
		template<typename Char> \
		static Char const* get( \
			typename boost::enable_if< \
				sprig::is_char_type<Char> \
			>::type* = 0 \
			) \
		{ \
			return LIT; \
		} \
		template<typename Char> \
		static Char const* get( \
			typename boost::enable_if< \
				sprig::is_wchar_type<Char> \
			>::type* = 0 \
			) \
		{ \
			return BOOST_PP_CAT(L, LIT); \
		} \
	}

//
// SPRIG_SPLIT_LITERAL_CHAR_DECL
//
#define SPRIG_SPLIT_LITERAL_CHAR_DECL(NAME, LIT) \
	struct NAME : public sprig::literal_char_tag { \
	public: \
		/* apply */ \
		template<typename Char, typename Enable = void> \
		struct apply {}; \
		template<typename Char> \
		struct apply< \
			Char, \
			typename boost::enable_if< \
				sprig::is_char_type<Char> \
			>::type \
		> : public boost::mpl::char_<LIT> \
		{}; \
		template<typename Char> \
		struct apply< \
			Char, \
			typename boost::enable_if< \
				sprig::is_wchar_type<Char> \
			>::type \
		> : public boost::mpl::integral_c<wchar_t, BOOST_PP_CAT(L, LIT)> \
		{}; \
	public: \
		/* get */ \
		template<typename Char> \
		static Char get( \
			typename boost::enable_if< \
				sprig::is_char_type<Char> \
			>::type* = 0 \
			) \
		{ \
			return LIT; \
		} \
		template<typename Char> \
		static Char get( \
			typename boost::enable_if< \
				sprig::is_wchar_type<Char> \
			>::type* = 0 \
			) \
		{ \
			return BOOST_PP_CAT(L, LIT); \
		} \
	}

namespace sprig {
	//
	// get_literal
	//
	template<typename Literal, typename Char>
	SPRIG_INLINE Char const* get_literal(
		typename boost::enable_if<
			boost::is_base_and_derived<literal_string_tag, Literal>
		>::type* = 0
		)
	{
		return Literal::template get<Char>();
	}
	template<typename Literal, typename Char>
	SPRIG_INLINE Char get_literal(
		typename boost::enable_if<
			boost::is_base_and_derived<literal_char_tag, Literal>
		>::type* = 0
		)
	{
		return Literal::template get<Char>();
	}
	//
	// apply_literal
	//
	template<typename Literal, typename Char>
	struct apply_literal
		: public Literal::template apply<Char>
	{
	private:
		BOOST_MPL_ASSERT((boost::is_base_and_derived<literal_char_tag, Literal>));
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_SPLIT_LITERAL_HPP
