#ifndef SPRIG_PRED_WARNING_HPP
#define SPRIG_PRED_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/preprocessor/cat.hpp>
#include <sprig/pred_check.hpp>

#define SPRIG_PRED_WARNING(PRED) \
	static sprig::PRED_WARNING_FAILED BOOST_PP_CAT(pred_warning_, __LINE__) \
		= (sprig::PRED_WARNING_CHECK)SPRIG_PRED_CHECK(PRED)

namespace sprig {
	//
	// PRED_WARNING_CHECK
	//
	typedef std::size_t PRED_WARNING_CHECK;
	//
	// PRED_WARNING_FAILED
	//
	typedef bool const PRED_WARNING_FAILED;
}	// namespace sprig

#endif	// #ifndef SPRIG_PRED_WARNING_HPP
