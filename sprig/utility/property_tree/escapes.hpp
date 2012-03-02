#ifndef SPRIG_UTILITY_PROPERTY_TREE_ESCAPES_HPP
#define SPRIG_UTILITY_PROPERTY_TREE_ESCAPES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace sprig {
	//
	// create_escapes
	//
	template<typename Iterator>
	SPRIG_INLINE std::basic_string<typename boost::iterator_value<Iterator>::type> create_escapes(
		Iterator first,
		Iterator last
		)
	{
		typedef typename boost::iterator_value<Iterator>::type value_type;
		typedef std::basic_string<value_type> string_type;
		return boost::property_tree::info_parser::create_escapes(string_type(first, last));
	}
	template<typename Range>
	SPRIG_INLINE std::basic_string<typename boost::range_value<Range>::type> create_escapes(
		Range const& range
		)
	{
		return create_escapes(boost::begin(range), boost::end(range));
	}
	template<typename Char>
	SPRIG_INLINE std::basic_string<Char> create_escapes(
		std::basic_string<Char> const& s
		)
	{
		return boost::property_tree::info_parser::create_escapes(s);
	}
	//
	// expand_escapes
	//
	template<typename Iterator>
	SPRIG_INLINE std::basic_string<typename boost::iterator_value<Iterator>::type> expand_escapes(
		Iterator first,
		Iterator last
		)
	{
		typedef typename boost::iterator_value<Iterator>::type value_type;
		typedef std::basic_string<value_type> string_type;
		return boost::property_tree::info_parser::expand_escapes(first, last);
	}
	template<typename Range>
	SPRIG_INLINE std::basic_string<typename boost::range_value<Range>::type> expand_escapes(
		Range const& range
		)
	{
		return expand_escapes(boost::begin(range), boost::end(range));
	}
	//
	// create_escapes_ptree
	//
	template<typename Ptree>
	SPRIG_INLINE void create_escapes_ptree(Ptree& pt) {
		BOOST_FOREACH(typename Ptree::value_type& e, pt) {
			create_escapes_ptree(e.second);
		}
		pt.data() = create_escapes(pt.data());
	}
	//
	// expand_escapes_ptree
	//
	template<typename Ptree>
	SPRIG_INLINE void expand_escapes_ptree(Ptree& pt) {
		BOOST_FOREACH(typename Ptree::value_type& e, pt) {
			expand_escapes_ptree(e.second);
		}
		pt.data() = expand_escapes(pt.data());
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_PROPERTY_TREE_ESCAPES_HPP
