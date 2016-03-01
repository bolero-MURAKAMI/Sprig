/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_PREDICATE_HPP
#define SPRIG_PREDICATE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <locale>
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace sprig {
	namespace predicate {
		//
		// is_equal
		// is_iequal
		// is_less
		// is_iless
		// is_not_greater
		// is_not_igreater
		//
		using boost::algorithm::is_equal;
		using boost::algorithm::is_iequal;
		using boost::algorithm::is_less;
		using boost::algorithm::is_iless;
		using boost::algorithm::is_not_greater;
		using boost::algorithm::is_not_igreater;
		//
		// is_greater
		//
		struct is_greater {
		private:
			boost::algorithm::is_not_greater pred_;
		public:
			template<typename T1, typename T2>
			bool operator()(T1 const& lhs, T2 const& rhs) const {
				return !pred_(lhs, rhs);
			}
		};
		//
		// is_igreater
		//
		struct is_igreater {
		private:
			boost::algorithm::is_not_igreater pred_;
		public:
			is_igreater(std::locale const& loc = std::locale())
				: pred_(loc)
			{}
			template<typename T1, typename T2>
			bool operator()(T1 const& lhs, T2 const& rhs) const {
				return !pred_(lhs, rhs);
			}
		};

		//
		// lexicographical_compare_t
		//
		template<typename Predicate = boost::algorithm::is_less>
		struct lexicographical_compare_t {
		public:
			typedef Predicate predicate_type;
		private:
			predicate_type pred_;
		public:
			lexicographical_compare_t() {}
			explicit lexicographical_compare_t(predicate_type pred)
				: pred_(pred)
			{}
			template<typename T1, typename T2>
			bool operator()(T1 const& lhs, T2 const& rhs) const {
				return boost::algorithm::lexicographical_compare(lhs, rhs, pred_);
			}
		};
		//
		// lexicographical_compare
		//
		SPRIG_INLINE sprig::predicate::lexicographical_compare_t<> lexicographical_compare() {
			return lexicographical_compare_t<>();
		}
		template<typename Predicate>
		SPRIG_INLINE sprig::predicate::lexicographical_compare_t<Predicate> lexicographical_compare() {
			return lexicographical_compare_t<Predicate>();
		}
		template<typename Predicate>
		SPRIG_INLINE sprig::predicate::lexicographical_compare_t<Predicate> lexicographical_compare(Predicate pred) {
			return lexicographical_compare_t<Predicate>(pred);
		}
	}	// namespace predicate
}	// namespace sprig

#endif	// #ifndef SPRIG_PREDICATE_HPP
