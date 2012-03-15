#ifndef SPRIG_KRKR_TJS_EXCEPTION_HPP
#define SPRIG_KRKR_TJS_EXCEPTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/exception/diagnostic_information.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/krkr/tjs/typedef.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// exception_information
			//
			template<typename Exception>
			SPRIG_INLINE sprig::krkr::tjs::string_type exception_information(Exception const& e) {
				return sprig::str_cast<sprig::krkr::tjs::string_type>(boost::diagnostic_information(e));
			}
			//
			// rethrow_exception_to_tjs_exception
			//
			// COMMENT: キャッチした例外をTJSの例外メッセージに変換する。
			//
			template<typename Exception>
			SPRIG_INLINE void rethrow_exception_to_tjs_exception(Exception const& e) {
				::TVPThrowExceptionMessage(sprig::krkr::tjs::exception_information(e).c_str());
			}
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_EXCEPTION_HPP
