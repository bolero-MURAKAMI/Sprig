#ifndef SPRIG_UCK_TYPES_HPP
#define SPRIG_UCK_TYPES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <vector>
#include <boost/integer.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <sprig/uck/traits.hpp>

namespace sprig {
	namespace uck {
		//
		// declares
		//
		template<typename Traits>
		class uck_block;
		template<typename Traits>
		class uck_data;
		template<typename Traits>
		class uck_conf;
		template<typename Traits>
		class uck_task;
		//
		// types
		//
		template<typename Traits = traits<> >
		struct types {
			typedef Traits traits_type;
			typedef uck_block<traits_type> block_type;
			typedef uck_data<traits_type> data_type;
			typedef std::string tag_type;
			typedef std::string type_type;
			typedef typename boost::uint_t<traits_type::size_size * 8>::least size_type;
			typedef boost::shared_ptr<block_type> node_elem_type;
			typedef std::vector<node_elem_type> node_type;
			typedef unsigned char byte_type;
			typedef std::vector<byte_type> bin_type;
			typedef typename boost::int_t<traits_type::int_size * 8>::least int_type;
			typedef typename boost::uint_t<traits_type::int_size * 8>::least uint_type;
			typedef boost::variant<node_type, bin_type, int_type, uint_type> variant_type;
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_TYPES_HPP
