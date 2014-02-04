/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_NONDET_RANDOM_HPP
#define SPRIG_RANDOM_NONDET_RANDOM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/nondet_random.hpp>
#include <boost/mpl/bool.hpp>
#include <sprig/singleton.hpp>
#include <sprig/random/fixed_range_helper.hpp>

namespace sprig {
	namespace random {
		//
		// singleton_random_device
		//
		class singleton_random_device
			: public fixed_range_helper<boost::random_device>
		{
		public:
			typedef boost::mpl::true_ is_static_random_engine;
			typedef boost::random_device base_type;
			typedef base_type::result_type result_type;
		public:
			//
			// proxy
			//
			class proxy
				: public sprig::singleton<proxy>
			{
			private:
				base_type engine_;
			public:
				base_type& get() {
					return engine_;
				}
				base_type const& get() const {
					return engine_;
				}
			};
		public:
			static result_type static_random() {
				return static_mutable_base()();
			}
			static result_type static_min() {
				return static_const_base().min();
			}
			static result_type static_max() {
				return static_const_base().max();
			}
			static double static_entropy() {
				return static_const_base().entropy();
			}
			static base_type const& static_const_base() {
				return proxy::get_const_instance().get();
			}
			static base_type& static_mutable_base() {
				return proxy::get_mutable_instance().get();
			}
			template<typename Elem, typename Traits>
			static std::basic_ostream<Elem, Traits>& static_out(std::basic_ostream<Elem, Traits>& s) {
				return s;
			}
			template<typename Elem, typename Traits>
			static std::basic_istream<Elem, Traits>& static_in(std::basic_istream<Elem, Traits>& s) {
				return s;
			}
		public:
			singleton_random_device() {}
			result_type operator()() {
				return base()();
			}
			result_type min() const {
				return base().min();
			}
			result_type max() const {
				return base().max();
			}
			double entropy() const {
				return base().entropy();
			}
			base_type const& base() const {
				return proxy::get_const_instance().get();
			}
			base_type& base() {
				return proxy::get_mutable_instance().get();
			}
		};
		template<typename Elem, typename Traits>
		SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
			std::basic_ostream<Elem, Traits>& lhs,
			singleton_random_device const& rhs
			)
		{
			return lhs;
		}
		template<typename Elem, typename Traits>
		SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
			std::basic_istream<Elem, Traits>& lhs,
			singleton_random_device& rhs
			)
		{
			return lhs;
		}
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_NONDET_RANDOM_HPP
