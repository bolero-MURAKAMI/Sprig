/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_JACK_HPP
#define SPRIG_BRAIN_JACK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <map>
#include <algorithm>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/exception.hpp>
#include <sprig/use_default.hpp>
#include <sprig/literal_array.hpp>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		namespace jack {
			//
			// bj_system_exit
			//
			SPRIG_EXCEPTION_INHERIT_DECL(bj_system_exit, engine_exit);

			//
			// bj_directives
			//
			struct bj_directives {
				enum tag {
					none = 0,
					dfn,
					ret,
					arg,
					a_out,
					a_in,
					a_next,
					a_prior,
					a_inc,
					a_dec,
					dir_end,
					fun_call,
					extends	/* use extended directives */
				};
			};

			//
			// bj_directives_base
			//
			template<
				typename Directives = use_default
			>
			struct bj_directives_base {
			public:
				typedef typename select_default<Directives, jack::bj_directives>::type bj_directives;
			};

			//
			// bj_directive_literals
			//
			template<
				typename Directives = use_default
			>
			struct bj_directive_literals
				: public bj_directives_base<Directives>
			{
				typedef typename bj_directives::tag key_type;
				typedef literal_array<char const, false> type;
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::dfn, type> const& get() {
					static type const lit = "dfn";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::ret, type> const& get() {
					static type const lit = "ret";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::arg, type> const& get() {
					static type const lit = "arg";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_out, type> const& get() {
					static type const lit = "a.";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_in, type> const& get() {
					static type const lit = "a,";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_next, type> const& get() {
					static type const lit = "a>";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_prior, type> const& get() {
					static type const lit = "a<";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_inc, type> const& get() {
					static type const lit = "a+";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::a_dec, type> const& get() {
					static type const lit = "a-";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::dir_end, type> const& get() {
					static type const lit = ";";
					return lit;
				}
				template<key_type K>
				static boost::enable_if_c<K == bj_directives::fun_call, type> const& get() {
					static type const lit = ":";
					return lit;
				}
			};

			//
			// bj_system_io
			//
			template<
				typename Types = use_default,
				typename Directives = use_default,
				typename DirectiveLiterals = use_default
			>
			class bj_system_io
				: public io_interface<Types>
				, public bj_directives_base<Directives>
			{
			public:
				typedef io_interface<Types> io_interface;
				typedef typename io_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				typedef typename select_default<
					DirectiveLiterals,
					bj_directive_literals<Directives>
				>::type bj_directive_literals;
			private:
				enum omode {
					default_omode,	// 通常出力モード
					dfn_omode,		// 関数定義モード
					arg_omode,		// 引数設定モード
					a_out_omode		// 引数出力モード
				};
				enum imode {
					default_imode,	// 通常入力モード
					a_in_imode		// 引数入力モード
				};
			private:
				template<typename T>
				struct buffer_comparator {
					bool operator()(T const& lhs, T const& rhs) const {
						return std::lexicographical_compare(
							boost::begin(lhs),
							boost::end(lhs),
							boost::begin(rhs),
							boost::end(rhs)
							);
					}
				};
			private:
				typedef std::vector<byte_type> buffer_type;
				typedef boost::shared_ptr<position_interface<types> > position_instance_type;
				typedef boost::tuple<
					position_instance_type,			// スタック上の呼出元プログラム位置
					position_instance_type,			// スタック上の呼出元メモリ位置
					position_instance_type			// スタック上の引数
				> stack_element_type;
				typedef std::vector<stack_element_type> stack_type;
				typedef std::map<
					buffer_type,
					position_instance_type,
					buffer_comparator<buffer_type>
				> function_map_type;
			private:
				engine_interface<types>* engine_;	// エンジン
				omode omode_;						// 出力モード
				imode imode_;						// 入力モード
				buffer_type output_buffer_;			// 出力バッファ
				buffer_type dfn_buffer_;			// 関数定義バッファ
				stack_type stack_;					// スタック
				position_instance_type arg_;		// 登録引数
				function_map_type function_map_;	// 関数マップ
			private:
				//	COMMENT: 出力バッファの末尾がディレクティブに等しいか
				bool equal_dir(typename bj_directive_literals::type const& dir) {
					return boost::size(output_buffer_) >= boost::size(dir)
						&& std::equal(
							boost::rbegin(dir),
							boost::rend(dir),
							boost::rbegin(output_buffer_)
							)
						;
				}
				//	COMMENT: 出力バッファの全てが関数識別子に等しいか
				bool equal_fun(buffer_type const& fun) {
					return boost::size(output_buffer_) == boost::size(fun)
						&& std::equal(
							boost::begin(fun),
							boost::end(fun),
							boost::begin(output_buffer_)
							)
						;
				}
				//	COMMENT: 出力バッファからディレクティブをポップする
				//	COMMENT: 出力バッファの末尾がディレクティブに等しくなければならない
				void pop_dir(typename bj_directive_literals::type const& dir) {
					output_buffer_.resize(
						boost::size(output_buffer_)
							- boost::size(bj_directive_literals::template get<bj_directives::dir_end>())
						);
				}
				//	COMMENT: スタック上のプログラム位置を返す
				//	COMMENT: スタックの要素が空であってはならない
				position_instance_type& get_stack_ppos() {
					return stack_.back().template get<0>();
				}
				//	COMMENT: スタック上の呼出元メモリ位置を返す
				//	COMMENT: スタックの要素が空であってはならない
				position_instance_type& get_stack_mpos() {
					return stack_.back().template get<1>();
				}
				//	COMMENT: スタック上の引数を返す
				//	COMMENT: スタックの要素が空であってはならない
				position_instance_type& get_stack_arg() {
					return stack_.back().template get<2>();
				}
				//	COMMENT: エンジンのメモリ位置をスタック上の引数に差し替えてコマンド実行させる
				//	COMMENT: 実行後、メモリ位置は復帰される
				void exec_at_arg(tag_type com) {
					std::auto_ptr<position_interface<types> > mpos = engine_->buffer()->mpos()->clone();
					engine_->buffer()->mpos()->assign(*get_stack_arg());
					engine_->executor()->exec(*engine_, com);
					engine_->buffer()->mpos()->assign(*mpos);
				}
			public:
				explicit bj_system_io(engine_interface<types>* engine)
					: engine_(engine)
					, omode_(default_omode)
					, imode_(default_imode)
					, stack_(
						1,
						stack_element_type(
							engine_->buffer()->ppos()->clone(),
							engine_->buffer()->mpos()->clone()
							)
						)
					, arg_(engine_->buffer()->mpos()->clone())
				{}
			public:
				virtual std::auto_ptr<io_interface> clone() {
					std::auto_ptr<io_interface> p(new bj_system_io(*this));
					return p;
				}
				virtual void out(position_interface<types>& pos) {
					static typename bj_directive_literals::type const& dfn
						= bj_directive_literals::template get<bj_directives::dfn>();
					static typename bj_directive_literals::type const& ret
						= bj_directive_literals::template get<bj_directives::ret>();
					static typename bj_directive_literals::type const& arg
						= bj_directive_literals::template get<bj_directives::arg>();
					static typename bj_directive_literals::type const& a_out
						= bj_directive_literals::template get<bj_directives::a_out>();
					static typename bj_directive_literals::type const& a_in
						= bj_directive_literals::template get<bj_directives::a_in>();
					static typename bj_directive_literals::type const& a_next
						= bj_directive_literals::template get<bj_directives::a_next>();
					static typename bj_directive_literals::type const& a_prior
						= bj_directive_literals::template get<bj_directives::a_prior>();
					static typename bj_directive_literals::type const& a_inc
						= bj_directive_literals::template get<bj_directives::a_inc>();
					static typename bj_directive_literals::type const& a_dec
						= bj_directive_literals::template get<bj_directives::a_dec>();
					static typename bj_directive_literals::type const& dir_end
						= bj_directive_literals::template get<bj_directives::dir_end>();
					static typename bj_directive_literals::type const& fun_call
						= bj_directive_literals::template get<bj_directives::fun_call>();

					byte_type const b = pos.get();

					switch (omode_) {
					case default_omode:
						//	COMMENT: 通常出力モード
						output_buffer_.push_back(b);
						if (equal_dir(dir_end)) {
							//	COMMENT: ディレクティブ終端に一致した場合
							//	COMMENT: 終端をポップ
							pop_dir(dir_end);
							if (equal_dir(dfn)) {
								//	COMMENT: 関数定義ディレクティブ
								omode_ = dfn_omode;
							} else if (equal_dir(ret)) {
								//	COMMENT: 返却ディレクティブ
								//	COMMENT: スタックがこれ以上ないときは、終了通知例外を投げる
								if (boost::size(stack_) == 1) {
									throw bj_system_exit("Brainjack system exit. (Returned from the primary stack)");
								}
								engine_->buffer()->ppos()->assign(*get_stack_ppos());
								engine_->buffer()->mpos()->assign(*get_stack_mpos());
								arg_->assign(*get_stack_arg());
								stack_.pop_back();
							} else if (equal_dir(arg)) {
								//	COMMENT: 引数設定ディレクティブ
								omode_ = arg_omode;
							} else if (equal_dir(a_out)) {
								//	COMMENT: 引数出力設定ディレクティブ
								omode_ = a_out_omode;
							} else if (equal_dir(a_in)) {
								//	COMMENT: 引数入力設定ディレクティブ
								imode_ = a_in_imode;
							} else if (equal_dir(a_next)) {
								//	COMMENT: 引数前進ディレクティブ
								exec_at_arg(commands::next);
							} else if (equal_dir(a_prior)) {
								//	COMMENT: 引数後退ディレクティブ
								exec_at_arg(commands::prior);
							} else if (equal_dir(a_inc)) {
								//	COMMENT: 引数インクリメントディレクティブ
								exec_at_arg(commands::inc);
							} else if (equal_dir(a_dec)) {
								//	COMMENT: 引数デクリメントディレクティブ
								exec_at_arg(commands::dec);
							}
							output_buffer_.clear();
						} else if (equal_dir(fun_call)) {
							//	COMMENT: 関数呼出に一致した場合
							//	COMMENT: 終端をポップ
							pop_dir(fun_call);
							BOOST_FOREACH(typename function_map_type::value_type const& e, function_map_) {
								//	COMMENT: 関数マップを走査
								if (equal_fun(e.first)) {
									//	COMMENT: 関数識別子に一致した場合
									//	COMMENT: スタックをプッシュ
									stack_.push_back(
										stack_element_type(
											engine_->buffer()->ppos()->clone(),
											engine_->buffer()->mpos()->clone(),
											arg_->clone()
											)
										);
									//	COMMENT: プログラム位置を関数エントリポイントに移動
									engine_->buffer()->ppos()->assign(*e.second);
									engine_->buffer()->mpos()->assign(*e.second);
									break;
								}
							}
							//	COMMENT: バッファはクリアする
							output_buffer_.clear();
						}
						break;
					case dfn_omode:
						//	COMMENT: 関数定義モード
						if (b != byte_type()) {
							//	COMMENT: 値がNULLでない場合、関数定義バッファにプッシュ
							dfn_buffer_.push_back(b);
						} else {
							//	COMMENT: 値がNULLである場合
							omode_ = default_omode;
							if (!boost::empty(dfn_buffer_)) {
								//	関数定義バッファが空でない場合、関数定義を追加
								function_map_.insert(
									typename function_map_type::value_type(
										dfn_buffer_,
										position_instance_type(pos.clone())
										)
									);
							}
							//	COMMENT: バッファはクリアする
							dfn_buffer_.clear();
						}
						break;
					case arg_omode:
						//	COMMENT: 引数設定モード
						omode_ = default_omode;
						arg_ = pos.clone();
						break;
					case a_out_omode:
						//	COMMENT: 引数出力モード
						omode_ = default_omode;
						get_stack_arg()->set(pos.get());
						break;
					}
				}
				virtual void in(position_interface<types>& pos) {
					switch (imode_) {
					case default_imode:
						//	COMMENT: 通常入力モード
						pos.set(byte_type());
						break;
					case a_in_imode:
						//	COMMENT: 引数入力モード
						imode_ = default_imode;
						pos.set(get_stack_arg()->get());
						break;
					}
				}
			};
		}	// namespace jack
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_JACK_HPP
