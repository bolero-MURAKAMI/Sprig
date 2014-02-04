/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_XML_HPP
#define SPRIG_XML_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_ast.hpp>

//
// SPRIG_XML_GRAMMER_RULE_TYPE
//
#define SPRIG_XML_GRAMMER_RULE_TYPE(RULE_INDEX) \
	boost::spirit::classic::rule<Scanner, boost::spirit::classic::parser_tag<RULE_INDEX> >
//
// SPRIG_XML_GRAMMER_RULE_DECLARE
//
#define SPRIG_XML_GRAMMER_RULE_DECLARE(RULE_NAME, RULE_INDEX) \
	SPRIG_XML_GRAMMER_RULE_TYPE(RULE_INDEX) RULE_NAME

namespace sprig {
	//
	// xml_grammar
	//
	class xml_grammar
		: public boost::spirit::classic::grammar<xml_grammar>
	{
	public:
		enum rule_index {
			document = 1,
			S = 3,
			Name = 5,
			AttValue = 10,
			CharData = 14,
			Comment = 15,
			Eq = 25,
			Misc = 27,
			element = 39,
			STag = 40,
			Attribute = 41,
			ETag = 42,
			content = 43,
			EmptyElemTag = 44,
			Reference = 67,
			EntityRef = 68,
		};
	public:
		template<typename Scanner>
		class definition {
		private:
			SPRIG_XML_GRAMMER_RULE_DECLARE(document_, document);
			SPRIG_XML_GRAMMER_RULE_DECLARE(S_, S);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Name_, xml_grammar::Name);
			SPRIG_XML_GRAMMER_RULE_DECLARE(AttValue_, AttValue);
			SPRIG_XML_GRAMMER_RULE_DECLARE(CharData_, CharData);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Comment_, Comment);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Eq_, Eq);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Misc_, Misc);
			SPRIG_XML_GRAMMER_RULE_DECLARE(element_, element);
			SPRIG_XML_GRAMMER_RULE_DECLARE(STag_, STag);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Attribute_, Attribute);
			SPRIG_XML_GRAMMER_RULE_DECLARE(ETag_, ETag);
			SPRIG_XML_GRAMMER_RULE_DECLARE(content_, content);
			SPRIG_XML_GRAMMER_RULE_DECLARE(EmptyElemTag_, EmptyElemTag);
			SPRIG_XML_GRAMMER_RULE_DECLARE(Reference_, Reference);
			SPRIG_XML_GRAMMER_RULE_DECLARE(EntityRef_, EntityRef);
		public:
			definition(xml_grammar const&) {
				using namespace boost::spirit::classic;
				document_ = no_node_d[*Misc_] >> element_ >> no_node_d[*Misc_];
				S_ =+space_p;
				Name_ = leaf_node_d[
					(alpha_p | '_' | ':')
					>> *(alnum_p | '.' | '-' | '_' | ':')
					];
				AttValue_
					= leaf_node_d['\"' >> *((anychar_p - (ch_p('<') | '&' | '\"')) | Reference_) >> '\"']
					| leaf_node_d['\'' >> *((anychar_p - (ch_p('<') | '&' | '\'')) | Reference_) >> '\'']
					;
				CharData_ = leaf_node_d[
					*(anychar_p - (ch_p('<') | '&')) - (*(anychar_p - (ch_p('<') | '&')) >> "]]>" >> *(anychar_p - (ch_p('<') | '&')))
					];
				Comment_ = "<!--" >> *((anychar_p - '-') | ('-' >> (anychar_p - '-'))) >> "-->";
				Eq_ = !S_ >> '=' >> !S_;
				Misc_ = Comment_ | S_;
				element_ = EmptyElemTag_ | (STag_ >> content_ >> no_node_d[ETag_]);
				STag_ = no_node_d[ch_p('<')] >> Name_ >> *(no_node_d[S_] >> Attribute_) >> no_node_d[!S_ >> '>'];
				Attribute_ = Name_ >> no_node_d[Eq_] >> AttValue_;
				ETag_ = no_node_d[str_p("</")] >> Name_ >> no_node_d[!S_ >> '>'];
				content_
					= (no_node_d[!S_] >> !CharData_)
					>> *((element_ | Reference_ | no_node_d[Comment_]) >> (no_node_d[*S_] >> !CharData_))
					>> no_node_d[*S_]
					;
				EmptyElemTag_ = no_node_d[ch_p('<')] >> Name_ >> *(no_node_d[S_] >> Attribute_) >> no_node_d[!S_ >> str_p("/>")];
				Reference_ = EntityRef_;
				EntityRef_ = str_p("&amp;") | "&lt;" | "&gt;" | "&quot;";
			}
			SPRIG_XML_GRAMMER_RULE_TYPE(document) const& start() const {
				return document_;
			}
		};
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_XML_HPP
