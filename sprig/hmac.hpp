/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_HMAC_HPP
#define SPRIG_HMAC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <sprig/octet.hpp>

namespace sprig {
	namespace hmac_detail {
		template<typename Container, typename Range>
		SPRIG_INLINE void insert(Container& container, Range const& range) {
			container.insert(
				boost::end(container),
				boost::begin(range),
				boost::end(range)
				);
		}
	}	// namespace hmac_detail
	//
	// hmac
	//
	template<typename Hasher, typename Range>
	SPRIG_INLINE typename Hasher::value_type hmac(Range const& key, Range const& data) {
		typedef Hasher hasher_type;
		typedef Range range_type;
		typedef typename hasher_type::value_type value_type;
		typedef typename sprig::byte_of<value_type>::type byte_type;
		typedef typename sprig::array_octet_of<value_type>::type octet_type;
		typedef std::vector<byte_type> bytes_type;
		static byte_type const ipad = 0x36;
		static byte_type const opad = 0x5C;

		bytes_type k(boost::begin(key), boost::end(key));
		if (k.size() < hasher_type::block_size) {
			k.resize(hasher_type::block_size);
		}
		bytes_type d(boost::begin(data), boost::end(data));

		bytes_type work1(k);
		BOOST_FOREACH(byte_type& e, work1) {
			e ^= ipad;
		}
		hmac_detail::insert(work1, d);

		bytes_type work2(k);
		BOOST_FOREACH(byte_type& e, work2) {
			e ^= opad;
		}

		hmac_detail::insert(
			work2,
			sprig::to_octet<octet_type>(
				hasher_type()(work1)
				)
			);

		return hasher_type()(work2);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_HMAC_HPP
