/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_FUN_FUN_ARITHMETIC_HPP
#define SPRIG_UCK_FUN_FUN_ARITHMETIC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <iterator>
#include <boost/cstdint.hpp>
#include <sprig/binary.hpp>
#include <sprig/utility/iterator.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/fun/fun_types.hpp>
#include <sprig/uck/fun/fun_manager.hpp>

namespace sprig {
	namespace uck {
		//
		// fun_arithmetic
		//
		template<typename Traits = traits<> >
		struct fun_arithmetic {
		public:
			typedef Traits traits_type;
			typedef types<traits_type> types_type;
			typedef std_types<traits_type> std_types_type;
			typedef fun_types<traits_type> fun_types_type;
		public:
			static typename fun_types_type::name_type const& name() {
				static typename fun_types_type::name_type const v("arithmetic");
				return v;
			}
		public:
			//
			// plus_int32
			//
			struct plus_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("+i4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::int32_t v = get_from_big_endian<boost::int32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v += get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// plus_uint32
			//
			struct plus_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("+u4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::uint32_t v = get_from_big_endian<boost::uint32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v += get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// minus_int32
			//
			struct minus_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("-i4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::int32_t v = get_from_big_endian<boost::int32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v -= get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// minus_uint32
			//
			struct minus_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("-u4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::uint32_t v = get_from_big_endian<boost::uint32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v -= get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// multiplies_int32
			//
			struct multiplies_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("*i4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::int32_t v = get_from_big_endian<boost::int32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v *= get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// multiplies_uint32
			//
			struct multiplies_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("*u4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::uint32_t v = get_from_big_endian<boost::uint32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v *= get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// devides_int32
			//
			struct devides_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("/i4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::int32_t v = get_from_big_endian<boost::int32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v /= get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// devides_uint32
			//
			struct devides_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("/u4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::uint32_t v = get_from_big_endian<boost::uint32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v /= get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// modulus_int32
			//
			struct modulus_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("%i4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::int32_t v = get_from_big_endian<boost::int32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v %= get_from_big_endian<boost::int32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
			//
			// modulus_uint32
			//
			struct modulus_uint32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("%u4");
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
					if (std::distance(arg_first, arg_last) < 2) {
						return;
					}
					boost::uint32_t v = get_from_big_endian<boost::uint32_t>(arg_first->begin(), arg_first->end());
					for (typename fun_types_type::fun_argument_type i = sprig::get_advance(arg_first, 1), last = arg_last; i != last; ++i) {
						v %= get_from_big_endian<boost::uint32_t>(i->begin(), i->end());
					}
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::uint32_t>(v, res_first, res_last);
				}
			};
			//
			// negate_int32
			//
			struct negate_int32 {
			public:
				static typename fun_types_type::name_type const& name() {
					static typename fun_types_type::name_type const v("-@i4");
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
					boost::int32_t v = -get_from_big_endian<boost::int32_t>(res_first, res_last);
					std::fill(res_first, res_last, 0);
					set_to_big_endian<boost::int32_t>(v, res_first, res_last);
				}
			};
		public:
			static typename fun_types_type::package_type const& package() {
				typedef typename fun_types_type::package_type result_type;
				typedef typename result_type::value_type value_type;
				static result_type v;
				struct initializer {
					int operator()() const {
						v.insert(value_type(plus_int32::name(), plus_int32()));
						v.insert(value_type(plus_uint32::name(), plus_uint32()));
						v.insert(value_type(minus_int32::name(), minus_int32()));
						v.insert(value_type(minus_uint32::name(), minus_uint32()));
						v.insert(value_type(multiplies_int32::name(), multiplies_int32()));
						v.insert(value_type(multiplies_uint32::name(), multiplies_uint32()));
						v.insert(value_type(devides_int32::name(), devides_int32()));
						v.insert(value_type(devides_uint32::name(), devides_uint32()));
						v.insert(value_type(modulus_int32::name(), modulus_int32()));
						v.insert(value_type(modulus_uint32::name(), modulus_uint32()));
						v.insert(value_type(negate_int32::name(), negate_int32()));
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

#endif	// #ifndef SPRIG_UCK_FUN_FUN_ARITHMETIC_HPP
