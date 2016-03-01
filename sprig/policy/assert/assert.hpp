/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLICY_ASSERT_ASSERT_HPP
#define SPRIG_POLICY_ASSERT_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/assert.hpp>

//
// SPRIG_POLICY_ASSERT((pred<x,...>))
//
#define SPRIG_POLICY_ASSERT(PRED) \
	BOOST_MPL_ASSERT(PRED)

#endif	// #ifndef SPRIG_POLICY_ASSERT_ASSERT_HPP
