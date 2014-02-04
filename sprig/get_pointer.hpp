/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_GET_POINTER_HPP
#define SPRIG_GET_POINTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/optional/optional.hpp>

namespace sprig {
	//
	// get_pointer
	//
	template<typename T>
	SPRIG_INLINE T* get_pointer(T* p) {
		return p;
	}
	template<typename T>
	SPRIG_INLINE T const* get_pointer(T const* p) {
		return p;
	}
	template<typename T>
	SPRIG_INLINE typename boost::shared_ptr<T>::pointer
	get_pointer(boost::shared_ptr<T> const& p) {
		return boost::get_pointer(p);
	}
	template<typename T>
	SPRIG_INLINE typename boost::scoped_ptr<T>::element_type*
	get_pointer(boost::scoped_ptr<T> const& p) {
		return boost::get_pointer(p);
	}
	template<typename T>
	SPRIG_INLINE typename boost::intrusive_ptr<T>::element_type*
	get_pointer(boost::intrusive_ptr<T> const& p) {
		return boost::get_pointer(p);
	}
	template<typename T>
	SPRIG_INLINE typename boost::optional<T>::pointer_type
	get_pointer(boost::optional<T>& p) {
		return boost::get_pointer(p);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_GET_POINTER_HPP
