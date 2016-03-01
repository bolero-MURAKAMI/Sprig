/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SERIALIZATION_KRKR_HPP
#define SPRIG_SERIALIZATION_KRKR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/utility/serialization.hpp>

SPRIG_SERIALIZATION_NAMESPACE_BEGIN
	//
	// tTJSString
	//
	template <typename Archive>
	SPRIG_INLINE void save(Archive& ar, tTJSString const& v, unsigned int const) {
		std::basic_string<tjs_char> str(v.c_str());
		ar
			& boost::serialization::make_nvp("str", str)
			;
	}
	template <typename Archive>
	SPRIG_INLINE void load(Archive& ar, tTJSString& v, unsigned int const) {
		std::basic_string<tjs_char> str;
		ar
			& boost::serialization::make_nvp("str", str)
			;
		v = str.c_str();
	}
	template <typename Archive>
	SPRIG_INLINE void serialize(Archive& ar, tTJSString& v, unsigned int const version) {
		boost::serialization::split_free(ar, v, version);
	}
SPRIG_SERIALIZATION_NAMESPACE_END

#endif	// #ifndef SPRIG_SERIALIZATION_KRKR_HPP
