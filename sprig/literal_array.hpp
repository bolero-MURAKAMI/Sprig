#ifndef SPRIG_LITERAL_ARRAY_HPP
#define SPRIG_LITERAL_ARRAY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <boost/utility/swap.hpp>
#include <sprig/assert.hpp>

namespace sprig {
	//
	// literal_array
	//
	template<typename T, bool NullEnd = true>
	class literal_array {
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef const value_type* const_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		static bool const null_end = NullEnd;
	private:
		value_type* elems_;
		size_type size_;
	public:
		literal_array()
			: elems_(0)
			, size_(0)
		{}
		template<size_type N>
		literal_array(value_type (&elems)[N])
			: elems_(elems)
			, size_(null_end ? N : N - 1)
		{}
		// begin, end
		iterator begin() {
			return elems_;
		}
		const_iterator begin() const {
			return elems_;
		}
		iterator end() {
			return elems_ + size_;
		}
		const_iterator end() const {
			return elems_ + size_;
		}
		// rbegin, rend
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
		// operator[]
		reference operator[](size_type i) {
			SPRIG_ASSERT(i < size_ && "index out of range");
			return elems_[i];
		}
		const_reference operator[](size_type i) const {
			SPRIG_ASSERT(i < size_ && "index out of range");
			return elems_[i];
		}
		// at
		reference at(size_type i) {
			rangecheck(i);
			return elems_[i];
		}
		const_reference at(size_type i) const {
			rangecheck(i);
			return elems_[i];
		}
		// front, back
		reference front() {
			return elems_[0];
		}
		const_reference front() const {
			return elems_[0];
		}
		reference back() {
			return elems_[size_ - 1];
		}
		const_reference back() const {
			return elems_[size_ - 1];
		}
		// size, max_size
		size_type size() const {
			return size_;
		}
		size_type max_size() const{
			return size_;
		}
		// empty
		bool empty() const {
			return size_;
		}
		// swap
		void swap(literal_array& rhs) {
			boost::swap(elems_, rhs.elems_);
			boost::swap(size_, rhs.size_);
		}
		// data
		value_type* data() {
			return elems_;
		}
		value_type const* data() const {
			return elems_;
		}
		// c_array
		value_type* c_array() {
			return elems_;
		}
		// rangecheck
		void rangecheck(size_type i) const {
			if (i >= size_) {
				throw std::out_of_range("literal_array<>: index out of range");
			}
		}
	};
	template<typename T>
	SPRIG_INLINE bool operator==(literal_array<T> const& lhs, literal_array<T> const& rhs) {
		return lhs.size() == rhs.size()
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin())
			;
	}
	template<typename T>
	SPRIG_INLINE bool operator!=(literal_array<T> const& lhs, literal_array<T> const& rhs) {
		return !(lhs == rhs);
	}
	//
	// swap
	//
	template<typename T>
	SPRIG_INLINE void swap(literal_array<T>& lhs, literal_array<T>& rhs) {
		lhs.swap(rhs);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_LITERAL_ARRAY_HPP
