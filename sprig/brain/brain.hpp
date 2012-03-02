#ifndef SPRIG_BRAIN_BRAIN_HPP
#define SPRIG_BRAIN_BRAIN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <memory>
#include <sprig/use_default.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	namespace brain {
		//
		// types
		//
		//	COMMENT: 基本型定義
		//
		struct types {
		public:
			typedef unsigned char byte_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t diff_type;
			typedef int tag_type;
		};

		//
		// type_base
		//
		//	COMMENT: 型定義のスーパークラス
		//
		template<typename Types = use_default>
		struct type_base {
		public:
			typedef typename select_default<Types, brain::types>::type types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		};

		//
		//	COMMENT: インタフェースの前方宣言
		//
		template<typename Types> class position_interface;
		template<typename Types> class buffer_interface;
		template<typename Types> class io_interface;
		template<typename Types> class iteration_interface;
		template<typename Types> class executor_interface;
		template<typename Types> class engine_interface;

		//
		// memory_interface
		//
		//	COMMENT: メモリクラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class memory_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~memory_interface() {}
			virtual byte_type& at(diff_type d) = 0;
			virtual bool is_out_of_range(diff_type d) = 0;
		};

		//
		// position_interface
		//
		//	COMMENT: 位置クラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class position_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~position_interface() {}
			virtual std::auto_ptr<position_interface> clone() = 0;
			virtual void set(byte_type b) = 0;
			virtual byte_type get() = 0;
			virtual void next() = 0;
			virtual void prior() = 0;
			virtual bool equal(position_interface& pos) = 0;
			virtual void assign(position_interface& pos) = 0;
		};

		//
		// buffer_interface
		//
		//	COMMENT: バッファクラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class buffer_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~buffer_interface() {}
			virtual std::auto_ptr<buffer_interface> clone() = 0;
			virtual position_interface<types>* ppos() = 0;
			virtual position_interface<types>* mpos() = 0;
		};

		//
		// io_interface
		//
		//	COMMENT: 入出力クラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class io_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~io_interface() {}
			virtual std::auto_ptr<io_interface> clone() = 0;
			virtual void out(position_interface<types>& pos) = 0;
			virtual void in(position_interface<types>& pos) = 0;
		};

		//
		// iteration_interface
		//
		//	COMMENT: 走査クラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class iteration_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~iteration_interface() {}
			virtual std::auto_ptr<iteration_interface> clone() = 0;
			virtual tag_type which(position_interface<types>& pos) = 0;
			virtual void next(position_interface<types>& pos) = 0;
			virtual void prior(position_interface<types>& pos) = 0;
			virtual void forward(position_interface<types>& pos) = 0;
			virtual void backward(position_interface<types>& pos) = 0;
		};

		//
		// executor_interface
		//
		//	COMMENT: コマンド実行クラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class executor_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~executor_interface() {}
			virtual std::auto_ptr<executor_interface> clone() = 0;
			virtual void exec(engine_interface<types>& eng, tag_type com) = 0;
		};

		//
		// engine_interface
		//
		//	COMMENT: エンジンクラスのインタフェース
		//
		template<
			typename Types = use_default
		>
		class engine_interface
			: public type_base<Types>
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		public:
			virtual ~engine_interface() {}
			virtual void init_begin() = 0;
			virtual void init_end() = 0;
			virtual void load(byte_type b) = 0;
			virtual void exec() = 0;
			virtual buffer_interface<types>* buffer() = 0;
			virtual io_interface<types>* io() = 0;
			virtual iteration_interface<types>* iteration() = 0;
			virtual executor_interface<types>* executor() = 0;
		};

		//
		// commands
		//
		//	COMMENT: 基本コマンド定義
		//
		struct commands {
			enum tag {
				none = 0,
				next,
				prior,
				inc,
				dec,
				out,
				in,
				begin,
				end,
				extends	/* use extended commands */
			};
		};

		//
		// position_tags
		//
		//	COMMENT: 位置タグ定義
		//
		struct position_tags {
			enum tag {
				ppos,
				mpos
			};
		};

		//
		// command_base
		//
		//	COMMENT: コマンド定義のスーパークラス
		//
		template<typename Commands = use_default>
		struct command_base {
		public:
			typedef typename select_default<Commands, brain::commands>::type commands;
		};

		//
		// brain_exception
		//
		//	COMMENT: 例外のベースクラス
		//
		SPRIG_EXCEPTION_DECL(brain_exception);

		//
		// engine_exit
		//
		//	COMMENT: エンジン実行時の正常終了を通知する例外
		//
		SPRIG_EXCEPTION_INHERIT_DECL(engine_exit, brain_exception);

	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_BRAIN_HPP
