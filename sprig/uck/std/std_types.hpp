#ifndef SPRIG_UCK_STD_STD_TYPES_HPP
#define SPRIG_UCK_STD_STD_TYPES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/function.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>

namespace sprig {
	namespace uck {
		//
		// std_types
		//
		template<typename Traits = traits<> >
		struct std_types {
			typedef Traits traits_type;
			typedef typename types<traits_type>::bin_type::const_iterator output_argument_type;
			typedef typename types<traits_type>::bin_type::iterator input_argument_type;
			typedef typename types<traits_type>::bin_type::iterator work_argument_type;
			typedef boost::function<
				void (
					output_argument_type,
					output_argument_type,
					work_argument_type,
					work_argument_type
					)
			> output_type;
			typedef boost::function<
				void (
					input_argument_type,
					input_argument_type,
					work_argument_type,
					work_argument_type
					)
			> input_type;
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_STD_STD_TYPES_HPP
