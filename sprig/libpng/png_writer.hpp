#ifndef SPRIG_LIBPNG_PNG_WRITER_HPP
#define SPRIG_LIBPNG_PNG_WRITER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <vector>
#include <iterator>
#include <boost/ref.hpp>
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
#include <sprig/type_traits/is_derived_basic_ostream.hpp>
#include <sprig/libpng/basic.hpp>

namespace sprig {
	namespace png {
		//
		// png_write_image
		//
		template<typename Vector>
		SPRIG_INLINE void png_write_image(
			png_structp png,
			png_infop info,
			IHDR const& ihdr,
			Vector const& image,
			png_pixels_order pixels_order,
			bool flip_v = false
			)
		{
			BOOST_MPL_ASSERT((boost::is_same<typename Vector::value_type, png_byte>));

			if (/*little_endian() && */ihdr.bit_depth > 8) {
				::png_set_swap(png);
			}

			std::size_t line_length = 0;

			png_color_8 sig_bit;
			sig_bit.red = 8;
			sig_bit.green = 8;
			sig_bit.blue = 8;
			sig_bit.gray = 0;
			switch (pixels_order) {
			case png_pixels_order_rgba:
				sig_bit.alpha = 8;
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0, PNG_FILLER_AFTER);
				}
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_bgra:
				sig_bit.alpha = 8;
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0, PNG_FILLER_AFTER);
				}
				::png_set_bgr(png);
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_argb:
				sig_bit.alpha = 8;
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0, PNG_FILLER_BEFORE);
				}
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_abgr:
				sig_bit.alpha = 8;
				if (!(ihdr.color_type & PNG_COLOR_MASK_ALPHA)) {
					::png_set_filler(png, 0, PNG_FILLER_BEFORE);
				}
				::png_set_bgr(png);
				line_length = ihdr.width * 4;
				break;
			case png_pixels_order_rgb:
				sig_bit.alpha = 0;
				line_length = ihdr.width * 3;
				break;
			case png_pixels_order_bgr:
				sig_bit.alpha = 0;
				::png_set_bgr(png);
				line_length = ihdr.width * 3;
				break;
			}
			::png_set_sBIT(png, info, &sig_bit);

			if (line_length % 4) {
				line_length += 4 - line_length % 4;
			}

			std::vector<png_bytep> lines(ihdr.height);
			if (flip_v) {
				std::size_t size = image.size();
				for (std::size_t i = 0, last = lines.size(); i != last; ++i) {
					lines[i] = const_cast<png_bytep>(&image[size - line_length * (i + 1)]);
				}
			} else {
				for (std::size_t i = 0, last = lines.size(); i != last; ++i) {
					lines[i] = const_cast<png_bytep>(&image[line_length * i]);
				}
			}

			::png_write_image(png, &lines[0]);
		}

		//
		// png_write_ostream_fn
		//
		template<typename Elem, typename Traits>
		SPRIG_INLINE void png_write_ostream_fn(png_structp png, png_bytep buf, png_size_t size){
			typedef std::basic_ostream<Elem, Traits> ostream_type;
			typedef typename ostream_type::char_type char_type;
			typedef typename ostream_type::traits_type traits_type;
			ostream_type* ostream = reinterpret_cast<ostream_type*>(::png_get_io_ptr(png));
			ostream->write(reinterpret_cast<char_type const*>(buf), size);
		}
		//
		// png_write_ostream_functors
		//
		template<typename Elem, typename Traits = std::char_traits<Elem> >
		class png_write_ostream_functors {
		public:
			typedef std::basic_ostream<Elem, Traits> ostream_type;
			typedef typename ostream_type::char_type char_type;
			typedef typename ostream_type::traits_type traits_type;
		private:
			ostream_type* ostream_;
		public:
			png_write_ostream_functors(
				png_structp png,
				ostream_type& ostream
				)
				: ostream_(boost::addressof(ostream))
			{
				::png_set_write_fn(png, ostream_, &png_write_ostream_fn<char_type, traits_type>, 0);
			}
		};

		//
		// png_write_iterator_fn
		//
		template<typename OutputIterator>
		SPRIG_INLINE void png_write_iterator_fn(png_structp png, png_bytep buf, png_size_t size){
			typedef OutputIterator iterator_type;
			iterator_type* iterator = reinterpret_cast<iterator_type*>(::png_get_io_ptr(png));
			std::copy(
				buf,
				buf + size,
				*iterator
				);
		}
		//
		// png_write_iterator_functors
		//
		template<typename OutputIterator>
		class png_write_iterator_functors {
		public:
			typedef OutputIterator iterator_type;
		private:
			iterator_type iterator_;
		public:
			png_write_iterator_functors(
				png_structp png,
				iterator_type iterator
				)
				: iterator_(iterator)
			{
				::png_set_write_fn(png, boost::addressof(iterator), &png_write_iterator_fn<iterator_type>, 0);
			}
		};

		//
		// png_write_structs
		//
		struct png_write_structs {
		public:
			png_structp png;
			png_infop info;
		public:
			explicit png_write_structs(
				png_structp png = 0,
				png_infop info = 0
				)
				: png(png)
				, info(info)
			{}
			~png_write_structs() throw() {
				reset();
			}
			void reset() throw() {
				if (png) {
					::png_destroy_write_struct(
						&png,
						info ? &info : 0
						);
				}
				png = 0;
				info = 0;
			}
		};

		//
		// png_writer
		//
		class png_writer {
		private:
			boost::shared_ptr<void> functors_;
			boost::shared_ptr<png_write_structs> structs_;
		public:
			png_writer()
				: structs_(boost::make_shared<png_write_structs>())
			{
				structs_->png = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
				if (!structs_->png) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_create_write_struct()"));
					return;
				}

				structs_->info = ::png_create_info_struct(structs_->png);
				if (!structs_->info) {
					SPRIG_THROW_EXCEPTION(libpng_error("error in png_create_info_struct()"));
					return;
				}
			}
			~png_writer() throw() {
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
			template<typename Elem, typename Traits>
			void set_functors(std::basic_ostream<Elem, Traits>& ostream) {
				functors_ = boost::make_shared<png_write_ostream_functors<Elem, Traits> >(structs_->png, boost::ref(ostream));
			}
			template<typename OutputIterator>
			void set_functors(OutputIterator iterator) {
				functors_ = boost::make_shared<png_write_iterator_functors<OutputIterator> >(structs_->png, iterator);
			}
			void init_io(png_FILE_p fp) {
				::png_init_io(structs_->png, fp);
			}
			void write_info() {
				::png_write_info(structs_->png, structs_->info);
			}
			void write_end() {
				::png_write_end(structs_->png, 0);
			}
			void set_IHDR(IHDR const& ihdr) const {
				png_set_IHDR(structs_->png, structs_->info, ihdr);
			}
			template<typename Vector>
			void write_image(
				IHDR const& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				png_write_image(structs_->png, structs_->info, ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector>
			void write_body(
				IHDR& ihdr,
				Vector const& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				set_IHDR(ihdr);
				write_info();
				write_image(ihdr, image, pixels_order, flip_v);
				write_end();
			}
			template<typename Vector>
			void write_all(
				png_FILE_p fp,
				IHDR& ihdr,
				Vector const& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				init_io(fp);
				write_body(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector, typename Elem, typename Traits>
			void write_all(
				std::basic_ostream<Elem, Traits>& ostream,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false
				)
			{
				set_functors(ostream);
				write_body(ihdr, image, pixels_order, flip_v);
			}
			template<typename Vector, typename OutputIterator>
			void write_all(
				OutputIterator iterator,
				IHDR& ihdr,
				Vector& image,
				png_pixels_order pixels_order,
				bool flip_v = false,
				typename boost::disable_if<
					boost::mpl::or_<
						boost::is_same<OutputIterator, png_FILE_p>,
						sprig::is_derived_basic_ostream<OutputIterator>
					>
				>::type* = 0
				)
			{
				set_functors(iterator);
				write_body(ihdr, image, pixels_order, flip_v);
			}
		};
	}	// namespace png
}	// namespace sprig

#endif	// #ifndef SPRIG_LIBPNG_PNG_WRITER_HPP
