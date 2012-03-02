#ifndef SPRIG_DG_RENDER_FILTER_HPP
#define SPRIG_DG_RENDER_FILTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/optional/optional.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/dg/foundation.hpp>

namespace sprig {
	namespace dg {
		//
		// locked_data
		//
		struct locked_data {
		public:
			typedef D3DLOCKED_RECT locked_rect_type;
			typedef RECT rect_type;
		public:
			locked_rect_type locked_rect;
			rect_type rect;
		public:
		};

		//
		// render_filter
		//
		class render_filter {
		public:
			typedef locked_data locked_data_type;
		public:
			typedef std::pair<HRESULT, boost::optional<locked_data_type const&> > result_type;
		public:
			virtual ~render_filter() {}
			virtual HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) = 0;
			virtual result_type apply(locked_data_type const& data) const = 0;
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {}
		};
	}	// namespace dg
}	// namespace sprig

//	COMMENT: íäè€ÉNÉâÉXÇ∆ÇµÇƒìoò^
BOOST_SERIALIZATION_ASSUME_ABSTRACT(sprig::dg::render_filter);

#endif	// #ifndef SPRIG_DG_RENDER_FILTER_HPP
