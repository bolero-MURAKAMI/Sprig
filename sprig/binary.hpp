/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BINARY_HPP
#define SPRIG_BINARY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <algorithm>
#include <iosfwd>
#include <sstream>
#include <iomanip>
#include <string>
#include <utility>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/value_init.hpp>
#include <sprig/split_literal.hpp>
#include <sprig/iterator/ostream_manip_iterator.hpp>
#include <sprig/iterator/binary_iterator.hpp>
#include <sprig/utility/iterator.hpp>

namespace sprig {
	namespace binary_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(line_feed, "\n");
		SPRIG_SPLIT_LITERAL_STRING_DECL(space, " ");
		SPRIG_SPLIT_LITERAL_CHAR_DECL(zero, '0');
	}	// namespace attributes_detail
	//
	// basic_stringize_binary
	//
	template<typename String, typename Iterator>
	SPRIG_INLINE String basic_stringize_binary(
		Iterator first,
		Iterator last,
		std::size_t line_size = 0
		)
	{
		typedef typename String::value_type char_type;
		typedef std::basic_ostringstream<
			char_type,
			typename String::traits_type,
			typename String::allocator_type
		> ostringstream_type;
		ostringstream_type oss(std::ios_base::out | std::ios_base::binary);
		oss
			<< std::hex
			<< std::uppercase
			<< std::setfill(sprig::apply_literal<binary_detail::zero, char_type>::value)
			;
		if (line_size) {
			std::ptrdiff_t d = std::distance(first, last);
			oss
				<< sprig::get_literal<binary_detail::line_feed, char_type>()
				;
			for (std::ptrdiff_t i = 0; i < d - static_cast<ptrdiff_t>(line_size); i += line_size) {
				std::istringstream iss(
					std::string(first, get_advance(first, line_size)),
					std::ios_base::in | std::ios_base::binary
					);
				iss >> std::noskipws;
				std::copy(
					std::istream_iterator<unsigned char>(iss),
					std::istream_iterator<unsigned char>(),
					make_ostream_manip_iterator<unsigned>(
						oss,
						std::setw(2),
						sprig::get_literal<binary_detail::space, char_type>()
						)
					);
				std::advance(first, line_size);
				oss
					<< sprig::get_literal<binary_detail::line_feed, char_type>()
					;
			}
			std::istringstream iss(
				std::string(first, last),
				std::ios_base::in | std::ios_base::binary
				);
			iss
				>> std::noskipws
				;
			std::copy(
				std::istream_iterator<unsigned char>(iss),
				std::istream_iterator<unsigned char>(),
				make_ostream_manip_iterator<unsigned>(
					oss,
					std::setw(2),
					sprig::get_literal<binary_detail::space, char_type>()
					)
				);
			oss
				<< sprig::get_literal<binary_detail::line_feed, char_type>()
				;
		} else {
			std::istringstream iss(
				std::string(first, last),
				std::ios_base::in | std::ios_base::binary
				);
			iss
				>> std::noskipws
				;
			std::copy(
				std::istream_iterator<unsigned char>(iss),
				std::istream_iterator<unsigned char>(),
				make_ostream_manip_iterator<unsigned>(
					oss,
					std::setw(2),
					sprig::get_literal<binary_detail::space, char_type>()
					)
				);
		}
		return oss.str();
	}
	//
	// stringize_binary, wstringize_binary
	//
	template<typename Iterator>
	SPRIG_INLINE std::string stringize_binary(
		Iterator first,
		Iterator last,
		std::size_t line_size = 0
		)
	{
		return basic_stringize_binary<std::string>(first, last, line_size);
	}
	template<typename Iterator>
	SPRIG_INLINE std::wstring wstringize_binary(
		Iterator first,
		Iterator last,
		std::size_t line_size = 0
		)
	{
		return basic_stringize_binary<std::wstring>(first, last, line_size);
	}
	//
	// get_from_big_endian
	//
	template<typename T, typename Iterator>
	SPRIG_INLINE T get_from_big_endian(Iterator first, Iterator last) {
		boost::value_initialized<T> v;
		typename boost::iterator_difference<Iterator>::type diff = std::distance(first, last);
		if (sizeof(T) == diff) {
			std::copy(
				first,
				last,
				big_endian_iterator<T>(v.data())
				);
		} else if (sizeof(T) < diff) {
			std::copy(
				get_advance(first, diff - sizeof(T)),
				last,
				big_endian_iterator<T>(v.data())
				);
		} else if (sizeof(T) > diff) {
			std::copy(
				first,
				last,
				get_advance(big_endian_iterator<T>(v.data()), sizeof(T) - diff)
				);
		}
		return v;
	}
	//
	// set_to_big_endian
	//
	template<typename T, typename Iterator>
	SPRIG_INLINE void set_to_big_endian(T v, Iterator first, Iterator last) {
		std::fill(first, last, boost::value_initialized<typename boost::iterator_value<Iterator>::type>());
		typename boost::iterator_difference<Iterator>::type diff = std::distance(first, last);
		if (sizeof(T) == diff) {
			std::copy(
				big_endian_iterator<T>(v),
				big_endian_iterator<T>(),
				first
				);
		} else if (sizeof(T) < diff) {
			std::copy(
				big_endian_iterator<T>(v),
				big_endian_iterator<T>(),
				get_advance(first, diff - sizeof(T))
				);
		} else if (sizeof(T) > diff) {
			std::copy(
				get_advance(big_endian_iterator<T>(v), sizeof(T) - diff),
				big_endian_iterator<T>(),
				first
				);
		}
	}
	//
	// int_from_big_endian_helper, int_from_big_endian
	//
	//	NOTE: compile-time size version.
	//
	template<typename T, std::size_t N, typename Iterator>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::equal_to<boost::mpl::size_t<N>, boost::mpl::size_t<0> >,
		T
	>::type
	int_from_big_endian_helper(Iterator it) {
		return static_cast<T>(*it);
	}
	template<typename T, std::size_t N, typename Iterator>
	SPRIG_INLINE typename boost::disable_if<
		boost::mpl::equal_to<boost::mpl::size_t<N>, boost::mpl::size_t<0> >,
		T
	>::type
	int_from_big_endian_helper(Iterator it) {
		T result = static_cast<T>(*it);
		return (result <<= N) + int_from_big_endian_helper<T, N - 8>(++it);
	}
	template<typename T, std::size_t N, typename Iterator>
	SPRIG_INLINE T int_from_big_endian(Iterator it) {
		typedef typename boost::mpl::min<
			boost::mpl::size_t<N>,
			boost::mpl::size_t<sizeof(T)>
		>::type size_type;
		if (size_type::value < N) {
			std::advance(it, N - size_type::value);
		}
		return int_from_big_endian_helper<T, (size_type::value - 1) * 8>(it);
	}
	//
	// int_from_big_endian_helper, int_from_big_endian
	//
	//	NOTE: run-time size version.
	//
	template<typename T, typename Iterator>
	SPRIG_INLINE T int_from_big_endian_helper(Iterator it, std::size_t n) {
		T result = static_cast<T>(*it);
		return n
			? (result <<= n) + int_from_big_endian_helper<T>(++it, n - 8)
			: result
			;
	}
	template<typename T, typename Iterator>
	SPRIG_INLINE T int_from_big_endian(Iterator it, std::size_t n) {
		std::size_t size = std::min(n, sizeof(T));
		if (size < n) {
			std::advance(it, n - size);
		}
		return int_from_big_endian_helper<T>(it, (size - 1) * 8);
	}
	//
	// int_from_little_endian_helper, int_from_little_endian
	//
	//	NOTE: compile-time size version.
	//
	template<typename T, std::size_t N, std::size_t Max, typename Iterator>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::equal_to<boost::mpl::size_t<N + 8>, boost::mpl::size_t<Max> >,
		T
	>::type
	int_from_little_endian_helper(Iterator it) {
		T result = static_cast<T>(*it);
		return result <<= N;
	}
	template<typename T, std::size_t N, std::size_t Max, typename Iterator>
	SPRIG_INLINE typename boost::disable_if<
		boost::mpl::equal_to<boost::mpl::size_t<N + 8>, boost::mpl::size_t<Max> >,
		T
	>::type
	int_from_little_endian_helper(Iterator it) {
		T result = static_cast<T>(*it);
		return (result <<= N) + int_from_little_endian_helper<T, N + 8, Max>(++it);
	}
	template<typename T, std::size_t N, typename Iterator>
	SPRIG_INLINE T int_from_little_endian(Iterator it) {
		typedef typename boost::mpl::min<
			boost::mpl::size_t<N>,
			boost::mpl::size_t<sizeof(T)>
		>::type size_type;
		T result = static_cast<T>(*it);
		return 1 != size_type::value
			? result + int_from_little_endian_helper<T, 8, size_type::value * 8>(++it)
			: result
			;
	}
	//
	// int_from_little_endian_helper, int_from_little_endian
	//
	//	NOTE: run-time size version.
	//
	template<typename T, typename Iterator>
	SPRIG_INLINE T int_from_little_endian_helper(Iterator it, std::size_t n, std::size_t max) {
		T result = static_cast<T>(*it);
		return n + 8 != max
			? (result <<= n) + int_from_little_endian_helper<T>(++it, n + 8, max)
			: result <<= n
			;
	}
	template<typename T, typename Iterator>
	SPRIG_INLINE T int_from_little_endian(Iterator it, std::size_t n) {
		std::size_t size = std::min(n, sizeof(T));
		T result = static_cast<T>(*it);
		return 1 != size
			? result + int_from_little_endian_helper<T>(++it, 8, size * 8)
			: result
			;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_BINARY_HPP
