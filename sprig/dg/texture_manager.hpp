/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_TEXTURE_MANAGER_HPP
#define SPRIG_DG_TEXTURE_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/get_pointer.hpp>
#include <sprig/accept.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>

namespace sprig {
	namespace dg {
		//
		// texture_parameters
		//
		class texture_parameters {
		public:
			typedef UINT size_type;
			typedef DWORD usage_type;
			typedef D3DFORMAT format_type;
			typedef D3DPOOL pool_type;
		public:
			size_type width;
			size_type height;
			size_type levels;
			usage_type usage;
			format_type format;
			pool_type pool;
		public:
			texture_parameters(
				size_type width = 0,
				size_type height = 0,
				size_type levels = 1,
				usage_type usage = 0,
				format_type format = D3DFMT_A8R8G8B8,
				pool_type pool = D3DPOOL_DEFAULT
				)
				: width(width)
				, height(height)
				, levels(levels)
				, usage(usage)
				, format(format)
				, pool(pool)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("width", width)
					& boost::serialization::make_nvp("height", height)
					& boost::serialization::make_nvp("levels", levels)
					& boost::serialization::make_nvp("usage", usage)
					& boost::serialization::make_nvp("format", format)
					& boost::serialization::make_nvp("pool", pool)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(texture_parameters);
		template<typename Logger>
		void value_info(texture_parameters const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("width"), value.width);
			logger.section_line(TEXT("height"), value.height);
			logger.section_line(TEXT("levels"), value.levels);
			logger.section_line(TEXT("usage"), value.usage);
			logger.section_line(TEXT("format"), value.format);
			logger.section_line(TEXT("pool"), value.pool);
		}

		//
		// texture_manager_init_params
		//
		class texture_manager_init_params {
		public:
			typedef texture_parameters::size_type size_type;
			typedef texture_parameters::format_type format_type;
		public:
			size_type width;
			size_type height;
			format_type format;
		public:
			texture_manager_init_params(
				size_type width = 0,
				size_type height = 0,
				format_type format = D3DFMT_A8R8G8B8
				)
				: width(width)
				, height(height)
				, format(format)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("width", width)
					& boost::serialization::make_nvp("height", height)
					& boost::serialization::make_nvp("format", format)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(texture_manager_init_params);
		template<typename Logger>
		void value_info(texture_manager_init_params const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("width"), value.width);
			logger.section_line(TEXT("height"), value.height);
			logger.section_line(TEXT("format"), value.format);
		}

		//
		// texture_manager_base
		//
		class texture_manager_base {
		public:
			virtual ~texture_manager_base() {}
			virtual HRESULT initialize(
				sprig::call_traits<device_type>::param_type device,
				sprig::call_traits<texture_manager_init_params>::param_type params
				) = 0;
			virtual HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) = 0;
			virtual bool is_initialized() const = 0;
			virtual sprig::call_traits<device_type>::getter_type get_device() const = 0;
			virtual sprig::call_traits<texture_manager_init_params>::getter_type get_texture_manager_init_params() const = 0;
			virtual sprig::call_traits<texture_parameters>::getter_type get_texture_parameters() const = 0;
			virtual sprig::call_traits<texture_type>::getter_type get_texture() const = 0;
			virtual sprig::call_traits<surface_type>::getter_type get_surface() const = 0;
			virtual sprig::call_traits<D3DSURFACE_DESC>::getter_type get_surface_desc() const = 0;
		};

		//
		// texture_manager_impl
		//
		class texture_manager_impl
			: public texture_manager_base
		{
		private:
			device_type device_;
			texture_manager_init_params texture_manager_init_params_;
			texture_parameters texture_parameters_;
			texture_type texture_;
			surface_type surface_;
			D3DSURFACE_DESC surface_desc_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("device_"), device_, logger);
				value_info_section_line(TEXT("texture_manager_init_params_"), texture_manager_init_params_, logger);
				value_info_section_line(TEXT("texture_parameters_"), texture_parameters_, logger);
				value_info_section_line(TEXT("texture_"), texture_, logger);
				value_info_section_line(TEXT("surface_"), surface_, logger);
				value_info_section_line(TEXT("surface_desc_"), surface_desc_, logger);
			}
		protected:
			~texture_manager_impl() {}
		public:
			texture_manager_impl(
				texture_parameters::size_type width = 0,
				texture_parameters::size_type height = 0,
				texture_parameters::size_type levels = 1,
				texture_parameters::usage_type usage = 0,
				texture_parameters::format_type format = D3DFMT_A8R8G8B8,
				texture_parameters::pool_type pool = D3DPOOL_DEFAULT
				)
				: texture_parameters_(width, height, levels, usage, format, pool)
			{}
			HRESULT initialize(
				sprig::call_traits<device_type>::param_type device,
				sprig::call_traits<texture_manager_init_params>::param_type params
				)
			{
				SPRIG_DG_SECTION(TEXT("texture_manager_impl::initialize"));
				HRESULT result = D3D_OK;

				texture_manager_init_params_ = params;

				device_ = device;
				texture_parameters_.width = texture_manager_init_params_.width;
				texture_parameters_.height = texture_manager_init_params_.height;
				texture_parameters_.format = texture_manager_init_params_.format;
				if (FAILED(result = device_->CreateTexture(
					texture_parameters_.width,	// テクスチャサイズ
					texture_parameters_.height,	// テクスチャサイズ
					texture_parameters_.levels,	// ミップレベル数
					texture_parameters_.usage,	// テクスチャの用途
					texture_parameters_.format,	// テクスチャ形式
					texture_parameters_.pool,	// メモリクラス
					sprig::accept(texture_),
					NULL	// 予約
					)))
				{
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャ生成に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = texture_->GetSurfaceLevel(0, sprig::accept(surface_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャからサーフェイス取得に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = surface_->GetDesc(&surface_desc_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("サーフェイス情報の取得に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				SPRIG_DG_SECTION(TEXT("texture_manager_impl::reinitialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				texture_parameters_.width = texture_manager_init_params_.width;
				texture_parameters_.height = texture_manager_init_params_.height;
				texture_parameters_.format = texture_manager_init_params_.format;
				if (FAILED(result = device_->CreateTexture(
					texture_parameters_.width,	// テクスチャサイズ
					texture_parameters_.height,	// テクスチャサイズ
					texture_parameters_.levels,	// ミップレベル数
					texture_parameters_.usage,	// テクスチャの用途
					texture_parameters_.format,	// テクスチャ形式
					texture_parameters_.pool,	// メモリクラス
					sprig::accept(texture_),
					NULL	// 予約
					)))
				{
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャ生成に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = texture_->GetSurfaceLevel(0, sprig::accept(surface_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャからサーフェイス取得に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = surface_->GetDesc(&surface_desc_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("サーフェイス情報の取得に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			bool is_initialized() const {
				return device_;
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_;
			}
			sprig::call_traits<texture_manager_init_params>::getter_type get_texture_manager_init_params() const {
				return texture_manager_init_params_;
			}
			sprig::call_traits<texture_parameters>::getter_type get_texture_parameters() const {
				return texture_parameters_;
			}
			sprig::call_traits<texture_type>::getter_type get_texture() const {
				return texture_;
			}
			sprig::call_traits<surface_type>::getter_type get_surface() const {
				return surface_;
			}
			sprig::call_traits<D3DSURFACE_DESC>::getter_type get_surface_desc() const {
				return surface_desc_;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("texture_manager_init_params_", texture_manager_init_params_)
					& boost::serialization::make_nvp("texture_parameters_", texture_parameters_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(texture_manager_impl);
		template<typename Logger>
		SPRIG_INLINE void value_info(texture_manager_impl const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}

		//
		// render_target
		//
		class render_target : public texture_manager_impl {
		public:
			render_target(
				texture_parameters::size_type width = 0,
				texture_parameters::size_type height = 0,
				texture_parameters::format_type format = D3DFMT_A8R8G8B8
				)
				: texture_manager_impl(width, height, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("texture_manager_impl", boost::serialization::base_object<texture_manager_impl>(*this))
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(render_target);
		template<typename Logger>
		SPRIG_INLINE void value_info(render_target const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}

		//
		// transfer_work
		//
		class transfer_work : public texture_manager_impl {
		public:
			transfer_work(
				texture_parameters::size_type width = 0,
				texture_parameters::size_type height = 0,
				texture_parameters::format_type format = D3DFMT_A8R8G8B8
				)
				: texture_manager_impl(width, height, 1, 0, format, D3DPOOL_SYSTEMMEM)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("texture_manager_impl", boost::serialization::base_object<texture_manager_impl>(*this))
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(transfer_work);
		template<typename Logger>
		SPRIG_INLINE void value_info(transfer_work const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}

		//
		// dynamic_texture
		//
		class dynamic_texture : public texture_manager_impl {
		public:
			dynamic_texture(
				texture_parameters::size_type width = 0,
				texture_parameters::size_type height = 0,
				texture_parameters::format_type format = D3DFMT_A8R8G8B8
				)
				: texture_manager_impl(width, height, 1, D3DUSAGE_DYNAMIC, format, D3DPOOL_DEFAULT)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("texture_manager_impl", boost::serialization::base_object<texture_manager_impl>(*this))
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(dynamic_texture);
		template<typename Logger>
		SPRIG_INLINE void value_info(dynamic_texture const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

//	COMMENT: 抽象クラスとして登録
BOOST_SERIALIZATION_ASSUME_ABSTRACT(sprig::dg::texture_manager_base);

#endif	// #ifndef SPRIG_DG_TEXTURE_MANAGER_HPP
