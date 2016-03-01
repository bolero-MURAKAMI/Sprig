/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_PROPERTY_TREE_INI_HPP
#define SPRIG_UTILITY_PROPERTY_TREE_INI_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/foreach.hpp>
#include <sprig/split_literal.hpp>

namespace sprig {
	namespace ptree_detail {
		//
		// period
		//
		SPRIG_SPLIT_LITERAL_CHAR_DECL(period, '.');
		//
		// format_to_ini_impl
		//
		template<typename Ptree>
		SPRIG_INLINE void format_to_ini_impl(
			Ptree& root,
			typename Ptree::key_type::value_type separator,
			Ptree const& pt,
			typename Ptree::key_type const& key = typename Ptree::key_type()
			)
		{
			typename Ptree::key_type next_key = key;
			next_key.push_back(separator);
			BOOST_FOREACH(typename Ptree::value_type const& e, pt) {
				if (e.second.empty()) {
					typename Ptree::assoc_iterator found = root.find(key);
					if (found == root.not_found()) {
						root.push_back(typename Ptree::value_type(key, Ptree()));
						found = root.find(key);
					}
					found->second.push_back(e);
				} else {
					format_to_ini_impl(root, separator, e.second, next_key + e.first);
				}
			}
		}
	}	// namespace ptree_detail
	//
	// format_to_ini
	//
	template<typename Ptree>
	SPRIG_INLINE Ptree format_to_ini(
		Ptree const& pt,
		typename Ptree::key_type::value_type separator
			= apply_literal<ptree_detail::period, typename Ptree::key_type::value_type>::value
		)
	{
		Ptree root;
		BOOST_FOREACH(typename Ptree::value_type const& e, pt) {
			if (e.second.empty()) {
				root.push_back(e);
			} else {
				ptree_detail::format_to_ini_impl(root, separator, e.second, e.first);
			}
		}
		return root;
	}
	//
	// format_from_ini
	//
	template<typename Ptree>
	SPRIG_INLINE Ptree format_from_ini(
		Ptree const& pt,
		typename Ptree::key_type::value_type separator
			= apply_literal<ptree_detail::period, typename Ptree::key_type::value_type>::value
		)
	{
		Ptree root;
		BOOST_FOREACH(typename Ptree::value_type const& e, pt) {
			if (e.second.empty()) {
				root.push_back(e);
			} else {
				root.put_child(typename Ptree::path_type(e.first, separator), e.second);
			}
		}
		return root;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_PROPERTY_TREE_INI_HPP
