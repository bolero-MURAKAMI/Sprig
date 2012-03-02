#ifndef SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_ZZ_HPP
#define SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_ZZ_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/external/ntl/rr.hpp>
#include <sprig/external/ntl/xdouble.hpp>
#include <sprig/external/ntl/quad_float.hpp>
#include <sprig/type_traits/remove_const_reference.hpp>

namespace sprig {
	//ntl_convertion_traits
	//
	// to_ZZ_convertion_traits
	//
	struct to_ZZ_convertion_traits {
		//
		// type_list
		//
		typedef boost::mpl::vector<
			long,
			int,
			unsigned long,
			unsigned int,
			double,
			float,
			NTL::ZZ,
			NTL::RR,
			NTL::xdouble,
			NTL::quad_float,
			char const*
		> type_list;
	public:
		//
		// is_unique_result
		//
		template<typename T>
		struct is_unique_result
			: public boost::mpl::bool_<T::value == 1>
		{};
		//
		// pure
		//
		template<typename T>
		struct pure
			: public remove_const_reference<T>
		{};
	public:
		//
		// is_same
		//
		template<typename lhsT>
		struct is_same {
			template<typename rhsT>
			struct apply
				: public boost::is_same<typename pure<lhsT>::type, rhsT>
			{};
		};
		//
		// is_convertible
		//
		template<typename lhsT>
		struct is_convertible {
			template<typename rhsT>
			struct apply
				: public boost::is_convertible<lhsT, rhsT>
			{};
		};
		//
		// less_sizeof_signed
		//
		struct less_sizeof_signed {
			template<typename lhsT, typename rhsT>
			struct apply
				: public boost::mpl::if_<
					typename boost::is_signed<lhsT>::type,
					typename boost::mpl::if_<
						typename boost::is_signed<rhsT>::type,
						boost::mpl::bool_<(sizeof(lhsT) < sizeof(rhsT))>,
						boost::mpl::false_
					>::type,
					typename boost::mpl::if_<
						typename boost::is_signed<rhsT>::type,
						boost::mpl::true_,
						boost::mpl::false_
					>::type
				>
			{};
		};
		//
		// less_sizeof_unsigned
		//
		struct less_sizeof_unsigned {
			template<typename lhsT, typename rhsT>
			struct apply
				: public boost::mpl::if_<
					typename boost::is_unsigned<lhsT>::type,
					typename boost::mpl::if_<
						typename boost::is_unsigned<rhsT>::type,
						boost::mpl::bool_<(sizeof(lhsT) < sizeof(rhsT))>,
						boost::mpl::false_
					>::type,
					typename boost::mpl::if_<
						typename boost::is_unsigned<rhsT>::type,
						boost::mpl::true_,
						boost::mpl::false_
					>::type
				>
			{};
		};
		//
		// less_sizeof_float
		//
		struct less_sizeof_float {
			template<typename lhsT, typename rhsT>
			struct apply
				: public boost::mpl::if_<
					typename boost::is_float<lhsT>::type,
					typename boost::mpl::if_<
						typename boost::is_float<rhsT>::type,
						boost::mpl::bool_<(sizeof(lhsT) < sizeof(rhsT))>,
						boost::mpl::false_
					>::type,
					typename boost::mpl::if_<
						typename boost::is_float<rhsT>::type,
						boost::mpl::true_,
						boost::mpl::false_
					>::type
				>
			{};
		};
	public:
		//
		// max_signed
		//
		typedef boost::mpl::deref<boost::mpl::max_element<type_list, less_sizeof_signed>::type>::type max_signed;
		//
		// max_unsigned
		//
		typedef boost::mpl::deref<boost::mpl::max_element<type_list, less_sizeof_unsigned>::type>::type max_unsigned;
		//
		// max_integral
		//
		typedef boost::mpl::if_c<
			(sizeof(max_unsigned) < sizeof(max_signed)),
			max_signed,
			max_unsigned
		>::type max_integral;
		//
		// max_float
		//
		typedef boost::mpl::deref<boost::mpl::max_element<type_list, less_sizeof_float>::type>::type max_float;
	};

	//
	// is_convertible_to_ZZ
	//
	template<typename T, typename Enable = void>
	struct is_convertible_to_ZZ
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_convertible_to_ZZ<
		T,
		typename boost::enable_if<
			boost::mpl::or_<
				typename to_ZZ_convertion_traits::is_unique_result<
					typename boost::mpl::count_if<
						to_ZZ_convertion_traits::type_list,
						to_ZZ_convertion_traits::is_same<T>
					>::type
				>::type,
				typename to_ZZ_convertion_traits::is_unique_result<
					typename boost::mpl::count_if<
						to_ZZ_convertion_traits::type_list,
						to_ZZ_convertion_traits::is_convertible<T>
					>::type
				>::type,
				typename boost::mpl::and_<
					typename boost::is_integral<T>::type,
					boost::mpl::bool_<(sizeof(T) < sizeof(to_ZZ_convertion_traits::max_integral))>
				>::type,
				typename boost::mpl::and_<
					typename boost::is_float<T>::type,
					boost::mpl::bool_<(sizeof(T) < sizeof(to_ZZ_convertion_traits::max_float))>
				>::type
			>
		>::type
	>
		: public boost::mpl::true_
	{};
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_TRAITS_IS_CONVERTIBLE_TO_ZZ_HPP
