/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BINARY_FROM_FILE_HPP
#define SPRIG_BINARY_FROM_FILE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <clocale>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/locale_saver.hpp>

namespace sprig {
	//
	// binary_from_file
	//
	template<typename T, typename Iterator, typename FileString>
	SPRIG_INLINE typename boost::enable_if<
		is_call_copy_param<FileString>,
		bool
	>::type
	binary_from_file(Iterator out, FileString file) {
		locale_saver saver;
		std::setlocale(LC_CTYPE, "");
		std::basic_ifstream<T> ifs(file, std::ios_base::in | std::ios_base::binary);
		if (!ifs) {
			return false;
		}
		ifs >> std::noskipws;
		std::copy(std::istreambuf_iterator<T>(ifs), std::istreambuf_iterator<T>(), out);
		return true;
	}
	template<typename T, typename Iterator, typename FileString>
	SPRIG_INLINE typename boost::disable_if<
		is_call_copy_param<FileString>,
		bool
	>::type
	binary_from_file(Iterator out, FileString const& file) {
		locale_saver saver;
		std::setlocale(LC_CTYPE, "");
		std::basic_ifstream<T> ifs(file.c_str(), std::ios_base::in | std::ios_base::binary);
		if (!ifs) {
			return false;
		}
		ifs >> std::noskipws;
		std::copy(std::istreambuf_iterator<T>(ifs), std::istreambuf_iterator<T>(), out);
		return true;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_BINARY_FROM_FILE_HPP
