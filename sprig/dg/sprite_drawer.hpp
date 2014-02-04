/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_SPRITE_DRAWER_HPP
#define SPRIG_DG_SPRITE_DRAWER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <memory>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/serialization/windows.hpp>
#include <sprig/serialization/d3dx9.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/utility.hpp>
#include <sprig/dg/value_info.hpp>
#include <sprig/dg/functions.hpp>
#include <sprig/dg/texture_manager.hpp>
#include <sprig/dg/sprite_drawer_base.hpp>
#include <sprig/dg/sprite_drawer_filter_manager.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_drawer
		//
		template<
			typename Key = std::basic_string<char_type>,
			typename Priority = double,
			typename TextureManager = dynamic_texture,
			typename SpriteDrawerFilter = sprite_drawer_filter_manager<Key, Priority>
		>
		class sprite_drawer
			: public sprite_drawer_base
		{
		public:
			typedef TextureManager texture_manager_type;
			typedef SpriteDrawerFilter sprite_drawer_filter_type;
			typedef D3DXVECTOR2 scaling_value_type;
			typedef FLOAT rotation_value_type;
			typedef D3DXVECTOR2 translation_value_type;
			typedef RECT rect_value_type;
			typedef D3DXVECTOR3 center_value_type;
			typedef D3DXVECTOR3 position_value_type;
			typedef D3DCOLOR color_value_type;
			typedef FLOAT scaling_element_value_type;
			typedef FLOAT translation_element_value_type;
			typedef UINT rect_element_value_type;
			typedef FLOAT center_element_value_type;
			typedef FLOAT position_element_value_type;
			typedef boost::optional<scaling_value_type> scaling_type;
			typedef boost::optional<rotation_value_type> rotation_type;
			typedef boost::optional<translation_value_type> translation_type;
			typedef boost::optional<rect_value_type> rect_type;
			typedef boost::optional<center_value_type> center_type;
			typedef boost::optional<position_value_type> position_type;
			typedef boost::optional<color_value_type> color_type;
			typedef boost::optional<scaling_element_value_type> scaling_element_type;
			typedef boost::optional<translation_element_value_type> translation_element_type;
			typedef boost::optional<rect_element_value_type> rect_element_type;
			typedef boost::optional<center_element_value_type> center_element_type;
			typedef boost::optional<position_element_value_type> position_element_type;
			typedef boost::optional<sprig::call_traits<scaling_value_type>::param_type> scaling_param_type;
			typedef boost::optional<sprig::call_traits<rotation_value_type>::param_type> rotation_param_type;
			typedef boost::optional<sprig::call_traits<translation_value_type>::param_type> translation_param_type;
			typedef boost::optional<sprig::call_traits<rect_value_type>::param_type> rect_param_type;
			typedef boost::optional<sprig::call_traits<center_value_type>::param_type> center_param_type;
			typedef boost::optional<sprig::call_traits<position_value_type>::param_type> position_param_type;
			typedef boost::optional<sprig::call_traits<color_value_type>::param_type> color_param_type;
			typedef D3DCOLOR hit_threshold_type;
		public:
			// 描画のためのワーク
			typedef typename sprite_drawer_filter_type::result_type filtered_value_type;
			typedef boost::optional<filtered_value_type> filtered_type;
		public:
			// ヒットテストのためのワーク
			typedef RECT surface_rect_value_type;
			typedef D3DXMATRIX matrix_value_type;
			typedef D3DLOCKED_RECT locked_rect_value_type;
			typedef boost::optional<surface_rect_value_type> surface_rect_type;
			typedef boost::optional<matrix_value_type> matrix_type;
			typedef boost::optional<locked_rect_value_type> locked_rect_type;
		public:
			// ブレンドモード
			enum BLEND_MODE {
				BLEND_MODE_DEFAULT = 1,
				BLEND_MODE_ALPHA = 2,
				BLEND_MODE_ADD_ALPHA = 3,
				BLEND_MODE_ADDITIVE = 4,
				BLEND_MODE_SUBTRACTIVE = 5,
				BLEND_MODE_MULTIPLICATIVE = 6,
				BLEND_MODE_LIGHTEN = 7,
				BLEND_MODE_DARKEN = 8,
				BLEND_MODE_SCREEN = 9
			};
			// ヒットテストモード
			enum HIT_TEST_MODE {
				HIT_TEST_MODE_NONE = 1,
				HIT_TEST_MODE_RECT = 2,
				HIT_TEST_MODE_COLOR = 3
			};
		public:
			template<typename T>
			static HIT_TEST_MODE to_hit_test_mode(T value) {
				switch (value) {
				case HIT_TEST_MODE_NONE:
					return HIT_TEST_MODE_NONE;
				case HIT_TEST_MODE_RECT:
					return HIT_TEST_MODE_RECT;
				case HIT_TEST_MODE_COLOR:
					return HIT_TEST_MODE_COLOR;
				default:
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("value"), value);
					SPRIG_DG_ERROR("値からヒットテストモードへの変換に失敗しました", bad_operation);
					return HIT_TEST_MODE();
				}
			}
			template<typename T>
			static BLEND_MODE to_blend_mode(T value) {
				switch (value) {
				case BLEND_MODE_DEFAULT:
					return BLEND_MODE_DEFAULT;
				case BLEND_MODE_ALPHA:
					return BLEND_MODE_ALPHA;
				case BLEND_MODE_ADD_ALPHA:
					return BLEND_MODE_ADD_ALPHA;
				case BLEND_MODE_ADDITIVE:
					return BLEND_MODE_ADDITIVE;
				case BLEND_MODE_SUBTRACTIVE:
					return BLEND_MODE_SUBTRACTIVE;
				case BLEND_MODE_MULTIPLICATIVE:
					return BLEND_MODE_MULTIPLICATIVE;
				case BLEND_MODE_LIGHTEN:
					return BLEND_MODE_LIGHTEN;
				case BLEND_MODE_DARKEN:
					return BLEND_MODE_DARKEN;
				case BLEND_MODE_SCREEN:
					return BLEND_MODE_SCREEN;
				default:
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("value"), value);
					SPRIG_DG_ERROR("値からブレンドモードへの変換に失敗しました", bad_operation);
					return BLEND_MODE();
				}
			}
		private:
			bool visible_;
			texture_manager_type texture_manager_;
			scaling_type scaling_;
			rotation_type rotation_;
			translation_type translation_;
			rect_type rect_;
			center_type center_;
			position_type position_;
			color_type color_;
			sprite_drawer_filter_type sprite_drawer_filter_;
			BLEND_MODE blend_mode_;
			HIT_TEST_MODE hit_test_mode_;
			hit_threshold_type hit_threshold_;
		private:
			// 描画のためのワーク
			filtered_type filtered_;
		private:
			// ヒットテストのためのワーク
			surface_rect_type surface_rect_;
			matrix_type matrix_;
			locked_rect_type locked_rect_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("visible_"), visible_, logger);
				value_info_section_line(TEXT("texture_manager_"), texture_manager_, logger);
				value_info_section_line(TEXT("scaling_"), scaling_, logger);
				value_info_section_line(TEXT("rotation_"), rotation_, logger);
				value_info_section_line(TEXT("translation_"), translation_, logger);
				value_info_section_line(TEXT("rect_"), rect_, logger);
				value_info_section_line(TEXT("center_"), center_, logger);
				value_info_section_line(TEXT("position_"), position_, logger);
				value_info_section_line(TEXT("color_"), color_, logger);
				value_info_section_line(TEXT("sprite_drawer_filter_"), sprite_drawer_filter_, logger);
				value_info_section_line(TEXT("blend_mode_"), blend_mode_, logger);
				value_info_section_line(TEXT("hit_test_mode_"), hit_test_mode_, logger);
				value_info_section_line(TEXT("hit_threshold_"), hit_threshold_, logger);
				// 描画のためのワーク
				value_info_section_line(TEXT("filtered_"), filtered_, logger);
				// ヒットテストのためのワーク
				value_info_section_line(TEXT("surface_rect_"), surface_rect_, logger);
				value_info_section_line(TEXT("matrix_"), matrix_, logger);
				value_info_section_line(TEXT("locked_rect_"), locked_rect_, logger);
			}
		public:
			sprite_drawer()
				: visible_(false)
				, blend_mode_(BLEND_MODE_DEFAULT)
				, hit_test_mode_(HIT_TEST_MODE_NONE)
				, hit_threshold_(D3DCOLOR_ARGB(0x10, 0x00, 0x00, 0x00))
			{}
			HRESULT initialize(
				sprig::call_traits<device_type>::param_type device,
				sprig::call_traits<texture_manager_init_params>::param_type params
				)
			{
				SPRIG_DG_SECTION(TEXT("sprite_drawer::initialize"));
				HRESULT result = D3D_OK;

				if (FAILED(result = texture_manager_.initialize(device, params))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				SPRIG_DG_SECTION(TEXT("sprite_drawer::reinitialize"));
				HRESULT result = D3D_OK;

				if (FAILED(result = texture_manager_.reinitialize(device))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("テクスチャマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}
				if (FAILED(result = sprite_drawer_filter_.reinitialize(device))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("フィルタの初期化に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			HRESULT begin_draw(sprig::call_traits<sprite_type>::param_type sprite) {
				HRESULT result = D3D_OK;

				if (!visible_) {
					result = S_FALSE;
					return result;
				}

				// フィルタの適用
				filtered_value_type filtered(sprite_drawer_filter_.apply(texture_manager_));
				if (FAILED(result = filtered.first)) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("フィルタの適用に失敗しました", bad_process);
					return result;
				}

				filtered_.reset(filtered);

				return result;
			}
			HRESULT end_draw(sprig::call_traits<sprite_type>::param_type sprite) {
				HRESULT result = D3D_OK;

				if (!visible_) {
					result = S_FALSE;
					return result;
				}

				filtered_.reset();

				return result;
			}
			HRESULT draw(sprig::call_traits<sprite_type>::param_type sprite) const {
				HRESULT result = D3D_OK;

				if (!visible_) {
					result = S_FALSE;
					return result;
				}

				// フィルタ結果が有効かチェック
				if (!filtered_->second) {
					return result;
				}

				// 座標変換行列の設定
				if (FAILED(result = set_sprite_transform(
					sprite,
					scaling_param_type(scaling_),
					rotation_param_type(rotation_),
					translation_param_type(translation_)
					)))
				{
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("座標変換行列の設定に失敗しました", bad_process);
					return result;
				}

				if (blend_mode_ != BLEND_MODE_DEFAULT) {
					// スプライトフラッシュ
					if (FAILED(result = sprite->Flush())) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトフラッシュに失敗しました", bad_process);
						return result;
					}
				}

				device_type device;
				sprite->GetDevice(sprig::accept(device));
				render_state_saver saver(device);

				switch (blend_mode_) {
				case BLEND_MODE_ALPHA:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					break;
				case BLEND_MODE_ADD_ALPHA:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_ONE);
					break;
				case BLEND_MODE_ADDITIVE:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_ONE);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_ONE);
					break;
				case BLEND_MODE_SUBTRACTIVE:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_ZERO);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
					break;
				case BLEND_MODE_MULTIPLICATIVE:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_ZERO);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
					break;
				case BLEND_MODE_LIGHTEN:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_MAX);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_ONE);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_ONE);
					break;
				case BLEND_MODE_DARKEN:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_MIN);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_ONE);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_ONE);
					break;
				case BLEND_MODE_SCREEN:
					// ブレンディングの設定
					saver.modify(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					saver.modify(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
					saver.modify(D3DRS_DESTBLEND, D3DBLEND_ONE);
					break;
				}

				// スプライト描画
				if (FAILED(result = draw_sprite(
					sprite,
					filtered_->second->get_texture(),
					rect_param_type(rect_),
					center_param_type(center_),
					position_param_type(position_),
					color_param_type(color_)
					)))
				{
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライト描画に失敗しました", bad_process);
					return result;
				}

				if (blend_mode_ != BLEND_MODE_DEFAULT) {
					// スプライトフラッシュ
					if (FAILED(result = sprite->Flush())) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトフラッシュに失敗しました", bad_process);
						return result;
					}
				}

				return result;
			}
			HRESULT begin_hit_test() {
				HRESULT result = D3D_OK;

				if (!visible_) {
					result = S_FALSE;
					return result;
				}

				surface_rect_value_type surface_rect;
				switch (hit_test_mode_) {
				case HIT_TEST_MODE_RECT:
				case HIT_TEST_MODE_COLOR:
					{
						// サーフェイスの有効領域に収まるよう補正した矩形
						if (rect_) {
							if (FAILED(result = normalize_surface_rect(
								surface_rect,
								texture_manager_.get_surface(),
								*rect_,
								texture_manager_.get_surface_desc()
								)))
							{
								SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
								SPRIG_DG_ERROR("サーフェイスの有効領域矩形の計算に失敗しました", bad_process);
								return result;
							}
						} else {
							surface_rect = make_rect(
								0,
								0,
								texture_manager_.get_surface_desc().Width,
								texture_manager_.get_surface_desc().Height
								);
						}
					}
					break;
				}

				matrix_value_type matrix;
				switch (hit_test_mode_) {
				case HIT_TEST_MODE_RECT:
				case HIT_TEST_MODE_COLOR:
					{
						// 座標逆変換行列の作成
						matrix_inverse_transformation_2d(
							matrix,
							scaling_param_type(scaling_),
							rotation_param_type(rotation_),
							translation_param_type(translation_)
							);
					}
					break;
				}

				locked_rect_value_type locked_rect;
				switch (hit_test_mode_) {
				case HIT_TEST_MODE_COLOR:
					{
						// サーフェイスのロック
						if (FAILED(result = lock_rect(
							locked_rect,
							texture_manager_.get_surface(),
							D3DLOCK_READONLY,
							rect_param_type(rect_),
							texture_manager_.get_surface_desc()
							)))
						{
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
							SPRIG_DG_ERROR("サーフェイスのロックに失敗しました", bad_process);
							return result;
						}
					}
					break;
				}

				surface_rect_.reset(surface_rect);
				matrix_.reset(matrix);
				locked_rect_.reset(locked_rect);

				return result;
			}
			HRESULT end_hit_test() {
				HRESULT result = D3D_OK;

				if (!visible_) {
					result = S_FALSE;
					return result;
				}

				surface_rect_.reset();
				matrix_.reset();
				locked_rect_.reset();

				switch (hit_test_mode_) {
				case HIT_TEST_MODE_COLOR:
					{
						// サーフェイスのアンロック
						if (FAILED(result = unlock_rect(
							texture_manager_.get_surface()
							)))
						{
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
							SPRIG_DG_ERROR("サーフェイスのアンロックに失敗しました", bad_process);
							return result;
						}
					}
					break;
				}

				return result;
			}
			HRESULT hit_test(bool& hit, typename sprig::call_traits<coord_type>::param_type point) const {
				HRESULT result = D3D_OK;

				if (!visible_) {
					hit = false;

					result = S_FALSE;
					return result;
				}

				switch (hit_test_mode_) {
				case HIT_TEST_MODE_RECT:
					{
						// サーフェイス座標におけるヒットテスト点
						coord_type hit_test_point;
						vec3_transformation_coord(hit_test_point, point, *matrix_);
						if (center_) {
							hit_test_point += *center_;
						}

						// ヒットテスト点
						POINT const surface_point = make_point(
							static_cast<LONG>(hit_test_point.x),
							static_cast<LONG>(hit_test_point.y)
							);

						// ヒットテスト点が矩形内にあるかチェック
						if (surface_point.x < surface_rect_->left
							|| surface_point.x > surface_rect_->right
							|| surface_point.y < surface_rect_->top
							|| surface_point.y > surface_rect_->bottom
							)
						{
							hit = false;
							return result;
						}
					}
					break;
				case HIT_TEST_MODE_COLOR:
					{
						// サーフェイス座標におけるヒットテスト点
						coord_type hit_test_point;
						vec3_transformation_coord(hit_test_point, point, *matrix_);
						if (center_) {
							hit_test_point += *center_;
						}

						// ヒットテスト点
						POINT const surface_point = make_point(
							static_cast<LONG>(hit_test_point.x),
							static_cast<LONG>(hit_test_point.y)
							);

						// ヒットテスト点が矩形内にあるかチェック
						if (surface_point.x < surface_rect_->left
							|| surface_point.x > surface_rect_->right
							|| surface_point.y < surface_rect_->top
							|| surface_point.y > surface_rect_->bottom
							)
						{
							hit = false;
							return result;
						}

						// ヒットテスト点のカラー値が閾値以上かチェック
						D3DCOLOR const color = get_pixel(*locked_rect_, surface_point);
						if ((color >> 24 & 0xff) < (hit_threshold_ >> 24 & 0xff)
							|| (color >> 16 & 0xff) < (hit_threshold_ >> 16 & 0xff)
							|| (color >> 8 & 0xff) < (hit_threshold_ >> 8 & 0xff)
							|| (color & 0xff) < (hit_threshold_ & 0xff)
							)
						{
							hit = false;
							return result;
						}
					}
					break;
				default:
					{
						hit = false;
						return result;
					}
					break;
				}

				hit = true;
				return result;
			}
			coord_type to_local_coord(typename sprig::call_traits<coord_type>::param_type global) const {
				// 座標変換行列の作成
				matrix_value_type matrix;
				matrix_transformation_2d(
					matrix,
					scaling_param_type(scaling_),
					rotation_param_type(rotation_),
					translation_param_type(translation_)
					);

				// ローカル座標へ変換
				coord_type local;
				vec3_transformation_coord(local, global, matrix);

				return local;
			}
			coord_type to_global_coord(typename sprig::call_traits<coord_type>::param_type local) const {
				// 座標逆変換行列の作成
				matrix_value_type matrix;
				matrix_inverse_transformation_2d(
					matrix,
					scaling_param_type(scaling_),
					rotation_param_type(rotation_),
					translation_param_type(translation_)
					);

				// グローバル座標へ変換
				coord_type global;
				vec3_transformation_coord(global, local, matrix);

				return local;
			}
			bool is_initialized() const {
				return texture_manager_.is_initialized();
			}
			typename sprig::call_traits<texture_type>::getter_type get_texture() const {
				return texture_manager_.get_texture();
			}
			typename sprig::call_traits<surface_type>::getter_type get_surface() const {
				return texture_manager_.get_surface();
			}
			typename sprig::call_traits<D3DSURFACE_DESC>::getter_type get_surface_desc() const {
				return texture_manager_.get_surface_desc();
			}
			sprig::call_traits<bool>::getter_type get_visible() const {
				return visible_;
			}
			void set_visible(sprig::call_traits<bool>::param_type v) {
				visible_ = v;
			}
			texture_manager_type& ref_texture_manager() {
				return texture_manager_;
			}
			typename sprig::call_traits<texture_manager_type>::getter_type get_texture_manager() const {
				return texture_manager_;
			}
			sprig::call_traits<scaling_type>::getter_type get_scaling() const {
				return scaling_;
			}
			void set_scaling(sprig::call_traits<scaling_type>::param_type v) {
				scaling_ = v;
			}
			scaling_element_type get_scaling_x() const {
				return scaling_ ? scaling_element_type(scaling_->x) : scaling_element_type();
			}
			scaling_element_type get_scaling_y() const {
				return scaling_ ? scaling_element_type(scaling_->y) : scaling_element_type();
			}
			void set_scaling_x(sprig::call_traits<scaling_element_value_type>::param_type v) {
				if (!scaling_) {
					scaling_ = scaling_value_type();
				}
				scaling_->x = v;
			}
			void set_scaling_y(sprig::call_traits<scaling_element_value_type>::param_type v) {
				if (!scaling_) {
					scaling_ = scaling_value_type();
				}
				scaling_->y = v;
			}
			sprig::call_traits<rotation_type>::getter_type get_rotation() const {
				return rotation_;
			}
			void set_rotation(sprig::call_traits<rotation_type>::param_type v) {
				rotation_ = v;
			}
			sprig::call_traits<translation_type>::getter_type get_translation() const {
				return translation_;
			}
			void set_translation(sprig::call_traits<translation_type>::param_type v) {
				translation_ = v;
			}
			translation_element_type get_translation_x() const {
				return translation_ ? translation_element_type(translation_->x) : translation_element_type();
			}
			translation_element_type get_translation_y() const {
				return translation_ ? translation_element_type(translation_->y) : translation_element_type();
			}
			void set_translation_x(sprig::call_traits<translation_element_value_type>::param_type v) {
				if (!translation_) {
					translation_ = translation_value_type();
				}
				translation_->x = v;
			}
			void set_translation_y(sprig::call_traits<translation_element_value_type>::param_type v) {
				if (!translation_) {
					translation_ = translation_value_type();
				}
				translation_->y = v;
			}
			sprig::call_traits<rect_type>::getter_type get_rect() const {
				return rect_;
			}
			void set_rect(sprig::call_traits<rect_type>::param_type v) {
				rect_ = v;
			}
			rect_element_type get_rect_left() const {
				return rect_ ? rect_element_type(rect_->left) : rect_element_type();
			}
			rect_element_type get_rect_top() const {
				return rect_ ? rect_element_type(rect_->top) : rect_element_type();
			}
			rect_element_type get_rect_right() const {
				return rect_ ? rect_element_type(rect_->right) : rect_element_type();
			}
			rect_element_type get_rect_bottom() const {
				return rect_ ? rect_element_type(rect_->bottom) : rect_element_type();
			}
			void set_rect_left(sprig::call_traits<rect_element_value_type>::param_type v) {
				if (!rect_) {
					rect_ = make_rect();
				}
				rect_->left = v;
			}
			void set_rect_top(sprig::call_traits<rect_element_value_type>::param_type v) {
				if (!rect_) {
					rect_ = make_rect();
				}
				rect_->top = v;
			}
			void set_rect_right(sprig::call_traits<rect_element_value_type>::param_type v) {
				if (!rect_) {
					rect_ = make_rect();
				}
				rect_->right = v;
			}
			void set_rect_bottom(sprig::call_traits<rect_element_value_type>::param_type v) {
				if (!rect_) {
					rect_ = make_rect();
				}
				rect_->bottom = v;
			}
			sprig::call_traits<center_type>::getter_type get_center() const {
				return center_;
			}
			void set_center(sprig::call_traits<center_type>::param_type v) {
				center_ = v;
			}
			center_element_type get_center_x() const {
				return center_ ? center_element_type(center_->x) : center_element_type();
			}
			center_element_type get_center_y() const {
				return center_ ? center_element_type(center_->y) : center_element_type();
			}
			center_element_type get_center_z() const {
				return center_ ? center_element_type(center_->z) : center_element_type();
			}
			void set_center_x(sprig::call_traits<center_element_value_type>::param_type v) {
				if (!center_) {
					center_ = center_value_type();
				}
				center_->x = v;
			}
			void set_center_y(sprig::call_traits<center_element_value_type>::param_type v) {
				if (!center_) {
					center_ = center_value_type();
				}
				center_->y = v;
			}
			void set_center_z(sprig::call_traits<center_element_value_type>::param_type v) {
				if (!center_) {
					center_ = center_value_type();
				}
				center_->z = v;
			}
			sprig::call_traits<position_type>::getter_type get_position() const {
				return position_;
			}
			void set_position(sprig::call_traits<position_type>::param_type v) {
				position_ = v;
			}
			position_element_type get_position_x() const {
				return position_ ? position_element_type(position_->x) : position_element_type();
			}
			position_element_type get_position_y() const {
				return position_ ? position_element_type(position_->y) : position_element_type();
			}
			position_element_type get_position_z() const {
				return position_ ? position_element_type(position_->z) : position_element_type();
			}
			void set_position_x(sprig::call_traits<position_element_value_type>::param_type v) {
				if (!position_) {
					position_ = position_value_type();
				}
				position_->x = v;
			}
			void set_position_y(sprig::call_traits<position_element_value_type>::param_type v) {
				if (!position_) {
					position_ = position_value_type();
				}
				position_->y = v;
			}
			void set_position_z(sprig::call_traits<position_element_value_type>::param_type v) {
				if (!position_) {
					position_ = position_value_type();
				}
				position_->z = v;
			}
			sprig::call_traits<color_type>::getter_type get_color() const {
				return color_;
			}
			void set_color(sprig::call_traits<color_type>::param_type v) {
				color_ = v;
			}
			sprite_drawer_filter_type& ref_filter_manager() {
				return sprite_drawer_filter_;
			}
			typename sprig::call_traits<sprite_drawer_filter_type>::getter_type get_filter_manager() const {
				return sprite_drawer_filter_;
			}
			BLEND_MODE get_blend_mode() const {
				return blend_mode_;
			}
			void set_blend_mode(BLEND_MODE const v) {
				blend_mode_ = v;
			}
			HIT_TEST_MODE get_hit_test_mode() const {
				return hit_test_mode_;
			}
			void set_hit_test_mode(HIT_TEST_MODE const v) {
				hit_test_mode_ = v;
			}
			sprig::call_traits<hit_threshold_type>::getter_type get_hit_threshold() const {
				return hit_threshold_;
			}
			void set_hit_threshold(sprig::call_traits<hit_threshold_type>::param_type v) {
				hit_threshold_ = v;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("sprite_drawer_base", boost::serialization::base_object<sprite_drawer_base>(*this))
					& boost::serialization::make_nvp("visible_", visible_)
					& boost::serialization::make_nvp("texture_manager_", texture_manager_)
					& boost::serialization::make_nvp("scaling_", scaling_)
					& boost::serialization::make_nvp("rotation_", rotation_)
					& boost::serialization::make_nvp("translation_", translation_)
					& boost::serialization::make_nvp("rect_", rect_)
					& boost::serialization::make_nvp("center_", center_)
					& boost::serialization::make_nvp("position_", position_)
					& boost::serialization::make_nvp("color_", color_)
					& boost::serialization::make_nvp("sprite_drawer_filter_", sprite_drawer_filter_)
					& boost::serialization::make_nvp("blend_mode_", blend_mode_)
					& boost::serialization::make_nvp("hit_test_mode_", hit_test_mode_)
					& boost::serialization::make_nvp("hit_threshold_", hit_threshold_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 5, sprite_drawer);
		template<typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename TextureManager, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer<Key, Priority, TextureManager> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename TextureManager, typename SpriteDrawerFilter, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer<Key, Priority, TextureManager, SpriteDrawerFilter> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_SPRITE_DRAWER_HPP
