#ifndef SPRIG_TMP_BIT_TRAITS_HPP
#define SPRIG_TMP_BIT_TRAITS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/mpl/void.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace sprig {
	namespace tmp {
		//
		// bit_traits
		//
		template<
			typename T1 = boost::mpl::void_,
			typename T2 = boost::mpl::void_,
			typename T3 = boost::mpl::void_,
			typename T4 = boost::mpl::void_,
			typename T5 = boost::mpl::void_,
			typename T6 = boost::mpl::void_,
			typename T7 = boost::mpl::void_,
			typename T8 = boost::mpl::void_
		>
		struct bit_traits {
		public:
			typedef std::size_t value_type;
		private:
			template<typename T, value_type N>
			struct correction
				: public boost::mpl::size_t<
					boost::mpl::if_<
						typename boost::is_same<T, boost::mpl::void_>::type,
						boost::mpl::size_t<0>,
						boost::mpl::size_t<1>
					>::type::value * N
				>
			{};
		public:
			static const value_type value
				= correction<T1, 0x0001>::value
				+ correction<T2, 0x0002>::value
				+ correction<T3, 0x0004>::value
				+ correction<T4, 0x0008>::value
				+ correction<T5, 0x0010>::value
				+ correction<T6, 0x0020>::value
				+ correction<T7, 0x0040>::value
				+ correction<T8, 0x0080>::value
				;
		public:
			template<value_type N>
			struct and_c
				: public boost::mpl::bool_<N & value>
			{};
			template<typename T>
			struct and_
				: public and_c<T::value>
			{};
			template<value_type N>
			struct xor_c
				: public boost::mpl::bool_<N ^ value>
			{};
			template<typename T>
			struct xor_
				: public xor_c<T::value>
			{};
			template<value_type N>
			struct or_c
				: public boost::mpl::bool_<N | value>
			{};
			template<typename T>
			struct or_
				: public xor_c<T::value>
			{};
		};
	}	// namespace tmp
}	// namespace sprig

#endif	// #ifndef SPRIG_TMP_BIT_TRAITS_HPP
