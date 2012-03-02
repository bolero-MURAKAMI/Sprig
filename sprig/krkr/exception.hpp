#ifndef SPRIG_KRKR_EXCEPTION_HPP
#define SPRIG_KRKR_EXCEPTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/exception.hpp>

namespace sprig {
	namespace krkr {
		//
		// bad_script
		//
		SPRIG_EXCEPTION_DECL(bad_script);
		//
		// bad_argument
		//
		SPRIG_EXCEPTION_INHERIT_DECL(bad_argument, bad_script);
		//
		// bad_state
		//
		SPRIG_EXCEPTION_INHERIT_DECL(bad_state, bad_script);

		//
		// internal_error
		//
		SPRIG_EXCEPTION_DECL(internal_error);
		//
		// tvp_error
		//
		SPRIG_EXCEPTION_INHERIT_DECL(tvp_error, internal_error);
		//
		// lib_error
		//
		SPRIG_EXCEPTION_INHERIT_DECL(lib_error, internal_error);
		//
		// win32_error
		//
		SPRIG_EXCEPTION_INHERIT_DECL(win32_error, internal_error);
		//
		// directx_error
		//
		SPRIG_EXCEPTION_INHERIT_DECL(directx_error, internal_error);
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_EXCEPTION_HPP