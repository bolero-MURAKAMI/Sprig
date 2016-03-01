/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_LINEARIZE_HPP
#define SPRIG_TMP_LINEARIZE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/lambda.hpp>

namespace sprig {
	namespace tmp {
		//
		// linearize
		//
		template<
			typename Sequence,
			typename Inserter = boost::mpl::back_inserter<boost::mpl::vector0<> >
		>
		struct linearize
			: public boost::mpl::fold<
				Sequence,
				typename Inserter::state,
				boost::mpl::eval_if<
					boost::mpl::is_sequence<boost::mpl::_2>,
					linearize<
						boost::mpl::_2,
						boost::mpl::identity<
							boost::mpl::inserter<
								boost::mpl::_1,
								typename Inserter::operation
							>
						>
					>,
					typename Inserter::operation::template apply<
						boost::mpl::_1,
						boost::mpl::_2
					>
				>
			>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_LINEARIZE_HPP
