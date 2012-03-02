#ifndef SPRIG_ASIO_EXTEND_BUFFER_HPP
#define SPRIG_ASIO_EXTEND_BUFFER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range.hpp>
#include <boost/asio/buffer.hpp>
#include <sprig/reference_holder.hpp>

namespace sprig {
	namespace asio {
		//
		// extend_buffers_iterator
		//
		template<typename Container, typename Buffer>
		class extend_buffers_iterator
			: public boost::iterator_facade<
				extend_buffers_iterator<Container, Buffer>,
				Buffer,
				boost::bidirectional_traversal_tag
			>
		{
		public:
			typedef Container container_type;
			typedef Buffer buffer_type;
			typedef typename boost::range_size<container_type>::type size_type;
		private:
			typedef boost::iterator_facade<
				extend_buffers_iterator<Container, Buffer>,
				Buffer,
				boost::bidirectional_traversal_tag
			> iterator_facade_type;
			typedef extend_buffers_iterator this_type;
		public:
			static std::size_t const elem_size = sizeof(typename boost::range_value<Container>::type);
		private:
			sprig::reference_holder<container_type> container_;
			mutable buffer_type buffer_;
			size_type size_;
			size_type offset_first_;
			size_type offset_;
			size_type max_size_;
			bool is_last_;
		public:
			extend_buffers_iterator()
				: size_(0)
				, offset_first_(0)
				, offset_(0)
				, max_size_(0)
				, is_last_(true)
			{}
			extend_buffers_iterator(
				container_type& container,
				size_type size,
				size_type offset_first,
				size_type max_size,
				bool is_last = false
				)
				: container_(container)
				, size_(size)
				, offset_first_(offset_first)
				, offset_(offset_first)
				, max_size_(max_size)
				, is_last_(is_last)
			{
				if (is_last_) {
					offset_ = max_size_ + (size_ - (max_size_ - offset_first) % size_);
				} else if (offset_ > max_size_) {
					is_last_ = true;
				}
			}
		private:
			friend class boost::iterator_core_access;
			typename iterator_facade_type::reference dereference() const {
				container_type& container = container_.get_mutable();
				size_type size = (std::min)(size_, max_size_ - offset_);
				size_type current_size = boost::size(container) * elem_size;
				size_type required_size = offset_ + size;
				if (current_size < required_size) {
					container.resize(required_size / elem_size);
				}
				buffer_ = buffer_type(&container[offset_ / elem_size], size);
				return buffer_;
			}
			bool equal(this_type const& other) const {
				return container_.get_pointer() == other.container_.get_pointer()
					&& size_ == other.size_
					&& offset_ == other.offset_
					&& offset_first_ == other.offset_first_
					&& max_size_ == other.max_size_
					;
			}
			void increment() {
				offset_ += size_;
				if (offset_ > max_size_) {
					is_last_ = true;
				}
			}
			void decrement() {
				offset_ -= size_;
				if (offset_ <= max_size_) {
					is_last_ = false;
				}
			}
		};
		//
		// extend_buffers_impl
		//
		template<typename Container, typename Buffer>
		class extend_buffers_impl {
		public:
			typedef Container container_type;
			typedef Buffer buffer_type;
			typedef extend_buffers_iterator<container_type, buffer_type> iterator_type;
			typedef typename boost::range_size<container_type>::type size_type;
			typedef buffer_type value_type;
			typedef iterator_type const_iterator;
		public:
			static std::size_t const elem_size = sizeof(typename boost::range_value<Container>::type);
		private:
			sprig::reference_holder<container_type> container_;
			size_type size_;
			size_type offset_first_;
			size_type max_size_;
		public:
			extend_buffers_impl()
				: size_(0)
				, offset_first_(0)
				, max_size_(0)
			{}
			extend_buffers_impl(
				container_type& container,
				size_type size,
				size_type offset_first
				)
				: container_(container)
				, size_(size)
				, offset_first_(offset_first)
				, max_size_(container.max_size() * elem_size)
			{}
			extend_buffers_impl(
				container_type& container,
				size_type size,
				size_type offset_first,
				size_type max_size
				)
				: container_(container)
				, size_(size)
				, offset_first_(offset_first)
				, max_size_((std::min)(max_size, container.max_size() * elem_size))
			{}
			const_iterator begin() const {
				return const_iterator(container_.get_mutable(), size_, offset_first_, max_size_);
			}
			const_iterator end() const {
				return const_iterator(container_.get_mutable(), size_, offset_first_, max_size_, true);
			}
		};
		//
		// extend_buffers
		//
		template<typename Container>
		class extend_buffers
			: public extend_buffers_impl<Container, boost::asio::mutable_buffer>
		{
		public:
			typedef Container container_type;
		private:
			typedef extend_buffers_impl<Container, boost::asio::mutable_buffer> impl_type;
		public:
			typedef typename impl_type::size_type size_type;
			typedef typename impl_type::value_type value_type;
			typedef typename impl_type::const_iterator const_iterator;
		public:
			extend_buffers() {}
			extend_buffers(
				container_type& container,
				size_type size,
				size_type offset_first = 0
				)
				: impl_type(container, size, offset_first)
			{}
			extend_buffers(
				container_type& container,
				size_type size,
				size_type offset_first,
				size_type max_size
				)
				: impl_type(container, size, offset_first, max_size)
			{}
		};
		//
		// extend_buffer
		//
		template<typename Container>
		extend_buffers<Container> extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size,
			typename boost::range_size<Container>::type offset_first
			)
		{
			return extend_buffers<Container>(container, size, offset_first);
		}
		template<typename Container>
		extend_buffers<Container> extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size,
			typename boost::range_size<Container>::type offset_first,
			typename boost::range_size<Container>::type max_size
			)
		{
			return extend_buffers<Container>(container, size, offset_first, max_size);
		}
		//
		// update_extend_buffer
		//
		template<typename Container>
		extend_buffers<Container> update_extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size
			)
		{
			return extend_buffers<Container>(container, size, 0);
		}
		template<typename Container>
		extend_buffers<Container> update_extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size,
			typename boost::range_size<Container>::type max_size
			)
		{
			return extend_buffers<Container>(container, size, 0, max_size);
		}
		//
		// append_extend_buffer
		//
		template<typename Container>
		extend_buffers<Container> append_extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size
			)
		{
			static std::size_t const elem_size = sizeof(typename boost::range_value<Container>::type);
			return extend_buffers<Container>(container, size, boost::size(container) * elem_size);
		}
		template<typename Container>
		extend_buffers<Container> append_extend_buffer(
			Container& container,
			typename boost::range_size<Container>::type size,
			typename boost::range_size<Container>::type max_size
			)
		{
			static std::size_t const elem_size = sizeof(typename boost::range_value<Container>::type);
			return extend_buffers<Container>(container, size, boost::size(container) * elem_size, max_size);
		}
	}	// namespace asio
}	// namespace sprig

#endif	// #ifndef SPRIG_ASIO_EXTEND_BUFFER_HPP
