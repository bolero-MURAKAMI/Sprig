/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_ANY_HPP
#define SPRIG_RANDOM_ANY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <memory>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/utility/swap.hpp>

namespace sprig {
	namespace random {
		//
		// variate_generator_base
		//
		template<typename Result>
		class variate_generator_base {
		public:
			typedef Result result_type;
		public:
			virtual ~variate_generator_base() {}
			virtual result_type operator()() = 0;
			virtual result_type min() const = 0;
			virtual result_type max() const = 0;
			virtual std::auto_ptr<variate_generator_base> clone() const = 0;
		};
		//
		// variate_generator_holder
		//
		template<typename Result, typename VariateGenerator>
		class variate_generator_holder
			: public variate_generator_base<Result>
		{
		public:
			typedef VariateGenerator type;
			typedef variate_generator_base<Result> base_type;
			typedef typename type::engine_type engine_type;
			typedef typename type::distribution_type distribution_type;
			typedef typename base_type::result_type result_type;
		private:
			type t_;
		public:
			explicit variate_generator_holder(type const& t)
				: t_(t)
			{}
			variate_generator_holder(engine_type eng, distribution_type dis)
				: t_(eng, dis)
			{}
			result_type operator()() {
				return result_type(t_());
			}
			result_type min() const {
				return result_type(t_.min());
			}
			result_type max() const {
				return result_type(t_.max());
			}
			std::auto_ptr<base_type> clone() const {
				return std::auto_ptr<base_type>(new variate_generator_holder(t_));
			}
		};
		//
		// any_variate_generator
		//
		template<typename Result>
		class any_variate_generator {
		private:
			typedef variate_generator_base<Result> base_type;
		public:
			typedef typename base_type::result_type result_type;
		private:
			boost::scoped_ptr<base_type> p_;
		public:
			any_variate_generator() {}
			any_variate_generator(any_variate_generator const& other)
				: p_(other.p_.get() ? other.p_->clone() : std::auto_ptr<base_type>())
			{}
			template<typename VariateGenerator>
			explicit any_variate_generator(VariateGenerator const& t)
				: p_(new variate_generator_holder<result_type, VariateGenerator>(t))
			{}
			template<typename Engine, typename Distribution>
			any_variate_generator(Engine const& eng, Distribution const& dis)
				: p_(new variate_generator_holder<result_type, boost::variate_generator<Engine, Distribution> >(eng, dis))
			{}
			any_variate_generator& operator=(any_variate_generator const& other) {
				assign(other);
				return *this;
			}
			template<typename VariateGenerator>
			any_variate_generator& operator=(VariateGenerator const& t) {
				assign(t);
				return *this;
			}
			void assign(any_variate_generator const& other) {
				any_variate_generator temp(other);
				temp.swap(*this);
			}
			template<typename VariateGenerator>
			void assign(VariateGenerator const& t) {
				any_variate_generator temp(t);
				temp.swap(*this);
			}
			template<typename Engine, typename Distribution>
			void assign(Engine const& eng, Distribution const& dis) {
				any_variate_generator temp(eng, dis);
				temp.swap(*this);
			}
			void swap(any_variate_generator& other) {
				boost::swap(p_, other.p_);
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
		};
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_ANY_HPP
