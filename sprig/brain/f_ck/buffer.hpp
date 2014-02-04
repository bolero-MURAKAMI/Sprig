/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_F_CK_BUFFER_HPP
#define SPRIG_BRAIN_F_CK_BUFFER_HPP

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
			// bf_buffer
			//
			//	COMMENT: メモリを所有するバッファクラス
			//	COMMENT: プログラムバッファとメモリバッファは独立している
			//
			template<
				typename Types = use_default,
				typename Memory = use_default,
				typename Position = use_default
			>
			class bf_buffer
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
				boost::shared_ptr<memory_interface<types> > pmemory_;
				boost::shared_ptr<memory_interface<types> > mmemory_;
				boost::shared_ptr<position_interface<types> > ppos_;
				boost::shared_ptr<position_interface<types> > mpos_;
			public:
				bf_buffer()
					: pmemory_(boost::make_shared<memory_type>())
					, mmemory_(boost::make_shared<memory_type>())
					, ppos_(boost::make_shared<position_type>(pmemory_, position_tags::ppos))
					, mpos_(boost::make_shared<position_type>(mmemory_, position_tags::mpos))
				{}
			public:
				virtual std::auto_ptr<buffer_interface> clone() {
					std::auto_ptr<buffer_interface> p(new bf_buffer(*this));
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

#endif	// #ifndef SPRIG_BRAIN_F_CK_BUFFER_HPP
