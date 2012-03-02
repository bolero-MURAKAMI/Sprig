#ifndef SPRIG_UCK_FUN_FUN_WORK_BOOL_HPP
#define SPRIG_UCK_FUN_FUN_WORK_BOOL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <iostream>
#include <sprig/binary.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/fun/fun_types.hpp>
#include <sprig/uck/fun/fun_manager.hpp>

namespace sprig {
	namespace uck {
		//
		// fun_work_bool
		//
		template<typename Traits = traits<> >
		struct fun_work_bool {
		public:
			typedef Traits traits_type;
			typedef types<traits_type> types_type;
			typedef std_types<traits_type> std_types_type;
			typedef fun_types<traits_type> fun_types_type;
		public:
			static typename fun_types_type::name_type const& name() {
				static typename fun_types_type::name_type const v("work_bool");
				return v;
			}
		public:
			//
			// work_false
			//
			struct work_false {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("w0");
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
					std::fill(work_first, work_last, 0);
				}
			};
			//
			// work_true
			//
			struct work_true {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("w1");
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
					std::fill(work_first, work_last, 1);
				}
			};
		public:
			static typename fun_types_type::package_type const& package() {
				typedef typename fun_types_type::package_type result_type;
				typedef typename result_type::value_type value_type;
				static result_type v;
				struct initializer {
					int operator()() const {
						v.insert(value_type(work_false::name(), work_false()));
						v.insert(value_type(work_true::name(), work_true()));
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

#endif	// #ifndef SPRIG_UCK_FUN_FUN_WORK_BOOL_HPP
