#ifndef SPRIG_STRING_FROM_FILE_HPP
#define SPRIG_STRING_FROM_FILE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <clocale>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <boost/optional/optional.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/locale_saver.hpp>

namespace sprig {
	//
	// string_from_file
	//
	template<typename String, typename FileString>
	SPRIG_INLINE typename boost::enable_if<
		sprig::is_call_copy_param<FileString>,
		bool
	>::type
	string_from_file(String& str, FileString file) {
		locale_saver saver;
		std::setlocale(LC_CTYPE, "");
		std::basic_ifstream<typename String::value_type, typename String::traits_type> ifs(file);
		if (!ifs) {
			return false;
		}
		{
			using std::swap;
			String s;
			std::copy(
				std::istreambuf_iterator<typename String::value_type, typename String::traits_type>(ifs),
				std::istreambuf_iterator<typename String::value_type, typename String::traits_type>(),
				std::back_inserter(s)
				);
			swap(str, s);
		}
		return true;
	}
	//
	// string_from_file
	//
	template<typename String, typename FileString>
	SPRIG_INLINE typename boost::disable_if<
		sprig::is_call_copy_param<FileString>,
		bool
	>::type
	string_from_file(String& str, FileString const& file) {
		locale_saver saver;
		std::setlocale(LC_CTYPE, "");
		std::basic_ifstream<typename String::value_type, typename String::traits_type> ifs(file.c_str());
		if (!ifs) {
			return false;
		}
		{
			using std::swap;
			String s;
			std::copy(
				std::istreambuf_iterator<typename String::value_type, typename String::traits_type>(ifs),
				std::istreambuf_iterator<typename String::value_type, typename String::traits_type>(),
				std::back_inserter(s)
				);
			swap(str, s);
		}
		return true;
	}
	//
	// get_string_from_file
	//
	template<typename String, typename FileString>
	SPRIG_INLINE typename boost::enable_if<
		sprig::is_call_copy_param<FileString>,
		boost::optional<String>
	>::type
	get_string_from_file(FileString file) {
		String result;
		return string_from_file(result, file)
			? result
			: boost::optional<String>()
			;
	}
	//
	// get_string_from_file
	//
	template<typename String, typename FileString>
	SPRIG_INLINE typename boost::disable_if<
		sprig::is_call_copy_param<FileString>,
		boost::optional<String>
	>::type
	get_string_from_file(FileString const& file) {
		String result;
		return string_from_file(result, file)
			? result
			: boost::optional<String>()
			;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_STRING_FROM_FILE_HPP
