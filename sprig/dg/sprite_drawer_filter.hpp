/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_SPRITE_DRAWER_FILTER_HPP
#define SPRIG_DG_SPRITE_DRAWER_FILTER_HPP

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
#include <sprig/dg/texture_manager.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_drawer_filter
		//
		class sprite_drawer_filter {
		public:
			typedef texture_manager_base texture_manager_type;
			typedef std::pair<HRESULT, boost::optional<texture_manager_type const&> > result_type;
		public:
			virtual ~sprite_drawer_filter() {}
			virtual HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) = 0;
			virtual result_type apply(texture_manager_type const& texture_manager) const = 0;
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {}
		};
	}	// namespace dg
}	// namespace sprig

//	COMMENT: íäè€ÉNÉâÉXÇ∆ÇµÇƒìoò^
BOOST_SERIALIZATION_ASSUME_ABSTRACT(sprig::dg::sprite_drawer_filter);

#endif	// #ifndef SPRIG_DG_SPRITE_DRAWER_FILTER_HPP
