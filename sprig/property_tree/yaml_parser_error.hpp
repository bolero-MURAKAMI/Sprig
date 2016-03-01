/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_ERROR_HPP
#define SPRIG_PROPERTY_TREE_YAML_PARSER_ERROR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/property_tree/json_parser.hpp>

namespace sprig {
	namespace property_tree {
		namespace yaml_parser {
			//
			// yaml_parser_error
			//
			class yaml_parser_error
				: public boost::property_tree::file_parser_error
			{
			public:
				yaml_parser_error(
					std::string const& message,
					std::string const& filename,
					unsigned long line
					)
					: boost::property_tree::file_parser_error(message, filename, line)
				{}
			};
		}	// namespace yaml_parser
	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_ERROR_HPP
