#ifndef SPRIG_POLICY_DETAIL_POLICY_CHECK_COLLECT_HPP
#define SPRIG_POLICY_DETAIL_POLICY_CHECK_COLLECT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <sprig/tmp/iter_index.hpp>
#include <sprig/policy/policy_traits/is_policy_of.hpp>
#include <sprig/policy/policy_traits/get_policy.hpp>

namespace sprig {
	namespace policy_detail {
		//
		// policy_check_collect
		//
		template<typename Tag, typename Types>
		struct policy_check_collect
			: public boost::mpl::iter_fold<
				Types,
				boost::mpl::vector2<boost::mpl::vector<>, boost::mpl::vector<> >,
				boost::mpl::eval_if<
					is_policy_of<Tag, boost::mpl::deref<boost::mpl::_2> >,
					boost::mpl::vector2<
						boost::mpl::push_back<
							boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<0> >,
							tmp::iter_index<Types, boost::mpl::_2>
						>,
						boost::mpl::push_back<
							boost::mpl::at<boost::mpl::_1, boost::mpl::size_t<1> >,
							get_policy<boost::mpl::deref<boost::mpl::_2> >
						>
					>,
					boost::mpl::_1
				>
			>
		{};
	}	// namespace policy_detail
}	// namespace sprig

#endif	// #ifndef SPRIG_POLICY_DETAIL_POLICY_CHECK_COLLECT_HPP
