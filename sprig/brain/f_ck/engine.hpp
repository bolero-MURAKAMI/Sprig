/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_ENGINE_HPP
#define SPRIG_BRAIN_F_CK_ENGINE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <sprig/exception.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/f_ck/memory.hpp>
#include <sprig/brain/f_ck/position.hpp>
#include <sprig/brain/f_ck/buffer.hpp>
#include <sprig/brain/f_ck/shared_buffer.hpp>
#include <sprig/brain/f_ck/io.hpp>
#include <sprig/brain/f_ck/literals/literals.hpp>
#include <sprig/brain/f_ck/iteration/iteration.hpp>
#include <sprig/brain/f_ck/executor.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// engine_initialization_error
			//
			//	COMMENT: エンジン初期化時にエラーが発生したときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(engine_initialization_error, brain_exception);
			//
			// engine_uninitialized
			//
			//	COMMENT: エンジンが未初期化状態で実行したときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(engine_uninitialized, brain_exception);

			//
			// bf_engine
			//
			//	COMMENT: 前方実行し、終端で実行を終了するエンジンクラス
			//
			template<
				typename Types = use_default,
				typename Commands = use_default,
				typename Memory = use_default,
				typename Position = use_default,
				typename Buffer = use_default,
				typename IO = use_default,
				typename Iteration = use_default,
				typename Executor = use_default
			>
			class bf_engine
				: public engine_interface<Types>
				, public command_base<Commands>
			{
			public:
				typedef engine_interface<Types> engine_interface;
				typedef typename engine_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				typedef typename select_default<Memory, bf_memory<types> >::type memory_type;
				typedef typename select_default<Position, bf_position<types> >::type position_type;
				typedef typename select_default<Buffer, bf_buffer<types, memory_type, position_type> >::type buffer_type;
				typedef typename select_default<IO, bf_io<types> >::type io_type;
				typedef typename select_default<Iteration, bf_iteration<types, commands> >::type iteration_type;
				typedef typename select_default<Executor, bf_executor<types, commands> >::type executor_type;
			private:
				boost::shared_ptr<buffer_type> buffer_;
				boost::shared_ptr<io_type> io_;
				boost::shared_ptr<iteration_type> iteration_;
				boost::shared_ptr<executor_type> executor_;
				bool initialized_;
				boost::shared_ptr<position_interface<types> > ppos_;
			public:
				bf_engine()
					: initialized_(false)
				{}
			public:
				virtual void init_begin() {
					initialized_ = false;
					buffer_ = boost::make_shared<buffer_type>();
					io_ = boost::make_shared<io_type>();
					iteration_ = boost::make_shared<iteration_type>();
					executor_ = boost::make_shared<executor_type>();
					ppos_ = boost::shared_ptr<position_interface<types> >(buffer_->ppos()->clone());
					return;
				}
				virtual void init_end() {
					if (!ppos_) {
						throw engine_initialization_error("Engine initialization error in init_end().");
					}
					ppos_.reset();
					initialized_ = true;
					return;
				}
				virtual void load(byte_type b) {
					if (!ppos_) {
						throw engine_initialization_error("Engine initialization error in load().");
					}
					ppos_->set(b);
					ppos_->next();
					return;
				}
				virtual void exec() {
					if (!initialized_) {
						throw engine_uninitialized("Engine uninitialized.");
					}
					tag_type com = iteration_->which(*buffer_->ppos());
					executor_->exec(*this, com);
					try {
						if (com != commands::end) {
							iteration_->next(*buffer_->ppos());
						}
					} catch (position_out_of_range const&) {
						throw engine_exit("Engine exit.");
					}
				}
				virtual buffer_interface<types>* buffer() {
					return initialized_ ? buffer_.get() : 0;
				}
				virtual io_interface<types>* io() {
					return initialized_ ? io_.get() : 0;
				}
				virtual iteration_interface<types>* iteration() {
					return initialized_ ? iteration_.get() : 0;
				}
				virtual executor_interface<types>* executor()  {
					return initialized_ ? executor_.get() : 0;
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_ENGINE_HPP
