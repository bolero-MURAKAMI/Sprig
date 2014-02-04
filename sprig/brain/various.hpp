/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_VARIOUS_HPP
#define SPRIG_BRAIN_VARIOUS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/static_assert.hpp>
#include <boost/assign/list_of.hpp>
#include <sprig/literal_array.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// neko_mimi_literals
			//
			//	COMMENT: neko mimi Fu** のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列を定義する
			//
			struct neko_mimi_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"ネコミミ！",
						"ネコミミモード",
						"おにいさま",
						"私のしもべー",
						"や・く・そ・く・よ",
						"フルフルフルムーン",
						"キスキス…",
						"キス…したくなっちゃった…"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// nagato_literals
			//
			//	COMMENT: 長門有希 のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列を定義する
			//
			struct nagato_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"………",
						"…………",
						"…",
						"……",
						"………………",
						"……………",
						"「",
						"」"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// aegi_literals
			//
			//	COMMENT: あえぎ声記述言語 のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列を定義する
			//
			struct aegi_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"ああッ",
						"んんッ！",
						"あッ",
						"んッ",
						"イク！イっちゃう！",
						"入ってるの感じちゃうぅ！",
						"してぇ！お願い！",
						"やめないでぇ！"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// hokuto_literals
			//
			//	COMMENT: 北斗脳裂斬 のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列を定義する
			//
			struct hokuto_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"あ",
						"ほ",
						"た",
						"ー",
						"おまえはもう死んでいる",
						"ふ",
						"っ",
						"！"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// misa_literals
			//
			//	COMMENT: Misa のリテラル定義
			//	COMMENT: 基本コマンドに対応する文字列セットを定義する
			//
			struct misa_literals {
				typedef std::vector<literal_array<char const, false> > type;
				template<int N>
				static type const& get() {
					typedef literal_array<char const, false> literal_type;
					static type const literals[] = {
						boost::assign::list_of<literal_type>(">")("→")("～")("ー"),
						boost::assign::list_of<literal_type>("<")("←")("★")("☆"),
						boost::assign::list_of<literal_type>("+")("あ")("ぁ")("お")("ぉ"),
						boost::assign::list_of<literal_type>("-")("っ")("ッ"),
						boost::assign::list_of<literal_type>(".")("！"),
						boost::assign::list_of<literal_type>(",")("？"),
						boost::assign::list_of<literal_type>("[")("「")("『"),
						boost::assign::list_of<literal_type>("]")("」")("』")
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_VARIOUS_HPP
