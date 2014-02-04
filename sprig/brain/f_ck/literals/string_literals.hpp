/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_LITERALS_STRING_LITERALS_HPP
#define SPRIG_BRAIN_F_CK_LITERALS_STRING_LITERALS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/static_assert.hpp>
#include <sprig/literal_array.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_string_literals
			//
			//	COMMENT: Brainf*ck のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列を定義する
			//
			struct bf_string_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						">",
						"<",
						"+",
						"-",
						".",
						",",
						"[",
						"]"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_LITERALS_STRING_LITERALS_HPP
