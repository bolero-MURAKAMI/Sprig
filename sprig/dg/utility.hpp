#ifndef SPRIG_DG_UTILITY_HPP
#define SPRIG_DG_UTILITY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <map>
#include <boost/foreach.hpp>
#include <sprig/dg/foundation.hpp>

namespace sprig {
	namespace dg {
		//
		// render_state_saver
		//
		class render_state_saver {
		public:
			typedef std::map<D3DRENDERSTATETYPE, DWORD> state_map_type;
		private:
			device_type device_;
			state_map_type state_map_;
		public:
			explicit render_state_saver(device_type device)
				: device_(device)
			{}
			~render_state_saver() {
				BOOST_FOREACH(state_map_type::value_type const& e, state_map_) {
					// レンダリングステートの設定復元
					if (FAILED(device_->SetRenderState(e.first, e.second))) {
						SPRIG_DG_ERROR_MESSAGE("レンダリングステートの設定復元に失敗しました");
						return;
					}
				}
			}
			HRESULT push(D3DRENDERSTATETYPE state) {
				HRESULT result = D3D_OK;

				if (state_map_.find(state) != state_map_.end()) {
					result = S_FALSE;
					return result;
				}

				DWORD value = 0;
				// レンダリングステートの取得
				if (FAILED(result = device_->GetRenderState(state, &value))) {
					SPRIG_DG_ERROR("レンダリングステートの取得に失敗しました", bad_process);
					return result;
				}
				state_map_.insert(state_map_type::value_type(state, value));

				return result;
			}
			HRESULT modify(D3DRENDERSTATETYPE state, DWORD value) {
				HRESULT result = D3D_OK;

				if (FAILED(result = push(state))) {
					return result;
				}

				// レンダリングステートの設定
				if (FAILED(result = device_->SetRenderState(state, value))) {
					SPRIG_DG_ERROR("レンダリングステートの設定に失敗しました", bad_process);
					return result ;
				}

				return result;
			}
		};
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_UTILITY_HPP
