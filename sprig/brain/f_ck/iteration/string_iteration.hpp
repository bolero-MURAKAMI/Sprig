#ifndef SPRIG_BRAIN_F_CK_ITERATION_STRING_ITERATION_HPP
#define SPRIG_BRAIN_F_CK_ITERATION_STRING_ITERATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <iterator>
#include <boost/range.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/utils.hpp>
#include <sprig/brain/f_ck/literals/string_literals.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_string_iteration
			//
			//	COMMENT: 基本コマンドに対応する文字列を扱う走査クラス
			//
			template<
				typename Types = use_default,
				typename Commands = use_default,
				typename Literals = use_default
			>
			class bf_string_iteration
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
				typedef typename select_default<Literals, bf_string_literals>::type literals;
			private:
				template<size_type N>
				bool match_next(position_interface<types>& pos) {
					std::auto_ptr<position_interface<types> > p = pos.clone();
					position_iterator<types> i = *p;
					return std::equal(
						boost::begin(literals::template get<N>()),
						boost::end(literals::template get<N>()),
						i
						);
				}
				template<size_type N>
				bool match_prior(position_interface<types>& pos) {
					std::auto_ptr<position_interface<types> > p = pos.clone();
					position_iterator<types> i = *p;
					return std::equal(
						boost::rbegin(literals::template get<N>()),
						boost::rend(literals::template get<N>()),
						std::reverse_iterator<position_iterator<types> >(i)
						);
				}
				template<size_type N>
				void advance_next(position_interface<types>& pos) {
					position_iterator<types> i = pos;
					std::advance(i, static_cast<diff_type>(boost::size(literals::template get<N>())));
				}
				template<size_type N>
				void advance_prior(position_interface<types>& pos) {
					position_iterator<types> i = pos;
					std::advance(i, -static_cast<diff_type>(boost::size(literals::template get<N>())));
				}
			public:
				virtual std::auto_ptr<iteration_interface> clone() {
					std::auto_ptr<iteration_interface> p(new bf_string_iteration(*this));
					return p;
				}
				virtual tag_type which(position_interface<types>& pos) {
					if (match_next<0>(pos)) {
						return commands::next;
					} else if (match_next<1>(pos)) {
						return commands::prior;
					} else if (match_next<2>(pos)) {
						return commands::inc;
					} else if (match_next<3>(pos)) {
						return commands::dec;
					} else if (match_next<4>(pos)) {
						return commands::out;
					} else if (match_next<5>(pos)) {
						return commands::in;
					} else if (match_next<6>(pos)) {
						return commands::begin;
					} else if (match_next<7>(pos)) {
						return commands::end;
					}
					return commands::none;
				}
				virtual void next(position_interface<types>& pos) {
					switch (which(pos)) {
					case commands::next:
						advance_next<0>(pos);
						break;
					case commands::prior:
						advance_next<1>(pos);
						break;
					case commands::inc:
						advance_next<2>(pos);
						break;
					case commands::dec:
						advance_next<3>(pos);
						break;
					case commands::out:
						advance_next<4>(pos);
						break;
					case commands::in:
						advance_next<5>(pos);
						break;
					case commands::begin:
						advance_next<6>(pos);
						break;
					case commands::end:
						advance_next<7>(pos);
						break;
					default:
						pos.next();
						break;
					}
				}
				virtual void prior(position_interface<types>& pos) {
					switch (which(pos)) {
					case commands::next:
						advance_prior<0>(pos);
						break;
					case commands::prior:
						advance_prior<1>(pos);
						break;
					case commands::inc:
						advance_prior<2>(pos);
						break;
					case commands::dec:
						advance_prior<3>(pos);
						break;
					case commands::out:
						advance_prior<4>(pos);
						break;
					case commands::in:
						advance_prior<5>(pos);
						break;
					case commands::begin:
						advance_prior<6>(pos);
						break;
					case commands::end:
						advance_prior<7>(pos);
						break;
					default:
						pos.prior();
						break;
					}
				}
				virtual void forward(position_interface<types>& pos) {
					int c = 1;
					do {
						next(pos);
						switch (which(pos)) {
						case commands::begin:
							++c;
							break;
						case commands::end:
							--c;
							break;
						}
					} while (c);
				}
				virtual void backward(position_interface<types>& pos) {
					int c = -1;
					do {
						prior(pos);
						switch (which(pos)) {
						case commands::begin:
							++c;
							break;
						case commands::end:
							--c;
							break;
						}
					} while (c);
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_ITERATION_STRING_ITERATION_HPP
