#ifndef SPRIG_STRING_ARGUMENT_FUNCTOR_HPP
#define SPRIG_STRING_ARGUMENT_FUNCTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/lexical_cast.hpp>
#include <boost/mpl/always.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/argument_functor.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// lexical_cast_functor
	//
	template<typename T>
	struct lexical_cast_functor {
		template<typename Param>
		typename boost::enable_if<sprig::is_call_copy_param<Param>, T>::type
		operator()(Param param) {
			return boost::lexical_cast<T>(param);
		}
		template<typename Param>
		typename boost::disable_if<sprig::is_call_copy_param<Param>, T>::type
		operator()(Param const& param) {
			return boost::lexical_cast<T>(param);
		}
	};
	//
	// str_cast_functor
	//
	template<typename T>
	struct str_cast_functor {
		template<typename Param>
		typename boost::enable_if<sprig::is_call_copy_param<Param>, T>::type
		operator()(Param param) {
			return str_cast<T>(param);
		}
		template<typename Param>
		typename boost::disable_if<sprig::is_call_copy_param<Param>, T>::type
		operator()(Param const& param) {
			return str_cast<T>(param);
		}
	};
	//
	// lexical_cast_argument_functor
	//
	template<typename T, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct lexical_cast_argument_functor
		: public argument_functor<T, lexical_cast_functor<T>, Predicate>
	{};
	template<typename T, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct implicit_lexical_cast_argument_functor
		: public implicit_argument_functor<T, lexical_cast_functor<T>, Predicate>
	{};
	//
	// str_cast_argument_functor
	//
	template<typename T, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct str_cast_argument_functor
		: public argument_functor<T, str_cast_functor<T>, Predicate>
	{};
	template<typename T, typename Predicate = boost::mpl::always<boost::mpl::true_> >
	struct implicit_str_cast_argument_functor
		: public implicit_argument_functor<T, str_cast_functor<T>, Predicate>
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_STRING_ARGUMENT_FUNCTOR_HPP
