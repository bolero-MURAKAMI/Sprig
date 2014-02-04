/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PROPERTY_TREE_STR_CONVERTER_HPP
#define SPRIG_PROPERTY_TREE_STR_CONVERTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <sprig/str_cast.hpp>

namespace sprig {
	namespace property_tree {
		//
		// default_str_converter
		//
		template<typename T>
		class default_str_converter {
		public:
			T from_str(std::string const& from) const {
				return sprig::str_cast<T>(from);
			}
			std::string to_str(T const& from) const {
				return sprig::str_cast<std::string>(from);
			}
		};
	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_STR_CONVERTER_HPP
