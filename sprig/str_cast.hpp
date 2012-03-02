#ifndef SPRIG_STR_CAST_HPP
#define SPRIG_STR_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <clocale>
#include <cstdlib>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/smart_ptr/shared_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/exception.hpp>
#include <sprig/locale_saver.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_call_reference_param.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/type_traits/c_str_element.hpp>
#include <sprig/type_traits/is_basic_string.hpp>
#include <sprig/type_traits/has_member_xxx.hpp>

#include <boost/version.hpp>
#if BOOST_VERSION == 104800
#	include <sstream>
#	include <boost/type_traits/is_void.hpp>
#	include <boost/type_traits/remove_pointer.hpp>
#endif	//#if BOOST_VERSION == 104800

namespace sprig {
	//
	// basic_str_cast_traits
	//
	template<typename T>
	struct basic_str_cast_traits {
	public:
		typedef typename T::value_type value_type;
		typedef boost::mpl::true_ explicit_c_str;
	public:
		static value_type const* c_str(T const& str) {
			return str.c_str();
		}
	};
	//
	// str_cast_traits
	//
	template<typename T, typename Enable = void>
	struct str_cast_traits {};
	template<typename T>
	struct str_cast_traits<
		T,
		typename boost::enable_if<
			is_basic_string<T>
		>::type
	>
		: public basic_str_cast_traits<T>
	{};

	namespace str_cast_detail {
		//
		// has_value_type;
		//
		BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type);
		//
		// has_explicit_c_str;
		//
		BOOST_MPL_HAS_XXX_TRAIT_DEF(explicit_c_str);
		//
		// has_member_c_str;
		//
		SPRIG_HAS_MEMBER_XXX_TRAIT_DEF(c_str);
		//
		// is_specialized
		//
		template<typename T>
		struct is_specialized
			: public has_value_type<str_cast_traits<T> >
		{};
		//
		// is_not_specialized
		//
		template<typename T>
		struct is_not_specialized
			: public boost::mpl::not_<
				is_specialized<T>
			>
		{};
		//
		// has_c_str
		//
		template<typename T, typename Enable = void>
		struct has_c_str
			: public boost::mpl::false_
		{};
		template<typename T>
		struct has_c_str<
			T,
			typename boost::enable_if<
				is_specialized<T>
			>::type
		>
			: public boost::mpl::or_<
				has_member_c_str<
					str_cast_traits<T>,
					typename str_cast_traits<T>::value_type const* (*)(T const&)
				>,
				has_explicit_c_str<
					str_cast_traits<T>
				>
			>
		{};
		//
		// has_not_c_str
		//
		template<typename T>
		struct has_not_c_str
			: public boost::mpl::not_<
				has_c_str<T>
			>
		{};
		//
		// is_convertible
		//
		template<typename From, typename To>
		struct is_convertible
			: public boost::is_convertible<From, To>
		{};
		//
		// is_not_convertible
		//
		template<typename From, typename To>
		struct is_not_convertible
			: public boost::mpl::not_<
				is_convertible<From, To>
			>
		{};
		//
		// is_c_str
		//
		template<typename T>
		struct is_c_str
			: public sprig::is_c_str<T>
		{};
		//
		// is_not_c_str
		//
		template<typename T>
		struct is_not_c_str
			: public boost::mpl::not_<
				is_c_str<T>
			>
		{};
		//
		// is_char_c_str
		//
		template<typename T>
		struct is_char_c_str
			: public is_char_type<
				typename c_str_element<T>::type
			>
		{};
		//
		// is_wchar_c_str
		//
		template<typename T>
		struct is_wchar_c_str
			: public is_wchar_type<
				typename c_str_element<T>::type
			>
		{};
		//
		// is_char_string
		//
		template<typename T, typename Enable = void>
		struct is_char_string
			: public boost::mpl::false_
		{};
		template<typename T>
		struct is_char_string<
			T,
			typename boost::enable_if<
				is_specialized<T>
			>::type
		>
			: public is_char_type<
				typename str_cast_traits<T>::value_type
			>
		{};
		//
		// is_wchar_string
		//
		template<typename T, typename Enable = void>
		struct is_wchar_string
			: public boost::mpl::false_
		{};
		template<typename T>
		struct is_wchar_string<
			T,
			typename boost::enable_if<
				is_specialized<T>
			>::type
		>
			: public is_wchar_type<
				typename str_cast_traits<T>::value_type
			>
		{};
		//
		// is_convertible_from_c_str
		//
		template<typename From, typename To, typename Enable = void>
		struct is_convertible_from_c_str
			: public boost::mpl::false_
		{};
		template<typename From, typename To>
		struct is_convertible_from_c_str<
			From,
			To,
			typename boost::enable_if<
				has_c_str<From>
			>::type
		>
			: public is_convertible<
				typename str_cast_traits<From>::value_type const*,
				To
			>
		{};
		//
		// is_not_convertible_from_c_str
		//
		template<typename From, typename To>
		struct is_not_convertible_from_c_str
			: public boost::mpl::not_<
				is_convertible_from_c_str<From, To>
			>
		{};
	}	// namespace str_cast_detail

	//
	// bad_str_cast
	//
	SPRIG_EXCEPTION_DECL(bad_str_cast);

	namespace str_cast_detail {
		//
		// convert
		//
		template<typename To, typename From>
		SPRIG_INLINE typename boost::enable_if<
			is_char_c_str<From>,
			To
		>::type convert(From from) {
			sprig::locale_saver saver;
			std::setlocale(LC_CTYPE, "");
			std::size_t const size = std::mbstowcs(0, from, 0) + 1;
			if (size == static_cast<std::size_t>(-1)) {
				throw bad_str_cast("error in std::mbstowcs()");
			}
			boost::shared_array<wchar_t> dest(new wchar_t[size]);
			std::mbstowcs(dest.get(), from, size);
			return To(dest.get());
		}
		template<typename To, typename From>
		SPRIG_INLINE typename boost::enable_if<
			is_wchar_c_str<From>,
			To
		>::type convert(From from) {
			sprig::locale_saver saver;
			std::setlocale(LC_CTYPE, "");
			std::size_t const size = /*std*/::wcstombs(0, from, 0) + 1;
			if (size == static_cast<std::size_t>(-1)) {
				throw bad_str_cast("error in std::wcstombs()");
			}
			boost::shared_array<char> dest(new char[size]);
			/*std*/::wcstombs(dest.get(), from, size);
			return To(dest.get());
		}
	}	// namespace str_cast_detail

	//
	// is_specialized_str_cast_traits
	//
	template<typename T>
	struct is_specialized_str_cast_traits
		: public boost::mpl::not_<
			str_cast_detail::is_specialized<T>
		>
	{};

	//
	// has_c_str
	//
	template<typename T>
	struct has_c_str
		: public str_cast_detail::has_c_str<T>
	{};

	//
	// str_cast
	//
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_convertible<From, To>,
			boost::mpl::or_<
				str_cast_detail::is_c_str<From>,
				str_cast_detail::is_specialized<From>
			>
		>,
		To
	>::type str_cast(From from) {
		return To(from);
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_convertible<From, To>,
			boost::mpl::or_<
				boost::mpl::and_<
					str_cast_detail::is_char_c_str<From>,
					str_cast_detail::is_wchar_string<To>,
					str_cast_detail::is_convertible<wchar_t const*, To>
				>,
				boost::mpl::and_<
					str_cast_detail::is_wchar_c_str<From>,
					str_cast_detail::is_char_string<To>,
					str_cast_detail::is_convertible<char const*, To>
				>
			>
		>,
		To
	>::type str_cast(From from) {
		return str_cast_detail::convert<To>(from);
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_convertible<From, To>,
			str_cast_detail::has_c_str<From>,
			str_cast_detail::is_convertible_from_c_str<From, To>
		>,
		To
	>::type str_cast(From const& from) {
		return To(str_cast_traits<From>::c_str(from));
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_convertible<From, To>,
			str_cast_detail::has_c_str<From>,
			str_cast_detail::is_not_convertible_from_c_str<From, To>,
			boost::mpl::or_<
				boost::mpl::and_<
					str_cast_detail::is_char_string<From>,
					str_cast_detail::is_wchar_string<To>,
					str_cast_detail::is_convertible<wchar_t const*, To>
				>,
				boost::mpl::and_<
					str_cast_detail::is_wchar_string<From>,
					str_cast_detail::is_char_string<To>,
					str_cast_detail::is_convertible<char const*, To>
				>
			>
		>,
		To
	>::type str_cast(From const& from) {
		return str_cast_detail::convert<To>(str_cast_traits<From>::c_str(from));
	}
#if BOOST_VERSION == 104800
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_copy_param<From>,
			boost::mpl::not_<boost::is_void<typename boost::remove_pointer<From>::type> >
		>,
		To
	>::type str_cast(From from) {
		return boost::lexical_cast<To>(from);
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_reference_param<From>,
			boost::mpl::not_<boost::is_void<typename boost::remove_pointer<From>::type> >
		>,
		To
	>::type str_cast(From const& from) {
		return boost::lexical_cast<To>(from);
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_copy_param<From>,
			boost::is_void<typename boost::remove_pointer<From>::type>
		>,
		To
	>::type str_cast(From from) {
		std::ostringstream oss;
		oss << from;
		return sprig::str_cast<To>(oss.str());
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_reference_param<From>,
			boost::is_void<typename boost::remove_pointer<From>::type>
		>,
		To
	>::type str_cast(From const& from) {
		std::ostringstream oss;
		oss << from;
		return sprig::str_cast<To>(oss.str());
	}
#else	//#if BOOST_VERSION == 104800
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_copy_param<From>
		>,
		To
	>::type str_cast(From from) {
		return boost::lexical_cast<To>(from);
	}
	template<typename To, typename From>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::and_<
			str_cast_detail::is_specialized<To>,
			str_cast_detail::is_not_c_str<From>,
			boost::mpl::or_<
				str_cast_detail::is_not_specialized<From>,
				boost::mpl::and_<
					str_cast_detail::is_specialized<From>,
					str_cast_detail::has_not_c_str<From>
				>
			>,
			is_call_reference_param<From>
		>,
		To
	>::type str_cast(From const& from) {
		return boost::lexical_cast<To>(from);
	}
#endif	//#if BOOST_VERSION == 104800
}	// namespace sprig

#endif	// #ifndef SPRIG_STR_CAST_HPP
