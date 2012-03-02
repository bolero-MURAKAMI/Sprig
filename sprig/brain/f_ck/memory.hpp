#ifndef SPRIG_BRAIN_F_CK_MEMORY_HPP
#define SPRIG_BRAIN_F_CK_MEMORY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_memory
			//
			//	COMMENT: 符号付きの添え字に対応したメモリクラス
			//	COMMENT: メモリはアクセスが行われたとき自動拡張される
			//
			template<
				typename Types = use_default
			>
			class bf_memory
				: public memory_interface<Types>
			{
			public:
				typedef memory_interface<Types> memory_interface;
				typedef typename memory_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			private:
				typedef std::vector<byte_type> buffer_type;
			private:
				buffer_type forward_;
				buffer_type backward_;
			private:
				byte_type& at(buffer_type& buffer, size_type i) {
					if (is_out_of_range(buffer, i)) {
						buffer.resize(i + 1);
					}
					return buffer.at(i);
				}
				bool is_out_of_range(buffer_type const& buffer, size_type i) const {
					return i >= buffer.size();
				}
			public:
				virtual byte_type& at(diff_type d) {
					return d >= 0
						? at(forward_, d)
						: at(backward_, -d - 1)
						;
				}
				virtual bool is_out_of_range(diff_type d) {
					return d >= 0
						? is_out_of_range(forward_, d)
						: is_out_of_range(backward_, -d - 1)
						;
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_MEMORY_HPP
