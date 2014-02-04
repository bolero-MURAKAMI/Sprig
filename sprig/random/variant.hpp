/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_VARIANT_HPP
#define SPRIG_RANDOM_VARIANT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/variant/static_visitor.hpp>
#include <boost/random/variate_generator.hpp>
#include <sprig/reference_holder.hpp>

namespace sprig {
	namespace random {
		//
		// distribution_visitor
		//
		template<typename Result, typename Distribution>
		struct distribution_visitor
			: public boost::static_visitor<Result>
		{
		public:
			typedef Result result_type;
			typedef Distribution distribution_type;
		private:
			mutable sprig::reference_holder<distribution_type> dis_;
		public:
			explicit distribution_visitor(distribution_type& dis)
				: dis_(dis)
			{}
			template<typename Engine>
			result_type operator()(Engine& eng) const {
				return result_type(dis_.get_mutable()(eng));
			}
		};
		//
		// make_distribution_visitor
		//
		template<typename Result, typename Distribution>
		distribution_visitor<Result, Distribution> make_distribution_visitor(Distribution& dis) {
			return distribution_visitor<Result, Distribution>(dis);
		}
		//
		// distribution_variate_visitor
		//
		template<typename Result, typename Distribution>
		struct distribution_variate_visitor
			: public boost::static_visitor<Result>
		{
		public:
			typedef Result result_type;
			typedef Distribution distribution_type;
		private:
			mutable sprig::reference_holder<distribution_type> dis_;
		public:
			explicit distribution_variate_visitor(distribution_type& dis)
				: dis_(dis)
			{}
			template<typename Engine>
			result_type operator()(Engine& eng) const {
				boost::variate_generator<Engine&, distribution_type> gen(eng, dis_.get_mutable());
				return result_type(gen());
			}
		};
		//
		// make_distribution_variate_visitor
		//
		template<typename Result, typename Distribution>
		distribution_variate_visitor<Result, Distribution> make_distribution_variate_visitor(Distribution& dis) {
			return distribution_variate_visitor<Result, Distribution>(dis);
		}
		//
		// generate_random_visitor
		//
		template<typename Result>
		struct generate_random_visitor
			: public boost::static_visitor<Result>
		{
		public:
			typedef Result result_type;
		public:
			template<typename Engine, typename Distribution>
			result_type operator()(Engine const& eng, Distribution const& dis) const {
				return Result(eng, dis);
			}
		};
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_VARIANT_HPP
