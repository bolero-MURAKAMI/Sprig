/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_IS_FUSION_VECTOR_HPP
#define SPRIG_TYPE_TRAITS_IS_FUSION_VECTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	namespace is_fusion_vector_detail {
		//
		// optional_size
		//
		template<typename T>
		struct optional_size
			: public boost::mpl::eval_if<
				boost::fusion::traits::is_sequence<T>,
				boost::fusion::result_of::size<T>,
				boost::mpl::int_<-1>
			>::type
		{};
		//
		// optional_value_at_c
		//
		template<typename T, int N>
		struct optional_value_at_c
			: public boost::mpl::eval_if_c<
				(optional_size<T>::value > N),
				boost::fusion::result_of::value_at_c<T, N>,
				boost::mpl::identity<void>
			>
		{};
	}	// namespace is_fusion_vector_detail
	//
	// is_fusion_vector0
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector0
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector0<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				boost::fusion::vector0<>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector1
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector1
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector1<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				boost::fusion::vector1<
					typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector2
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector2
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector2<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				boost::fusion::vector2<
					typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type,
					typename is_fusion_vector_detail::optional_value_at_c<T, 1>::type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector3
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector3
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector3<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				boost::fusion::vector3<
					typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type,
					typename is_fusion_vector_detail::optional_value_at_c<T, 1>::type,
					typename is_fusion_vector_detail::optional_value_at_c<T, 2>::type
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector_0
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector_0
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector_0<
		T,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::mpl::bool_<is_fusion_vector_detail::optional_size<T>::value == 0>,
				boost::is_same<
					T,
					boost::fusion::vector<>
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector_1
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector_1
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector_1<
		T,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::mpl::bool_<is_fusion_vector_detail::optional_size<T>::value == 1>,
				boost::is_same<
					T,
					boost::fusion::vector<
						typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type
					>
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector_2
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector_2
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector_2<
		T,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::mpl::bool_<is_fusion_vector_detail::optional_size<T>::value == 2>,
				boost::is_same<
					T,
					boost::fusion::vector<
						typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type,
						typename is_fusion_vector_detail::optional_value_at_c<T, 1>::type
					>
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector_3
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector_3
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector_3<
		T,
		typename boost::enable_if<
			boost::mpl::and_<
				boost::mpl::bool_<is_fusion_vector_detail::optional_size<T>::value == 3>,
				boost::is_same<
					T,
					boost::fusion::vector<
						typename is_fusion_vector_detail::optional_value_at_c<T, 0>::type,
						typename is_fusion_vector_detail::optional_value_at_c<T, 1>::type,
						typename is_fusion_vector_detail::optional_value_at_c<T, 2>::type
					>
				>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// is_fusion_vector
	//
	template<typename T, typename Enable = void>
	struct is_fusion_vector
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_fusion_vector<
		T,
		typename boost::enable_if<
			boost::mpl::or_<
				is_fusion_vector_0<T>,
				is_fusion_vector_1<T>,
				is_fusion_vector_2<T>,
				is_fusion_vector_3<T>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_FUSION_VECTOR_HPP
