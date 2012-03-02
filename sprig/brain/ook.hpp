#ifndef SPRIG_BRAIN_OOK_HPP
#define SPRIG_BRAIN_OOK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cctype>
#include <memory>
#include <iterator>
#include <algorithm>
#include <boost/range.hpp>
#include <boost/static_assert.hpp>
#include <sprig/use_default.hpp>
#include <sprig/literal_array.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/utils.hpp>

namespace sprig {
	namespace brain {
		namespace ook {
			//
			// ook_literals
			//
			//	COMMENT: Ook! のリテラル定義
			//	COMMENT: 基本コマンドに対応する Ook! の構成トークンを定義する
			//
			struct ook_literals {
				template<int N>
				static literal_array<char const, false> const& get() {
					static literal_array<char const, false> const literals[] = {
						"Ook.",
						"Ook!",
						"Ook?"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// ook_iteration
			//
			//	COMMENT: 基本コマンドに対応する Ook! のトークンを扱う走査クラス
			//	COMMENT: 構成トークンは空白文字で区切られる
			//	COMMENT: 構成トークンが区切られていなくても問題ない
			//
			template<
				typename Types = use_default,
				typename Commands = use_default,
				typename Literals = use_default
			>
			class ook_iteration
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
				typedef typename select_default<Literals, ook_literals>::type literals;
			private:
				void skip_next(position_interface<types>& pos) {
					position_iterator<types> i = pos;
					while (std::isspace(static_cast<char>(*i))) {
						++i;
					}
				}
				void skip_prior(position_interface<types>& pos) {
					position_iterator<types> i = pos;
					do {
						--i;
					} while (std::isspace(static_cast<char>(*i)));
				}
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
					std::auto_ptr<iteration_interface> p(new ook_iteration(*this));
					return p;
				}
				virtual tag_type which(position_interface<types>& pos) {
					std::auto_ptr<position_interface<types> > p = pos.clone();
					if (match_next<0>(*p)) {
						advance_next<0>(*p);
						skip_next(*p);
						if (match_next<0>(*p)) {
							return commands::inc;
						} else if (match_next<1>(*p)) {
							return commands::in;
						} else if (match_next<2>(*p)) {
							return commands::next;
						}
					} else if (match_next<1>(*p)) {
						advance_next<1>(*p);
						skip_next(*p);
						if (match_next<0>(*p)) {
							return commands::out;
						} else if (match_next<1>(*p)) {
							return commands::dec;
						} else if (match_next<2>(*p)) {
							return commands::begin;
						}
					} else if (match_next<2>(*p)) {
						advance_next<2>(*p);
						skip_next(*p);
						if (match_next<0>(*p)) {
							return commands::prior;
						} else if (match_next<1>(*p)) {
							return commands::end;
						}
					}
					return commands::none;
				}
				virtual void next(position_interface<types>& pos) {
					switch (which(pos)) {
					case commands::next:
						advance_next<0>(pos);
						skip_next(pos);
						advance_next<2>(pos);
						break;
					case commands::prior:
						advance_next<2>(pos);
						skip_next(pos);
						advance_next<0>(pos);
						break;
					case commands::inc:
						advance_next<0>(pos);
						skip_next(pos);
						advance_next<0>(pos);
						break;
					case commands::dec:
						advance_next<1>(pos);
						skip_next(pos);
						advance_next<1>(pos);
						break;
					case commands::out:
						advance_next<1>(pos);
						skip_next(pos);
						advance_next<0>(pos);
						break;
					case commands::in:
						advance_next<0>(pos);
						skip_next(pos);
						advance_next<1>(pos);
						break;
					case commands::begin:
						advance_next<1>(pos);
						skip_next(pos);
						advance_next<2>(pos);
						break;
					case commands::end:
						advance_next<2>(pos);
						skip_next(pos);
						advance_next<1>(pos);
						break;
					default:
						pos.next();
						break;
					}
				}
				virtual void prior(position_interface<types>& pos) {
					switch (which(pos)) {
					case commands::next:
						advance_prior<2>(pos);
						skip_prior(pos);
						advance_prior<0>(pos);
						break;
					case commands::prior:
						advance_prior<0>(pos);
						skip_prior(pos);
						advance_prior<2>(pos);
						break;
					case commands::inc:
						advance_prior<0>(pos);
						skip_prior(pos);
						advance_prior<0>(pos);
						break;
					case commands::dec:
						advance_prior<1>(pos);
						skip_prior(pos);
						advance_prior<1>(pos);
						break;
					case commands::out:
						advance_prior<0>(pos);
						skip_prior(pos);
						advance_prior<1>(pos);
						break;
					case commands::in:
						advance_prior<1>(pos);
						skip_prior(pos);
						advance_prior<0>(pos);
						break;
					case commands::begin:
						advance_prior<2>(pos);
						skip_prior(pos);
						advance_prior<1>(pos);
						break;
					case commands::end:
						advance_prior<1>(pos);
						skip_prior(pos);
						advance_prior<2>(pos);
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
		}	// namespace ook
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_OOK_HPP
