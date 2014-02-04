/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_CONTAINER_HPP
#define SPRIG_UTILITY_CONTAINER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <functional>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// push_back_
	//
	template<typename T1, typename T2 = typename T1::value_type, typename Dummy = void>
	struct push_back_ {};
	template<typename T1, typename T2>
	struct push_back_<T1, T2, typename boost::enable_if<sprig::is_call_copy_param<T2> >::type>
		: public std::binary_function<T1, T2, void>
	{
	private:
		typedef std::binary_function<T1, T2, void> binary_function_type;
	public:
		typedef typename binary_function_type::result_type result_type;
		typedef typename binary_function_type::first_argument_type first_argument_type;
		typedef typename binary_function_type::second_argument_type second_argument_type;
	public:
		result_type operator()(first_argument_type& lhs, second_argument_type rhs) const {
			lhs.push_back(rhs);
		}
	};
	template<typename T1, typename T2>
	struct push_back_<T1, T2, typename boost::disable_if<sprig::is_call_copy_param<T2> >::type>
		: public std::binary_function<T1, T2, void>
	{
	private:
		typedef std::binary_function<T1, T2, void> binary_function_type;
	public:
		typedef typename binary_function_type::result_type result_type;
		typedef typename binary_function_type::first_argument_type first_argument_type;
		typedef typename binary_function_type::second_argument_type second_argument_type;
	public:
		result_type operator()(first_argument_type& lhs, second_argument_type const& rhs) const {
			lhs.push_back(rhs);
		}
	};
	//
	// any_push_back_
	//
	struct any_push_back_ {
		template<typename T1, typename T2>
		typename boost::enable_if<sprig::is_call_copy_param<T2> >::type
		operator()(T1& lhs, T2 rhs) const {
			lhs.push_back(rhs);
		}
		template<typename T1, typename T2>
		typename boost::disable_if<sprig::is_call_copy_param<T2> >::type
		operator()(T1& lhs, T2 const& rhs) const {
			lhs.push_back(rhs);
		}
	};
	//
	// push_front_
	//
	template<typename T1, typename T2 = typename T1::value_type, typename Dummy = void>
	struct push_front_ {};
	template<typename T1, typename T2>
	struct push_front_<T1, T2, typename boost::enable_if<sprig::is_call_copy_param<T2> >::type>
		: public std::binary_function<T1, T2, void>
	{
	private:
		typedef std::binary_function<T1, T2, void> binary_function_type;
	public:
		typedef typename binary_function_type::result_type result_type;
		typedef typename binary_function_type::first_argument_type first_argument_type;
		typedef typename binary_function_type::second_argument_type second_argument_type;
	public:
		result_type operator()(first_argument_type& lhs, second_argument_type rhs) const {
			lhs.push_front(rhs);
		}
	};
	template<typename T1, typename T2>
	struct push_front_<T1, T2, typename boost::disable_if<sprig::is_call_copy_param<T2> >::type>
		: public std::binary_function<T1, T2, void>
	{
	private:
		typedef std::binary_function<T1, T2, void> binary_function_type;
	public:
		typedef typename binary_function_type::result_type result_type;
		typedef typename binary_function_type::first_argument_type first_argument_type;
		typedef typename binary_function_type::second_argument_type second_argument_type;
	public:
		result_type operator()(first_argument_type& lhs, second_argument_type const& rhs) const {
			lhs.push_front(rhs);
		}
	};
	//
	// any_push_front_
	//
	struct any_push_front_ {
		template<typename T1, typename T2>
		typename boost::enable_if<sprig::is_call_copy_param<T2> >::type
		operator()(T1& lhs, T2 rhs) const {
			lhs.push_front(rhs);
		}
		template<typename T1, typename T2>
		typename boost::disable_if<sprig::is_call_copy_param<T2> >::type
		operator()(T1& lhs, T2 const& rhs) const {
			lhs.push_front(rhs);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_CONTAINER_HPP
