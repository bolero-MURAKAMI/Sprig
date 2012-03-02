#ifndef SPRIG_KRKR_TJS_IO_HPP
#define SPRIG_KRKR_TJS_IO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <sprig/external/tp_stub.hpp>
#include <iosfwd>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/krkr/tjs/str_cast.hpp>

//
// operator<<
//
template<typename Elem, typename Traits>
SPRIG_INLINE typename boost::enable_if<
	boost::is_same<Elem, tjs_char>,
	std::basic_ostream<Elem, Traits>&
>::type
operator<<(std::basic_ostream<Elem, Traits>& lhs, tTJSString const& rhs) {
	return lhs << rhs.c_str();
}
template<typename Elem, typename Traits>
SPRIG_INLINE typename boost::disable_if<
	boost::is_same<Elem, tjs_char>,
	std::basic_ostream<Elem, Traits>&
>::type
operator<<(std::basic_ostream<Elem, Traits>& lhs, tTJSString const& rhs) {
	typedef std::basic_string<Elem, Traits> string_type;
	return lhs << sprig::str_cast<string_type>(rhs);
}
//
// operator>>
//
template<typename Elem, typename Traits>
SPRIG_INLINE typename boost::enable_if<
	boost::is_same<Elem, tjs_char>,
	std::basic_istream<Elem, Traits>&
>::type
operator>>(std::basic_istream<Elem, Traits>& lhs, tTJSString& rhs) {
	std::basic_string<Elem, Traits> s;
	lhs >> s;
	rhs = s.c_str();
	return lhs;
}
template<typename Elem, typename Traits>
SPRIG_INLINE typename boost::disable_if<
	boost::is_same<Elem, tjs_char>,
	std::basic_istream<Elem, Traits>&
>::type
operator>>(std::basic_istream<Elem, Traits>& lhs, tTJSString& rhs) {
	std::basic_string<Elem, Traits> s;
	lhs >> s;
	rhs = sprig::str_cast<tTJSString>(s);
	return lhs;
}

#endif	// #ifndef SPRIG_KRKR_TJS_IO_HPP
