/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_RENDER_TRANSFERER_HPP
#define SPRIG_DG_RENDER_TRANSFERER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/get_pointer.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>
#include <sprig/dg/functions.hpp>
#include <sprig/dg/texture_manager.hpp>
#include <sprig/dg/render_filter_manager.hpp>

namespace sprig {
	namespace dg {
		//
		// render_transferer
		//
		template<
			typename Key = std::basic_string<char_type>,
			typename Priority = double,
			typename RenderFilter = render_filter_manager<Key, Priority>
		>
		class render_transferer {
		public:
			typedef RenderFilter render_filter_type;
			typedef render_target render_target_type;
			typedef transfer_work transfer_work_type;
		private:
			device_type device_;
			render_target_type render_target_;
			transfer_work_type transfer_work_;
			render_filter_type render_filter_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("device_"), device_, logger);
				value_info_section_line(TEXT("render_target_"), render_target_, logger);
				value_info_section_line(TEXT("transfer_work_"), transfer_work_, logger);
				value_info_section_line(TEXT("render_filter_"), render_filter_, logger);
			}
		public:
			render_transferer(
				texture_parameters::size_type width = 0,
				texture_parameters::size_type height = 0,
				texture_parameters::format_type format = D3DFMT_A8R8G8B8
				)
				: render_target_(width, height, format)
				, transfer_work_(width, height, format)
			{}
			HRESULT initialize(
				sprig::call_traits<device_type>::param_type device,
				sprig::call_traits<texture_manager_init_params>::param_type params
				)
			{
				SPRIG_DG_SECTION(TEXT("render_transferer::initialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				if (FAILED(result = render_target_.initialize(device_, params))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダーターゲットの初期化に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = transfer_work_.initialize(device_, params))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("転送ワークの初期化に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				SPRIG_DG_SECTION(TEXT("render_transferer::reinitialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				if (FAILED(result = render_target_.reinitialize(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダーターゲットの初期化に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = transfer_work_.reinitialize(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("転送ワークの初期化に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = render_filter_.reinitialize(device))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("フィルタの初期化に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			bool is_initialized() const {
				return device_;
			}
			HRESULT transfer(
				sprig::call_traits<void*>::param_type bits,
				sprig::call_traits<SIZE>::param_type size,
				sprig::call_traits<std::size_t>::param_type pitch,
				sprig::call_traits<std::size_t>::param_type pixel_size,
				sprig::call_traits<POINT>::param_type offset,
				sprig::call_traits<RECT>::param_type rect
				) const
			{
				HRESULT result = D3D_OK;
				//	TODO: フィルタを適用していないので、適用するように書き換える。
				if (FAILED(result = transfer_from_render_target(
					device_,
					render_target_.get_surface(),
					transfer_work_.get_surface(),
					bits,
					size,
					pitch,
					pixel_size,
					offset,
					rect,
					transfer_work_.get_surface_desc()
					)))
				{
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					return result;
				}
				return result;
			}
			HRESULT set_render_target(DWORD render_target_index = 0) const {
				using sprig::get_pointer;

				HRESULT result = D3D_OK;
				if (FAILED(device_->SetRenderTarget(render_target_index, get_pointer(render_target_.get_surface())))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダーターゲットの設定に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_;
			}
			render_target& ref_render_target() {
				return render_target_;
			}
			sprig::call_traits<render_target>::getter_type get_render_target() const {
				return render_target_;
			}
			transfer_work& ref_transfer_work() {
				return transfer_work_;
			}
			sprig::call_traits<transfer_work>::getter_type get_transfer_work() const {
				return transfer_work_;
			}
			render_filter_type& ref_filter_manager() {
				return render_filter_;
			}
			typename sprig::call_traits<render_filter_type>::getter_type get_filter_manager() const {
				return render_filter_;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("render_target_", render_target_)
					& boost::serialization::make_nvp("transfer_work_", transfer_work_)
					& boost::serialization::make_nvp("render_filter_", render_filter_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 4, render_transferer);
		template<typename Logger>
		SPRIG_INLINE void value_info(render_transferer<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(render_transferer<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(render_transferer<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename RenderFilter, typename Logger>
		SPRIG_INLINE void value_info(render_transferer<Key, Priority, RenderFilter> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_RENDER_TRANSFERER_HPP
