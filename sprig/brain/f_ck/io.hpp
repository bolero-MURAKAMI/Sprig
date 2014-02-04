/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_IO_HPP
#define SPRIG_BRAIN_F_CK_IO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iostream>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_io
			//
			//	COMMENT: 標準入出力を行う入出力クラス
			//	COMMENT: バイト型は常に単一文字型として扱われる
			//
			template<
				typename Types = use_default
			>
			class bf_io
				: public io_interface<Types>
			{
			public:
				typedef io_interface<Types> io_interface;
				typedef typename io_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				virtual std::auto_ptr<io_interface> clone() {
					std::auto_ptr<io_interface> p(new bf_io(*this));
					return p;
				}
				virtual void out(position_interface<types>& pos) {
					std::cout << static_cast<char>(pos.get());
				}
				virtual void in(position_interface<types>& pos) {
					char b;
					std::cin >> b;
					pos.set(b);
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_IO_HPP
