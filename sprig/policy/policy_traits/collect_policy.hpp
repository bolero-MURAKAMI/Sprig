/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_POLICY_TRAITS_COLLECT_POLIYCY_HPP
#define SPRIG_POLICY_POLICY_TRAITS_COLLECT_POLIYCY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/lambda.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>
#include <sprig/policy/policy_traits/get_policy.hpp>

namespace sprig {
	//
	// collect_policy
	//
	template<
		typename Sequence,
		typename Tag,
		typename Inserter = boost::mpl::back_inserter<boost::mpl::vector0<> >
	>
	struct collect_policy
		: public boost::mpl::transform<
			typename boost::mpl::copy_if<
				Sequence,
				is_policy_of<Tag, boost::mpl::_1>,
				boost::mpl::back_inserter<boost::mpl::vector0<> >
			>::type,
			get_policy<boost::mpl::_1>,
			Inserter
		>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_POLICY_TRAITS_COLLECT_POLIYCY_HPP
