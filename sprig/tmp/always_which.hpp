#ifndef SPRIG_TMP_ALWAYS_WHICH_HPP
#define SPRIG_TMP_ALWAYS_WHICH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/void.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	namespace tmp {
		//
		// always_which
		//
		template<typename T, typename Dummy = void>
		struct always_which {};
		template<typename T>
		struct always_which<T, typename boost::enable_if_c<T::value == 1>::type> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T1 type;
			};
		};
		template<typename T>
		struct always_which<T, typename boost::enable_if_c<T::value == 2>::type> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T2 type;
			};
		};
		template<typename T>
		struct always_which<T, typename boost::enable_if_c<T::value == 3>::type> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T3 type;
			};
		};
		//
		// always_which_c
		//
		template<std::size_t N>
		struct always_which_c {};
		template<>
		struct always_which_c<1> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T1 type;
			};
		};
		template<>
		struct always_which_c<2> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T2 type;
			};
		};
		template<>
		struct always_which_c<3> {
			template<
				typename T1 = boost::mpl::void_,
				typename T2 = boost::mpl::void_,
				typename T3 = boost::mpl::void_
			>
			struct apply {
				typedef T3 type;
			};
		};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_ALWAYS_WHICH_HPP
