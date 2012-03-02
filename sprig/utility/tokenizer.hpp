#ifndef SPRIG_UTILITY_TOKENIZER_HPP
#define SPRIG_UTILITY_TOKENIZER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <sprig/utility/utility.hpp>

namespace sprig {
	namespace {
		//
		// get_first_token
		//
		SPRIG_INLINE std::string get_first_token(std::string const& source, char const* delimiters) {
			boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string>
				tokens(source, boost::char_separator<char>(delimiters));
			return boost::lexical_cast<std::string>(*tokens.begin());
		}
		SPRIG_INLINE std::wstring get_first_token(std::wstring const& source, wchar_t const* delimiters) {
			boost::tokenizer<boost::char_separator<wchar_t>, std::wstring::const_iterator, std::wstring>
				tokens(source, boost::char_separator<wchar_t>(delimiters));
			return boost::lexical_cast<std::wstring>(*tokens.begin());
		}
		//
		// get_last_token
		//
		SPRIG_INLINE std::string get_last_token(std::string const& source, char const* delimiters) {
			boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string>
				tokens(source, boost::char_separator<char>(delimiters));
			return boost::lexical_cast<std::string>(*back(tokens.begin(), tokens.end()));
		}
		SPRIG_INLINE std::wstring get_last_token(std::wstring const& source, wchar_t const* delimiters) {
			boost::tokenizer<boost::char_separator<wchar_t>, std::wstring::const_iterator, std::wstring>
				tokens(source, boost::char_separator<wchar_t>(delimiters));
			return boost::lexical_cast<std::wstring>(*back(tokens.begin(), tokens.end()));
		}
	}	// anonymous-namespace
} // namespace sprig

#endif	// #ifndef SPRIG_UTILITY_TOKENIZER_HPP
