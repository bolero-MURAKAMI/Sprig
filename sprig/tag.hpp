#ifndef SPRIG_TAG_HPP
#define SPRIG_TAG_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/int.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

//
// SPRIG_NTH_TAG_TYPEDEF_N
//
#ifndef SPRIG_NTH_TAG_TYPEDEF_N
#	define SPRIG_NTH_TAG_TYPEDEF_N 64
#endif
//
// SPRIG_NTH_TAG_TYPEDEF_GEN
//
#define SPRIG_NTH_TAG_TYPEDEF_GEN(z, n, d) typedef nth_tag<n> tag##n;

namespace sprig {
	//
	// nth_tag
	//
	template<int N>
	struct nth_tag
		: public boost::mpl::int_<N>
	{};
	//
	// tag[N]
	//
	BOOST_PP_REPEAT(SPRIG_NTH_TAG_TYPEDEF_N, SPRIG_NTH_TAG_TYPEDEF_GEN, BOOST_PP_EMPTY());
}	// namespace sprig

#endif	// #ifndef SPRIG_TAG_HPP
