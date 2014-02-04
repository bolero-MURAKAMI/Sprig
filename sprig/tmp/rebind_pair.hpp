/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_REBIND_PAIR_HPP
#define SPRIG_TMP_REBIND_PAIR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_pair.hpp>
#include <sprig/type_traits/is_fusion_vector.hpp>

namespace sprig {
	namespace tmp {
		namespace rebind_pair_detail {
			//
			// rebind_pair_helper
			//
			template<typename T, typename T1, typename T2, typename Enable = void>
			struct rebind_pair_helper {};
			template<typename T, typename T1, typename T2>
			struct rebind_pair_helper<
				T,
				T1,
				T2,
				typename boost::enable_if<
					sprig::is_pair<T>
				>::type
			>
				: public boost::mpl::identity<std::pair<T1, T2> >
			{};
			template<typename T, typename T1, typename T2>
			struct rebind_pair_helper<
				T,
				T1,
				T2,
				typename boost::enable_if<
					sprig::is_fusion_vector2<T>
				>::type
			>
				: public boost::mpl::identity<boost::fusion::vector2<T1, T2> >
			{};
			template<typename T, typename T1, typename T2>
			struct rebind_pair_helper<
				T,
				T1,
				T2,
				typename boost::enable_if<
					sprig::is_fusion_vector_2<T>
				>::type
			>
				: public boost::mpl::identity<boost::fusion::vector<T1, T2> >
			{};
		}	// namespace rebind_pair_detail
		//
		// rebind_pair
		//
		template<typename T, typename T1, typename T2>
		struct rebind_pair
			: public rebind_pair_detail::rebind_pair_helper<T, T1, T2>
		{};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_REBIND_PAIR_HPP
