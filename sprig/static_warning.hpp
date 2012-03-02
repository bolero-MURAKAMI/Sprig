#ifndef SPRIG_STATIC_WARNING_HPP
#define SPRIG_STATIC_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <sprig/pred_check.hpp>

#define SPRIG_STATIC_WARNING(B) \
	static sprig::STATIC_WARNING_FAILED BOOST_PP_CAT(static_warning_, __LINE__) \
		= (sprig::STATIC_WARNING_CHECK)SPRIG_PRED_CHECK((boost::mpl::bool_<B>))

namespace sprig {
	//
	// STATIC_WARNING_CHECK
	//
	typedef std::size_t STATIC_WARNING_CHECK;
	//
	// STATIC_WARNING_FAILED
	//
	typedef bool const STATIC_WARNING_FAILED;
}	// namespace sprig

#endif	// #ifndef SPRIG_STATIC_WARNING_HPP
