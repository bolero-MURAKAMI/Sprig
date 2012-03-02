#ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_HPP
#define SPRIG_PROPERTY_TREE_HTML_PARSER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <clocale>
#include <iterator>
#include <string>
#include <locale>
#include <fstream>
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <sprig/external/htmlcxx/html/tree.hpp>
#include <sprig/external/htmlcxx/html/node.hpp>
#include <sprig/external/htmlcxx/html/parserdom.hpp>
#include <sprig/external/htmlcxx/html/utils.hpp>
#include <sprig/locale_saver.hpp>
#include <sprig/property_tree/html_parser_error.hpp>
#include <sprig/property_tree/html_parser_flags.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	namespace property_tree {
		namespace html_parser {
			namespace parser_detail {
				//
				// is_internal_implemented
				//
				template<typename Ptree>
				class is_internal_implemented
					: public boost::mpl::and_<
						boost::is_same<typename Ptree::key_type, std::string>,
						boost::is_same<typename Ptree::data_type, std::string>
					>
				{};
			}	// namespace parser_detail
			namespace parser_detail {
				//
				// read_html_impl_process
				//
				template<typename Ptree>
				SPRIG_INLINE void read_html_impl_process(
					tree<htmlcxx::HTML::Node>::sibling_iterator const& it,
					Ptree& pt,
					std::string const& filename,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					if (it->isTag()) {
						ptree_type next;
						{
							ptree_type attributes;
							if (it->text().size() > it->tagName().size() + 2) {
								it->parseAttributes();
							}
							for (std::map<std::string, std::string>::const_iterator attr = it->attributes().begin(), last = it->attributes().end(); attr != last; ++attr) {
								if (attr->first.empty()) {
									continue;
								}
								attributes.push_back(
									value_type(
										attr->first,
										ptree_type(attr->second)
										)
									);
							}
							if (!attributes.empty()) {
								next.push_back(
									value_type(
										"<xmlattr>",
										attributes
										)
									);
							}
						}
						for (tree<htmlcxx::HTML::Node>::sibling_iterator i = it.begin(), last = it.end(); i != last; ++i) {
							read_html_impl_process(i, next, filename, flags);
						}
						pt.push_back(
							value_type(
								it->tagName(),
								next
								)
							);
					} else if (it->isComment()) {
						if (!(flags & reader_flags::no_comments)) {
							if (it->text().size() >= 7) {
								pt.push_back(
									value_type(
										"<xmlcomment>",
										ptree_type(it->text().substr(4, it->text().size() - 7))
										)
									);
							}
						}
					} else {
						std::string text(
							flags & reader_flags::trim_whitespace
								? htmlcxx::HTML::single_blank(it->text())
								: it->text()
							);
						if (flags & reader_flags::no_concat_text) {
							if (!text.empty()) {
								pt.push_back(
									value_type(
										"<xmltext>",
										ptree_type(text)
										)
									);
							}
						} else {
							pt.data() += text;
						}
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_html_impl_process(
					tree<htmlcxx::HTML::Node>::sibling_iterator const& it,
					Ptree& pt,
					std::string const& filename,
					Converter converter,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					if (it->isTag()) {
						ptree_type next;
						{
							ptree_type attributes;
							if (it->text().size() > it->tagName().size() + 2) {
								it->parseAttributes();
							}
							for (std::map<std::string, std::string>::const_iterator attr = it->attributes().begin(), last = it->attributes().end(); attr != last; ++attr) {
								if (attr->first.empty()) {
									continue;
								}
								attributes.push_back(
									value_type(
										converter.from_str(attr->first),
										ptree_type(converter.from_str(attr->second))
										)
									);
							}
							if (!attributes.empty()) {
								next.push_back(
									value_type(
										converter.from_str("<xmlattr>"),
										attributes
										)
									);
							}
						}
						for (tree<htmlcxx::HTML::Node>::sibling_iterator i = it.begin(), last = it.end(); i != last; ++i) {
							read_html_impl_process(i, next, filename, converter, flags);
						}
						pt.push_back(
							value_type(
								converter.from_str(it->tagName()),
								next
								)
							);
					} else if (it->isComment()) {
						if (!(flags & reader_flags::no_comments)) {
							if (it->text().size() >= 7) {
								pt.push_back(
									value_type(
										converter.from_str("<xmlcomment>"),
										ptree_type(converter.from_str(it->text().substr(4, it->text().size() - 7)))
										)
									);
							}
						}
					} else {
						std::string text(
							flags & reader_flags::trim_whitespace
								? htmlcxx::HTML::single_blank(it->text())
								: it->text()
							);
						if (flags & reader_flags::no_concat_text) {
							if (!text.empty()) {
								pt.push_back(
									value_type(
										converter.from_str("<xmltext>"),
										ptree_type(converter.from_str(text))
										)
									);
							}
						} else {
							pt.data() += converter.from_str(text);
						}
					}
				}
				//
				// read_html_impl
				//
				template<typename Ptree>
				SPRIG_INLINE void read_html_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					int flags = 0,
					typename boost::enable_if<
						is_internal_implemented<Ptree>
					>::type* = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					key_type src;
					std::copy(
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(stream),
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(),
						std::back_inserter(src)
						);
					{
						sprig::locale_saver saver;
						std::setlocale(LC_CTYPE, "");
						htmlcxx::HTML::ParserDom parser;
						tree<htmlcxx::HTML::Node> doc(parser.parseTree(src));
						{
							tree<htmlcxx::HTML::Node>::sibling_iterator it = doc.begin();
							for (tree<htmlcxx::HTML::Node>::sibling_iterator i = it.begin(), last = it.end(); i != last; ++i) {
								if (i->isTag()) {
									read_html_impl_process(i, pt, filename, flags);
								}
							}
						}
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_html_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					Converter converter,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					key_type src;
					std::copy(
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(stream),
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(),
						std::back_inserter(src)
						);
					{
						sprig::locale_saver saver;
						std::setlocale(LC_CTYPE, "");
						htmlcxx::HTML::ParserDom parser;
						tree<htmlcxx::HTML::Node> doc(parser.parseTree(converter.to_str(src)));
						{
							tree<htmlcxx::HTML::Node>::sibling_iterator it = doc.begin();
							for (tree<htmlcxx::HTML::Node>::sibling_iterator i = it.begin(), last = it.end(); i != last; ++i) {
								if (i->isTag()) {
									read_html_impl_process(i, pt, filename, converter, flags);
								}
							}
						}
					}
				}
			}	// namespace parser_detail
			//
			// read_html
			//
			template<typename Ptree>
			SPRIG_INLINE void read_html(
				std::basic_istream<typename Ptree::key_type::value_type>& stream,
				Ptree& pt,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				parser_detail::read_html_impl(stream, pt, std::string(), flags);
			}
			template<typename Ptree>
			SPRIG_INLINE void read_html(
				std::string const& filename,
				Ptree& pt,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				std::basic_ifstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						html_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::read_html_impl(stream, pt, filename, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void read_html(
				std::basic_istream<typename Ptree::key_type::value_type>& stream,
				Ptree& pt,
				Converter converter,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				parser_detail::read_html_impl(stream, pt, std::string(), converter, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void read_html(
				std::string const& filename,
				Ptree& pt,
				Converter converter,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				std::basic_ifstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						html_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::read_html_impl(stream, pt, filename, converter, flags);
			}
		}	// namespace html_parser

		//
		// read_html
		//
		using html_parser::read_html;

	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_HPP
