/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ITERATOR_BINARY_ITERATOR_HPP
#define SPRIG_ITERATOR_BINARY_ITERATOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iterator>
#include <boost/cstdint.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/addressof.hpp>
#include <sprig/assert.hpp>
#include <sprig/endian.hpp>

namespace sprig {
	//
	// big_endian_iterator
	//
	template<typename T>
	class big_endian_iterator
		: public boost::iterator_facade<
			big_endian_iterator<T>,
			unsigned char,
			boost::random_access_traversal_tag
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T data_type;
		typedef boost::uint8_t byte_type;
	private:
		typedef big_endian_iterator this_type;
		typedef boost::iterator_facade<
			big_endian_iterator,
			unsigned char,
			boost::random_access_traversal_tag
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		typedef data_type* data_ptr_type;
		typedef byte_type* byte_ptr_type;
	private:
		data_ptr_type ptr_;
		difference_type index_;
	private:
		reference dereference() const {
			SPRIG_ASSERT(index_ >= 0 && index_ < sizeof(data_type));
			return *(reinterpret_cast<byte_ptr_type>(ptr_) + (is_big_endian() ? index_ : sizeof(data_type) - 1 - index_));
		}
		bool equal(this_type const& rhs) const {
			return index_ == rhs.index_;
		}
		void increment() {
			++index_;
		}
		void decrement() {
			--index_;
		}
		void advance(difference_type n) {
			index_ += n;
		}
		difference_type distance_to(this_type const& rhs) const {
			return rhs.index_ - index_;
		}
	public:
		big_endian_iterator()
			: ptr_(0)
			, index_(sizeof(data_type))
		{}
		explicit big_endian_iterator(data_type& value)
			: ptr_(boost::addressof(value))
			, index_(0)
		{}
		data_type const& get() const {
			return *ptr_;
		}
		data_type& get() {
			return *ptr_;
		}
	};
	//
	// make_big_endian_iterator
	//
	template<typename T>
	SPRIG_INLINE big_endian_iterator<T> make_big_endian_iterator(T& value) {
		return big_endian_iterator<T>(value);
	}
	//
	// little_endian_iterator
	//
	template<typename T>
	class little_endian_iterator
		: public boost::iterator_facade<
			little_endian_iterator<T>,
			unsigned char,
			boost::random_access_traversal_tag
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T data_type;
		typedef unsigned char byte_type;
	private:
		typedef little_endian_iterator this_type;
		typedef boost::iterator_facade<
			little_endian_iterator,
			unsigned char,
			boost::random_access_traversal_tag
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		typedef data_type* data_ptr_type;
		typedef byte_type* byte_ptr_type;
	private:
		data_ptr_type ptr_;
		difference_type index_;
	private:
		reference dereference() const {
			SPRIG_ASSERT(index_ >= 0 && index_ < sizeof(data_type));
			return *(reinterpret_cast<byte_ptr_type>(ptr_) + (is_little_endian() ? index_ : sizeof(data_type) - 1 - index_));
		}
		bool equal(this_type const& rhs) const {
			return index_ == rhs.index_;
		}
		void increment() {
			++index_;
		}
		void decrement() {
			--index_;
		}
		void advance(difference_type n) {
			index_ += n;
		}
		difference_type distance_to(this_type const& rhs) const {
			return rhs.index_ - index_;
		}
	public:
		little_endian_iterator()
			: ptr_(0)
			, index_(sizeof(data_type))
		{}
		explicit little_endian_iterator(data_type& value)
			: ptr_(boost::addressof(value))
			, index_(0)
		{}
		data_type const& get() const {
			return *ptr_;
		}
		data_type& get() {
			return *ptr_;
		}
	};
	//
	// make_little_endian_iterator
	//
	template<typename T>
	SPRIG_INLINE little_endian_iterator<T> make_little_endian_iterator(T& value) {
		return little_endian_iterator<T>(value);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ITERATOR_BINARY_ITERATOR_HPP
