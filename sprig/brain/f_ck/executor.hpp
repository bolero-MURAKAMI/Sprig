/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_EXECTOR_HPP
#define SPRIG_BRAIN_F_CK_EXECTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_executor
			//
			//	COMMENT: 基本コマンドに対応するコマンド実行クラス
			//
			template<
				typename Types = use_default,
				typename Commands = use_default
			>
			class bf_executor
				: public executor_interface<Types>
				, public command_base<Commands>
			{
			public:
				typedef executor_interface<Types> executor_interface;
				typedef typename executor_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				virtual std::auto_ptr<executor_interface> clone() {
					std::auto_ptr<executor_interface> p(new bf_executor(*this));
					return p;
				}
				virtual void exec(engine_interface<types>& eng, tag_type com) {
					switch (com) {
					case commands::next:
						eng.buffer()->mpos()->next();
						break;
					case commands::prior:
						eng.buffer()->mpos()->prior();
						break;
					case commands::inc:
						eng.buffer()->mpos()->set(eng.buffer()->mpos()->get() + 1);
						break;
					case commands::dec:
						eng.buffer()->mpos()->set(eng.buffer()->mpos()->get() - 1);
						break;
					case commands::out:
						eng.io()->out(*eng.buffer()->mpos());
						break;
					case commands::in:
						eng.io()->in(*eng.buffer()->mpos());
						break;
					case commands::begin:
						if (!eng.buffer()->mpos()->get()) {
							eng.iteration()->forward(*eng.buffer()->ppos());
						}
						break;
					case commands::end:
						eng.iteration()->backward(*eng.buffer()->ppos());
						break;
					}
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_EXECTOR_HPP
