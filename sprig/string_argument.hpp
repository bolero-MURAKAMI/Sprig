#ifndef SPRIG_STRING_ARGUMENT_HPP
#define SPRIG_STRING_ARGUMENT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_call_reference_param.hpp>

namespace sprig {
	//
	// forward
	//
	template<typename Value>
	class basic_string_argument;
	//
	// is_basic_string_argument
	//
	template<typename T, typename Enable = void>
	struct is_basic_string_argument
		: public boost::mpl::false_
	{};
	template<typename T>
	struct is_basic_string_argument<
		T,
		typename boost::enable_if<
			boost::is_same<
				T,
				basic_string_argument<typename T::value_type>
			>
		>::type
	>
		: public boost::mpl::true_
	{};
	//
	// basic_string_argument
	//
	template<typename Value>
	class basic_string_argument {
	public:
		typedef Value value_type;
	private:
		value_type value_;
	public:
		basic_string_argument() {}
		basic_string_argument(basic_string_argument const& value)
			: value_(value.ref())
		{}
		basic_string_argument(value_type const& value)
			: value_(value)
		{}
		template<typename T>
		basic_string_argument(
			T const& value,
			typename boost::enable_if<
				is_basic_string_argument<T>
			>::type* = 0
			)
			: value_(str_cast<value_type>(value.ref()))
		{}
		template<typename T>
		basic_string_argument(
			T const& value,
			typename boost::enable_if<
				boost::mpl::and_<
					boost::mpl::not_<
						is_basic_string_argument<T>
					>,
					sprig::is_call_reference_param<T>
				>
			>::type* = 0
			)
			: value_(str_cast<value_type>(value))
		{}
		template<typename T>
		basic_string_argument(
			T value,
			typename boost::enable_if<
				boost::mpl::and_<
					boost::mpl::not_<
						is_basic_string_argument<T>
					>,
					sprig::is_call_copy_param<T>
				>
			>::type* = 0
			)
			: value_(str_cast<value_type>(value))
		{}
		basic_string_argument& operator=(basic_string_argument rhs) {
			swap(rhs);
			return *this;
		}
		void swap(basic_string_argument& rhs) {
			value_.swap(rhs.value_);
		}
		value_type const& get() const {
			return value_;
		}
		value_type const& cref() const {
			return value_;
		}
		value_type const& ref() const {
			return value_;
		}
		value_type& ref() {
			return value_;
		}
		value_type const& operator*() const {
			return value_;
		}
		value_type& operator*() {
			return value_;
		}
		value_type const* operator->() const {
			return &value_;
		}
		value_type* operator->() {
			return &value_;
		}
		operator value_type const&() const {
			return value_;
		}
		operator value_type&() {
			return value_;
		}
	};
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename Value>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_string_argument<Value> const& rhs
		)
	{
		return lhs << rhs.get();
	}
	//
	// operator>>
	//
	template<typename Elem, typename Traits, typename Value>
	SPRIG_INLINE std::basic_istream<Elem, Traits>& operator>>(
		std::basic_istream<Elem, Traits>& lhs,
		basic_string_argument<Value>& rhs
		)
	{
		return lhs >> rhs.ref();
	}
	//
	// string_argument
	// wstring_argument
	//
	typedef basic_string_argument<std::string> string_argument;
	typedef basic_string_argument<std::wstring> wstring_argument;
} // namespace sprig

#endif	// #ifndef SPRIG_STRING_ARGUMENT_HPP
