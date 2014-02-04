/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_STD_STD_IO_HPP
#define SPRIG_UCK_STD_STD_IO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstdio>
#include <algorithm>
#include <sprig/binary.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>

namespace sprig {
	namespace uck {
		namespace io {
			//
			// std_output
			//
			template<typename Traits = traits<> >
			struct std_output {
			public:
				typedef Traits traits_type;
				typedef types<traits_type> types_type;
				typedef std_types<traits_type> std_types_type;
			public:
				void operator()(
					typename std_types_type::output_argument_type first,
					typename std_types_type::output_argument_type last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::putchar(get_from_big_endian<char>(first, last));
				}
			};
			//
			// std_input
			//
			template<typename Traits = traits<> >
			struct std_input {
			public:
				typedef Traits traits_type;
				typedef types<traits_type> types_type;
				typedef std_types<traits_type> std_types_type;
			public:
				void operator()(
					typename std_types_type::input_argument_type first,
					typename std_types_type::input_argument_type last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::fill(first, last, 0);
					set_to_big_endian<char>(::getchar(), first, last);
				}
			};
		}	// namespace io
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_STD_STD_IO_HPP
