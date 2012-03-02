#ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_FLAGS_HPP
#define SPRIG_PROPERTY_TREE_HTML_PARSER_FLAGS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	namespace property_tree {
		namespace html_parser {
			//
			// reader_flags
			//
			struct reader_flags {
				//
				// no_concat_text
				// no_comments
				// trim_whitespace
				//
				static int const no_concat_text = 0x01;
				static int const no_comments = 0x02;
				static int const trim_whitespace = 0x04;
			};
			//
			// validate_reader_flags
			//
			SPRIG_INLINE bool validate_reader_flags(int flags) {
				return (
					flags & ~(
						reader_flags::no_concat_text
						| reader_flags::no_comments
						| reader_flags::trim_whitespace
						)
					) == 0;
			}
		}	// namespace html_parser
	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_HTML_PARSER_FLAGS_HPP
