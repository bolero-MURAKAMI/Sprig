#ifndef SPRIG_BASE64_HPP
#define SPRIG_BASE64_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/array.hpp>
#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>
#include <sprig/type_traits/is_char_type.hpp>

namespace sprig {
	//
	// base64_table
	//
	template<typename Char = char>
	struct base64_table {
	public:
		typedef Char char_type;
	public:
		typedef boost::array<char_type, 64> array_type;
		typedef typename array_type::size_type size_type;
	public:
		static size_type const static_size = array_type::static_size;
		static char_type const e_enc = '=';
		static char_type const e_dec = static_size;
		static char_type const c_lf = '\n';
	public:
		static array_type const array;
	public:
		static char_type encode(char_type c) {
			return c < 0 || c >= static_size
				? e_enc
				: array[c]
				;
		}
		static char_type decode(char_type c) {
			size_type i = 0;
			for (; i != static_size; ++i) {
				if (array[i] == c) {
					break;
				}
			}
			return i == static_size
				? e_dec
				: i
				;
		}
	private:
		BOOST_MPL_ASSERT((is_char_type<char_type>));
	};
	template<typename Char>
	typename base64_table<Char>::array_type const base64_table<Char>::array = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
	};
	namespace base64_detail {
		//
		// encoded_inserter
		//
		template<typename Range>
		struct encoded_inserter {
		public:
			typedef typename boost::range_value<Range>::type value_type;
			typedef base64_table<value_type> table_type;
		private:
			std::size_t const line_max_length_;
			std::size_t line_length_;
		public:
			explicit encoded_inserter(std::size_t line_max_length)
				: line_max_length_(line_max_length)
				, line_length_(0)
			{}
			template<typename OutputIterator>
			void operator()(
				OutputIterator& out,
				value_type c
				)
			{
				*out++ = c;
				++line_length_;
				if (line_max_length_ && line_length_ >= line_max_length_) {
					*out++ = table_type::c_lf;
					line_length_ = 0;
				}
			}
		};
	}	// namespace base64_detail
	//
	// base64_encode
	//
	template<typename Range, typename OutputIterator>
	bool base64_encode(
		Range const& range,
		OutputIterator out,
		std::size_t line_max_length = 76
		)
	{
		typedef typename boost::range_value<Range>::type value_type;
		typedef typename boost::range_size<Range>::type size_type;
		typedef typename boost::range_const_iterator<Range>::type const_iterator;
		typedef base64_table<value_type> table_type;
		const_iterator it = boost::begin(range);
		size_type const size = boost::size(range);
		base64_detail::encoded_inserter<Range> inserter(line_max_length);
		for (size_type i = 0, last = size / 3; i != last; ++i) {
			value_type const e0 = *it++;
			value_type const e1 = *it++;
			value_type const e2 = *it++;
			inserter(out, table_type::encode(e0 >> 2 & 0x3F));
			inserter(out, table_type::encode((e0 << 4 & 0x30) | (e1 >> 4 & 0x0F)));
			inserter(out, table_type::encode((e1 << 2 & 0x3C) | (e2 >> 6 & 0x03)));
			inserter(out, table_type::encode(e2 & 0x3F));
		}
		switch (size % 3) {
		case 2:
			{
				value_type const e0 = *it++;
				value_type const e1 = *it++;
				inserter(out, table_type::encode(e0 >> 2 & 0x3F));
				inserter(out, table_type::encode((e0 << 4 & 0x30) | (e1 >> 4 & 0x0F)));
				inserter(out, table_type::encode(e1 << 2 & 0x3F));
				inserter(out, table_type::e_enc);
			}
			break;
		case 1:
			{
				value_type const e0 = *it++;
				inserter(out, table_type::encode(e0 >> 2 & 0x3F));
				inserter(out, table_type::encode(e0 << 4 & 0x3F));
				inserter(out, table_type::e_enc);
				inserter(out, table_type::e_enc);
			}
			break;
		}
		return true;
	}
	namespace base64_detail {
		//
		// process_decoder
		//
		template<typename Range>
		struct process_decoder {
		public:
			typedef typename boost::range_value<Range>::type value_type;
			typedef typename boost::range_size<Range>::type size_type;
			typedef typename boost::range_const_iterator<Range>::type const_iterator;
			typedef base64_table<value_type> table_type;
		private:
			size_type const size_;
			size_type current_;
			value_type decoded_;
		public:
			explicit process_decoder(size_type size)
				: size_(size)
				, current_(0)
				, decoded_('\0')
			{}
			bool next(const_iterator& it) {
				while (current_ < size_) {
					value_type c = *it++;
					++current_;
					if (c == table_type::c_lf) {
						continue;
					} else if (c == table_type::e_enc) {
						decoded_ = table_type::e_dec;
						return true;
					}
					decoded_ = table_type::decode(c);
					if (decoded_ == table_type::e_dec) {
						return false;
					} else {
						return true;
					}
				}
				decoded_ = '\0';
				return false;
			}
			bool full() const {
				return current_ == size_;
			}
			value_type operator()() const {
				return decoded_;
			}
			operator bool() const {
				return decoded_ != table_type::e_dec;
			}
			bool operator!() const {
				return decoded_ == table_type::e_dec;
			}
		};
	}	// namespace base64_detail
	//
	// base64_decode
	//
	template<typename Range, typename OutputIterator>
	bool base64_decode(
		Range const& range,
		OutputIterator out
		)
	{
		typedef typename boost::range_value<Range>::type value_type;
		typedef typename boost::range_size<Range>::type size_type;
		typedef typename boost::range_const_iterator<Range>::type const_iterator;
		typedef base64_table<value_type> table_type;
		const_iterator it = boost::begin(range);
		size_type const size = boost::size(range);
		base64_detail::process_decoder<Range> decoder(size);
		for (; ; ) {
			if (!decoder.next(it) && !decoder) {
				return false;
			}
			value_type const e0 = decoder();
			if (!decoder.next(it) && !decoder) {
				return false;
			}
			value_type const e1 = decoder();
			if (!decoder.next(it) && !decoder) {
				return false;
			}
			value_type const e2 = decoder();
			if (!decoder.next(it) && !decoder) {
				return false;
			}
			value_type const e3 = decoder();
			if (e0 == table_type::e_dec || e1 == table_type::e_dec) {
				return false;
			} else if (e2 == table_type::e_dec) {
				*out++ = (e0 << 2 & 0xFC) | (e1 >> 4 & 0x03);
				break;
			} else if (e3 == table_type::e_dec) {
				*out++ = (e0 << 2 & 0xFC) | (e1 >> 4 & 0x03);
				*out++ = (e1 << 4 & 0xF0) | (e2 >> 2 & 0x0F);
				break;
			}
			*out++ = (e0 << 2 & 0xFC) | (e1 >> 4 & 0x03);
			*out++ = (e1 << 4 & 0xF0) | (e2 >> 2 & 0x0F);
			*out++ = (e2 << 6 & 0xC0) | (e3 & 0x3F);
		}
		if (!decoder.full()) {
			return false;
		}
		return true;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_BASE64_HPP
