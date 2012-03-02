#ifndef SPRIG_ITERATOR_COUNTED_ITERATOR_HPP
#define SPRIG_ITERATOR_COUNTED_ITERATOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iterator>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// counted_iterator
	//
	template<typename T, typename Enable = void>
	class counted_iterator {};
	//
	// counted_iterator
	//
	//	COMMENT: incrementable_traversal_tag
	//
	template<typename T>
	class counted_iterator<
		T,
		typename boost::enable_if<boost::is_same<typename boost::iterator_traversal<T>::type, boost::incrementable_traversal_tag> >::type
	>
		: public boost::iterator_facade<
			counted_iterator<T>,
			typename std::iterator_traits<T>::value_type,
			typename std::iterator_traits<T>::iterator_category,
			typename std::iterator_traits<T>::reference,
			typename std::iterator_traits<T>::difference_type
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T interior_type;
	private:
		typedef counted_iterator this_type;
		typedef boost::iterator_facade<
			counted_iterator,
			typename std::iterator_traits<interior_type>::value_type,
			typename std::iterator_traits<interior_type>::iterator_category,
			typename std::iterator_traits<interior_type>::reference,
			typename std::iterator_traits<interior_type>::difference_type
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		interior_type it_;
		difference_type count_;
	private:
		reference dereference() const {
			return *it_;
		}
		void increment() {
			++it_;
			++count_;
		}
	public:
		counted_iterator(interior_type it, difference_type count = 0)
			: it_(it)
			, count_(count)
		{}
		interior_type get() const {
			return it_;
		}
		difference_type count() const {
			return count_;
		}
	};
	//
	// counted_iterator
	//
	//	COMMENT: single_pass_traversal_tag
	//
	template<typename T>
	class counted_iterator<
		T,
		typename boost::enable_if<boost::is_same<typename boost::iterator_traversal<T>::type, boost::single_pass_traversal_tag> >::type
	>
		: public boost::iterator_facade<
			counted_iterator<T>,
			typename std::iterator_traits<T>::value_type,
			typename std::iterator_traits<T>::iterator_category,
			typename std::iterator_traits<T>::reference,
			typename std::iterator_traits<T>::difference_type
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T interior_type;
	private:
		typedef counted_iterator this_type;
		typedef boost::iterator_facade<
			counted_iterator,
			typename std::iterator_traits<interior_type>::value_type,
			typename std::iterator_traits<interior_type>::iterator_category,
			typename std::iterator_traits<interior_type>::reference,
			typename std::iterator_traits<interior_type>::difference_type
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		interior_type it_;
		difference_type count_;
	private:
		reference dereference() const {
			return *it_;
		}
		bool equal(this_type const& rhs) const {
			return it_ == rhs.it_;
		}
		void increment() {
			++it_;
			++count_;
		}
	public:
		counted_iterator(interior_type it, difference_type count = 0)
			: it_(it)
			, count_(count)
		{}
		interior_type get() const {
			return it_;
		}
		difference_type count() const {
			return count_;
		}
	};
	//
	// counted_iterator
	//
	//	COMMENT: forward_traversal_tag
	//
	template<typename T>
	class counted_iterator<
		T,
		typename boost::enable_if<boost::is_same<typename boost::iterator_traversal<T>::type, boost::forward_traversal_tag> >::type
	>
		: public boost::iterator_facade<
			counted_iterator<T>,
			typename std::iterator_traits<T>::value_type,
			typename std::iterator_traits<T>::iterator_category,
			typename std::iterator_traits<T>::reference,
			typename std::iterator_traits<T>::difference_type
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T interior_type;
	private:
		typedef counted_iterator this_type;
		typedef boost::iterator_facade<
			counted_iterator,
			typename std::iterator_traits<interior_type>::value_type,
			typename std::iterator_traits<interior_type>::iterator_category,
			typename std::iterator_traits<interior_type>::reference,
			typename std::iterator_traits<interior_type>::difference_type
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		interior_type it_;
		difference_type count_;
	private:
		reference dereference() const {
			return *it_;
		}
		bool equal(this_type const& rhs) const {
			return it_ == rhs.it_;
		}
		void increment() {
			++it_;
			++count_;
		}
	public:
		counted_iterator(interior_type it, difference_type count = 0)
			: it_(it)
			, count_(count)
		{}
		interior_type get() const {
			return it_;
		}
		difference_type count() const {
			return count_;
		}
	};
	//
	// counted_iterator
	//
	//	COMMENT: bidirectional_traversal_tag
	//
	template<typename T>
	class counted_iterator<
		T,
		typename boost::enable_if<boost::is_same<typename boost::iterator_traversal<T>::type, boost::bidirectional_traversal_tag> >::type
	>
		: public boost::iterator_facade<
			counted_iterator<T>,
			typename std::iterator_traits<T>::value_type,
			typename std::iterator_traits<T>::iterator_category,
			typename std::iterator_traits<T>::reference,
			typename std::iterator_traits<T>::difference_type
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T interior_type;
	private:
		typedef counted_iterator this_type;
		typedef boost::iterator_facade<
			counted_iterator,
			typename std::iterator_traits<interior_type>::value_type,
			typename std::iterator_traits<interior_type>::iterator_category,
			typename std::iterator_traits<interior_type>::reference,
			typename std::iterator_traits<interior_type>::difference_type
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		interior_type it_;
		difference_type count_;
	private:
		reference dereference() const {
			return *it_;
		}
		bool equal(this_type const& rhs) const {
			return it_ == rhs.it_;
		}
		void increment() {
			++it_;
			++count_;
		}
		void decrement() {
			--it_;
			--count_;
		}
	public:
		counted_iterator(interior_type it, difference_type count = 0)
			: it_(it)
			, count_(count)
		{}
		interior_type get() const {
			return it_;
		}
		difference_type count() const {
			return count_;
		}
	};
	//
	// counted_iterator
	//
	//	COMMENT: random_access_traversal_tag
	//
	template<typename T>
	class counted_iterator<
		T,
		typename boost::enable_if<boost::is_same<typename boost::iterator_traversal<T>::type, boost::random_access_traversal_tag> >::type
	>
		: public boost::iterator_facade<
			counted_iterator<T>,
			typename std::iterator_traits<T>::value_type,
			typename std::iterator_traits<T>::iterator_category,
			typename std::iterator_traits<T>::reference,
			typename std::iterator_traits<T>::difference_type
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T interior_type;
	private:
		typedef counted_iterator this_type;
		typedef boost::iterator_facade<
			counted_iterator,
			typename std::iterator_traits<interior_type>::value_type,
			typename std::iterator_traits<interior_type>::iterator_category,
			typename std::iterator_traits<interior_type>::reference,
			typename std::iterator_traits<interior_type>::difference_type
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		interior_type it_;
		difference_type count_;
	private:
		reference dereference() const {
			return *it_;
		}
		bool equal(this_type const& rhs) const {
			return it_ == rhs.it_;
		}
		void increment() {
			++it_;
			++count_;
		}
		void decrement() {
			--it_;
			--count_;
		}
		void advance(difference_type n) {
			std::advance(it_, n);
			count_ += n;
		}
		difference_type distance_to(this_type const& rhs) const {
			return std::distance(it_, rhs.it_);
		}
	public:
		counted_iterator(interior_type it, difference_type count = 0)
			: it_(it)
			, count_(count)
		{}
		interior_type get() const {
			return it_;
		}
		difference_type count() const {
			return count_;
		}
	};
	//
	// make_counted_iterator
	//
	template<typename T>
	SPRIG_INLINE counted_iterator<T> make_counted_iterator(T it) {
		return counted_iterator<T>(it);
	}
	template<typename T, typename differenceT>
	SPRIG_INLINE counted_iterator<T> make_counted_iterator(T it, differenceT n) {
		return counted_iterator<T>(it, n);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ITERATOR_COUNTED_ITERATOR_HPP
