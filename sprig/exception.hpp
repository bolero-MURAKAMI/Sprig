#ifndef SPRIG_EXCEPTION_HPP
#define SPRIG_EXCEPTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <exception>
#include <string>
#include <boost/current_function.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/preprocessor/stringize.hpp>

//
// SPRIG_EXCEPTION_INHERIT_DECL
//
#define SPRIG_EXCEPTION_INHERIT_DECL(CLASS_NAME, BASE_CLASS_NAME) \
	class CLASS_NAME : public BASE_CLASS_NAME { \
	public: \
		CLASS_NAME() {} \
		explicit CLASS_NAME(std::string const& message) \
			: BASE_CLASS_NAME(message) \
		{} \
		explicit CLASS_NAME(char const* message) \
			: BASE_CLASS_NAME(message) \
		{} \
	}
//
// SPRIG_EXCEPTION_DECL
//
#define SPRIG_EXCEPTION_DECL(CLASS_NAME) \
	SPRIG_EXCEPTION_INHERIT_DECL(CLASS_NAME, sprig::exception)
//
// SPRIG_THROW_EXCEPTION
//
#ifndef SPRIG_EXCEPTION_CONFIG_DISABLE
#	define SPRIG_THROW_EXCEPTION(x) BOOST_THROW_EXCEPTION(x)
#else	// #ifndef SPRIG_EXCEPTION_CONFIG_DISABLE
#	define SPRIG_THROW_EXCEPTION(x) boost::throw_exception(x)
#endif	// #ifndef SPRIG_EXCEPTION_CONFIG_DISABLE

//
// SPRIG_ASSERT_EXCEPTION
//
#define SPRIG_ASSERT_EXCEPTION(EXPR) \
	if (!(EXPR)) { \
		SPRIG_THROW_EXCEPTION(sprig::assert_exception("assertion failed: expression=" BOOST_PP_STRINGIZE(EXPR))); \
	}

//
// SPRIG_ADD_EXCEPTION_INFO
//
#define SPRIG_ADD_EXCEPTION_INFO(e) \
	(e \
		<< boost::throw_function(BOOST_CURRENT_FUNCTION) \
		<< boost::throw_file(__FILE__) \
		<< boost::throw_line(__LINE__) \
		)

namespace sprig {
	//
	// exception
	//
	class exception
		: public std::exception
		, public boost::exception
	{
		std::string message_;
	public:
		exception() {}
		explicit exception(std::string const& message)
			: message_(message)
		{}
		explicit exception(char const* message)
			: message_(message)
		{}
		virtual ~exception() throw() {}
		char const* what() const throw() {
			return message_.c_str();
		}
	};

	//
	// intentional_exception
	// assert_exception
	//
	SPRIG_EXCEPTION_DECL(intentional_exception);
	SPRIG_EXCEPTION_DECL(assert_exception);
} // namespace sprig

#endif	// #ifndef SPRIG_EXCEPTION_HPP
