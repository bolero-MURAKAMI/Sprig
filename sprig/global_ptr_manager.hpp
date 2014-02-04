/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_GLOBAL_PTR_MANAGER_HPP
#define SPRIG_GLOBAL_PTR_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <sprig/singleton.hpp>

namespace sprig {
	//
	// global_ptr_manager
	//
	class global_ptr_manager
		: public sprig::singleton<global_ptr_manager>
	{
		SPRIG_FRIEND_SINGLETON(global_ptr_manager);
	private:
		typedef boost::shared_ptr<void> ptr_type;
		typedef int count_type;
		typedef std::pair<ptr_type, count_type> element_type;
		typedef std::vector<element_type> container_type;
	private:
		container_type container_;
	private:
		global_ptr_manager() {}
		~global_ptr_manager() {}
	private:
		container_type::iterator find(void* ptr) {
			container_type::iterator i = container_.begin();
			container_type::iterator last = container_.end();
			for (; i != last; ++i) {
				if (i->first.get() == ptr)
					break;
			}
			return i;
		}
		container_type::const_iterator find(void* ptr) const {
			container_type::const_iterator i = container_.begin();
			container_type::const_iterator last = container_.end();
			for (; i != last; ++i) {
				if (i->first.get() == ptr)
					break;
			}
			return i;
		}
	public:
		template<typename T>
		bool add_ref(T* ptr) {
			if (!ptr)
				return false;
			container_type::iterator i = find(ptr);
			if (i != container_.end()) {
				++i->second;
			} else {
				ptr_type ensured(ptr);
				container_.push_back(element_type(ensured, 1));
			}
			return true;
		}
		template<typename T>
		bool release(T* ptr) {
			if (!ptr)
				return false;
			container_type::iterator i = find(ptr);
			if (i != container_.end() && !--i->second) {
				container_.erase(i);
				return true;
			}
			return false;
		}
		template<typename T>
		bool exist(T* ptr) const {
			return ptr && find(ptr) != container_.end();
		}
	};
} // namespace sprig

#endif	// #ifndef SPRIG_GLOBAL_PTR_MANAGER_HPP
