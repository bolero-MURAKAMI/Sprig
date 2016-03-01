/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_FUN_FUN_IO_HPP
#define SPRIG_UCK_FUN_FUN_IO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/fun/fun_manager.hpp>

namespace sprig {
	namespace uck {
		namespace io {
			//
			// fun_output
			//
			template<typename Traits = traits<> >
			struct fun_output {
			public:
				typedef Traits traits_type;
				typedef types<traits_type> types_type;
				typedef std_types<traits_type> std_types_type;
			public:
				void operator()(
					typename std_types_type::output_argument_type arg_first,
					typename std_types_type::output_argument_type arg_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					fun_manager<Traits>::get_mutable_instance().push(arg_first, arg_last, work_first, work_last);
				}
			};
			//
			// fun_input
			//
			template<typename Traits = traits<> >
			struct fun_input {
			public:
				typedef Traits traits_type;
				typedef types<traits_type> types_type;
				typedef std_types<traits_type> std_types_type;
			public:
				void operator()(
					typename std_types_type::input_argument_type res_first,
					typename std_types_type::input_argument_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					fun_manager<Traits>::get_mutable_instance().call(res_first, res_last, work_first, work_last);
				}
			};
		}	// namespace io
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_FUN_FUN_IO_HPP
