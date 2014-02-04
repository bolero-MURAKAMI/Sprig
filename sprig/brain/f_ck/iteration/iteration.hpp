/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_ITERATION_ITERATION_HPP
#define SPRIG_BRAIN_F_CK_ITERATION_ITERATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/f_ck/literals/literals.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_iteration
			//
			//	COMMENT: 基本コマンドに対応する単一文字を扱う走査クラス
			//
			template<
				typename Types = use_default,
				typename Commands = use_default,
				typename Literals = use_default
			>
			class bf_iteration
				: public iteration_interface<Types>
				, public command_base<Commands>
			{
			public:
				typedef iteration_interface<Types> iteration_interface;
				typedef typename iteration_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				typedef typename select_default<Literals, bf_literals>::type literals;
			public:
				virtual std::auto_ptr<iteration_interface> clone() {
					std::auto_ptr<iteration_interface> p(new bf_iteration(*this));
					return p;
				}
				virtual tag_type which(position_interface<types>& pos) {
					switch (pos.get()) {
					case literals::template get<0>::value:
						return commands::next;
					case literals::template get<1>::value:
						return commands::prior;
					case literals::template get<2>::value:
						return commands::inc;
					case literals::template get<3>::value:
						return commands::dec;
					case literals::template get<4>::value:
						return commands::out;
					case literals::template get<5>::value:
						return commands::in;
					case literals::template get<6>::value:
						return commands::begin;
					case literals::template get<7>::value:
						return commands::end;
					}
					return commands::none;
				}
				virtual void next(position_interface<types>& pos) {
					pos.next();
				}
				virtual void prior(position_interface<types>& pos) {
					pos.prior();
				}
				virtual void forward(position_interface<types>& pos) {
					int c = 1;
					do {
						next(pos);
						switch (pos.get()) {
						case literals::template get<6>::value:
							++c;
							break;
						case literals::template get<7>::value:
							--c;
							break;
						}
					} while (c);
				}
				virtual void backward(position_interface<types>& pos) {
					int c = -1;
					do {
						prior(pos);
						switch (pos.get()) {
						case literals::template get<6>::value:
							++c;
							break;
						case literals::template get<7>::value:
							--c;
							break;
						}
					} while (c);
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_ITERATION_ITERATION_HPP
