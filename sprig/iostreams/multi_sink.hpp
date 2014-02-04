/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_IOSTREAMS_MUTTI_SINK_HPP
#define SPRIG_IOSTREAMS_MUTTI_SINK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/foreach.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/write.hpp>

namespace sprig {
	namespace iostreams {
		//
		// multi_sink
		//
		template<
			typename Sink,
			typename Value = Sink*,
			typename Container = std::vector<Value>
		>
		class multi_sink {
		public:
			typedef Sink sink_type;
			typedef Value value_type;
			typedef Container container_type;
			typedef typename container_type::size_type size_type;
			typedef typename boost::iostreams::char_type_of<sink_type>::type char_type;
			typedef boost::iostreams::sink_tag category;
		private:
			container_type container_;
		public:
			std::streamsize write(char_type const* s, std::streamsize n) {
				BOOST_FOREACH(value_type const& e, container_) {
					boost::iostreams::write(*e, s, n);
				}
				return n;
			}
			void push_back(value_type const& e) {
				container_.push_back(e);
			}
			void pop_back() {
				container_.pop_back();
			}
			void push_front(value_type const& e) {
				container_.push_front(e);
			}
			void pop_front() {
				container_.pop_front();
			}
			value_type& back() {
				return container_.back();
			}
			value_type const& back() const {
				return container_.back();
			}
			value_type& front() {
				return container_.front();
			}
			value_type const& front() const {
				return container_.front();
			}
			size_type size() const {
				return container_.size();
			}
			bool empty() const {
				return container_.empty();
			}
		};
	}	// namespace iostreams
}	// namespace sprig

#endif	// #ifndef SPRIG_IOSTREAMS_MUTTI_SINK_HPP
