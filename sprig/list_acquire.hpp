#ifndef SPRIG_LIST_ACQUIRE_HPP
#define SPRIG_LIST_ACQUIRE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/any_functional.hpp>
#include <sprig/utility/container.hpp>
#include <sprig/acquire.hpp>

//
// SPRIG_LIST_ACQUIRE_LIST_ACQUIRER_DECL
//
#define SPRIG_LIST_ACQUIRE_LIST_ACQUIRER_DECL(NAME, RULE) \
	template< \
		typename T, \
		typename Elem = char, \
		typename Action = list_acquire_action<T, Elem> \
	> \
	class NAME \
		: public list_acquirer_base<NAME<T, Elem, Action>, T, Elem, Action> \
	{ \
	private: \
		typedef list_acquirer_base<NAME, T, Elem, Action> list_acquirer_base_type; \
	public: \
		typedef typename list_acquirer_base_type::value_type value_type; \
		typedef typename list_acquirer_base_type::derived_type derived_type; \
		typedef typename list_acquirer_base_type::action_type action_type; \
	public: \
		NAME(value_type& value) \
			: list_acquirer_base_type(value) \
		{} \
	public: \
		template<typename Scanner> \
		class definition \
			: public list_acquirer_base_type::template definition_base<Scanner> \
		{ \
		public: \
			definition(derived_type const& self) { \
				this->ref_start() = \
					!( \
						(RULE)[action_type(self.ref_value())] \
						>> *( \
							*boost::spirit::classic::space_p \
							>> !boost::spirit::classic::ch_p(',') \
							>> *boost::spirit::classic::space_p \
							>> (RULE)[action_type(self.ref_value())] \
							) \
						) \
				; \
			} \
		}; \
	};
//
// SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_DECL
//
#define SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_DECL(NAME, ACQUIRER_NAME) \
	template<typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is) { \
		return list_acquire(arg, is, acquirer_generator<ACQUIRER_NAME<T, Elem> >()); \
	} \
	template<typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter) { \
		return list_acquire(arg, is, delimiter, acquirer_generator<ACQUIRER_NAME<T, Elem> >()); \
	} \
	template<typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Assign const& assign) { \
		return list_acquire(arg, is, acquirer_generator<ACQUIRER_NAME<T, Elem> >(), assign); \
	} \
	template<typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter, Assign const& assign) { \
		return list_acquire(arg, is, delimiter, acquirer_generator<ACQUIRER_NAME<T, Elem> >(), assign); \
	}
//
// SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_EX_DECL
//
#define SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_EX_DECL(NAME, ACQUIRER_NAME) \
	template<typename Action, typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is) { \
		return list_acquire(arg, is, acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >()); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter) { \
		return list_acquire(arg, is, delimiter, acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >()); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Assign const& assign) { \
		return list_acquire(arg, is, acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >(), assign); \
	} \
	template<typename Action, typename T, typename Elem, typename Traits, typename Assign> \
	SPRIG_INLINE bool NAME(T& arg, std::basic_istream<Elem, Traits>& is, Elem delimiter, Assign const& assign) { \
		return list_acquire(arg, is, delimiter, acquirer_generator<ACQUIRER_NAME<T, Elem, Action> >(), assign); \
	}

namespace sprig {
	//
	// list_acquire_action
	//
	template<
		typename T,
		typename Elem = char,
		typename Assign = sprig::any_push_back_
	>
	class list_acquire_action
		: public acquire_action<T, Elem, Assign>
	{
	private:
		typedef acquire_action<T, Elem, Assign> acquire_action_type;
	public:
		typedef typename acquire_action_type::value_type value_type;
	public:
		list_acquire_action(value_type& value)
			: acquire_action_type(value)
		{}
	};
	//
	// list_acquirer_base
	//
	template<
		typename Derived,
		typename T,
		typename Elem = char,
		typename Action = list_acquire_action<T, Elem>
	>
	class list_acquirer_base
		: public acquirer_base<Derived, T, Elem, Action>
	{
	private:
		typedef acquirer_base<Derived, T, Elem, Action> acquirer_base_type;
	public:
		typedef typename acquirer_base_type::value_type value_type;
	public:
		list_acquirer_base(value_type& value)
			: acquirer_base_type(value)
		{}
	};
	//
	// list_acquire
	//
	template<typename T, typename Elem, typename Traits, typename Generator>
	SPRIG_INLINE bool list_acquire(
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
		if (!pi.full) {
			return false;
		}
		boost::swap(arg, value);
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator>
	SPRIG_INLINE bool list_acquire(
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
		if (!pi.full) {
			return false;
		}
		boost::swap(arg, value);
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator, typename Assign>
	SPRIG_INLINE bool list_acquire(
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
		if (!pi.full) {
			return false;
		}
		assign(arg, value);
		return true;
	}
	template<typename T, typename Elem, typename Traits, typename Generator, typename Assign>
	SPRIG_INLINE bool list_acquire(
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
		if (!pi.full) {
			return false;
		}
		assign(arg, value);
		return true;
	}
	//
	// list_acquire_int
	//
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRER_DECL(int_list_acquirer, (boost::spirit::classic::int_p));
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_DECL(list_acquire_int, int_list_acquirer);
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_EX_DECL(list_acquire_int_ex, int_list_acquirer)
	//
	// list_acquire_uint
	//
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRER_DECL(uint_list_acquirer, (boost::spirit::classic::uint_p));
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_DECL(list_acquire_uint, uint_list_acquirer);
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_EX_DECL(list_acquire_uint_ex, uint_list_acquirer)
	//
	// list_acquire_real
	//
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRER_DECL(real_list_acquirer, (boost::spirit::classic::real_p));
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_DECL(list_acquire_real, real_list_acquirer);
	SPRIG_LIST_ACQUIRE_LIST_ACQUIRE_EX_DECL(list_acquire_real_ex, real_list_acquirer)
}	// namespace sprig

#endif	// #ifndef SPRIG_LIST_ACQUIRE_HPP
