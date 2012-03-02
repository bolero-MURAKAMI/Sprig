#ifndef SPRIG_KRKR_TJS_EXCEPTION_HPP
#define SPRIG_KRKR_TJS_EXCEPTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/exception/diagnostic_information.hpp>
#include <sprig/external/tp_stub.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// rethrow_exception_to_tjs_exception
			//
			// COMMENT: キャッチした例外をTJSの例外メッセージに変換する。
			//
			template<typename T>
			SPRIG_INLINE void rethrow_exception_to_tjs_exception(T const& e) {
				::TVPThrowExceptionMessage(sprig::str_cast<string_type>(boost::diagnostic_information(e)).c_str());
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_EXCEPTION_HPP
