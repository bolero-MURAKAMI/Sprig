#ifndef SPRIG_KRKR_TJS_INTRUSIVE_PTR_HPP
#define SPRIG_KRKR_TJS_INTRUSIVE_PTR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/external/tp_stub.hpp>

namespace {
	//
	// intrusive_ptr_add_ref
	// intrusive_ptr_release
	//
	// overload: (iTJSDispatch2*)
	//
	SPRIG_INLINE void intrusive_ptr_add_ref(iTJSDispatch2* p) {
		p->AddRef();
	}
	SPRIG_INLINE void intrusive_ptr_release(iTJSDispatch2* p) {
		p->Release();
	}
	//
	// overload: (tTJSVariantString*)
	//
	SPRIG_INLINE void intrusive_ptr_add_ref(tTJSVariantString* p) {
		p->AddRef();
	}
	SPRIG_INLINE void intrusive_ptr_release(tTJSVariantString* p) {
		p->Release();
	}
	//
	// overload: (tTJSVariantOctet*)
	//
	SPRIG_INLINE void intrusive_ptr_add_ref(tTJSVariantOctet* p) {
		p->AddRef();
	}
	SPRIG_INLINE void intrusive_ptr_release(tTJSVariantOctet* p) {
		p->Release();
	}
}	// anonymous-namespace

#endif	// #ifndef SPRIG_KRKR_TJS_INTRUSIVE_PTR_HPP
