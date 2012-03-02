#ifndef SPRIG_TEMPSTREAM_HPP
#define SPRIG_TEMPSTREAM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <sstream>
#include <sprig/string_argument.hpp>

namespace sprig {
	//
	// basic_otempstream
	//
	template<
		typename Elem,
		typename Traits = std::char_traits<Elem>,
		typename Allocator = std::allocator<Elem>
	>
	class basic_otempstream {
	public:
		typedef Elem element_type;
		typedef Traits traits_type;
		typedef Allocator allocator_type;
		typedef std::basic_string<Elem, Traits, Allocator> string_type;
	private:
		std::basic_ostringstream<Elem, Traits, Allocator> oss_;
	public:
		basic_otempstream() {}
		~basic_otempstream() {}
		basic_otempstream& operator<<(
			basic_string_argument<std::basic_string<Elem, Traits, Allocator> > const& rhs
			)
		{
			oss_ << rhs;
			return *this;
		}
		basic_otempstream& operator<<(
			std::basic_ostream<element_type, traits_type>& (*rhs)(std::basic_ostream<element_type, traits_type>&)
			)
		{
			oss_ << rhs;
			return *this;
		}
		string_type str() const {
			return oss_.str();
		}
	};
	template<typename Elem, typename Traits, typename Traits2, typename Allocator>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_otempstream<Elem, Traits2, Allocator> const& rhs
		)
	{
		return lhs << rhs.str();
	}
	typedef basic_otempstream<char> otempstream;
	typedef basic_otempstream<wchar_t> wotempstream;
} // namespace sprig

#endif	// #ifndef SPRIG_TEMPSTREAM_HPP
