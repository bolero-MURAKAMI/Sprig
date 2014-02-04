/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_PROPERTY_TREE_XML_HPP
#define SPRIG_UTILITY_PROPERTY_TREE_XML_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/foreach.hpp>
#include <sprig/split_literal.hpp>

namespace sprig {
	namespace ptree_detail {
		//
		// xmlcomment
		// xmltext
		// xmlattr
		//
		SPRIG_SPLIT_LITERAL_STRING_DECL(xmlcomment, "<xmlcomment>");
		SPRIG_SPLIT_LITERAL_STRING_DECL(xmltext, "<xmltext>");
		SPRIG_SPLIT_LITERAL_STRING_DECL(xmlattr, "<xmlattr>");
	}	// namespace ptree_detail
	//
	// trim_xml
	//
	template<typename Ptree>
	SPRIG_INLINE void trim_xml(Ptree& pt) {
		typedef typename Ptree::key_type::value_type char_type;
		pt.erase(get_literal<ptree_detail::xmlcomment, char_type>());
		if (pt.size() == 1 && pt.count(get_literal<ptree_detail::xmltext, char_type>())) {
			pt.data() = pt.back().second.data();
		}
		pt.erase(get_literal<ptree_detail::xmltext, char_type>());
		BOOST_FOREACH(typename Ptree::value_type& e, pt) {
			trim_xml(e.second);
		}
		if (!pt.empty()) {
			pt.data() = typename Ptree::data_type();
		}
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_PROPERTY_TREE_XML_HPP
