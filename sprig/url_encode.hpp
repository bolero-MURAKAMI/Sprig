/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_URL_ENCODE_HPP
#define SPRIG_URL_ENCODE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/array.hpp>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/or.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>

namespace sprig {
	//
	// url_encode_table
	//
	namespace url_encode_detail {
		template<typename Char>
		static bool is_unreserved(Char c) {
			BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<Char>, is_wchar_type<Char> >));
			return c >= 'a' && c <= 'z'
				|| c >= 'A' && c <= 'Z'
				|| c >= '0' && c <= '9'
				|| c == '-'
				|| c == '.'
				|| c == '_'
				|| c == '~'
				;
		}
		template<typename Char>
		static bool is_num(Char c) {
			BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<Char>, is_wchar_type<Char> >));
			return c >= '0' && c <= '9';
		}
		template<typename Char>
		static bool is_upper(Char c) {
			BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<Char>, is_wchar_type<Char> >));
			return c >= 'A' && c <= 'F';
		}
		template<typename Char>
		static bool is_lower(Char c) {
			BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<Char>, is_wchar_type<Char> >));
			return c >= 'a' && c <= 'f';
		}
	}	// namespace url_encode_detail
	//
	// url_encode_table
	//
	template<typename Char = char>
	struct url_encode_table {
	public:
		typedef Char char_type;
	public:
		typedef boost::array<char_type, 16> array_type;
		typedef typename array_type::size_type size_type;
	public:
		static size_type const static_size = array_type::static_size;
	public:
		static array_type const array;
	public:
		static bool is_unreserved(char_type c) {
			return url_encode_detail::is_unreserved(c);
		}
		static bool is_space(char_type c) {
			return c == ' ';
		}
		static bool is_tilde(char_type c) {
			return c == '~';
		}
		static char_type encode_high(char_type c) {
			return array[c >> 4 & 0x0F];
		}
		static char_type encode_low(char_type c) {
			return array[c & 0x0F];
		}
	private:
		BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<char_type>, is_wchar_type<char_type> >));
	};
	template<typename Char>
	typename url_encode_table<Char>::array_type const url_encode_table<Char>::array = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	//
	// url_decode_table
	//
	template<typename Char = char>
	struct url_decode_table {
	public:
		typedef Char char_type;
	public:
		static char_type const e_dec = '\xFF';
	public:
		static bool is_unreserved(char_type c) {
			return url_encode_detail::is_unreserved(c);
		}
		static bool is_percent(char_type c) {
			return c == '%';
		}
		static bool is_plus(char_type c) {
			return c == '+';
		}
		static char_type decode(char_type c) {
			switch (c) {
			case '0':
				return 0;
			case '1':
				return 1;
			case '2':
				return 2;
			case '3':
				return 3;
			case '4':
				return 4;
			case '5':
				return 5;
			case '6':
				return 6;
			case '7':
				return 7;
			case '8':
				return 8;
			case '9':
				return 9;
			case 'A':
			case 'a':
				return 10;
			case 'B':
			case 'b':
				return 11;
			case 'C':
			case 'c':
				return 12;
			case 'D':
			case 'd':
				return 13;
			case 'E':
			case 'e':
				return 14;
			case 'F':
			case 'f':
				return 15;
			}
			return e_dec;
		}
		static char_type decode(char_type h, char_type l) {
			char_type e_h = decode(h);
			char_type e_l = decode(l);
			return e_h == e_dec || e_l == e_dec
				? e_dec
				: e_h << 4 & 0xF0 | e_l & 0x0F
				;
		}
	private:
		BOOST_MPL_ASSERT((boost::mpl::or_<is_char_type<char_type>, is_wchar_type<char_type> >));
	};
	//
	// url_encode_options
	//
	struct url_encode_options {
	public:
		typedef unsigned type;
	public:
		static type const space_to_plus = 0x00000001;
		static type const tilde = 0x00000100;
	};
	//
	// url_encode
	//
	template<typename Range, typename OutputIterator>
	bool url_encode(
		Range const& range,
		OutputIterator out,
		url_encode_options::type options = 0
		)
	{
		typedef typename boost::range_value<Range>::type value_type;
		typedef typename boost::range_size<Range>::type size_type;
		typedef typename boost::range_const_iterator<Range>::type const_iterator;
		typedef url_encode_table<value_type> table_type;
		if (options & url_encode_options::space_to_plus && options & url_encode_options::tilde) {
			BOOST_FOREACH(value_type e, range) {
				if (table_type::is_unreserved(e) && !table_type::is_tilde(e)) {
					*out++ = e;
				} else if (table_type::is_space(e)) {
					*out++ = '+';
				} else {
					*out++ = '%';
					*out++ = table_type::encode_high(e);
					*out++ = table_type::encode_low(e);
				}
			}
		} else if (options & url_encode_options::space_to_plus) {
			BOOST_FOREACH(value_type e, range) {
				if (table_type::is_unreserved(e)) {
					*out++ = e;
				} else if (table_type::is_space(e)) {
					*out++ = '+';
				} else {
					*out++ = '%';
					*out++ = table_type::encode_high(e);
					*out++ = table_type::encode_low(e);
				}
			}
		} else if (options & url_encode_options::tilde) {
			BOOST_FOREACH(value_type e, range) {
				if (table_type::is_unreserved(e) && !table_type::is_tilde(e)) {
					*out++ = e;
				} else {
					*out++ = '%';
					*out++ = table_type::encode_high(e);
					*out++ = table_type::encode_low(e);
				}
			}
		} else {
			BOOST_FOREACH(value_type e, range) {
				if (table_type::is_unreserved(e)) {
					*out++ = e;
				} else {
					*out++ = '%';
					*out++ = table_type::encode_high(e);
					*out++ = table_type::encode_low(e);
				}
			}
		}
		return true;
	}
	//
	// url_decode
	//
	template<typename Range, typename OutputIterator>
	bool url_decode(
		Range const& range,
		OutputIterator out
		)
	{
		typedef typename boost::range_value<Range>::type value_type;
		typedef typename boost::range_size<Range>::type size_type;
		typedef typename boost::range_const_iterator<Range>::type const_iterator;
		typedef url_decode_table<value_type> table_type;
		for (const_iterator i = boost::begin(range), last = boost::end(range); i != last; ++i) {
			value_type e = *i;
			if (table_type::is_percent(e)) {
				if (++i == last) {
					return false;
				}
				value_type h = *i;
				if (++i == last) {
					return false;
				}
				value_type l = *i;
				value_type dec = table_type::decode(h, l);
				if (dec == table_type::e_dec) {
					return false;
				}
				*out++ = dec;
			} else if (table_type::is_unreserved(e)) {
				*out++ = e;
			} else if (table_type::is_plus(e)) {
				*out++ = ' ';
			} else {
				return false;
			}
		}
		return true;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_URL_ENCODE_HPP
