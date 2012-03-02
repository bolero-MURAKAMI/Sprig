#ifndef SPRIG_LIBPNG_PNG_READER_HPP
#define SPRIG_LIBPNG_PNG_READER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <vector>
#include <iterator>
#include <boost/next_prior.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/addressof.hpp>
#include <sprig/external/png.hpp>
#include <sprig/exception.hpp>
#include <sprig/type_traits/is_derived_basic_istream.hpp>
#include <sprig/libpng/basic.hpp>

namespace sprig {
	namespace png {
		//
		// png_read_image
		//
		template<typename Vector>
		SPRIG_INLINE void png_read_image(
			png_structp png,
			png_infop info,
			IHDR const& ihdr,
			Vector& image,
			png_pixels_order pixels_order,
			bool flip_v = false
			)
		{
			BOOST_MPL_ASSERT((boost::is_same<typename Vector::value_type, png_byte>));

			if(::png_get_valid(png, info, PNG_INFO_tRNS)
				|| ihdr.color_type == PNG_COLOR_TYPE_PALETTE
				|| ihdr.color_type == PNG_COLOR_TYPE_GRAY && ihdr.bit_depth < 8
				)
			{
				::png_set_expand(png);
			}
			if (ihdr.bit_depth > 8) {
				::png_set_strip_16(png);
			}
			if (ihdr.color_type == PNG_COLOR_TYPE_GRAY) {
				::png_set_gray_to_rgb(png);
			}

			std::size_t line_length = 0;

			switch (pixels_order) {
			case png_pixels_order_rgba:
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
				}
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_bgra:
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
				}
				::png_set_bgr(png);
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_argb:
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0xFF, PNG_FILLER_BEFORE);
				}
				::png_set_swap_alpha(png);
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_abgr:
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0xFF, PNG_FILLER_BEFORE);
				}
				::png_set_swap_alpha(png);
				::png_set_bgr(png);
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_rgb:
				if (ihdr.color_type & PNG_COLOR_MASK_ALPHA) {
					::png_set_strip_alpha(png);
				}
				line_length = ihdr.width * 3;
				break;
			case png_pixels_order_bgr:
				if (ihdr.color_type & PNG_COLOR_MASK_ALPHA) {
					::png_set_strip_alpha(png);
				}
				::png_set_bgr(png);
				line_length = ihdr.width * 3;
				break;
			}

			if (line_length % 4) {
				line_length += 4 - line_length % 4;
			}

			::png_read_update_info(png, info);

			image.resize(line_length * ihdr.height);

			std::vector<png_bytep> lines(ihdr.height);
			if (flip_v) {
				std::size_t size = image.size();
				for (std::size_t i = 0, last = lines.size(); i != last; ++i) {
					lines[i] = &image[size - line_length * (i + 1)];
				}
			} else {
				for (std::size_t i = 0, last = lines.size(); i != last; ++i) {
					lines[i] = &image[line_length * i];
				}
			}

			::png_read_image(png, &lines[0]);
		}

		namespace {
			//
			// png_read_buffer_fn
			//
			SPRIG_INLINE void png_read_buffer_fn(png_structp png, png_bytep buf, png_size_t size){
				png_byte const** p = reinterpret_cast<png_byte const**>(::png_get_io_ptr(png));
				std::memcpy(buf, *p, size);
				*p += size;
			}
		}	// anonymous-namespace
		//
		// png_read_buffer_functors
		//
		class png_read_buffer_functors {
		private:
			png_byte const* data_;
		public:
			png_read_buffer_functors(
				png_structp png,
				png_byte const* data
				)
				: data_(data)
			{
				::png_set_read_fn(png, &data_, &png_read_buffer_fn);
			}
		};

		//
		// png_read_istream_fn
		//
		template<typename Elem, typename Traits>
		SPRIG_INLINE void png_read_istream_fn(png_structp png, png_bytep buf, png_size_t size){
			typedef std::basic_istream<Elem, Traits> istream_type;
			typedef typename istream_type::char_type char_type;
			typedef typename istream_type::traits_type traits_type;
			istream_type* istream = reinterpret_cast<istream_type*>(::png_get_io_ptr(png));
			istream->read(reinterpret_cast<char_type*>(buf), size);
		}
		//
		// png_read_istream_functors
		//
		template<typename Elem, typename Traits = std::char_traits<Elem> >
		class png_read_istream_functors {
		public:
			typedef std::basic_istream<Elem, Traits> istream_type;
			typedef typename istream_type::char_type char_type;
			typedef typename istream_type::traits_type traits_type;
		private:
			istream_type* istream_;
		public:
			png_read_istream_functors(
				png_structp png,
				istream_type& istream
				)
				: istream_(boost::addressof(istream))
			{
				::png_set_read_fn(png, istream_, &png_read_istream_fn<char_type, traits_type>);
			}
		};

		//
		// png_read_iterator_fn
		//
		template<typename InputIterator>
		SPRIG_INLINE void png_read_iterator_fn(png_structp png, png_bytep buf, png_size_t size){
			typedef InputIterator iterator_type;
			iterator_type* iterator = reinterpret_cast<iterator_type*>(::png_get_io_ptr(png));
			std::copy(
				iterator,
				boost::next(iterator, size),
				buf
				);
			std::advance(iterator, size);
		}
		//
		// png_read_iterator_functors
		//
		template<typename InputIterator>
		class png_read_iterator_functors {
		public:
			typedef InputIterator iterator_type;
		private:
			iterator_type iterator_;
		public:
			png_read_iterator_functors(
				png_structp png,
				iterator_type iterator
				)
				: iterator_(iterator)
			{
				::png_set_read_fn(png, boost::addressof(iterator), &png_read_iterator_fn<iterator_type>);
			}
		};

		//
		// png_read_structs
		//
		struct png_read_structs {
		public:
			png_structp png;
			png_infop info;
			png_infop end_info;
		public:
			explicit png_read_structs(
				png_structp png = 0,
				png_infop info = 0,
				png_infop end_info = 0
				)
				: png(png)
				, info(info)
				, end_info(end_info)
			{}
			~png_read_structs() throw() {
				reset();
			}
			void reset() throw() {
				if (png) {
					::png_destroy_read_struct(
						&png,
						info ? &info : 0,
						end_info ? &end_info : 0
						);
				}
				png = 0;
				info = 0;
				end_info = 0;
			}
		};

		//
		// png_reader
		//
		class png_reader {
		private:
			boost::shared_ptr<void> functors_;
			boost::shared_ptr<png_read_structs> structs_;
		public:
			png_reader()
				: structs_(boost::make_shared<png_read_structs>())
			{
				structs_->png = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
				if (!structs_->png) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_create_read_struct()"));
					return;
				}

				structs_->info = ::png_create_info_struct(structs_->png);
				if (!structs_->info) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_create_info_struct()"));
					return;
				}

				structs_->end_info = ::png_create_info_struct(structs_->png);
				if (!structs_->end_info) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_create_info_struct()"));
					return;
				}
			}
			~png_reader() throw() {
				reset();
			}
			void reset() throw() {
				structs_->reset();
				functors_.reset();
			}
			png_structp png() const {
				return structs_->png;
			}
			png_infop info() const {
				return structs_->info;
			}
			png_infop end_info() const {
				return structs_->end_info;
			}
			void set_functors(png_byte const* data) {
				functors_ = boost::make_shared<png_read_buffer_functors>(structs_->png, data);
			}
			template<typename Elem, typename Traits>
			void set_functors(std::basic_istream<Elem, Traits>& istream) {
				functors_ = boost::make_shared<png_read_istream_functors<Elem, Traits> >(structs_->png, istream);
			}
			template<typename InputIterator>
			void set_functors(InputIterator itertor) {
				functors_ = boost::make_shared<png_read_iterator_functors<InputIterator> >(structs_->png, itertor);
			}
			void init_io(png_FILE_p fp) {
				::png_init_io(structs_->png, fp);
			}
			void read_info() {
				::png_read_info(structs_->png, structs_->info);
			}
			bool get_IHDR(IHDR& ihdr) const {
				return png_get_IHDR(structs_->png, structs_->info, ihdr);
			}
			template<typename Vector>
			void read_image(
				IHDR const& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				png_read_image(structs_->png, structs_->info, ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector>
			void read_body(
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				read_info();
				if (!get_IHDR(ihdr)) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_get_IHDR()"));
					return;
				}
				read_image(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector>
			void read_all(
				png_FILE_p fp,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				init_io(fp);
				read_body(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector>
			void read_all(
				png_byte const* data,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				set_functors(data);
				read_body(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector, typename Elem, typename Traits>
			void read_all(
				std::basic_istream<Elem, Traits>& istream,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				set_functors(istream);
				read_body(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector, typename InputIterator>
			void read_all(
				InputIterator itertor,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false,
				typename boost::disable_if<
					boost::mpl::or_<
						boost::is_same<InputIterator, png_FILE_p>,
						boost::is_same<InputIterator, png_byte const*>,
						boost::is_same<InputIterator, png_byte*>,
						sprig::is_derived_basic_istream<InputIterator>
					>
				>::type* = 0
				)
			{
				set_functors(itertor);
				read_body(ihdr, image, pixels_order, flip_v);
			}
		};
	}	// namespace png
}	// namespace sprig

#endif	// #ifndef SPRIG_LIBPNG_PNG_READER_HPP
