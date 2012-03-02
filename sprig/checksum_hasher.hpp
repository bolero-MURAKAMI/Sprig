#ifndef SPRIG_CHECKSUM_HASHER_HPP
#define SPRIG_CHECKSUM_HASHER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/range.hpp>
#include <boost/foreach.hpp>

namespace sprig {
	//
	// checksum_hasher
	//
	template<typename Checksum, std::size_t BlockSize = 64>
	class checksum_hasher {
	public:
		typedef Checksum checksum_type;
		typedef std::size_t size_type;
		typedef typename checksum_type::value_type value_type;
	public:
		static size_type const block_size = BlockSize;
	public:
		template<typename Pointer>
		static value_type calculate_block(Pointer first, Pointer last) {
			checksum_type checksum;
			checksum.process_block(first, last);
			return checksum.checksum();
		}
		template<typename Pointer>
		static value_type calculate_bytes(Pointer data, size_type size) {
			checksum_type checksum;
			checksum.process_bytes(data, size);
			return checksum.checksum();
		}
		template<typename Range>
		static value_type calculate(Range const& range) {
			checksum_type checksum;
			BOOST_FOREACH(typename boost::range_value<Range>::type e, range) {
				checksum.process_byte(e);
			}
			return checksum.checksum();
		}
	public:
		template<typename Range>
		value_type operator()(Range const& range) const {
			return calculate(range);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CHECKSUM_HASHER_HPP
