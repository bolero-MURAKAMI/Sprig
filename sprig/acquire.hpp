/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ACQUIRE_HPP
#define SPRIG_ACQUIRE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <sprig/functional.hpp>

namespace sprig {
	//
	// acquirer_generator
	//
	template<typename Parser>
	class acquirer_generator {
	public:
		typedef Parser parser_type;
	public:
		template<typename T>
		parser_type operator()(T& value) const {
			return parser_type(value);
		}
	};

	//
	// acquire_action
	//
	template<
		typename T,
		typename Elem = char,
		typename Assign = assign<T>
	>
	class acquire_action {
	public:
		typedef T value_type;
		typedef Elem char_type;
		typedef Assign assign_type;
	private:
		mutable value_type& value_;
	public:
		explicit acquire_action(value_type& value)
			: value_(value)
		{}
		template<typename Iterator>
		void operator()(Iterator first, Iterator last) const {
			assign_type()(value_, boost::lexical_cast<value_type>(std::basic_string<char_type>(first, last)));
		}
		template<typename Value>
		void operator()(Value const& value) const {
			assign_type()(value_, value);
		}
	};

	//
	// acquirer_base
	//
	template<
		typename Derived,
		typename T,
		typename Elem = char,
		typename Action = acquire_action<T, Elem>
	>
	class acquirer_base
		: public boost::spirit::classic::grammar<Derived>
	{
	public:
		typedef Derived derived_type;
		typedef T value_type;
		typedef Elem char_type;
		typedef Action action_type;
	protected:
		typedef boost::reference_wrapper<value_type> reference_value_type;
	private:
		value_type& value_;
	protected:
		reference_value_type ref_value() const {
			return boost::ref(value_);
		}
	public:
		explicit acquirer_base(value_type& value)
			: value_(value)
		{}
		value_type const& value() const {
			return value_;
		}
		void clear() {
			value_ = value_type();
		}
	public:
		template<typename Scanner>
		class definition_base {
		public:
			typedef boost::spirit::classic::rule<Scanner> rule_type;
		private:
			rule_type start_;
		protected:
			rule_type& ref_start() {
				return start_;
			}
		public:
			rule_type const& start() const {
				return start_;
			}
		};
	};

	//
	// acquire
	//
	template<typename T, typename Elem, typename Traits, typename Generator>
	SPRIG_INLINE bool acquire(
		T& arg,
		std::basic_istream<Elem, Traits>& is,
		Generator const& generator
		)
	{
		T value;
		std::string s;
		typename Generator::parser_type p(generator(value));
		std::getline(is, s);
		boost::spirit::classic::parse_info<std::string::const_iterator> pi(
			boost::spirit::classic::parse<std::string::const_iterator>(s.begin(), s.end(), p)
			);
		if (!pi.full)
			return false;
		arg = value;
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator>
	SPRIG_INLINE bool acquire(
		T& arg,
		std::basic_istream<Elem, Traits>& is,
		Elem delimiter,
		Generator const& generator
		)
	{
		T value;
		std::string s;
		typename Generator::parser_type p(generator(value));
		std::getline(is, s, delimiter);
		boost::spirit::classic::parse_info<std::string::const_iterator> pi(
			boost::spirit::classic::parse<std::string::const_iterator>(s.begin(), s.end(), p)
			);
		if (!pi.full)
			return false;
		arg = value;
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator, typename Assign>
	SPRIG_INLINE bool acquire(
		T& arg,
		std::basic_istream<Elem, Traits>& is,
		Generator const& generator,
		Assign const& assign
		)
	{
		T value;
		std::string s;
		typename Generator::parser_type p(generator(value));
		std::getline(is, s);
		boost::spirit::classic::parse_info<std::string::const_iterator> pi(
			boost::spirit::classic::parse<std::string::const_iterator>(s.begin(), s.end(), p)
			);
		if (!pi.full)
			return false;
		assign(arg, value);
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator, typename Assign>
	SPRIG_INLINE bool acquire(
		T& arg,
		std::basic_istream<Elem, Traits>& is,
		Elem delimiter,
		Generator const& generator,
		Assign const& assign
		)
	{
		T value;
		std::string s;
		typename Generator::parser_type p(generator(value));
		std::getline(is, s, delimiter);
		boost::spirit::classic::parse_info<std::string::const_iterator> pi(
			boost::spirit::classic::parse<std::string::const_iterator>(s.begin(), s.end(), p)
			);
		if (!pi.full)
			return false;
		assign(arg, value);
		return true;
	}

	//
	// SPRIG_ACQUIRE_ACQUIRER_DECL
	//
#define SPRIG_ACQUIRE_ACQUIRER_DECL(NAME, RULE) \
	template< \
		typename T, \
		typename Elem = char, \
		typename Action = sprig::acquire_action<T, Elem> \
	> \
	class NAME \
		: public sprig::acquirer_base<NAME<T, Elem, Action>, T, Elem, Action> \
	{ \
	private: \
		typedef sprig::acquirer_base<NAME, T, Elem, Action> acquirer_base_type; \
	public: \
		typedef typename acquirer_base_type::value_type value_type; \
		typedef typename acquirer_base_type::derived_type derived_type; \
		typedef typename acquirer_base_type::action_type action_type; \
	public: \
		NAME(value_type& value) \
			: acquirer_base_type(value) \
		{} \
	public: \
		template<typename Scanner> \
		class definition \
			: public acquirer_base_type::template definition_base<Scanner> \
		{ \
		public: \
			definition(derived_type const& self) { \
				this->ref_start() = (RULE)[action_type(self.ref_value())]; \
			} \
		}; \
	};

	//
	// SPRIG_ACQUIRE_ACQUIRE_DECL
	//
#define SPRIG_ACQUIRE_ACQUIRE_DECL(NAME, ACQUIRER_NAME) \
	template<typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is) { \
		return sprig::acquire(arg, is, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem> >()); \
	} \
	template<typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter) { \
		return sprig::acquire(arg, is, delimiter, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem> >()); \
	} \
	template<typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Assign const& assign) { \
		return sprig::acquire(arg, is, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem> >(), assign); \
	} \
	template<typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter, Assign const& assign) { \
		return sprig::acquire(arg, is, delimiter, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem> >(), assign); \
	}

	//
	// SPRIG_ACQUIRE_ACQUIRE_EX_DECL
	//
#define SPRIG_ACQUIRE_ACQUIRE_EX_DECL(NAME, ACQUIRER_NAME) \
	template<typename Action, typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is) { \
		return sprig::acquire(arg, is, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >()); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter) { \
		return sprig::acquire(arg, is, delimiter, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >()); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Assign const& assign) { \
		return sprig::acquire(arg, is, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >(), assign); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter, Assign const& assign) { \
		return sprig::acquire(arg, is, delimiter, sprig::acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >(), assign); \
	}

	// any_acquirer
	SPRIG_ACQUIRE_ACQUIRER_DECL(any_acquirer, (*boost::spirit::classic::anychar_p));
	// acquire_any
	SPRIG_ACQUIRE_ACQUIRE_DECL(acquire_any, any_acquirer);
	// acquire_any_ex
	SPRIG_ACQUIRE_ACQUIRE_EX_DECL(acquire_any_ex, any_acquirer);

	// int_acquirer
	SPRIG_ACQUIRE_ACQUIRER_DECL(int_acquirer, (boost::spirit::classic::int_p));
	// acquire_int
	SPRIG_ACQUIRE_ACQUIRE_DECL(acquire_int, int_acquirer);
	// acquire_int_ex
	SPRIG_ACQUIRE_ACQUIRE_EX_DECL(acquire_int_ex, int_acquirer);

	// uint_acquirer
	SPRIG_ACQUIRE_ACQUIRER_DECL(uint_acquirer, (boost::spirit::classic::uint_p));
	// acquire_uint
	SPRIG_ACQUIRE_ACQUIRE_DECL(acquire_uint, uint_acquirer);
	// acquire_uint_ex
	SPRIG_ACQUIRE_ACQUIRE_EX_DECL(acquire_uint_ex, uint_acquirer);

	// real_acquirer
	SPRIG_ACQUIRE_ACQUIRER_DECL(real_acquirer, (boost::spirit::classic::real_p));
	// acquire_real
	SPRIG_ACQUIRE_ACQUIRE_DECL(acquire_real, real_acquirer);
	// acquire_real_ex
	SPRIG_ACQUIRE_ACQUIRE_EX_DECL(acquire_real_ex, real_acquirer);

}	// namespace sprig

#endif	// #ifndef SPRIG_ACQUIRE_HPP
