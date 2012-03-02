#ifndef SPRIG_BRAIN_F_CK_SHARED_BUFFER_HPP
#define SPRIG_BRAIN_F_CK_SHARED_BUFFER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/f_ck/memory.hpp>
#include <sprig/brain/f_ck/position.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_shared_buffer
			//
			//	COMMENT: メモリを所有するバッファクラス
			//	COMMENT: プログラムバッファとメモリバッファは共有されている
			//
			template<
				typename Types = use_default,
				typename Memory = use_default,
				typename Position = use_default
			>
			class bf_shared_buffer
				: public buffer_interface<Types>
			{
			public:
				typedef buffer_interface<Types> buffer_interface;
				typedef typename buffer_interface::types types;
				typedef typename types::byte_type byte_type;
				typedef typename types::size_type size_type;
				typedef typename types::diff_type diff_type;
				typedef typename types::tag_type tag_type;
			public:
				typedef typename select_default<Memory, bf_memory<types> >::type memory_type;
				typedef typename select_default<Position, bf_position<types> >::type position_type;
			private:
				boost::shared_ptr<memory_interface<types> > memory_;
				boost::shared_ptr<position_interface<types> > ppos_;
				boost::shared_ptr<position_interface<types> > mpos_;
			public:
				bf_shared_buffer()
					: memory_(boost::make_shared<memory_type>())
					, ppos_(boost::make_shared<position_type>(memory_, position_tags::ppos))
					, mpos_(boost::make_shared<position_type>(memory_, position_tags::mpos))
				{}
			public:
				virtual std::auto_ptr<buffer_interface> clone() {
					std::auto_ptr<buffer_interface> p(new bf_shared_buffer(*this));
					return p;
				}
				virtual position_interface<types>* ppos() {
					return ppos_.get();
				}
				virtual position_interface<types>* mpos() {
					return mpos_.get();
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_SHARED_BUFFER_HPP
