/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_NA_HPP
#define SPRIG_TMP_NA_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/remove.hpp>

namespace sprig {
	namespace tmp {
		//
		// na
		//
		struct na {
			typedef na type;
			static bool const value = false;
		};

		//
		// is_na
		//
		template<typename T>
		struct is_na
			: public boost::mpl::false_
		{};
		template<>
		struct is_na<na>
			: public boost::mpl::true_
		{};

		//
		// is_not_na
		//
		template<typename T>
		struct is_not_na
			: public boost::mpl::true_
		{};
		template<>
		struct is_not_na<na>
			: public boost::mpl::false_
		{};

		//
		// if_na
		//
		template<typename T, typename Default>
		struct if_na
			: public boost::mpl::identity<T>
		{};
		template<typename Default>
		struct if_na<
			na,
			Default
		>
			: public boost::mpl::identity<Default>
		{};

		//
		// remove_na
		//
		template<typename Seq>
		struct remove_na
			: public boost::mpl::remove<Seq, na>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_NA_HPP
