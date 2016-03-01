/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_LIBPNG_BASIC_HPP
#define SPRIG_LIBPNG_BASIC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <csetjmp>
#include <sprig/external/png.hpp>
#include <sprig/exception.hpp>

//
// SPRIG_PNG_SETJMP
//
#define SPRIG_PNG_SETJMP(PNG) (setjmp(png_jmpbuf(PNG)))

namespace sprig {
	namespace png {
		//
		// typedef
		//
		typedef png_byte byte_type;

		//
		// png_error
		//
		SPRIG_EXCEPTION_DECL(png_error);
		//
		// libpng_error
		//
		SPRIG_EXCEPTION_INHERIT_DECL(libpng_error, png_error);

		//
		// png_pixels_order
		//
		enum png_pixels_order {
			png_pixels_order_rgba,
			png_pixels_order_bgra,
			png_pixels_order_argb,
			png_pixels_order_abgr,
			png_pixels_order_rgb,
			png_pixels_order_bgr
		};

		//
		// IHDR
		//
		struct IHDR {
			png_uint_32 width;
			png_uint_32 height;
			int bit_depth;
			int color_type;
			int interlace_method;
			int compression_method;
			int filter_method;
		public:
			IHDR()
				: width(0)
				, height(0)
				, bit_depth(8)
				, color_type(PNG_COLOR_TYPE_RGB_ALPHA)
				, interlace_method(PNG_FILTER_TYPE_DEFAULT)
				, compression_method(PNG_COMPRESSION_TYPE_DEFAULT)
				, filter_method(PNG_INTERLACE_NONE)
			{}
		};

		//
		// png_sig_check
		//
		SPRIG_INLINE bool png_sig_check(png_byte const* sig, png_size_t num_to_check) {
			return ::png_sig_cmp(const_cast<png_bytep>(sig), 0, num_to_check) == 0;
		}

		//
		// png_get_IHDR
		//
		SPRIG_INLINE bool png_get_IHDR(
			png_structp png,
			png_infop info,
			IHDR& ihdr
			)
		{
			return ::png_get_IHDR(
				png,
				info,
				&ihdr.width,
				&ihdr.height,
				&ihdr.bit_depth,
				&ihdr.color_type,
				&ihdr.interlace_method,
				&ihdr.compression_method,
				&ihdr.filter_method
				)
				!= 0;
		}

		//
		// png_set_IHDR
		//
		SPRIG_INLINE void png_set_IHDR(
			png_structp png,
			png_infop info,
			IHDR const& ihdr
			)
		{
			::png_set_IHDR(
				png,
				info,
				ihdr.width,
				ihdr.height,
				ihdr.bit_depth,
				ihdr.color_type,
				ihdr.interlace_method,
				ihdr.compression_method,
				ihdr.filter_method
				);
		}
	}	// namespace png
}	// namespace sprig

#endif	// #ifndef SPRIG_LIBPNG_BASIC_HPP
