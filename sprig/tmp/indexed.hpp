/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_INDEXED_HPP
#define SPRIG_TMP_INDEXED_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/fold.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/lambda.hpp>
#include <sprig/use_default.hpp>

namespace sprig {
	namespace tmp {
		namespace indexed_detail {
			template<
				typename initialSequenceT,
				typename firstKeyT,
				typename Position
			>
			struct arguments {
				typedef typename sprig::select_default<
					initialSequenceT,
					boost::mpl::map<>
				>::type initial_sequence;
				typedef typename sprig::select_default<
					firstKeyT,
					typename boost::mpl::size<initial_sequence>::type
				>::type first_key;
				typedef typename sprig::select_default<
					Position,
					typename boost::mpl::end<initial_sequence>::type
				>::type position;
				typedef typename boost::mpl::distance<
					typename boost::mpl::begin<initial_sequence>::type,
					position
				>::type difference;
				typedef boost::mpl::vector3<
					initial_sequence,
					first_key,
					difference
				> state;
			};
		}	// namespace indexed_detail
		//
		// indexed
		//
		//	COMMENT: シーケンスの各インデックスをキー、各要素を値としたマップを返す
		//
		template<
			typename Sequence,
			typename initialSequenceT = use_default,
			typename firstKeyT = use_default,
			typename Position = use_default
		>
		struct indexed
			: public boost::mpl::at<
				typename boost::mpl::fold<
					Sequence,
					typename indexed_detail::arguments<initialSequenceT, firstKeyT, Position>::state,
					boost::mpl::vector3<
						boost::mpl::insert<
							boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<0> >,
							boost::mpl::advance<
								boost::mpl::begin<
									boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<0> >
								>,
								boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<2> >
							>,
							boost::mpl::pair<
								boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<1> >,
								boost::mpl::_2
							>
						>,
						boost::mpl::next<
							boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<1> >
						>,
						boost::mpl::next<
							boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<2> >
						>
					>
				>::type,
				boost::mpl::size_t<0>
			>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_INDEXED_HPP
