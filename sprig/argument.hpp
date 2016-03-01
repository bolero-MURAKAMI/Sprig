/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ARGUMENT_HPP
#define SPRIG_ARGUMENT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/always.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/tmp/applies.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// argument
	//
	template<typename T, typename Func, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	class argument {
	private:
		typedef argument this_type;
	public:
		typedef T value_type;
		typedef Func function_type;
		typedef Predicate predicate_type;
		typedef typename boost::add_reference<value_type>::type reference_type;
		typedef typename boost::add_reference<typename boost::add_const<value_type>::type>::type const_reference_type;
	private:
		value_type value_;
	public:
		template<typename Param>
		argument(
			Param param,
			typename boost::enable_if<
				boost::mpl::and_<
					typename is_call_copy_param<Param>::type,
					typename predicate_type::template apply<Param>::type
				>
			>::type* = 0
			)
			: value_(function_type()(param))
		{}
		template<typename Param>
		argument(
			Param const& param,
			typename boost::enable_if<
				boost::mpl::and_<
					typename boost::mpl::not_<
						typename is_call_copy_param<Param>::type
					>::type,
					typename predicate_type::template apply<Param>::type
				>
			>::type* = 0
			)
			: value_(function_type()(param))
		{}
		template<typename Param>
		argument(
			Param param,
			typename boost::enable_if<
				boost::mpl::and_<
					typename is_call_copy_param<Param>::type,
					typename boost::mpl::not_<
						typename predicate_type::template apply<Param>::type
					>::type
				>
			>::type* = 0
			)
			: value_(param)
		{}
		template<typename Param>
		argument(
			Param const& param,
			typename boost::enable_if<
				boost::mpl::and_<
					typename boost::mpl::not_<
						typename is_call_copy_param<Param>::type
					>::type,
					typename boost::mpl::not_<
						typename predicate_type::template apply<Param>::type
					>::type
				>
			>::type* = 0
			)
			: value_(param)
		{}
		value_type get() const {
			return value_;
		}
		reference_type ref() {
			return value_;
		}
		const_reference_type ref() const {
			return value_;
		}
		const_reference_type cref() const {
			return value_;
		}
		operator reference_type() {
			return value_;
		}
		operator const_reference_type() const {
			return value_;
		}
	};
	//
	// argument_functor_sequence
	//
	template<typename T, typename Sequence>
	struct argument_functor_sequence {
		typedef T result_type;
		typedef Sequence sequence_type;
	public:
		template<typename Param>
		struct apply {
			typedef typename boost::mpl::if_<
				typename boost::is_same<
					typename boost::mpl::find_if<
						sequence_type,
						boost::mpl::bind<tmp::applies_c<1>, boost::mpl::_1, Param>
					>::type,
					typename boost::mpl::end<sequence_type>::type
				>::type,
				boost::mpl::false_,
				boost::mpl::true_
			>::type type;
		};
	public:
		template<typename Param>
		typename boost::enable_if<is_call_copy_param<Param>, T>::type
		operator()(Param param) {
			return typename boost::mpl::deref<
				typename boost::mpl::find_if<
					sequence_type,
					boost::mpl::bind<tmp::applies_c<1>, boost::mpl::_1, Param>
				>::type
			>::type()(param);
		}
		template<typename Param>
		typename boost::disable_if<is_call_copy_param<Param>, T>::type
		operator()(Param const& param) {
			return typename boost::mpl::deref<
				typename boost::mpl::find_if<
					sequence_type,
					boost::mpl::bind<tmp::applies_c<1>, boost::mpl::_1, Param>
				>::type
			>::type()(param);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_ARGUMENT_HPP
