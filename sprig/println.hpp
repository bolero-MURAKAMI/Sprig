#ifndef SPRIG_PRINTLN_HPP
#define SPRIG_PRINTLN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <sprig/string_argument.hpp>

namespace sprig {
		//
		// basic_println_adapter
		//
		template<typename Elem, typename Traits = std::char_traits<Elem> >
		class basic_println_adapter {
		public:
			typedef Elem element_type;
			typedef Traits traits_type;
			typedef std::basic_ostream<element_type, traits_type> ostream_type;
			typedef basic_string_argument<std::basic_string<element_type, traits_type> > string_argument_type;
		private:
			ostream_type& ostream_;
		public:
			explicit basic_println_adapter(ostream_type& ostream)
				: ostream_(ostream)
			{}
			~basic_println_adapter() throw() {
				ostream_ << std::endl;
			}
			void print(string_argument_type const& v) {
				ostream_ << v;
			}
			basic_println_adapter& operator()(string_argument_type const& v) {
				print(v);
				return *this;
			}
			basic_println_adapter& operator,(string_argument_type const& v) {
				return operator()(v);
			}
		};
		//
		// println_adapter, wprintln_adapter
		//
		typedef basic_println_adapter<char> println_adapter;
		typedef basic_println_adapter<wchar_t> wprintln_adapter;
		//
		// println
		//
		template<typename Elem, typename Traits>
		basic_println_adapter<Elem, Traits> println(std::basic_ostream<Elem, Traits>& ostream) {
			return basic_println_adapter<Elem, Traits>(ostream);
		}
}	// namespace sprig

#endif	// #ifndef SPRIG_PRINTLN_HPP
