/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_SPRITE_DRAWER_BASE_HPP
#define SPRIG_DG_SPRITE_DRAWER_BASE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/serialization.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/dg/foundation.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_drawer_base
		//
		class sprite_drawer_base {
		public:
			typedef D3DXVECTOR3 coord_type;
		public:
			virtual ~sprite_drawer_base() {}
			virtual HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				return S_FALSE;
			}
			virtual HRESULT begin_draw(sprig::call_traits<sprite_type>::param_type sprite) {
				return S_FALSE;
			}
			virtual HRESULT end_draw(sprig::call_traits<sprite_type>::param_type sprite) {
				return S_FALSE;
			}
			virtual HRESULT draw(sprig::call_traits<sprite_type>::param_type sprite) const {
				return S_FALSE;
			}
			virtual HRESULT begin_hit_test() {
				return S_FALSE;
			}
			virtual HRESULT end_hit_test() {
				return S_FALSE;
			}
			virtual HRESULT hit_test(bool& hit, sprig::call_traits<coord_type>::param_type point) const {
				return S_FALSE;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {}
		};
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_SPRITE_DRAWER_BASE_HPP
