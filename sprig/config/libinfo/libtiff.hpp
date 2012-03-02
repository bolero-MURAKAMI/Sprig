#ifndef SPRIG_CONFIG_LIBINFO_LIBTIFF_HPP
#define SPRIG_CONFIG_LIBINFO_LIBTIFF_HPP

#include <sprig/config/pragma_once.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBTIFF)

#	include <sprig/config/pragma_message.hpp>
#	ifdef SPRIG_HAS_PRAGMA_MESSAGE

#		include <boost/preprocessor/stringize.hpp>
#		include <tiffconf.h>
#		include <tiff.h>
#		include <tiffvers.h>

#		pragma message("sprig/config/libinfo/libtiff.hpp")
#		pragma message("    SIZEOF_INT                      = " BOOST_PP_STRINGIZE(SIZEOF_INT))
#		pragma message("    SIZEOF_LONG                     = " BOOST_PP_STRINGIZE(SIZEOF_LONG))
#		pragma message("    HAVE_IEEEFP                     = " BOOST_PP_STRINGIZE(HAVE_IEEEFP))
#		pragma message("    HOST_FILLORDER                  = " BOOST_PP_STRINGIZE(HOST_FILLORDER))
#		pragma message("    HOST_BIGENDIAN                  = " BOOST_PP_STRINGIZE(HOST_BIGENDIAN))
#		pragma message("    CCITT_SUPPORT                   = " BOOST_PP_STRINGIZE(CCITT_SUPPORT))
#		pragma message("    JPEG_SUPPORT                    = " BOOST_PP_STRINGIZE(JPEG_SUPPORT))
#		pragma message("    LOGLUV_SUPPORT                  = " BOOST_PP_STRINGIZE(LOGLUV_SUPPORT))
#		pragma message("    LZW_SUPPORT                     = " BOOST_PP_STRINGIZE(LZW_SUPPORT))
#		pragma message("    NEXT_SUPPORT                    = " BOOST_PP_STRINGIZE(NEXT_SUPPORT))
#		pragma message("    PACKBITS_SUPPORT                = " BOOST_PP_STRINGIZE(PACKBITS_SUPPORT))
#		pragma message("    PIXARLOG_SUPPORT                = " BOOST_PP_STRINGIZE(PIXARLOG_SUPPORT))
#		pragma message("    THUNDER_SUPPORT                 = " BOOST_PP_STRINGIZE(THUNDER_SUPPORT))
#		pragma message("    ZIP_SUPPORT                     = " BOOST_PP_STRINGIZE(ZIP_SUPPORT))
#		pragma message("    STRIPCHOP_DEFAULT               = " BOOST_PP_STRINGIZE(STRIPCHOP_DEFAULT))
#		pragma message("    SUBIFD_SUPPORT                  = " BOOST_PP_STRINGIZE(SUBIFD_SUPPORT))
#		pragma message("    DEFAULT_EXTRASAMPLE_AS_ALPHA    = " BOOST_PP_STRINGIZE(DEFAULT_EXTRASAMPLE_AS_ALPHA))
#		pragma message("    CHECK_JPEG_YCBCR_SUBSAMPLING    = " BOOST_PP_STRINGIZE(CHECK_JPEG_YCBCR_SUBSAMPLING))
#		pragma message("    MDI_SUPPORT                     = " BOOST_PP_STRINGIZE(MDI_SUPPORT))
#		pragma message("    TIFF_VERSION                    = " BOOST_PP_STRINGIZE(TIFF_VERSION))
#		pragma message("    TIFF_BIGTIFF_VERSION            = " BOOST_PP_STRINGIZE(TIFF_BIGTIFF_VERSION))
#		pragma message("    TIFFLIB_VERSION                 = " BOOST_PP_STRINGIZE(TIFFLIB_VERSION))

#	endif	// #ifdef SPRIG_HAS_PRAGMA_MESSAGE

#endif	// #if defined(SPRIG_CONFIG_LIBINFO_MESSAGE) || defined(SPRIG_CONFIG_LIBINFO_MESSAGE_LIBTIFF)

#endif	// #ifndef SPRIG_CONFIG_LIBINFO_LIBTIFF_HPP
