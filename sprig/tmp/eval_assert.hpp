/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_EVAL_ASSERT_HPP
#define SPRIG_TMP_EVAL_ASSERT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

namespace sprig {
	namespace tmp {
		//
		// eval_assert_c
		//
		template<bool B>
		struct eval_assert_c
			: public boost::mpl::bool_<B>
		{
			BOOST_STATIC_ASSERT(B);
		};
		//
		// eval_assert
		//
		template<typename T>
		struct eval_assert
			: public boost::mpl::bool_<T::value>
		{
			BOOST_STATIC_ASSERT(T::value);
		};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_EVAL_ASSERT_HPP
