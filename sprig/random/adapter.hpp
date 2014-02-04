/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_ADAPTER_HPP
#define SPRIG_RANDOM_ADAPTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <memory>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/config/inline.hpp>
#include <sprig/random/fixed_range_helper.hpp>

namespace sprig {
	namespace random {
		//
		// shared_engine_adapter
		//
		template<typename Engine, bool HasStreamIO = false>
		class shared_engine_adapter
			: public fixed_range_helper<Engine>
		{
		public:
			typedef Engine base_type;
			typedef typename base_type::result_type result_type;
			typedef boost::shared_ptr<base_type> shared_type;
			static bool const has_stream_io = HasStreamIO;
		private:
			shared_type p_;
		public:
			shared_engine_adapter() {}
			shared_engine_adapter(shared_engine_adapter const& other)
				: p_(other.p_)
			{}
			explicit shared_engine_adapter(shared_type const& p)
				: p_(p)
			{}
			explicit shared_engine_adapter(base_type const& t)
				: p_(boost::make_shared<base_type>(t))
			{}
			shared_engine_adapter& operator=(shared_engine_adapter const& other) {
				shared_engine_adapter temp(other);
				temp.swap(*this);
				return *this;
			}
			result_type operator()() {
				return (*p_)();
			}
			result_type min() const {
				return p_->min();
			}
			result_type max() const {
				return p_->max();
			}
			void swap(shared_engine_adapter& other) {
				boost::swap(p_, other.p_);
			}
			shared_type const& get() const {
				return p_;
			}
			base_type const& base() const {
				return *p_;
			}
			base_type& base() {
				return *p_;
			}
		};
		template<typename Elem, typename Traits, typename Engine>
		SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
			std::basic_ostream<Elem, Traits>& lhs,
			shared_engine_adapter<Engine, true> const& rhs
			)
		{
			return lhs << rhs.base();
		}
		template<typename Elem, typename Traits, typename Engine>
		SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
			std::basic_istream<Elem, Traits>& lhs,
			shared_engine_adapter<Engine, true>& rhs
			)
		{
			return lhs >> rhs.base();
		}
		//
		// make_shared_engine_adapter
		//
		template<typename Engine>
		SPRIG_INLINE shared_engine_adapter<Engine> make_shared_engine_adapter(
			boost::shared_ptr<Engine> const& t
			)
		{
			return shared_engine_adapter<Engine>(t);
		}

		//
		// shared_distribution_adapter
		//
		template<typename Distribution>
		class shared_distribution_adapter {
		public:
			typedef Distribution base_type;
			typedef typename base_type::result_type result_type;
			typedef typename base_type::input_type input_type;
			typedef boost::shared_ptr<base_type> shared_type;
		private:
			shared_type p_;
		public:
			shared_distribution_adapter() {}
			shared_distribution_adapter(shared_distribution_adapter const& other)
				: p_(other.p_)
			{}
			explicit shared_distribution_adapter(shared_type const& p)
				: p_(p)
			{}
			explicit shared_distribution_adapter(base_type const& t)
				: p_(boost::make_shared<base_type>(t))
			{}
			shared_distribution_adapter& operator=(shared_distribution_adapter const& other) {
				shared_distribution_adapter temp(other);
				temp.swap(*this);
				return *this;
			}
			shared_distribution_adapter& operator=(shared_type const& p) {
				shared_distribution_adapter temp(p);
				temp.swap(*this);
				return *this;
			}
			shared_distribution_adapter& operator=(base_type const& t) {
				shared_distribution_adapter temp(t);
				temp.swap(*this);
				return *this;
			}
			void reset() {
				p_->reset();
			}
			template<typename Engine>
			result_type operator()(Engine& eng) {
				return (*p_)(eng);
			}
			result_type min() const {
				return p_->min();
			}
			result_type max() const {
				return p_->max();
			}
			void swap(shared_distribution_adapter& other) {
				boost::swap(p_, other.p_);
			}
			shared_type const& get() const {
				return p_;
			}
			base_type const& base() const {
				return *p_;
			}
			base_type& base() {
				return *p_;
			}
		};
		template<typename Elem, typename Traits, typename Distribution>
		SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
			std::basic_ostream<Elem, Traits>& lhs,
			shared_distribution_adapter<Distribution> const& rhs
			)
		{
			return lhs << rhs.base();
		}
		template<typename Elem, typename Traits, typename Distribution>
		SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
			std::basic_istream<Elem, Traits>& lhs,
			shared_distribution_adapter<Distribution>& rhs
			)
		{
			return lhs >> rhs.base();
		}
		//
		// make_shared_distribution_adapter
		//
		template<typename Distribution>
		SPRIG_INLINE shared_distribution_adapter<Distribution> make_shared_distribution_adapter(
			boost::shared_ptr<Distribution> const& t
			)
		{
			return shared_distribution_adapter<Distribution>(t);
		}
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_ADAPTER_HPP
