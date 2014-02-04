/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_XPRESSIVE_HPP
#define SPRIG_UTILITY_XPRESSIVE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/xpressive/xpressive.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// is_word_token
	//
	struct is_word_token {
		template<typename T>
		typename boost::enable_if<boost::is_pointer<T>, bool>::type
		operator()(T value) {
			boost::xpressive::basic_regex<T> regex(
				boost::xpressive::_w
					>> boost::xpressive::after(~boost::xpressive::_d)
					>> *boost::xpressive::_w
				);
			return boost::xpressive::regex_match(value, regex);
		}
		template<typename T>
		typename boost::disable_if<boost::is_pointer<T>, bool>::type
		operator()(T const& value) {
			boost::xpressive::basic_regex<typename T::const_iterator> regex(
				boost::xpressive::_w
					>> boost::xpressive::after(~boost::xpressive::_d)
					>> *boost::xpressive::_w
				);
			return boost::xpressive::regex_match(value, regex);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_XPRESSIVE_HPP
