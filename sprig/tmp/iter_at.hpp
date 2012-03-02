#ifndef SPRIG_TMP_ITER_AT_HPP
#define SPRIG_TMP_ITER_AT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>

namespace sprig {
	namespace tmp {
		//
		// iter_at
		//
		template<typename Sequence, typename indexT>
		struct iter_at
			: public boost::mpl::advance<
				typename boost::mpl::begin<Sequence>::type,
				indexT
			>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_ITER_AT_HPP
