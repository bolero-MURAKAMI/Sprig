/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ARGUMENT_FUNCTOR_HPP
#define SPRIG_ARGUMENT_FUNCTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/always.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// argument_functor
	//
	template<typename T, typename Func, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct argument_functor {
		typedef T result_type;
		typedef Func function_type;
		typedef Predicate predicate_type;
	public:
		template<typename Param>
		struct apply {
			typedef typename predicate_type::template apply<Param>::type type;
		};
	public:
		template<typename Param>
		typename boost::enable_if<is_call_copy_param<Param>, T>::type
		operator()(Param param) {
			return function_type()(param);
		}
		template<typename Param>
		typename boost::disable_if<is_call_copy_param<Param>, T>::type
		operator()(Param const& param) {
			return function_type()(param);
		}
	};
	//
	// implicit_argument_functor
	//
	template<typename T, typename Func, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct implicit_argument_functor {
		typedef T result_type;
		typedef Func function_type;
		typedef Predicate predicate_type;
	public:
		template<typename Param>
		struct apply {
			typedef typename predicate_type::template apply<Param>::type type;
		};
	public:
		template<typename Param>
		typename boost::enable_if<
			boost::mpl::and_<
				typename is_call_copy_param<Param>::type,
				typename boost::is_convertible<Param, T>::type
			>,
			T
		>::type
		operator()(Param param) {
			return param;
		}
		template<typename Param>
		typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<
					typename is_call_copy_param<Param>::type
				>::type,
				typename boost::is_convertible<Param, T>::type
			>,
			T
		>::type
		operator()(Param const& param) {
			return param;
		}
		template<typename Param>
		typename boost::enable_if<
			boost::mpl::and_<
				typename is_call_copy_param<Param>::type,
				typename boost::mpl::not_<
					typename boost::is_convertible<Param, T>::type
				>::type
			>,
			T
		>::type
		operator()(Param param) {
			return function_type()(param);
		}
		template<typename Param>
		typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<
					typename is_call_copy_param<Param>::type
				>::type,
				typename boost::mpl::not_<
					typename boost::is_convertible<Param, T>::type
				>::type
			>,
			T
		>::type
		operator()(Param const& param) {
			return function_type()(param);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_ARGUMENT_FUNCTOR_HPP
