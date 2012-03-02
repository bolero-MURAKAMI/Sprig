#ifndef SPRIG_TMP_APPLIES_HPP
#define SPRIG_TMP_APPLIES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	namespace tmp {
		//
		// applies
		//
		template<typename Size = boost::mpl::size_t<0>, typename Dummy = void>
		struct applies {};
		template<typename Size>
		struct applies<Size, typename boost::enable_if_c<Size::value == 0>::type> {
			template<typename T, typename T1>
			struct apply {
				typedef typename T::template apply<>::type type;
			};
		};
		template<typename Size>
		struct applies<Size, typename boost::enable_if_c<Size::value == 1>::type> {
			template<typename T, typename T1>
			struct apply {
				typedef typename T::template apply<T1>::type type;
			};
		};
		template<typename Size>
		struct applies<Size, typename boost::enable_if_c<Size::value == 2>::type> {
			template<typename T, typename T1, typename T2>
			struct apply {
				typedef typename T::template apply<T1, T2>::type type;
			};
		};
		template<typename Size>
		struct applies<Size, typename boost::enable_if_c<Size::value == 3>::type> {
			template<typename T, typename T1, typename T2, typename T3>
			struct apply {
				typedef typename T::template apply<T1, T2, T3>::type type;
			};
		};
		//
		// applies_c
		//
		template<std::size_t N = 0>
		struct applies_c {
			template<typename T>
			struct apply {
				typedef typename T::template apply<>::type type;
			};
		};
		template<>
		struct applies_c<1> {
			template<typename T, typename T1>
			struct apply {
				typedef typename T::template apply<T1>::type type;
			};
		};
		template<>
		struct applies_c<2> {
			template<typename T, typename T1, typename T2>
			struct apply {
				typedef typename T::template apply<T1, T2>::type type;
			};
		};
		template<>
		struct applies_c<3> {
			template<typename T, typename T1, typename T2, typename T3>
			struct apply {
				typedef typename T::template apply<T1, T2, T3>::type type;
			};
		};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_APPLIES_HPP
