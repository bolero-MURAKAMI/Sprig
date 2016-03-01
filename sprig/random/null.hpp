/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANDOM_NULL_HPP
#define SPRIG_RANDOM_NULL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/mpl/integral_c.hpp>

namespace sprig {
	namespace random {
		//
		// null_engine
		//
		template<
			typename Result = int,
			typename Min = boost::mpl::integral_c<Result, 0>,
			typename Max = boost::mpl::integral_c<Result, 1>
		>
		class null_engine {
		public:
			typedef Result result_type;
		public:
			static bool const has_fixed_range = true;
			static result_type const min_value = Min::value;
			static result_type const max_value = Max::value;
		public:
			null_engine() {}
			result_type operator()() {
				return min_value;
			}
			result_type min() const {
				return min_value;
			}
			result_type max() const {
				return max_value;
			}
		};
		template<typename Elem, typename Traits, typename Result, typename Min, typename Max>
		SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
			std::basic_ostream<Elem, Traits>& lhs,
			null_engine<Result, Min, Max> const& rhs
			)
		{
			return lhs;
		}
		template<typename Elem, typename Traits, typename Result, typename Min, typename Max>
		SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
			std::basic_istream<Elem, Traits>& lhs,
			null_engine<Result, Min, Max>& rhs
			)
		{
			return lhs;
		}
		//
		// null_distribution
		//
		template<
			typename Result = int,
			typename Input = int,
			typename Min = boost::mpl::integral_c<Input, 0>,
			typename Max = boost::mpl::integral_c<Input, 1>
		>
		class null_distribution {
		public:
			typedef Result result_type;
			typedef Input input_type;
		public:
			null_distribution() {}
			void reset() {}
			template<typename Engine>
			result_type operator()(Engine& eng) {
				return static_cast<result_type>(eng());
			}
			result_type min() const {
				return Min::value;
			}
			result_type max() const {
				return Max::value;
			}
		};
		template<typename Elem, typename Traits, typename Result, typename Input>
		SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
			std::basic_ostream<Elem, Traits>& lhs,
			null_distribution<Result, Input> const& rhs
			)
		{
			return lhs;
		}
		template<typename Elem, typename Traits, typename Result, typename Input>
		SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
			std::basic_istream<Elem, Traits>& lhs,
			null_distribution<Result, Input>& rhs
			)
		{
			return lhs;
		}
	}	// namespace random
}	// namespace sprig

#endif	// #ifndef SPRIG_RANDOM_NULL_HPP
