/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_ITER_INDEX_HPP
#define SPRIG_TMP_ITER_INDEX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin.hpp>

namespace sprig {
	namespace tmp {
		//
		// iter_index
		//
		template<typename Sequence, typename Iterator>
		struct iter_index
			: public boost::mpl::distance<
				typename boost::mpl::begin<Sequence>::type,
				Iterator
			>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_ITER_INDEX_HPP
