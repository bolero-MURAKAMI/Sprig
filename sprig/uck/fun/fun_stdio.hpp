#ifndef SPRIG_UCK_FUN_FUN_STDIO_HPP
#define SPRIG_UCK_FUN_FUN_STDIO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstdio>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/bind/bind.hpp>
#include <sprig/binary.hpp>
#include <sprig/cin_acquire.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/fun/fun_types.hpp>
#include <sprig/uck/fun/fun_manager.hpp>

namespace sprig {
	namespace uck {
		//
		// fun_stdio
		//
		template<typename Traits = traits<> >
		struct fun_stdio {
		public:
			typedef Traits traits_type;
			typedef types<traits_type> types_type;
			typedef std_types<traits_type> std_types_type;
			typedef fun_types<traits_type> fun_types_type;
		public:
			static typename fun_types_type::name_type const& name() {
				static typename fun_types_type::name_type const v("stdio");
				return v;
			}
		public:
			//
			// output_char
			//
			struct output_char {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("opch");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					for (typename fun_types_type::fun_argument_type i = arg_first, last = arg_last; i != last; ++i) {
						std::putchar(get_from_big_endian<char>(i->begin(), i->end()));
					}
				}
			};
			//
			// output_string
			//
			struct output_string {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("opst");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::ostringstream v;
					for (typename fun_types_type::fun_argument_type i = arg_first, last = arg_last; i != last; ++i) {
						v << std::string(i->begin(), i->end());
					}
					std::cout << v.str().c_str();
				}
			};
			//
			// output_line_feed
			//
			struct output_line_feed {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("oplf");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::cout << std::endl;
				}
			};
			//
			// output_int32
			//
			struct output_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("opi4");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					for (typename fun_types_type::fun_argument_type i = arg_first, last = arg_last; i != last; ++i) {
						std::cout << get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
				}
			};
			//
			// output_uint32
			//
			struct output_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("opu4");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					for (typename fun_types_type::fun_argument_type i = arg_first, last = arg_last; i != last; ++i) {
						std::cout << get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
				}
			};
			//
			// input_char
			//
			struct input_char {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("ipch");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::fill(res_first, res_last, 0);
					set_to_big_endian(static_cast<char>(std::getchar()), res_first, res_last);
				}
			};
			//
			// input_char8
			//
			struct input_char8 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("ipc1");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::string v;
					sprig::cin_acquire_any_repeat_until(v, boost::bind(&std::string::size, _1));
					std::fill(res_first, res_last, 0);
					set_to_big_endian<char>(v.at(0), res_first, res_last);
				}
			};
			//
			// input_int32
			//
			struct input_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("ipi4");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					boost::int32_t v;
					sprig::cin_acquire_int_repeat(v);
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// input_uint32
			//
			struct input_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("ipu4");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					boost::uint32_t v;
					sprig::cin_acquire_uint_repeat(v);
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// input_wait
			//
			struct input_wait {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("ipwt");
					return v;
				}
			public:
				void operator()(
					typename fun_types_type::fun_argument_type arg_first,
					typename fun_types_type::fun_argument_type arg_last,
					typename fun_types_type::fun_result_type res_first,
					typename fun_types_type::fun_result_type res_last,
					typename std_types_type::work_argument_type work_first,
					typename std_types_type::work_argument_type work_last
					) const
				{
					std::string v;
					std::getline(std::cin, v);
				}
			};
		public:
			static typename fun_types_type::package_type const& package() {
				typedef typename fun_types_type::package_type result_type;
				typedef typename result_type::value_type value_type;
				static result_type v;
				struct initializer {
					int operator()() const {
						v.insert(value_type(output_char::name(), output_char()));
						v.insert(value_type(output_string::name(), output_string()));
						v.insert(value_type(output_line_feed::name(), output_line_feed()));
						v.insert(value_type(output_int32::name(), output_int32()));
						v.insert(value_type(output_uint32::name(), output_uint32()));
						v.insert(value_type(input_char::name(), input_char()));
						v.insert(value_type(input_char8::name(), input_char8()));
						v.insert(value_type(input_int32::name(), input_int32()));
						v.insert(value_type(input_uint32::name(), input_uint32()));
						v.insert(value_type(input_wait::name(), input_wait()));
						return 0;
					}
				};
				static int const init = initializer()();
				return v;
			}
			static bool attach() {
				return fun_manager<traits_type>::get_mutable_instance().attach(name(), package().begin(), package().end());
			}
			static bool detach() {
				return fun_manager<traits_type>::get_mutable_instance().detach(name());
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_FUN_FUN_STDIO_HPP
