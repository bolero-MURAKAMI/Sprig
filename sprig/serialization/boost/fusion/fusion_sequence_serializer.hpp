#ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZER_HPP
#define SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/nvp.hpp>
#include <boost/utility/addressof.hpp>

namespace sprig {
	namespace serialization {
		//
		// fusion_sequence_serializer
		//
		template<typename Archive>
		class fusion_sequence_serializer {
		public:
			typedef Archive archive_type;
		private:
			archive_type* ar_;
		public:
			explicit fusion_sequence_serializer(archive_type& ar)
				: ar_(boost::addressof(ar))
			{}
			template<typename T>
			void operator()(T& t) const {
				(*ar_)
					& boost::serialization::make_nvp("item", t)
					;
			}
		};
		//
		// make_fusion_sequence_serializer
		//
		template<typename Archive>
		fusion_sequence_serializer<Archive> make_fusion_sequence_serializer(Archive& ar) {
			return fusion_sequence_serializer<Archive>(ar);
		}
	}	// namespace serialization
}	// namespace serialization

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_FUSION_SEQUENCE_SERIALIZER_HPP
