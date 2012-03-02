#ifndef SPRIG_INITIALIZING_CHECK_HPP
#define SPRIG_INITIALIZING_CHECK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <exception>
#include <boost/function.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/exception.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// initializing_check_failed
	//
	SPRIG_EXCEPTION_DECL(initializing_check_failed);

	//
	// throw_exception
	//
	template<typename T>
	class throw_exception {
	public:
		typedef T exception_type;
	public:
		void operator()() {
			throw T();
		}
		template<typename Arg>
		typename boost::enable_if<sprig::is_call_copy_param<Arg> >::type
		operator()(Arg const arg) {
			throw T(arg);
		}
		template<typename Arg>
		typename boost::disable_if<sprig::is_call_copy_param<Arg> >::type
		operator()(Arg const& arg) {
			throw T(arg);
		}
	};
	//
	// initializing_check
	//
	class initializing_check {
	public:
		explicit initializing_check(
			bool pred,
			boost::function<void ()> const& func = throw_exception<initializing_check_failed>()
			)
		{
			if (!pred)
				func();
		}
		template<typename T>
		initializing_check(
			bool pred,
			T const message,
			typename boost::enable_if<sprig::is_call_copy_param<T> >::type* = 0
			)
		{
			if (!pred)
				throw_exception<initializing_check_failed>()(message);
		}
		template<typename T>
		initializing_check(
			bool pred,
			T const& message,
			typename boost::disable_if<sprig::is_call_copy_param<T> >::type* = 0
			)
		{
			if (!pred)
				throw_exception<initializing_check_failed>()(message);
		}
		~initializing_check() {}
	};
} // namespace sprig

#endif	// #ifndef SPRIG_INITIALIZING_CHECK_HPP
