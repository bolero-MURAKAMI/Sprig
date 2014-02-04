/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_CHECKS_POLICY_EXIST_CHECK_HPP
#define SPRIG_POLICY_POLICY_CHECKS_POLICY_EXIST_CHECK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/policy/detail/policy_check_collect.hpp>

namespace sprig {
	//
	// policy_exist_check_result
	//
	template<
		typename Tag,
		typename Types,
		typename Indexes,
		typename Founds,
		std::size_t Count,
		typename Enable = void
	>
	struct policy_exist_check_result
		: public boost::mpl::false_
	{};
	template<
		typename Tag,
		typename Types,
		typename Indexes,
		typename Founds,
		std::size_t Count
	>
	struct policy_exist_check_result<
		Tag,
		Types,
		Indexes,
		Founds,
		Count,
		typename boost::enable_if_c<boost::mpl::size<Founds>::value >= 1>::type
	>
		: public boost::mpl::true_
	{};

	//
	// policy_exist_check
	//
	template<
		typename Tag,
		typename Types
	>
	struct policy_exist_check {
		typedef typename policy_detail::policy_check_collect<Tag, Types>::type collected;
		typedef typename boost::mpl::at<collected, boost::mpl::size_t<0> >::type indexes;
		typedef typename boost::mpl::at<collected, boost::mpl::size_t<1> >::type founds;
		typedef typename boost::mpl::size<indexes>::type count;
		typedef policy_exist_check_result<
			Tag,
			Types,
			indexes,
			founds,
			count::value
		> type;
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_CHECKS_POLICY_EXIST_CHECK_HPP
