/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_FLAGS_HPP
#define SPRIG_PROPERTY_TREE_YAML_PARSER_FLAGS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	namespace property_tree {
		namespace yaml_parser {
			//
			// reader_flags
			//
			struct reader_flags {
				//
				// multi_document
				//
				static int const multi_document  = 0x01;
			};
			//
			// validate_reader_flags
			//
			SPRIG_INLINE bool validate_reader_flags(int flags) {
				return (
					flags & ~(
						reader_flags::multi_document
						)
					) == 0;
			}
			//
			// writer_flags
			//
			struct writer_flags {
				//
				// multi_document
				// sequence_flow
				// sequence_block
				// map_flow
				// map_block
				//
				static int const multi_document  = 0x01;
				static int const sequence_flow  = 0x02;
				static int const sequence_block  = 0x04;
				static int const map_flow  = 0x08;
				static int const map_block  = 0x10;
				static int const insert_end_of_document  = 0x20;
			};
			//
			// validate_writer_flags
			//
			SPRIG_INLINE bool validate_writer_flags(int flags) {
				return (
					flags & ~(
						writer_flags::multi_document
						| writer_flags::sequence_flow
						| writer_flags::sequence_block
						| writer_flags::map_flow
						| writer_flags::map_block
						)
					) == 0;
			}
		}	// namespace yaml_parser
	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_FLAGS_HPP
