#ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_ERROR_HPP
#define SPRIG_PROPERTY_TREE_HTML_PARSER_ERROR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/property_tree/json_parser.hpp>

namespace sprig {
	namespace property_tree {
		namespace html_parser {
			//
			// html_parser_error
			//
			class html_parser_error
				: public boost::property_tree::file_parser_error
			{
			public:
				html_parser_error(
					std::string const& message,
					std::string const& filename,
					unsigned long line
					)
					: boost::property_tree::file_parser_error(message, filename, line)
				{}
			};
		}	// namespace html_parser
	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_ERROR_HPP
