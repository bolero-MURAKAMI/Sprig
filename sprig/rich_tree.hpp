/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RICH_TREE_HPP
#define SPRIG_RICH_TREE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <map>
#include <string>
#include <functional>
#include <utility>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/foreach.hpp>
#include <sprig/tree.hpp>
#include <sprig/utility/utility.hpp>

namespace sprig {
	//
	// rich_tree_traits_detail
	//
	template<typename Name, typename AttValue>
	struct rich_tree_traits_detail {
		typedef tree_traits_detail<
			boost::compressed_pair<
				Name,
				std::map<Name, AttValue>
			>
		> type;
	};
	//
	// rich_tree_traits
	//
	template<typename Name, typename AttValue>
	struct rich_tree_traits {
		typedef tree_traits<typename rich_tree_traits_detail<Name, AttValue>::type> type;
	};
	//
	// rich_tree
	//
	template<typename Name, typename AttValue>
	struct rich_tree {
		typedef tree<Name, typename rich_tree_traits<Name, AttValue>::type> type;
	};
	//
	// typedef rich_string_tree
	//
	typedef rich_tree<std::string, std::string>::type rich_string_tree;
	typedef rich_tree<std::wstring, std::wstring>::type rich_wstring_tree;
	//
	// rich_tree_name_equal_to
	//
	template<typename Tree>
	struct rich_tree_name_equal_to
		: std::binary_function<Tree, Tree, bool>
	{
	public:
		typedef std::binary_function<Tree, Tree, bool> function_type;
		typedef typename function_type::first_argument_type first_argument_type;
		typedef typename function_type::second_argument_type second_argument_type;
		typedef typename function_type::result_type result_type;
	public:
		result_type operator()(first_argument_type const& arg1, second_argument_type const& arg2) const {
			return arg1.option().first() == arg2.option().first();
		}
	};
	//
	// rich_tree_name_not_equal_to
	//
	template<typename Tree>
	struct rich_tree_name_not_equal_to
		: std::binary_function<Tree, Tree, bool>
	{
	public:
		typedef std::binary_function<Tree, Tree, bool> function_type;
		typedef typename function_type::first_argument_type first_argument_type;
		typedef typename function_type::second_argument_type second_argument_type;
		typedef typename function_type::result_type result_type;
	public:
		result_type operator()(first_argument_type const& arg1, second_argument_type const& arg2) const {
			return arg1.option().first() != arg2.option().first();
		}
	};
	//
	// output_rich_string_tree_visitor
	//
	template<typename Tree, typename Stream = std::ostream>
	struct output_rich_string_tree_visitor
		: public boost::static_visitor<void>
	{
	public:
		typedef Tree tree_type;
		typedef Stream stream_type;
		typedef typename tree_type::template node<>::type node_type;
		typedef typename tree_type::leaf_type leaf_type;
		typedef typename tree_type::option_type option_type;
	private:
		stream_type& stream_;
		std::size_t tab_;
		std::string tab_unit_;
	public:
		explicit output_rich_string_tree_visitor(stream_type& stream)
			: stream_(stream)
			, tab_(0)
			, tab_unit_("    ")
		{}
		output_rich_string_tree_visitor(stream_type& stream, std::size_t init)
			: stream_(stream)
			, tab_(init)
			, tab_unit_("    ")
		{}
		output_rich_string_tree_visitor(stream_type& stream, std::size_t init, std::string const& unit)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(unit)
		{}
		std::string tab() const {
			return multipries<std::string>(tab_unit_, tab_);
		}
		void output(tree_type const& tree) {
			stream_ << tab() << "<" << tree.option().first();
			BOOST_FOREACH(typename option_type::second_type::value_type const& e, tree.option().second()) {
				stream_ << " " << e.first << "=\"" << e.second << "\"";
			}
			if (tree.empty()) {
				stream_ << "/>\n";
				return;
			}
			stream_ << (tree.is_node() ? ">\n" : ">");
			++tab_;
			boost::apply_visitor(*this, tree.variant());
			--tab_;
			if (tree.is_node())
				stream_ << tab();
			stream_ << "</" << tree.option().first() << ">\n";
		}
		void operator()(node_type const& node) {
			BOOST_FOREACH(typename node_type::value_type const& e, node) {
				output(e);
			}
		}
		void operator()(leaf_type const& leaf) const {
			stream_ << leaf;
		}
		stream_type& stream() {
			return stream_;
		}
	};
	//
	// output_rich_wstring_tree_visitor
	//
	template<typename Tree, typename Stream = std::wostream>
	struct output_rich_wstring_tree_visitor
		: public boost::static_visitor<void>
	{
	public:
		typedef Tree tree_type;
		typedef Stream stream_type;
		typedef typename tree_type::template node<>::type node_type;
		typedef typename tree_type::leaf_type leaf_type;
		typedef typename tree_type::option_type option_type;
	private:
		stream_type& stream_;
		std::size_t tab_;
		std::wstring tab_unit_;
	public:
		explicit output_rich_wstring_tree_visitor(stream_type& stream)
			: stream_(stream)
			, tab_(0)
			, tab_unit_(L"    ")
		{}
		output_rich_wstring_tree_visitor(stream_type& stream, std::size_t init)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(L"    ")
		{}
		output_rich_wstring_tree_visitor(stream_type& stream, std::size_t init, std::string const& unit)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(unit)
		{}
		std::wstring tab() const {
			return multipries<std::wstring>(tab_unit_, tab_);
		}
		void output(tree_type const& tree) {
			stream_ << tab() << L"<" << tree.option().first();
			BOOST_FOREACH(typename option_type::second_type::value_type const& e, tree.option().second()) {
				stream_ << L" " << e.first << L"=\"" << e.second << L"\"";
			}
			if (tree.empty()) {
				stream_ << L"/>\n";
				return;
			}
			stream_ << (tree.is_node() ? L">\n" : L">");
			++tab_;
			boost::apply_visitor(*this, tree.variant());
			--tab_;
			if (tree.is_node())
				stream_ << tab();
			stream_ << L"</" << tree.option().first() << L">\n";
		}
		void operator()(node_type const& node) {
			BOOST_FOREACH(typename node_type::value_type const& e, node) {
				output(e);
			}
		}
		void operator()(leaf_type const& leaf) const {
			stream_ << leaf;
		}
		stream_type& stream() {
			return stream_;
		}
	};

	//
	// construct_test_rich_string_tree
	//
	SPRIG_INLINE void construct_test_rich_string_tree(
		sprig::rich_string_tree& tree,
		std::size_t size,
		std::size_t index,
		std::size_t depth = 0,
		std::size_t current = 0
		)
	{
		typedef rich_string_tree tree_t;
		typedef tree_t::node<>::type node_t;
		typedef tree_t::leaf_type leaf_t;
		typedef tree_t::option_type option_t;
		tree.clear();
		tree.option().first() = option_t::first_type("node");
		tree.option().second().insert(
			option_t::second_type::value_type(
				option_t::second_type::value_type::first_type("depth"),
				option_t::second_type::value_type::second_type(boost::lexical_cast<option_t::second_type::value_type::second_type>(current))
				)
			);
		node_t& node(tree.get_node());
		++current;
		for (std::size_t i = 0; i < size; ++i) {
			node.push_back(tree_t());
			tree_t& child(node.at(i));
			if (i == index && depth > current) {
				construct_test_rich_string_tree(child, size, index, depth, current);
			} else {
				child.option().first() = option_t::first_type("leaf");
				child.assign_leaf(boost::lexical_cast<leaf_t>(i));
			}
		}
	}
	//
	// construct_test_rich_wstring_tree
	//
	SPRIG_INLINE void construct_test_rich_wstring_tree(
		sprig::rich_wstring_tree& tree,
		std::size_t size,
		std::size_t index,
		std::size_t depth = 0,
		std::size_t current = 0
		)
	{
		typedef rich_wstring_tree tree_t;
		typedef tree_t::node<>::type node_t;
		typedef tree_t::leaf_type leaf_t;
		typedef tree_t::option_type option_t;
		tree.clear();
		tree.option().first() = option_t::first_type(L"node");
		tree.option().second().insert(
			option_t::second_type::value_type(
				option_t::second_type::value_type::first_type(L"depth"),
				option_t::second_type::value_type::second_type(boost::lexical_cast<option_t::second_type::value_type::second_type>(current))
				)
			);
		node_t& node(tree.get_node());
		++current;
		for (std::size_t i = 0; i < size; ++i) {
			node.push_back(tree_t());
			tree_t& child(node.at(i));
			if (i == index && depth > current) {
				construct_test_rich_wstring_tree(child, size, index, depth, current);
			} else {
				child.option().first() = option_t::first_type(L"leaf");
				child.assign_leaf(boost::lexical_cast<leaf_t>(i));
			}
		}
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_RICH_TREE_HPP
