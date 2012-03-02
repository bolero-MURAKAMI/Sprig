#ifndef SPRIG_FUSION_LINEAR_VALUE_AT_HPP
#define SPRIG_FUSION_LINEAR_VALUE_AT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/advance.hpp>
#include <boost/fusion/include/value_of.hpp>

namespace sprig {
	namespace fusion {
		namespace result_of {
			//
			// linear_value_at_c
			// linear_value_at
			//
			template<typename Seq, int M>
			struct linear_value_at_c
				: public boost::fusion::result_of::value_of<
					typename boost::fusion::result_of::advance_c<
						typename boost::fusion::result_of::begin<Seq>::type,
						M
					>::type
				>
			{};
			template<typename Seq, typename N>
			struct linear_value_at
				: public linear_value_at_c<Seq, N::value>
			{};
		}	// namespace result_of
	}	// namespace fusion
}	// namespace sprig

#endif	// #ifndef SPRIG_FUSION_LINEAR_VALUE_AT_HPP
