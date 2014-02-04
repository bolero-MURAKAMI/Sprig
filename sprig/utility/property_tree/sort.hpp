/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_PROPERTY_TREE_SORT_HPP
#define SPRIG_UTILITY_PROPERTY_TREE_SORT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <iterator>
#include <functional>
#include <boost/range.hpp>
#include <boost/next_prior.hpp>
#include <boost/foreach.hpp>
#include <sprig/split_join.hpp>

namespace sprig {
	//
	// stable_sort_ptree_compare
	//
	template<
		typename Ptree,
		typename KeyCompare = typename Ptree::key_compare
	>
	class stable_sort_ptree_compare
		: public std::binary_function<
			typename Ptree::value_type,
			typename Ptree::value_type,
			bool
		>
		, private KeyCompare
	{
	public:
		typedef Ptree ptree_type;
		typedef KeyCompare key_compare;
		typedef typename ptree_type::value_type value_type;
		typedef typename ptree_type::size_type size_type;
	public:
		explicit stable_sort_ptree_compare(
			key_compare key_comp = key_compare()
			)
			: key_compare(key_comp)
		{}
		bool operator()(
			value_type const& lhs,
			value_type const& rhs
			) const
		{
			return key_compare::operator()(lhs.first, rhs.first)
				|| !key_compare::operator()(rhs.first, lhs.first)
				&& sprig::integer_join<size_type>(
					boost::prior(
						boost::end(lhs.second.data()),
						static_cast<std::ptrdiff_t>(sizeof(size_type))
						)
					)
				< sprig::integer_join<size_type>(
					boost::prior(
						boost::end(rhs.second.data()),
						static_cast<std::ptrdiff_t>(sizeof(size_type))
						)
					)
				;
		}
	};
	//
	// stable_sort_ptree
	//
	template<typename Ptree>
	void stable_sort_ptree(Ptree& ptree) {
		typedef typename Ptree::size_type size_type;
		{
			size_type i = 0;
			BOOST_FOREACH(typename boost::range_reference<Ptree>::type e, ptree) {
				sprig::integer_split(i, std::back_inserter(e.second.data()));
				++i;
			}
		}
		ptree.sort(stable_sort_ptree_compare<Ptree>());
		BOOST_FOREACH(typename boost::range_reference<Ptree>::type e, ptree) {
			typename Ptree::data_type& data = e.second.data();
			data.erase(
				boost::prior(
					boost::end(data),
					static_cast<std::ptrdiff_t>(sizeof(size_type))
					),
				boost::end(data)
				);
		}
	}
	//
	// stable_sort_ptree
	//
	template<typename Ptree, typename KeyCompare>
	void stable_sort_ptree(Ptree& ptree, KeyCompare key_comp) {
		typedef typename Ptree::size_type size_type;
		{
			size_type i = 0;
			BOOST_FOREACH(typename boost::range_reference<Ptree>::type e, ptree) {
				sprig::integer_split(i, std::back_inserter(e.second.data()));
				++i;
			}
		}
		ptree.sort(stable_sort_ptree_compare<Ptree, KeyCompare>(key_comp));
		BOOST_FOREACH(typename boost::range_reference<Ptree>::type e, ptree) {
			typename Ptree::data_type& data = e.second.data();
			data.erase(
				boost::prior(
					boost::end(data),
					static_cast<std::ptrdiff_t>(sizeof(size_type))
					),
				boost::end(data)
				);
		}
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_PROPERTY_TREE_SORT_HPP
