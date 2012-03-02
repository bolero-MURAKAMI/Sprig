#ifndef SPRIG_IOSTREAMS_CONTAINER_HPP
#define SPRIG_IOSTREAMS_CONTAINER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <algorithm>
#include <boost/next_prior.hpp>
#include <boost/iostreams/categories.hpp>

namespace sprig {
	namespace iostreams {
		//
		// container_source
		//
		template<typename Container>
		class container_source {
		public:
			typedef Container container_type;
			typedef typename container_type::value_type char_type;
			typedef typename container_type::size_type size_type;
			typedef boost::iostreams::source_tag category;
		private:
			container_type& container_;
			size_type pos_;
		public:
			explicit container_source(container_type& container)
				: container_(container)
				, pos_(0)
			{}
			std::streamsize read(char_type* s, std::streamsize n) {
				std::streamsize const amt = static_cast<std::streamsize>(container_.size() - pos_);
				std::streamsize const result = (std::min)(n, amt);
				if (result) {
					std::copy(
						boost::next(container_.begin(), pos_),
						boost::next(container_.begin(), pos_ + result),
						s
						);
					pos_ += result;
					return result;
				} else {
					return -1;
				}
			}
			container_type& container() {
				return container_;
			}
			container_type const& container() const {
				return container_;
			}
		};
	}	// namespace iostreams
}	// namespace sprig

#endif	// #ifndef SPRIG_IOSTREAMS_CONTAINER_HPP
