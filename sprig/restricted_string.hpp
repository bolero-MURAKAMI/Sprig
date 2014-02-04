/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RESTRICTED_STRING_HPP
#define SPRIG_RESTRICTED_STRING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/operators.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/exception.hpp>
#include <sprig/utility/utility.hpp>

namespace sprig {
	//
	// restricted_string_policy
	//
	template<
		typename T,
		typename Predicate = unconditional<true>,
		typename Clearable = boost::mpl::true_,
		typename Addable = boost::mpl::true_,
		typename OrderComparable = boost::mpl::true_,
		typename EqualityComparable = boost::mpl::true_
	>
	struct restricted_string_policy {
		typedef T value_type;
		typedef Predicate predicate_type;
		typedef Clearable clearable_type;
		typedef Addable addable_type;
		typedef OrderComparable order_comparable_type;
		typedef EqualityComparable equality_comparable_type;
	public:
		bool operator()(value_type const& value) const {
			return Predicate()(value);
		}
	};

	//
	// restricted_string_nonconformance
	//
	SPRIG_EXCEPTION_DECL(restricted_string_nonconformance);

	//
	// restricted_string
	//
	template<typename Value, typename Policy = restricted_string_policy<Value> >
	class restricted_string
		: boost::mpl::if_<
			typename Policy::addable_type,
			boost::addable<restricted_string<Value, Policy> >,
			empty_class_enum<0>
		>::type
		, boost::mpl::if_<
			typename Policy::order_comparable_type,
			boost::less_than_comparable<restricted_string<Value, Policy> >,
			empty_class_enum<1>
		>::type
		, boost::mpl::if_<
			typename Policy::equality_comparable_type,
			boost::equality_comparable<restricted_string<Value, Policy> >,
			empty_class_enum<2>
		>::type
	{
	private:
		typedef restricted_string this_type;
	public:
		typedef Value value_type;
		typedef Policy policy_type;
	private:
		value_type value_;
	public:
		static bool is_conform(value_type const& value) {
			return policy_type()(value);
		}
	private:
		static void conform_check(value_type const& value) {
			if (!value.empty() && !is_conform(value))
				throw(restricted_string_nonconformance("êßå¿Ç…ìKçáÇµÇ‹ÇπÇÒ"));
		}
		template<typename Clearable>
		static typename boost::enable_if<Clearable>::type
		fork_clear_check(value_type const&) {}
		template<typename Clearable>
		static typename boost::disable_if<Clearable>::type
		fork_clear_check(value_type const& value) {
			if (value.empty())
				throw(restricted_string_nonconformance("ãÛÇ…ïœçXÇ≈Ç´Ç‹ÇπÇÒ"));
		}
		static void clear_check(value_type const& value) {
			fork_clear_check<typename policy_type::clearable_type>(value);
		}
	public:
		restricted_string() {}
		restricted_string(this_type const& other)
			: value_(other.value_)
		{}
		restricted_string(value_type const& value)
			: value_(value)
		{
			conform_check(value_);
		}
		template<typename OtherPolicy>
		restricted_string(restricted_string<value_type, OtherPolicy> const& other)
			: value_(other.value_)
		{
			conform_check(value_);
		}
		this_type& operator=(this_type rhs) {
			clear_check(rhs.value_);
			swap(rhs);
			return *this;
		}
		this_type& operator=(value_type const& rhs) {
			conform_check(rhs);
			clear_check(rhs);
			swap(this_type(rhs));
			return *this;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::addable_type,
				typename boost::is_same<T, this_type>::type
			>,
			this_type
		>::type&
		operator+=(T const& rhs) {
			value_ += rhs.value_;
			return *this;
		}
		template<typename OtherPolicy>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::addable_type,
				typename boost::mpl::not_<
					typename boost::is_same<OtherPolicy, policy_type>::type
				>::type
			>,
			this_type
		>::type&
		operator+=(restricted_string<value_type, OtherPolicy> const& rhs) {
			conform_check(value_ + rhs.value_);
			value_ += rhs;
			return *this;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::addable_type,
				typename boost::is_same<T, value_type>::type
			>,
			this_type
		>::type&
		operator+=(T const& rhs) {
			conform_check(value_ + rhs);
			value_ += rhs;
			return *this;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::equality_comparable_type,
				typename boost::is_same<T, this_type>::type
			>,
			bool
		>::type
		operator==(T const& rhs) const {
			return value_ == rhs.value_;
		}
		template<typename OtherPolicy>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::addable_type,
				typename boost::mpl::not_<
					typename boost::is_same<OtherPolicy, policy_type>::type
				>::type
			>,
			this_type
		>::type
		operator==(restricted_string<value_type, OtherPolicy> const& rhs) const {
			return value_ == rhs.value_;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::equality_comparable_type,
				typename boost::is_same<T, value_type>::type
			>,
			bool
		>::type
		operator==(T const& rhs) const {
			return value_ == rhs;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::order_comparable_type,
				typename boost::is_same<T, this_type>::type
			>,
			bool
		>::type
		operator<(T const& rhs) const {
			return value_ < rhs.value_;
		}
		template<typename T>
		typename boost::enable_if<
			boost::mpl::and_<
				typename policy_type::order_comparable_type,
				typename boost::is_same<T, value_type>::type
			>,
			bool
		>::type
		operator<(T const& rhs) const {
			return value_ < rhs;
		}
		void swap(this_type& rhs) {
			boost::swap(value_, rhs.value_);
		}
		bool empty() const {
			return value_.empty();
		}
		value_type const& get() const {
			return value_;
		}
		operator value_type const&() const {
			return value_;
		}
	};
	template<typename Value, typename Policy>
	SPRIG_INLINE void swap(
		restricted_string<Value, Policy>& lhs,
		restricted_string<Value, Policy>& rhs
		)
	{
		lhs.swap(rhs);
	}
	template<typename Elem, typename Traits, typename Value, typename Policy>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		restricted_string<Value, Policy> const& rhs
		)
	{
		return lhs << rhs.get();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_RESTRICTED_STRING_HPP
