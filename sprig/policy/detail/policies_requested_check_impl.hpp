#ifndef SPRIG_POLICY_DETAIL_POLICIES_REQUESTED_CHECK_IMPL_HPP
#define SPRIG_POLICY_DETAIL_POLICIES_REQUESTED_CHECK_IMPL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/preprocessor/cat.hpp>
#include <sprig/tmp/iter_index.hpp>
#include <sprig/policy/detail/is_policy_check_impl.hpp>
#include <sprig/policy/detail/is_policy_any_of_check_impl.hpp>

//
// SPRIG_POLICYIES_REQUESTED_CHECK_IMPL
//
#define SPRIG_POLICYIES_REQUESTED_CHECK_IMPL(TAGS, TYPES, DELECTIVE) \
	struct BOOST_PP_CAT(policies_requested_checker_, __LINE__) { \
	private: \
		template<typename T, std::size_t Index, typename Tags, typename Types> \
		struct policy_checker { \
		private: \
			SPRIG_IS_POLICY_CHECK_IMPL(T, DELECTIVE); \
		}; \
		template<typename T, std::size_t Index, typename Tags, typename Types> \
		struct policy_any_of_checker { \
		private: \
			SPRIG_IS_POLICY_ANY_OF_CHECK_IMPL(TAGS, T, DELECTIVE); \
		}; \
		template<typename T, typename indexT, typename Tags, typename Types> \
		struct element_checker \
			: public boost::mpl::size_t<0> \
			, public policy_checker<T, indexT::value, Tags, Types> \
			, public policy_any_of_checker<T, indexT::value, Tags, Types> \
		{}; \
	public: \
		static std::size_t const value = boost::mpl::iter_fold< \
			TYPES, \
			boost::mpl::size_t<0>, \
			element_checker< \
				boost::mpl::deref<boost::mpl::_2>, \
				sprig::tmp::iter_index<TYPES, boost::mpl::_2>, \
				TAGS, \
				TYPES \
			> \
		>::type::value; \
	}; \
	static std::size_t const BOOST_PP_CAT(policies_requested_check_, __LINE__) \
		= (BOOST_PP_CAT(policies_requested_checker_, __LINE__)::value)

#endif	// #ifndef SPRIG_POLICY_DETAIL_POLICIES_REQUESTED_CHECK_IMPL_HPP
