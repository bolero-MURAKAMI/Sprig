/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_SECTION_HPP
#define SPRIG_SECTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <sstream>
#include <sprig/split_literal.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/attributes.hpp>

namespace sprig {
	namespace section_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(lt, "<");
		SPRIG_SPLIT_LITERAL_STRING_DECL(gt, ">");
	}	// namespace section_detail
	//
	// basic_section_begin
	//
	template<typename T>
	SPRIG_INLINE T basic_section_begin(basic_string_argument<T> const& name) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::lt, char_type>()
			<< name
			<< sprig::get_literal<section_detail::gt, char_type>()
			;
		return oss.str();
	}
	template<typename T>
	SPRIG_INLINE T basic_section_begin(basic_string_argument<T> const& name, basic_attributes<T> const& attr) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::lt, char_type>()
			<< name
			<< attr
			<< sprig::get_literal<section_detail::gt, char_type>()
			;
		return oss.str();
	}
	//
	// section_begin
	// wsection_begin
	//
	SPRIG_INLINE std::string section_begin(string_argument const& name) {
		return basic_section_begin<std::string>(name);
	}
	SPRIG_INLINE std::string section_begin(string_argument const& name, attributes const& attr) {
		return basic_section_begin<std::string>(name, attr);
	}
	SPRIG_INLINE std::wstring wsection_begin(wstring_argument const& name) {
		return basic_section_begin<std::wstring>(name);
	}
	SPRIG_INLINE std::wstring wsection_begin(wstring_argument const& name, wattributes const& attr) {
		return basic_section_begin<std::wstring>(name, attr);
	}

	namespace section_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(lt_slash, "</");
	}	// namespace attributes_detail
	//
	// basic_section_end
	//
	template<typename T>
	SPRIG_INLINE T basic_section_end(basic_string_argument<T> const& name) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::lt_slash, char_type>()
			<< name
			<< sprig::get_literal<section_detail::gt, char_type>()
			;
		return oss.str();
	}
	//
	// section_end
	// wsection_end
	//
	SPRIG_INLINE std::string section_end(string_argument const& name) {
		return basic_section_end<std::string>(name);
	}
	SPRIG_INLINE std::wstring wsection_end(wstring_argument const& name) {
		return basic_section_end<std::wstring>(name);
	}

	namespace section_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(slash_gt, " />");
	}	// namespace attributes_detail
	//
	// basic_section_empty
	//
	template<typename T>
	SPRIG_INLINE T basic_section_empty(basic_string_argument<T> const& name) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::lt, char_type>()
			<< name
			<< sprig::get_literal<section_detail::slash_gt, char_type>()
			;
		return oss.str();
	}
	template<typename T>
	SPRIG_INLINE T basic_section_empty(basic_string_argument<T> const& name, basic_attributes<T> const& attr) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::lt, char_type>()
			<< name
			<< attr
			<< sprig::get_literal<section_detail::slash_gt, char_type>()
			;
		return oss.str();
	}
	//
	// section_empty
	// wsection_empty
	//
	SPRIG_INLINE std::string section_empty(string_argument const& name) {
		return basic_section_empty<std::string>(name);
	}
	SPRIG_INLINE std::string section_empty(string_argument const& name, attributes const& attr) {
		return basic_section_empty<std::string>(name, attr);
	}
	SPRIG_INLINE std::wstring wsection_empty(wstring_argument const& name) {
		return basic_section_empty<std::wstring>(name);
	}
	SPRIG_INLINE std::wstring wsection_empty(wstring_argument const& name, wattributes const& attr) {
		return basic_section_empty<std::wstring>(name, attr);
	}

	//
	// basic_section_line
	//
	template<typename T>
	SPRIG_INLINE T basic_section_line(
		basic_string_argument<T> const& name,
		basic_string_argument<T> const& contents
		)
	{
		return basic_section_begin<T>(name) + contents.get() + basic_section_end<T>(name);
	}
	template<typename T>
	SPRIG_INLINE T basic_section_line(
		basic_string_argument<T> const& name,
		basic_string_argument<T> const& contents,
		basic_attributes<T> const& attr
		)
	{
		return basic_section_begin<T>(name, attr) + contents.get() + basic_section_end<T>(name);
	}
	//
	// section_line
	// wsection_line
	//
	SPRIG_INLINE std::string section_line(
		string_argument const& name,
		string_argument const& contents
		)
	{
		return basic_section_line<std::string>(name, contents);
	}
	SPRIG_INLINE std::string section_line(
		string_argument const& name,
		string_argument const& contents,
		attributes const& attr
		)
	{
		return basic_section_line<std::string>(name, contents, attr);
	}
	SPRIG_INLINE std::wstring wsection_line(
		wstring_argument const& name,
		wstring_argument const& contents
		)
	{
		return basic_section_line<std::wstring>(name, contents);
	}
	SPRIG_INLINE std::wstring wsection_line(
		wstring_argument const& name,
		wstring_argument const& contents,
		wattributes const& attr
		)
	{
		return basic_section_line<std::wstring>(name, contents, attr);
	}

	namespace section_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(comm_begin, "<!-- ");
		SPRIG_SPLIT_LITERAL_STRING_DECL(comm_end, " -->");
	}	// namespace attributes_detail
	//
	// basic_section_comment_begin
	//
	template<typename T>
	SPRIG_INLINE T basic_section_comment_begin() {
		typedef typename T::value_type char_type;
		return T(sprig::get_literal<section_detail::comm_begin, char_type>());
	}
	//
	// section_comment_begin
	// wsection_comment_begin
	//
	SPRIG_INLINE std::string section_comment_begin() {
		return basic_section_comment_begin<std::string>();
	}
	SPRIG_INLINE std::wstring wsection_comment_begin() {
		return basic_section_comment_begin<std::wstring>();
	}

	//
	// basic_section_comment_end
	//
	template<typename T>
	SPRIG_INLINE T basic_section_comment_end() {
		typedef typename T::value_type char_type;
		return T(sprig::get_literal<section_detail::comm_end, char_type>());
	}
	//
	// section_comment_end
	// wsection_comment_end
	//
	SPRIG_INLINE std::string section_comment_end() {
		return basic_section_comment_end<std::string>();
	}
	SPRIG_INLINE std::wstring wsection_comment_end() {
		return basic_section_comment_end<std::wstring>();
	}

	//
	// basic_section_comment
	//
	template<typename T>
	SPRIG_INLINE T basic_section_comment(basic_string_argument<T> const& comment) {
		typedef typename T::value_type char_type;
		std::basic_ostringstream<
			char_type,
			typename T::traits_type,
			typename T::allocator_type
		> oss;
		oss
			<< sprig::get_literal<section_detail::comm_begin, char_type>()
			<< comment
			<< sprig::get_literal<section_detail::comm_end, char_type>()
			;
		return oss.str();
	}
	//
	// section_comment
	// wsection_comment
	//
	SPRIG_INLINE std::string section_comment(string_argument const& comment) {
		return basic_section_comment<std::string>(comment);
	}
	SPRIG_INLINE std::wstring wsection_comment(wstring_argument const& comment) {
		return basic_section_comment<std::wstring>(comment);
	}
} // namespace sprig

#endif	// #ifndef SPRIG_SECTION_HPP
