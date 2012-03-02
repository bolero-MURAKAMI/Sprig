#ifndef SPRIG_ITERATOR_REFERENCE_ITERATOR_HPP
#define SPRIG_ITERATOR_REFERENCE_ITERATOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <deque>
#include <iterator>
#include <utility>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/ref.hpp>
#include <boost/call_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

//
// SPRIG_REFERENCE_ITERATOR_ARGS_MAX
//
#ifndef SPRIG_REFERENCE_ITERATOR_ARGS_MAX
#	define SPRIG_REFERENCE_ITERATOR_ARGS_MAX 15
#endif	// #ifndef SPRIG_REFERENCE_ITERATOR_ARGS_MAX

//
// SPRIG_REFERENCE_ITERATOR_ENUM[_N]
//
#define SPRIG_REFERENCE_ITERATOR_ENUM(gen) BOOST_PP_ENUM(SPRIG_REFERENCE_ITERATOR_ARGS_MAX, gen, BOOST_PP_EMPTY())
#define SPRIG_REFERENCE_ITERATOR_ENUM_N(n, gen) BOOST_PP_ENUM(n, gen, BOOST_PP_EMPTY())

//
// SPRIG_REFERENCE_ITERATOR_REPEAT[_N]
//
#define SPRIG_REFERENCE_ITERATOR_REPEAT(gen) BOOST_PP_REPEAT(SPRIG_REFERENCE_ITERATOR_ARGS_MAX, gen, BOOST_PP_EMPTY())
#define SPRIG_REFERENCE_ITERATOR_REPEAT_N(n, gen) BOOST_PP_REPEAT(n, gen, BOOST_PP_EMPTY())

//
// SPRIG_REFERENCE_ITERATOR_ARGS_GEN
// SPRIG_REFERENCE_ITERATOR_PUSH_BACK_GEN
// SPRIG_REFERENCE_ITERATOR_CONSTRUCTOR_GEN
// SPRIG_REFERENCE_ITERATOR_OPERATOR_GEN
//
#define SPRIG_REFERENCE_ITERATOR_ARGS_GEN(z, n, d) reference BOOST_PP_CAT(v, n)
#define SPRIG_REFERENCE_ITERATOR_PUSH_BACK_GEN(z, n, d) container_->push_back(boost::ref(BOOST_PP_CAT(v, n)));
#define SPRIG_REFERENCE_ITERATOR_CONSTRUCTOR_GEN(z, n, d) \
	reference_iterator( \
		reference value, \
		SPRIG_REFERENCE_ITERATOR_ENUM_N(BOOST_PP_INC(n), SPRIG_REFERENCE_ITERATOR_ARGS_GEN) \
		) \
		: container_(boost::make_shared<container_type>(1, boost::ref(value))) \
	{ \
		SPRIG_REFERENCE_ITERATOR_REPEAT_N(BOOST_PP_INC(n), SPRIG_REFERENCE_ITERATOR_PUSH_BACK_GEN) \
		initialize(); \
	}
#define SPRIG_REFERENCE_ITERATOR_OPERATOR_GEN(z, n, d) \
	this_type& operator()( \
		reference value, \
		SPRIG_REFERENCE_ITERATOR_ENUM_N(BOOST_PP_INC(n), SPRIG_REFERENCE_ITERATOR_ARGS_GEN) \
		) \
	{ \
		container_->push_back(boost::ref(value)); \
		SPRIG_REFERENCE_ITERATOR_REPEAT_N(BOOST_PP_INC(n), SPRIG_REFERENCE_ITERATOR_PUSH_BACK_GEN) \
		initialize(); \
		return *this; \
	}

namespace sprig {
	//
	// reference_iterator
	//
	template<typename T>
	class reference_iterator
		: public boost::iterator_facade<
			reference_iterator<T>,
			T,
			boost::random_access_traversal_tag
		>
	{
	private:
		typedef reference_iterator this_type;
		typedef boost::iterator_facade<
			reference_iterator,
			T,
			boost::random_access_traversal_tag
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
		typedef typename iterator_facade_type::value_type value_type;
	private:
		typedef boost::reference_wrapper<value_type> wrapper_type;
		typedef std::deque<wrapper_type> container_type;
		typedef boost::shared_ptr<container_type> container_instance_type;
		typedef typename container_type::iterator iterator_type;
		typedef typename container_type::const_iterator const_iterator_type;
	public:
		typedef typename container_type::size_type size_type;
	private:
		container_instance_type container_;
		iterator_type it_;
		iterator_type last_;
	public:
		reference dereference() const {
			return *it_;
		}
		bool equal(this_type const& rhs) const {
			return this == &rhs
				? it_ == rhs.it_
				: it_ == last_ && rhs.it_ == rhs.last_
				;
		}
		void increment() {
			++it_;
		}
		void decrement() {
			--it_;
		}
		void advance(difference_type n) {
			std::advance(it_, n);
		}
		difference_type distance_to(this_type const& rhs) const {
			return std::distance(it_, rhs.it_);
		}
	public:
		reference_iterator()
			: container_(boost::make_shared<container_type>())
			, it_(container_->begin())
			, last_(container_->end())
		{}
		reference_iterator(this_type const& that)
			: container_(that.container_)
			, it_(that.it_)
			, last_(that.last_)
		{}
		explicit reference_iterator(reference value)
			: container_(boost::make_shared<container_type>(1, boost::ref(value)))
			, it_(container_->begin())
			, last_(container_->end())
		{}
		reference_iterator(reference value, size_type const n)
			: container_(boost::make_shared<container_type>(n, boost::ref(value)))
			, it_(container_->begin())
			, last_(container_->end())
		{}
		SPRIG_REFERENCE_ITERATOR_REPEAT(SPRIG_REFERENCE_ITERATOR_CONSTRUCTOR_GEN);
		void initialize() {
			it_ = container_->begin();
			last_ = container_->end();
		}
		this_type& operator()(reference value) {
			container_->push_back(boost::ref(value));
			initialize();
			return *this;
		}
		this_type& operator()(reference value, size_type const n) {
			for (size_type i = 0; i != n; ++i) {
				container_->push_back(boost::ref(value));
			}
			initialize();
			return *this;
		}
		SPRIG_REFERENCE_ITERATOR_REPEAT(SPRIG_REFERENCE_ITERATOR_OPERATOR_GEN);
	};
}

#endif	// #ifndef SPRIG_ITERATOR_REFERENCE_ITERATOR_HPP
