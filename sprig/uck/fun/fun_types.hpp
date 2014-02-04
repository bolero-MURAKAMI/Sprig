/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_FUN_FUN_TYPES_HPP
#define SPRIG_UCK_FUN_FUN_TYPES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <string>
#include <map>
#include <boost/function.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>

namespace sprig {
	namespace uck {
		//
		// fun_types
		//
		template<typename Traits = traits<> >
		struct fun_types {
			typedef Traits traits_type;
			typedef typename types<traits_type>::bin_type argument_type;
			typedef std::vector<argument_type> arguments_type;
			typedef std::string name_type;
			typedef typename arguments_type::const_iterator fun_argument_type;
			typedef typename std_types<traits_type>::input_argument_type fun_result_type;
			typedef boost::function<
				void (
					fun_argument_type,
					fun_argument_type,
					fun_result_type,
					fun_result_type,
					typename std_types<traits_type>::work_argument_type,
					typename std_types<traits_type>::work_argument_type
					)
			> function_type;
			typedef std::map<name_type, function_type> package_type;
			typedef std::map<name_type, package_type> library_type;
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_FUN_FUN_TYPES_HPP
