/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_MACRO_RESULT_HPP
#define SPRIG_KRKR_MACRO_RESULT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/optional/optional.hpp>
#include <sprig/external/tp_stub.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// optional_result_set
			//
			// COMMENT: boost::optionalå^ÇÃèÛë‘Ç…âûÇ∂ÇƒÇªÇÃílÇ‹ÇΩÇÕvoidÇê›íËÇ∑ÇÈÅB
			//
			template<typename T>
			SPRIG_INLINE void optional_result_set(tTJSVariant* result, boost::optional<T> const& value) {
				if (result) {
					if (value) {
						*result = *value;
					} else {
						*result = tTJSVariant();
					}
				}
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

//
// SPRIG_KRKR_RESULT_SET
//
#define SPRIG_KRKR_RESULT_SET(EXPR) \
	if (result) { \
		*result = (EXPR); \
	}
//
// SPRIG_KRKR_INVOKE_RESULT_SET
//
#define SPRIG_KRKR_INVOKE_RESULT_SET(EXPR) \
	if (result) { \
		*result = (EXPR); \
	} else { \
		(EXPR); \
	}

//
// SPRIG_KRKR_OPTIONAL_RESULT_SET
//
#define SPRIG_KRKR_OPTIONAL_RESULT_SET(EXPR) \
	if (result) { \
		sprig::krkr::tjs::optional_result_set(result, (EXPR)); \
	}
//
// SPRIG_KRKR_INVOKE_OPTIONAL_RESULT_SET
//
#define SPRIG_KRKR_INVOKE_OPTIONAL_RESULT_SET(EXPR) \
	sprig::krkr::tjs::optional_result_set(result, (EXPR));

#endif	// #ifndef SPRIG_KRKR_MACRO_RESULT_HPP
