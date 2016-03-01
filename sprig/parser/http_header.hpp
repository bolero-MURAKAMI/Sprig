/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PARSER_HTTP_HEADER_HPP
#define SPRIG_PARSER_HTTP_HEADER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <sprig/tmp/rebind_pair.hpp>
#include <sprig/fusion/linear_value_at.hpp>

namespace sprig {
	namespace parser {
		//
		// http_response_line
		//
		template<
			typename Iterator,
			typename Tuple
		>
		class http_response_line
			: public boost::spirit::qi::grammar<Iterator, Tuple ()>
		{
		public:
			typedef Iterator iterator_type;
			typedef Tuple tuple_type;
			typedef typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<tuple_type, 0>::type
			>::type http_version_type;
			typedef typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<tuple_type, 1>::type
			>::type status_code_type;
			typedef typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<tuple_type, 2>::type
			>::type reason_phrase_type;
		private:
			boost::spirit::qi::rule<iterator_type, tuple_type ()> response_line_;
			boost::spirit::qi::rule<iterator_type, http_version_type ()> http_version_;
			boost::spirit::qi::rule<iterator_type, status_code_type ()> status_code_;
			boost::spirit::qi::rule<iterator_type, reason_phrase_type ()> reason_phrase_;
		public:
			explicit http_response_line(bool parsing_crlf = true)
				: http_response_line::base_type(response_line_)
			{
				if (parsing_crlf) {
					response_line_ = http_version_ >> ' ' >> status_code_ >> ' ' >> reason_phrase_
						>> boost::spirit::qi::lit("\r\n")
						;
				} else {
					response_line_ = http_version_ >> ' ' >> status_code_ >> ' ' >> reason_phrase_;
				}
				http_version_ = boost::spirit::qi::raw[
					boost::spirit::qi::lit("HTTP/")
					>> +boost::spirit::qi::digit >> '.' >> +boost::spirit::qi::digit
					];
				status_code_ = boost::spirit::qi::digit >> boost::spirit::qi::digit >> boost::spirit::qi::digit;
				reason_phrase_ = boost::spirit::qi::raw[
					+(boost::spirit::qi::char_ - boost::spirit::qi::lit("\r\n"))
					];
			}
		};
		//
		// http_header
		//
		template<
			typename Iterator,
			typename Map,
			typename Pair = typename sprig::tmp::rebind_pair<
				typename Map::value_type,
				typename boost::remove_const<
					typename sprig::fusion::result_of::linear_value_at_c<typename Map::value_type, 0>::type
				>::type,
				typename boost::remove_const<
					typename sprig::fusion::result_of::linear_value_at_c<typename Map::value_type, 1>::type
				>::type
			>::type,
			typename Key = typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<Pair, 0>::type
			>::type,
			typename Mapped = typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<Pair, 1>::type
			>::type
		>
		class http_header
			: public boost::spirit::qi::grammar<Iterator, Map ()>
		{
		public:
			typedef Iterator iterator_type;
			typedef Map map_type;
			typedef Pair pair_type;
			typedef Key key_type;
			typedef Mapped mapped_type;
		private:
			boost::spirit::qi::rule<iterator_type, map_type ()> headers_;
			boost::spirit::qi::rule<iterator_type, pair_type ()> message_header_;
			boost::spirit::qi::rule<iterator_type, key_type ()> field_name_;
			boost::spirit::qi::rule<iterator_type, mapped_type ()> field_value_;
		public:
			explicit http_header(bool parsing_last_crlf = true, bool omit_first_sp = true)
				: http_header::base_type(headers_)
			{
				if (parsing_last_crlf) {
					headers_ = *(
						message_header_ >> boost::spirit::qi::lit("\r\n")
						)
						>> boost::spirit::qi::lit("\r\n")
						;
				} else {
					headers_ = *(
						message_header_ >> boost::spirit::qi::lit("\r\n")
						);
				}
				message_header_ = field_name_ >> ':' >> -field_value_;
				field_name_ = +(
					boost::spirit::qi::char_ - (
						boost::spirit::qi::char_('\x00', '\x1f')
						| '\x7f'
						| boost::spirit::qi::char_('\x80', '\xff')
						| '(' | ')'
						| '<' | '>'
						| '@'
						| ',' | ';' | ':'
						| '\\' | '\"' | '/'
						| '[' | ']'
						| '?' | '='
						| '{' | '}'
						| ' ' | '\t'
						)
					);
				if (omit_first_sp) {
					field_value_ = boost::spirit::qi::omit[
							*(
								-boost::spirit::qi::lit("\r\n")
								>> +(boost::spirit::qi::lit(' ') | '\t')
							)
						]
						>> boost::spirit::qi::raw[
							*(
								(
									-boost::spirit::qi::lit("\r\n")
									>> +(boost::spirit::qi::lit(' ') | '\t')
									)
								| boost::spirit::qi::char_('\x20', '\x7e')
								| boost::spirit::qi::char_('\x80', '\xff')
								)
							];
				} else {
					field_value_ = boost::spirit::qi::raw[
						*(
							(
								-boost::spirit::qi::lit("\r\n")
								>> +(boost::spirit::qi::lit(' ') | '\t')
								)
							| boost::spirit::qi::char_('\x20', '\x7e')
							| boost::spirit::qi::char_('\x80', '\xff')
							)
						];
				}
			}
		};
	}	// namespace parser
}	// namespace sprig

#endif	// #ifndef SPRIG_PARSER_HTTP_HEADER_HPP
