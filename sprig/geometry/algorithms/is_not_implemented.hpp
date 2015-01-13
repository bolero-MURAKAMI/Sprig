/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_GEOMETRY_ALGORITHMS_IS_NOT_IMPLEMENTED_HPP
#define SPRIG_GEOMETRY_ALGORITHMS_IS_NOT_IMPLEMENTED_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_base_of.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace sprig {
	namespace geometry {
		//
		// is_not_implemented
		//
		template<typename Dispatch>
		struct is_not_implemented
			: public boost::is_base_of<
				boost::geometry::nyi::not_implemented_tag,
				Dispatch
			>
		{};
	}	// namespace geometry
}	// namespace sprig

#endif	// #ifndef SPRIG_GEOMETRY_ALGORITHMS_IS_NOT_IMPLEMENTED_HPP
