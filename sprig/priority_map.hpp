/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PRIORITY_MAP_HPP
#define SPRIG_PRIORITY_MAP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/functional.hpp>

namespace sprig {
	//
	// priority_maps
	//
	struct priority_maps {
	public:
		//
		// tags
		//
		struct key_tag {};
		struct priority_tag {};
	};

	//
	// priority_map_element
	//
	template<
		typename Key,
		typename Priority,
		typename Mapped
	>
	class priority_map_element {
	public:
		typedef Key key_type;
		typedef Priority priority_type;
		typedef Mapped mapped_type;
	private:
		key_type key_;
		priority_type priority_;
		mutable mapped_type mapped_;
	public:
		priority_map_element()
			: key_()
			, priority_()
			, mapped_()
		{}
		priority_map_element(
			typename sprig::call_traits<key_type>::param_type key,
			typename sprig::call_traits<priority_type>::param_type priority,
			typename sprig::call_traits<mapped_type>::param_type mapped
			)
			: key_(key)
			, priority_(priority)
			, mapped_(mapped)
		{}
		mapped_type& ref_mapped() const {
			return mapped_;
		}
		typename sprig::call_traits<key_type>::getter_type get_key() const {
			return key_;
		}
		void set_key(typename sprig::call_traits<key_type>::param_type v) {
			key_ = v;
		}
		typename sprig::call_traits<priority_type>::getter_type get_priority() const {
			return priority_;
		}
		void set_priority(typename sprig::call_traits<priority_type>::param_type v) {
			priority_ = v;
		}
		typename sprig::call_traits<mapped_type>::getter_type get_mapped() const {
			return mapped_;
		}
		void set_mapped(typename sprig::call_traits<mapped_type>::param_type v) {
			mapped_ = v;
		}
	};

	//
	// priority_map_comparator
	//
	template<
		typename Value,
		typename KeyComparator = sprig::less<typename Value::key_type>
	>
	struct priority_map_comparator {
	public:
		typedef Value value_type;
		typedef KeyComparator key_comparator_type;
		typedef typename value_type::key_type key_type;
		typedef typename value_type::priority_type priority_type;
		typedef typename value_type::mapped_type mapped_type;
	public:
		bool operator()(
			typename sprig::call_traits<value_type>::param_type lhs,
			typename sprig::call_traits<value_type>::param_type rhs
			) const
		{
			return key_comparator_type()(lhs.get_key(), rhs.get_key());
		}
		bool operator()(
			typename sprig::call_traits<value_type>::param_type lhs,
			typename sprig::call_traits<key_type>::param_type rhs
			) const
		{
			return key_comparator_type()(lhs.get_key(), rhs);
		}
		bool operator()(
			typename sprig::call_traits<key_type>::param_type lhs,
			typename sprig::call_traits<value_type>::param_type rhs
			) const
		{
			return key_comparator_type()(lhs, rhs.get_key());
		}
		bool operator()(
			typename sprig::call_traits<key_type>::param_type lhs,
			typename sprig::call_traits<key_type>::param_type rhs
			) const
		{
			return key_comparator_type()(lhs, rhs);
		}
	};

	//
	// priority_map_defs
	//
	template<
		typename Key,
		typename Priority,
		typename Mapped,
		typename Value = priority_map_element<Key, Priority, Mapped>,
		typename KeyComparator = sprig::less<Key>,
		typename Comparator = priority_map_comparator<Value, KeyComparator>,
		typename KeyTag = priority_maps::key_tag,
		typename PriorityTag = priority_maps::priority_tag
	>
	struct priority_map_defs {
	public:
		typedef Key key_type;
		typedef Priority priority_type;
		typedef Mapped mapped_type;
		typedef Value value_type;
		typedef KeyComparator key_comparator_type;
		typedef Comparator comparator_type;
		typedef KeyTag key_tag_type;
		typedef PriorityTag priority_tag_type;
		typedef boost::multi_index_container<
			value_type,
			boost::multi_index::indexed_by<
				boost::multi_index::ordered_unique<
					boost::multi_index::tag<key_tag_type>,
					boost::multi_index::const_mem_fun<
						value_type,
						typename sprig::call_traits<key_type>::getter_type,
						&value_type::get_key
					>,
					comparator_type
				>,
				boost::multi_index::ordered_non_unique<
					boost::multi_index::tag<priority_tag_type>,
					boost::multi_index::const_mem_fun<
						value_type,
						typename sprig::call_traits<priority_type>::getter_type,
						&value_type::get_priority
					>
				>
			>
		> type;
	};

	//
	// priority_modifier
	//
	template<typename Defs>
	class priority_modifier {
	public:
		typedef Defs defs_type;
	private:
		typename defs_type::priority_type priority_;
	public:
		priority_modifier(typename sprig::call_traits<typename defs_type::priority_type>::param_type priority)
			: priority_(priority)
		{}
		void operator()(typename defs_type::value_type& element) const {
			element.set_priority(priority_);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_PRIORITY_MAP_HPP
