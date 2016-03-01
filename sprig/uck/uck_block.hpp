/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_UCK_BLOCK_HPP
#define SPRIG_UCK_UCK_BLOCK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <utility>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <sprig/assert.hpp>
#include <sprig/binary.hpp>
#include <sprig/utility/iterator.hpp>
#include <sprig/uck/magic.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>

namespace sprig {
	namespace uck {
		//
		// uck_block
		//
		template<typename Traits = traits<> >
		class uck_block {
		private:
			typedef uck_block this_type;
		public:
			typedef types<Traits> types_type;
		private:
			std::size_t tag_size_;
			std::size_t type_size_;
			std::size_t size_size_;
			typename types_type::tag_type tag_;
			typename types_type::type_type type_;
			typename types_type::size_type size_;
			typename types_type::variant_type data_;
			typename types_type::bin_type bin_;
		public:
			explicit uck_block(std::size_t tag_size = 4, std::size_t type_size = 4, std::size_t size_size = 4)
				: tag_size_(tag_size)
				, type_size_(type_size)
				, size_size_(size_size)
			{}
			template<typename Iterator>
			bool analyze(Iterator first, Iterator last) {
				std::size_t d = std::distance(first, last);
				if (d < tag_size_ + type_size_ + size_size_) {
					return false;
				}
				tag_.assign(first, sprig::get_advance(first, tag_size_));
				std::advance(first, tag_size_);
				type_.assign(first, sprig::get_advance(first, type_size_));
				std::advance(first, type_size_);
				size_ = sprig::int_from_big_endian<typename types_type::size_type, types_type::traits_type::size_size>(first);
				if (d < block_size()) {
					return false;
				}
				std::advance(first, size_size_);
				switch (magic::type_index_bimap().left.at(type_)) {
				case magic::indexes::variant_node_index:
					{
						data_ = typename types_type::node_type();
						Iterator node_last = sprig::get_advance(first, size_);
						std::size_t current_block_size = 0;
						while (current_block_size < size_) {
							boost::shared_ptr<this_type> elem(boost::make_shared<this_type>(tag_size_, type_size_, size_size_));
							if (!elem->analyze(first, node_last)) {
								return false;
							}
							boost::get<typename types_type::node_type>(data_).push_back(elem);
							std::advance(first, elem->block_size());
							current_block_size += elem->block_size();
						}
					}
					break;
				case magic::indexes::variant_bin_index:
					{
						data_ = typename types_type::bin_type();
						boost::get<typename types_type::bin_type>(data_).assign(first, sprig::get_advance(first, size_));
					}
					break;
				case magic::indexes::variant_int_index:
					{
						data_ = typename types_type::int_type();
						boost::get<typename types_type::int_type>(data_) = sprig::int_from_big_endian<typename types_type::int_type>(first, size_);
					}
					break;
				case magic::indexes::variant_uint_index:
					{
						data_ = typename types_type::uint_type();
						boost::get<typename types_type::uint_type>(data_) = sprig::int_from_big_endian<typename types_type::uint_type>(first, size_);
					}
					break;
				default:
					SPRIG_ASSERT(0);
				}
				return true;
			}
			std::size_t tag_size() const {
				return tag_size_;
			}
			std::size_t type_size() const {
				return type_size_;
			}
			std::size_t size_size() const {
				return size_size_;
			}
			typename types_type::tag_type const& tag() const {
				return tag_;
			}
			typename types_type::type_type const& type() const {
				return type_;
			}
			typename types_type::size_type size() const {
				return size_;
			}
			typename types_type::variant_type const& data() const {
				return data_;
			}
			std::size_t block_size() const {
				return tag_size_ + type_size_ + size_size_ + size_;
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_UCK_BLOCK_HPP
