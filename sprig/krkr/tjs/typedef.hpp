/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_TYPEDEF_HPP
#define SPRIG_KRKR_TJS_TYPEDEF_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/tmp/eval_assert.hpp>
#include <sprig/krkr/tjs/intrusive_ptr.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// char_type
			//
			typedef tjs_char char_type;
			//
			// string_type
			//
			typedef std::basic_string<char_type> string_type;
			//
			// string_argument_type
			//
			typedef sprig::basic_string_argument<string_type> string_argument_type;

			//
			// object_type
			//
			typedef boost::intrusive_ptr<iTJSDispatch2> object_type;

			//
			// intptr_type
			//
			typedef boost::mpl::eval_if_c<
				sizeof(void*) == sizeof(tjs_int),
				boost::mpl::identity<tjs_int>,
				boost::mpl::eval_if_c<
					sizeof(void*) == sizeof(tTVInteger),
					boost::mpl::identity<tTVInteger>,
					tmp::eval_assert_c<0>
				>
			>::type intptr_type;
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_TYPEDEF_HPP
