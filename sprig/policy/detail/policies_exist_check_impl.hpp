/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_DETAIL_POLICIES_EXIST_CHECK_IMPL_HPP
#define SPRIG_POLICY_DETAIL_POLICIES_EXIST_CHECK_IMPL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/preprocessor/cat.hpp>
#include <sprig/tmp/iter_index.hpp>
#include <sprig/policy/detail/policy_exist_check_impl.hpp>

//
// SPRIG_POLICYIES_EXIST_CHECK_IMPL
//
#define SPRIG_POLICYIES_EXIST_CHECK_IMPL(TAGS, TYPES, DELECTIVE) \
	struct BOOST_PP_CAT(policies_exist_checker_, __LINE__) { \
	private: \
		template<typename Tag, std::size_t Index, typename Tags, typename Types> \
		struct policy_exist_checker { \
		private: \
			SPRIG_POLICY_EXIST_CHECK_IMPL(Tag, TYPES, DELECTIVE); \
		}; \
		template<typename Tag, typename indexT, typename Tags, typename Types> \
		struct element_checker \
			: public boost::mpl::size_t<0> \
			, public policy_exist_checker<Tag, indexT::value, Tags, Types> \
		{}; \
	public: \
		static std::size_t const value = boost::mpl::iter_fold< \
			TAGS, \
			boost::mpl::size_t<0>, \
			element_checker< \
				boost::mpl::deref<boost::mpl::_2>, \
				sprig::tmp::iter_index<TAGS, boost::mpl::_2>, \
				TAGS, \
				TYPES \
			> \
		>::type::value; \
	}; \
	static std::size_t const BOOST_PP_CAT(policies_exist_check_, __LINE__) \
		= (BOOST_PP_CAT(policies_exist_checker_, __LINE__)::value)

#endif	// #ifndef SPRIG_POLICY_DETAIL_POLICIES_EXIST_CHECK_IMPL_HPP
