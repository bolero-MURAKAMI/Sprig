#ifndef SPRIG_ALGORITHM_HPP
#define SPRIG_ALGORITHM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <functional>
#include <boost/ref.hpp>
#include <boost/next_prior.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// find
	//
	template<typename InputIterator, typename T, typename Predicate>
	SPRIG_INLINE typename boost::enable_if<
		is_call_copy_param<T>,
		InputIterator
	>::type find(InputIterator first, InputIterator last, T const value, Predicate pred) {
		for (; first != last; ++first) {
			if (pred(*first, value)) {
				return first;
			}
		}
		return last;
	}
	template<typename InputIterator, typename T, typename Predicate>
	SPRIG_INLINE typename boost::disable_if<
		is_call_copy_param<T>,
		InputIterator
	>::type find(InputIterator first, InputIterator last, T const& value, Predicate pred) {
		for (; first != last; ++first) {
			if (pred(*first, value)) {
				return first;
			}
		}
		return last;
	}
	//
	// count
	//
	template<typename InputIterator, typename T, typename Predicate>
	SPRIG_INLINE typename boost::enable_if<
		is_call_copy_param<T>,
		typename boost::iterator_difference<InputIterator>::type
	>::type count(InputIterator first, InputIterator last, T const value, Predicate pred) {
		typename boost::iterator_difference<InputIterator>::type result = 0;
		for (; first != last; ++first) {
			if (pred(*first, value)) {
				++result;
			}
		}
		return result;
	}
	template<typename Iterator, typename T, typename Predicate>
	SPRIG_INLINE typename boost::disable_if<
		is_call_copy_param<T>,
		typename boost::iterator_difference<Iterator>::type
	>::type count(Iterator first, Iterator last, T const& value, Predicate pred) {
		typename boost::iterator_difference<Iterator>::type result = 0;
		for (; first != last; ++first) {
			if (pred(*first, value)) {
				++result;
			}
		}
		return result;
	}
	//
	// is_sorted
	//
	template<typename InputIterator>
	SPRIG_INLINE bool is_sorted(InputIterator first, InputIterator last) {
		return boost::range::is_sorted(
			boost::make_iterator_range(first, last)
			);
	}
	template<typename InputIterator, typename Predicate>
	SPRIG_INLINE bool is_sorted(InputIterator first, InputIterator last, Predicate pred) {
		return boost::range::is_sorted(
			boost::make_iterator_range(first, last),
			pred
			);
	}
	//
	// is_unique
	//
	template<typename InputIterator>
	SPRIG_INLINE bool is_unique(InputIterator first, InputIterator last) {
		return is_unique(
			first,
			last,
			std::equal_to<typename boost::iterator_value<InputIterator>::type>()
			);
	}
	template<typename InputIterator, typename Predicate>
	SPRIG_INLINE bool is_unique(InputIterator first, InputIterator last, Predicate pred) {
		for (; first != last; ++first) {
			if (find(boost::next(first), last, *first, pred) != last) {
				return false;
			}
		}
		return true;
	}
	template<typename Range>
	SPRIG_INLINE bool is_unique(Range const& range) {
		return is_unique(
			boost::begin(range),
			boost::end(range)
			);
	}
	template<typename Range, typename Predicate>
	SPRIG_INLINE bool is_unique(Range const& range, Predicate pred) {
		return is_unique(
			boost::begin(range),
			boost::end(range),
			pred
			);
	}
	//
	// is_equality
	//
	template<typename InputIterator>
	SPRIG_INLINE bool is_equality(InputIterator first, InputIterator last) {
		return is_equality(boost::make_iterator_range(first, last));
	}
	template<typename InputIterator, typename Predicate>
	SPRIG_INLINE bool is_equality(InputIterator first, InputIterator last, Predicate pred) {
		return is_equality(boost::make_iterator_range(first, last), pred);
	}
	template<typename Range>
	SPRIG_INLINE bool is_equality(Range const& range) {
		return is_equality(range, std::equal_to<typename boost::range_value<Range>::type>());
	}
	template<typename Range, typename Predicate>
	SPRIG_INLINE bool is_equality(Range const& range, Predicate pred) {
		return boost::range::is_sorted(range, pred);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ALGORITHM_HPP
