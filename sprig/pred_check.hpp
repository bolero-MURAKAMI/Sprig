/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PRED_CHECK_HPP
#define SPRIG_PRED_CHECK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/eval_if.hpp>
#include <boost/serialization/static_warning.hpp>

//
// SPRIG_EXEC_PRED_CHECKER
//
#define SPRIG_EXEC_PRED_CHECKER(PRED) \
	(sprig::pred_checker((void (*) PRED)0).exec())

//
// SPRIG_PRED_CHECK
//
//	COMMENT: PRED ? T : F
//	COMMENT: ( T and F are unsigned, T <= 1, F > 1 )
#define SPRIG_PRED_CHECK(PRED) \
	sizeof(SPRIG_EXEC_PRED_CHECKER(PRED))

namespace sprig {
	//
	// pred_check_succeeded
	//
	typedef char pred_check_succeeded;
	BOOST_STATIC_WARNING((sizeof(pred_check_succeeded) <= 1));
	//
	// pred_check_failed
	//
	struct pred_check_failed {
		char value[2];
	};
	BOOST_STATIC_WARNING((sizeof(pred_check_failed) > 1));

	//
	// pred_check_result_succeeded
	//
	template<typename Pred>
	struct pred_check_result_succeeded {
		pred_check_succeeded exec();
		typedef pred_check_result_succeeded type;
	};

	//
	// pred_check_result_failed
	//
	template<typename Pred>
	struct pred_check_result_failed {
		pred_check_failed exec();
		typedef pred_check_result_failed type;
	};

	//
	// pred_check_result
	//
	template<typename Pred>
	struct pred_check_result
		: public boost::mpl::eval_if<
			Pred,
			pred_check_result_succeeded<Pred>,
			pred_check_result_failed<Pred>
		>::type
	{};

	//
	// pred_checker
	//
	template<typename Pred>
	pred_check_result<Pred> pred_checker(void (*) (Pred));
}	// namespace sprig

#endif	// #ifndef SPRIG_PRED_CHECK_HPP
