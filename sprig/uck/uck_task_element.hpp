/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_UCK_TASK_ELEMENT_HPP
#define SPRIG_UCK_UCK_TASK_ELEMENT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <boost/utility/value_init.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>

namespace sprig {
	namespace uck {
		//
		// uck_task_element
		//
		template<typename Traits = traits<> >
		struct uck_task_element {
		public:
			typedef types<Traits> types_type;
			typedef int ptr_type;
		private:
			ptr_type pptr_;
			ptr_type mptr_;
			typename types_type::bin_type work_;
		public:
			uck_task_element() {}
			uck_task_element(uck_task<Traits> const& task, std::size_t bytes)
				: pptr_(task.pptr())
				, mptr_(task.mptr())
				, work_(bytes)
			{
				std::fill(work_.begin(), work_.end(), boost::value_initialized<typename types_type::byte_type>());
			}
			ptr_type const& pptr() const {
				return pptr_;
			}
			ptr_type const& mptr() const {
				return mptr_;
			}
			typename types_type::bin_type const& work() const {
				return work_;
			}
			ptr_type& pptr() {
				return pptr_;
			}
			ptr_type& mptr() {
				return mptr_;
			}
			typename types_type::bin_type& work() {
				return work_;
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_UCK_TASK_ELEMENT_HPP
