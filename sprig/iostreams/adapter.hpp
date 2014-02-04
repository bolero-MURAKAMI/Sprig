/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_IOSTREAMS_ADAPTER_HPP
#define SPRIG_IOSTREAMS_ADAPTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/write.hpp>
#include <sprig/reference_holder.hpp>

namespace sprig {
	namespace iostreams {
		//
		// source_adapter
		//
		template<typename Device>
		class source_adapter {
		public:
			typedef Device device_type;
			typedef typename boost::iostreams::char_type_of<device_type>::type char_type;
			typedef boost::iostreams::source_tag category;
		public:
			sprig::reference_holder<device_type> device_;
		public:
			explicit source_adapter(device_type& device)
				: device_(device)
			{}
			std::streamsize read(char_type* s, std::streamsize n) {
				return boost::iostreams::read(*device_, s, n);
			}
		};
		//
		// to_source
		//
		template<typename Device>
		source_adapter<Device> to_source(Device& device) {
			return source_adapter<Device>(device);
		}
		//
		// sink_adapter
		//
		template<typename Device>
		class sink_adapter {
		public:
			typedef Device device_type;
			typedef typename boost::iostreams::char_type_of<device_type>::type char_type;
			typedef boost::iostreams::sink_tag category;
		public:
			sprig::reference_holder<device_type> device_;
		public:
			explicit sink_adapter(device_type& device)
				: device_(device)
			{}
			std::streamsize write(char_type const* s, std::streamsize n) {
				return boost::iostreams::write(*device_, s, n);
			}
		};
		//
		// to_sink
		//
		template<typename Device>
		sink_adapter<Device> to_sink(Device& device) {
			return sink_adapter<Device>(device);
		}
	}	// namespace iostreams
}	// namespace sprig

#endif	// #ifndef SPRIG_IOSTREAMS_ADAPTER_HPP
