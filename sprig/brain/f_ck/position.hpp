#ifndef SPRIG_BRAIN_F_CK_POSITION_HPP
#define SPRIG_BRAIN_F_CK_POSITION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <sprig/exception.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// position_out_of_range
			//
			//	COMMENT: 位置がバッファの範囲外を指したときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(position_out_of_range, brain_exception);

			//
			// position_out_of_range_forward, position_out_of_range_backward
			//
			//	COMMENT: 位置がバッファの範囲外（前方または後方）を指したときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(position_out_of_range_forward, position_out_of_range);
			SPRIG_EXCEPTION_INHERIT_DECL(position_out_of_range_backward, position_out_of_range);

			//
			// position_bad_assign
			//
			//	COMMENT: 位置代入で失敗したときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(position_bad_assign, brain_exception);

			//
			// position_expired
			//
			//	COMMENT: 位置が指すバッファがすでに無効化されているときに投げられる例外
			//
			SPRIG_EXCEPTION_INHERIT_DECL(position_expired, brain_exception);

			//
			// bf_position
			//
			//	COMMENT: メモリを参照する位置クラス
			//	COMMENT: コンストラクタでメモリクラスおよび位置タグを受けとる
			//	COMMENT: プログラム位置を指す場合、位置が範囲外を指したとき例外を投げる
			//	COMMENT: コピーされた位置クラスは、メモリ位置を指すものと同様である
			//
			template<
				typename Types = use_default
			>
			class bf_position
				: public position_interface<Types>
			{
			public:
				typedef position_interface<Types> position_interface;
				typedef typename position_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			private:
				boost::weak_ptr<memory_interface<types> > memory_;
				diff_type where_;
				bool range_checked_;
			private:
				void check_expired() const {
					if (memory_.expired()) {
						throw position_expired("Position expired.");
					}
				}
				void check_range() const {
					if (range_checked_) {
						check_expired();
						if (memory_.lock()->is_out_of_range(where_)) {
							if (where_ >= 0) {
								throw position_out_of_range_forward("Position out of range forward.");
							} else {
								throw position_out_of_range_backward("Position out of range backward.");
							}
						}
					}
				}
			public:
				virtual std::auto_ptr<position_interface> clone() {
					check_expired();
					std::auto_ptr<position_interface> p(new bf_position(*this));
					return p;
				}
				virtual void set(byte_type b) {
					check_expired();
					memory_.lock()->at(where_) = b;
				}
				virtual byte_type get() {
					check_expired();
					return memory_.lock()->at(where_);
				}
				virtual void next() {
					check_expired();
					++where_;
					check_range();
				}
				virtual void prior() {
					check_expired();
					--where_;
					check_range();
				}
				virtual bool equal(position_interface& pos) {
					check_expired();
					bf_position* p = dynamic_cast<bf_position*>(&pos);
					if (p) {
						p->check_expired();
						return memory_.lock() == p->memory_.lock()
							&& where_ == p->where_
							;
					} else {
						return false;
					}
				}
				virtual void assign(position_interface& pos) {
					check_expired();
					bf_position* p = dynamic_cast<bf_position*>(&pos);
					if (p) {
						p->check_expired();
						if (memory_.lock() == p->memory_.lock()) {
							where_ = p->where_;
						} else {
							throw position_bad_assign("Tried to assign a different memory location reference.");
						}
					} else {
						throw position_bad_assign("Tried to assign the position of different instance types.");
					}
					check_range();
				}
			public:
				bf_position(
					boost::weak_ptr<memory_interface<types> > memory,
					position_tags::tag ptag
					)
					: memory_(memory)
					, where_(0)
					, range_checked_(ptag == position_tags::ppos)
				{}
				bf_position(bf_position& other)
					: memory_(other.memory_)
					, where_(other.where_)
					, range_checked_(false)
				{}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_POSITION_HPP
