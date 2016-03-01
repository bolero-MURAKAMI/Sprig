/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_LITERALS_MULTI_LITERALS_HPP
#define SPRIG_BRAIN_F_CK_LITERALS_MULTI_LITERALS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/static_assert.hpp>
#include <sprig/literal_array.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_multi_literals
			//
			//	COMMENT: Brainf*ck のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列セットを定義する
			//
			struct bf_multi_literals {
				typedef std::vector<literal_array<char const, false> > type;
				template<int N>
				static type const& get() {
					typedef literal_array<char const, false> literal_type;
					static type const literals[] = {
						boost::assign::list_of<literal_type>(">"),
						boost::assign::list_of<literal_type>("<"),
						boost::assign::list_of<literal_type>("+"),
						boost::assign::list_of<literal_type>("-"),
						boost::assign::list_of<literal_type>("."),
						boost::assign::list_of<literal_type>(","),
						boost::assign::list_of<literal_type>("["),
						boost::assign::list_of<literal_type>("]")
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_LITERALS_MULTI_LITERALS_HPP
