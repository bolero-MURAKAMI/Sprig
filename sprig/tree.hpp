#ifndef SPRIG_TREE_HPP
#define SPRIG_TREE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <deque>
#include <boost/variant.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/optional/optional.hpp>
#include <boost/mpl/void.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/utility/utility.hpp>

namespace sprig {
	//
	// tree_traits_detail
	//
	template<typename Option = empty_class>
	struct tree_traits_detail {
		template<typename T>
		struct element {
			typedef T type;
		};
		template<typename T>
		struct container {
			typedef std::deque<T> type;
		};
		template<typename T = boost::mpl::void_>
		struct option {
			typedef Option type;
		};
		template<typename T, typename U>
		struct variant {
			typedef boost::variant<T, U> type;
		};
		template<typename T>
		struct recursive {
			typedef boost::recursive_wrapper<T> type;
		};
	};
	//
	// tree_traits
	//
	template<typename Detail = tree_traits_detail<> >
	struct tree_traits {
		template<typename Leaf>
		struct leaf {
			typedef typename Detail::template element<Leaf>::type type;
		};
		template<typename Node>
		struct node {
			typedef typename Detail::template container<Node>::type type;
		};
		template<typename Node>
		struct recursive_node {
			typedef typename Detail::template recursive<
				typename node<Node>::type
			>::type type;
		};
		template<typename T = boost::mpl::void_>
		struct option {
			typedef typename Detail::template option<>::type type;
		};
		template<typename Node, typename Leaf>
		struct variant {
			typedef typename Detail::template variant<
				typename recursive_node<Node>::type,
				typename leaf<Leaf>::type
			>::type type;
		};
	};
	//
	// tree
	//
	template<typename T, typename Traits = tree_traits<> >
	class tree {
	private:
	public:
		typedef tree this_type;
	public:
		typedef T element_type;
		typedef Traits traits_type;
		typedef typename traits_type::template leaf<element_type>::type leaf_type;
		typedef typename traits_type::template recursive_node<this_type>::type recursive_node_type;
		typedef typename traits_type::template option<>::type option_type;
		typedef typename traits_type::template variant<this_type, element_type>::type variant_type;
		typedef boost::compressed_pair<variant_type, option_type> pair_type;
		typedef pair_type value_type;
	public:
		template<typename Dummy = boost::mpl::void_>
		struct node {
			typedef typename traits_type::template node<this_type>::type type;
		};
	private:
		value_type value_;
	private:
		template<typename Param>
		static variant_type to_value_param(Param const& value) {
			return variant_type(value);
		}
	public:
		tree() {}
		tree(this_type const& other)
			: value_(other.value_)
		{}
		explicit tree(option_type const& option)
			: value_(option)
		{}
		explicit tree(typename node<>::type const& value)
			: value_(to_value_param(value))
		{}
		explicit tree(typename node<>::type const& value, option_type const& option)
			: value_(to_value_param(value), option)
		{}
		explicit tree(leaf_type const& value)
			: value_(to_value_param(value))
		{}
		explicit tree(leaf_type const& value, option_type const& option)
			: value_(to_value_param(value), option)
		{}
		this_type& operator=(this_type rhs) {
			assign(rhs);
			return *this;
		}
		this_type& operator=(typename node<>::type const& rhs) {
			assign(rhs);
			return *this;
		}
		this_type& operator=(leaf_type const& rhs) {
			assign(rhs);
			return *this;
		}
		void swap(this_type& rhs) {
			boost::swap(value_, rhs.value_);
		}
		void assign(this_type other) {
			swap(other);
		}
		void assign(typename node<>::type const& value) {
			assign_node(value);
		}
		void assign(leaf_type const& value) {
			assign_leaf(value);
		}
		void assign_node(typename node<>::type const& value) {
			variant() = value;
		}
		void assign_leaf(leaf_type const& value) {
			variant() = value;
		}
		bool empty() const {
			return is_node() && get_node().empty();
		}
		bool is_node() const {
			return variant().which() == 0;
		}
		bool is_leaf() const {
			return variant().which() == 1;
		}
		value_type const& get() const {
			return value_;
		}
		value_type& get() {
			return value_;
		}
		value_type const& pair() const {
			return get();
		}
		value_type& pair() {
			return get();
		}
		variant_type const& variant() const {
			return pair().first();
		}
		variant_type& variant() {
			return pair().first();
		}
		option_type const& option() const {
			return pair().second();
		}
		option_type& option() {
			return pair().second();
		}
		typename node<>::type const& get_node() const {
			return boost::get<typename node<>::type>(variant());
		}
		typename node<>::type& get_node() {
			return boost::get<typename node<>::type>(variant());
		}
		leaf_type const& get_leaf() const {
			return boost::get<leaf_type>(variant());
		}
		leaf_type& get_leaf() {
			return boost::get<leaf_type>(variant());
		}
		void clear() {
			value_.first() = to_value_param(typename node<>::type());
		}
	};
	template<typename T, typename Traits>
	SPRIG_INLINE void swap(
		tree<T, Traits>& lhs,
		tree<T, Traits>& rhs
		)
	{
		lhs.swap(rhs);
	}
	//
	// for_each_tree_visitor
	//
	template<
		typename T,
		typename LeafFunc,
		typename NodeBeforeFunc = do_nothing,
		typename NodeArterFunc = do_nothing
	>
	class for_each_tree_visitor
		: public boost::static_visitor<void>
	{
	public:
		typedef T tree_type;
		typedef LeafFunc leaf_func_type;
		typedef NodeBeforeFunc node_before_func_type;
		typedef NodeArterFunc node_after_func_type;
	public:
		leaf_func_type leaf_func;
		node_before_func_type node_before_func;
		node_after_func_type node_after_func;
	public:
		for_each_tree_visitor() {}
		explicit for_each_tree_visitor(
			leaf_func_type const& leaf_init,
			node_before_func_type const& node_before_init = node_before_func_type(),
			node_after_func_type const& node_after_init = node_after_func_type()
			)
			: leaf_func(leaf_init)
			, node_before_func(node_before_init)
			, node_after_func(node_after_init)
		{}
		void operator()(typename tree_type::leaf_type const& leaf) {
			leaf_func(leaf);
		}
		void operator()(typename tree_type::template node<>::type const& node) {
			typedef typename T::template node<>::type::const_iterator const_iterator;
			for(const_iterator i = node.begin(), last = node.end(); i != last; ++i) {
				node_bofore_func(*i);
				if (!i->empty())
					boost::apply_visitor(*this, *i);
				node_after_func(*i);
			}
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_TREE_HPP
