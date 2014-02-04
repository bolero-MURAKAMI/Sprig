/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_HAS_MEMBER_XXX_HPP
#define SPRIG_TYPE_TRAITS_HAS_MEMBER_XXX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/config/suffix.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>

//
// SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF_IMPL
//
#define SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF_IMPL(TRAIT, NAME, DEFAULT) \
	template<typename T, typename Member, Member member> \
	struct BOOST_PP_CAT(TRAIT, _msvc_sfinae_helper) { \
		typedef void type; \
	}; \
	template<typename T, typename Member, typename U = void> \
	struct BOOST_PP_CAT(TRAIT, _impl) { \
		BOOST_STATIC_CONSTANT(bool, value = false); \
		typedef boost::mpl::bool_<value> type; \
	}; \
	template<typename T, typename Member> \
	struct BOOST_PP_CAT(TRAIT, _impl)< \
		T, \
		Member, \
		typename BOOST_PP_CAT(TRAIT, _msvc_sfinae_helper)<T, Member, &T::NAME>::type \
	> { \
		BOOST_STATIC_CONSTANT(bool, value = true); \
		typedef boost::mpl::bool_<value> type; \
	}; \
	template<typename T, typename Member, typename Fallback = boost::mpl::bool_<DEFAULT> > \
	struct TRAIT \
		: public BOOST_PP_CAT(TRAIT, _impl)<T, Member> \
	{};

//
// SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF
//
#define SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF(TRAIT, NAME) \
	SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF_IMPL(TRAIT, NAME, false)

//
// SPRIG_HAS_MEMBER_XXX_TRAIT_DEF
//
#define SPRIG_HAS_MEMBER_XXX_TRAIT_DEF(NAME) \
	SPRIG_HAS_MEMBER_XXX_TRAIT_NAMED_DEF(BOOST_PP_CAT(has_member_, NAME), NAME)

#endif	// #ifndef SPRIG_TYPE_TRAITS_HAS_MEMBER_XXX_HPP
