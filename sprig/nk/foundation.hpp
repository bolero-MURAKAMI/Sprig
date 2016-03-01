/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NK_FOUNDATION_HPP
#define SPRIG_NK_FOUNDATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <memory>
#include <boost/optional/optional.hpp>
#include <boost/numeric/interval.hpp>

namespace sprig {
	namespace nk {
		//
		// declare
		//
		class unit;
		class engine;

		//
		// typedef
		//
		typedef char byte_type;
		typedef boost::optional<byte_type> popped_byte_type;
		typedef std::ptrdiff_t ptr_type;
		typedef boost::numeric::interval<ptr_type> interval_type;
		typedef std::size_t size_type;
		typedef std::size_t unit_id_type;
		typedef std::auto_ptr<unit> created_unit_type;

		//
		// unit_state
		//
		enum unit_state {
			normal,					// 正常
			abnormal,				// 異常
			requires_input,			// 入力が必要
			stopped					// 未参照メモリを指して停止
		};

		//
		// unit_error
		//
		enum unit_error {
			no_error,				// エラーでない
			un_executable,			// 実行可能な状態でない
			out_of_bounds_forward,	// 前方捜査で未参照メモリまで捜査しても発見できなかった
			out_of_bounds_backward	// 後方捜査で未参照メモリまで捜査しても発見できなかった
		};

		//
		// unit_info
		//
		struct unit_info {
			ptr_type pptr;
			ptr_type dptr;
			unit_state state;
			unit_error error;
		public:
			unit_info()
				: pptr(0)
				, dptr(0)
				, state(normal)
				, error(no_error)
			{}
		};

		//
		// unit
		//
		class unit {
		public:
			virtual ~unit() {}
			virtual unit_id_type const get_id() = 0;
			// ユニット情報
			virtual unit_info const get_info() const = 0;
			virtual void set_info(unit_info const& info) = 0;
			// 入力バッファ
			virtual void push_input(byte_type const in) = 0;
			virtual popped_byte_type const pop_input() = 0;
			virtual bool const empty_input() = 0;
			// 出力バッファ
			virtual void push_output(byte_type const out) = 0;
			virtual popped_byte_type const pop_output() = 0;
			virtual bool const empty_output() = 0;
		};

		//
		// engine
		//
		class engine {
		public:
			virtual ~engine() {}
			virtual created_unit_type create_unit() = 0;
			virtual interval_type const referenced_interval(unit& u) const = 0;
			// アロケーション
			virtual bool const allocate(unit& u, size_type const s) = 0;
			virtual bool const is_allocated(unit& u) const = 0;
			virtual size_type const allocated_size(unit& u) const = 0;
			// ローディング
			virtual bool const load(unit& u, byte_type const c) = 0;
			virtual bool const is_full_loaded(unit& u) const = 0;
			virtual size_type const loaded_size(unit& u) const = 0;
			// 実行
			virtual bool const is_executable(unit& u) const = 0;
			virtual bool const begin_execution(unit& u) = 0;
			virtual bool const end_execution(unit& u) = 0;
			virtual bool const execute(unit& u) = 0;
		};
	}	// namespace nk
}	// namespace sprig

#endif	// #ifndef SPRIG_NK_FOUNDATION_HPP
