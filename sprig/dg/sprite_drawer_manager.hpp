/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_SPRITE_DRAWER_MANAGER_HPP
#define SPRIG_DG_SPRITE_DRAWER_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <sprig/serialization/sprig/priority_map.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/accept.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>
#include <sprig/dg/functions.hpp>
#include <sprig/dg/texture_manager.hpp>
#include <sprig/dg/sprite_drawer_base.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_drawer_manager
		//
		template<
			typename Key = std::basic_string<char_type>,
			typename Priority = double
		>
		class sprite_drawer_manager {
		public:
			typedef boost::shared_ptr<sprite_drawer_base> instance_type;
			typedef priority_map_defs<Key, Priority, instance_type> priority_map_defs_type;
			typedef typename priority_map_defs_type::key_type key_type;
			typedef typename priority_map_defs_type::priority_type priority_type;
			typedef typename priority_map_defs_type::mapped_type mapped_type;
			typedef typename priority_map_defs_type::value_type value_type;
			typedef typename priority_map_defs_type::key_comparator_type key_comparator_type;
			typedef typename priority_map_defs_type::comparator_type comparator_type;
			typedef typename priority_map_defs_type::key_tag_type key_tag_type;
			typedef typename priority_map_defs_type::priority_tag_type priority_tag_type;
			typedef typename priority_map_defs_type::type priority_map_type;
			typedef typename priority_map_type::template index<typename priority_map_defs_type::key_tag_type>::type key_index_type;
			typedef typename priority_map_type::template index<typename priority_map_defs_type::priority_tag_type>::type priority_index_type;
			typedef std::pair<typename priority_map_type::iterator, bool> insert_result_type;
			typedef DWORD flag_type;
			typedef sprite_drawer_base::coord_type coord_type;
		private:
			device_type device_;
			sprite_type sprite_;
			priority_map_type priority_map_;
			flag_type flag_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("device_"), device_, logger);
				value_info_section_line(TEXT("sprite_"), sprite_, logger);
				value_info_section_line(TEXT("priority_map_"), priority_map_, logger);
				value_info_section_line(TEXT("flag_"), flag_, logger);
			}
			void output_members_value_info() const {
				SPRIG_DG_SECTION(TEXT("members"));
				SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("device_"), device_);
				SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("sprite_"), sprite_);
				SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("priority_map_"), priority_map_);
				SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("flag_"), flag_);
			}
		public:
			sprite_drawer_manager()
				: flag_(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT)
			{}
			HRESULT initialize(sprig::call_traits<device_type>::param_type device)
			{
				using sprig::get_pointer;
				SPRIG_DG_SECTION(TEXT("sprite_drawer_manager::initialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				if (FAILED(result = D3DXCreateSprite(get_pointer(device_), sprig::accept(sprite_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトの作成に失敗しました", bad_initialize);
					return result;
				}
				priority_map_.clear();
				return result;
			}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				using sprig::get_pointer;
				SPRIG_DG_SECTION(TEXT("sprite_drawer_manager::reinitialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				if (FAILED(result = D3DXCreateSprite(get_pointer(device_), sprig::accept(sprite_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトの作成に失敗しました", bad_initialize);
					return result;
				}
				BOOST_FOREACH(value_type const& e, priority_map_) {
					if (FAILED(result = e.ref_mapped()->reinitialize(device_))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトドローワの初期化に失敗しました", bad_initialize);
						return result;
					}
				}

				return result;
			}
			bool is_initialized() const {
				return device_;
			}
			insert_result_type insert(typename sprig::call_traits<value_type>::param_type element) {
				return priority_map_.insert(element);
			}
			insert_result_type insert(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority,
				typename sprig::call_traits<instance_type>::param_type sprite_drawer
				)
			{
				return priority_map_.insert(value_type(key, priority, sprite_drawer));
			}
			void erase(typename sprig::call_traits<typename priority_map_type::iterator>::param_type position) {
				priority_map_.erase(position);
			}
			typename priority_map_type::size_type erase(typename sprig::call_traits<key_type>::param_type key) {
				return priority_map_.erase(key);
			}
			void clear() {
				priority_map_.clear();
			}
			typename priority_map_type::size_type size() const {
				return priority_map_.size();
			}
			typename priority_map_type::const_iterator begin() const {
				return priority_map_.begin();
			}
			typename priority_map_type::iterator begin() {
				return priority_map_.begin();
			}
			typename priority_map_type::const_iterator end() const {
				return priority_map_.end();
			}
			typename priority_map_type::iterator end() {
				return priority_map_.end();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::const_iterator begin() const {
				return priority_map_.get<Tag>().begin();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::iterator begin() {
				return priority_map_.get<Tag>().begin();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::const_iterator end() const {
				return priority_map_.get<Tag>().end();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::iterator end() {
				return priority_map_.get<Tag>().end();
			}
			typename priority_map_type::const_iterator find(typename sprig::call_traits<key_type>::param_type key) const {
				return priority_map_.find(key);
			}
			typename priority_map_type::iterator find(typename sprig::call_traits<key_type>::param_type key) {
				return priority_map_.find(key);
			}
			bool modify_priority(
				typename sprig::call_traits<typename priority_map_type::iterator>::param_type position,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				return priority_map_.modify(position, priority_modifier<priority_map_defs_type>(priority));
			}
			bool modify_priority(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				typename priority_map_type::iterator position = priority_map_.find(key);
				if (position == priority_map_.end()) {
					return false;
				}
				return priority_map_.modify(position, priority_modifier<priority_map_defs_type>(priority));
			}
			//	COMMENT: スプライトの描画開始。
			//	COMMENT: これ以前にシーン描画開始が呼ばれていなければならない。
			HRESULT begin_draw() const {
				HRESULT result = D3D_OK;

				//	COMMENT: スプライトの描画開始
				if (FAILED(result = sprite_->Begin(flag_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトの描画開始に失敗しました", bad_process);
					return result;
				}

				//	COMMENT: アルファチャネルに対するブレンディングモードの設定
				if (FAILED(result = device_->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("アルファチャネルに対するブレンディングモードの設定に失敗しました", bad_process);
					return result;
				}

				//	COMMENT: アルファチャネルに対する算術演算の設定
				if (FAILED(result = device_->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MAX))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("アルファチャネルに対する算術演算の設定に失敗しました", bad_process);
					return result;
				}

				//	COMMENT: 描画元ブレンディング係数の設定
				if (FAILED(result = device_->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("描画元ブレンディング係数の設定に失敗しました", bad_process);
					return result;
				}

				//	COMMENT: 描画先ブレンディング係数の設定
				if (FAILED(result = device_->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("描画先ブレンディング係数の設定に失敗しました", bad_process);
					return result;
				}

				//	COMMENT: ドローワの描画開始
				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					if (FAILED(result = e.get_mapped()->begin_draw(sprite_))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("ドローワの描画開始に失敗しました", bad_process);
						return result;
					}
				}

				return result;
			}
			//	COMMENT: スプライトの描画終了。
			//	COMMENT: これ以後にシーン描画終了を呼ばなければならない。
			HRESULT end_draw() const {
				HRESULT result = D3D_OK;

				//	COMMENT: ドローワの描画終了
				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					if (FAILED(result = e.get_mapped()->end_draw(sprite_))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("ドローワの描画終了に失敗しました", bad_process);
						return result;
					}
				}

				//	COMMENT: スプライトの描画終了
				if (FAILED(result = sprite_->End())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトの描画終了に失敗しました", bad_process);
					return result;
				}

				return result;
			}
			//	COMMENT: スプライトの描画。
			//	COMMENT: スプライトの描画開始～描画終了の間に呼ばれなければならない。
			HRESULT draw() const {
				HRESULT result = D3D_OK;

				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					//	COMMENT: スプライトの描画
					if (FAILED(result = e.get_mapped()->draw(sprite_))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトの描画に失敗しました", bad_process);
						return result;
					}
				}

				return result;
			}
			//	COMMENT: スプライトの描画。
			//	COMMENT: スプライトの描画開始～描画終了は自動的に呼ばれる。
			HRESULT draw_sprite() const {
				HRESULT result = D3D_OK;
				if (FAILED(result = begin_draw())) {
					return result;
				}
				if (FAILED(result = draw())) {
					return result;
				}
				if (FAILED(result = end_draw())) {
					return result;
				}
				return result;
			}
			//	COMMENT: シーン描画開始。
			HRESULT begin_scene() const {
				HRESULT result = D3D_OK;
				if (FAILED(result = device_->BeginScene())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("シーン描画開始に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			//	COMMENT: シーン描画終了。
			HRESULT end_scene() const {
				HRESULT result = D3D_OK;
				if (FAILED(result = device_->EndScene())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("シーン描画終了に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			//	COMMENT: デバイスのクリア。
			//	COMMENT: 通常、シーン描画の前に呼ばれる。
			HRESULT clear_target(sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)) const {
				HRESULT result = D3D_OK;
				if (FAILED(device_->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("デバイスのクリアに失敗しました", bad_process);
					return false;
				}
				return result;
			}
			//	COMMENT: シーンおよびスプライトの描画。
			//	COMMENT: 描画開始～描画終了のシーケンスは自動的に呼ばれる。
			HRESULT draw_scene(
				bool clear = true,
				sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)
				) const
			{
				HRESULT result = D3D_OK;
				if (clear) {
					if (FAILED(result = clear_target(color))) {
						return result;
					}
				}
				if (FAILED(result = begin_scene())) {
					return result;
				}
				if (FAILED(result = draw_sprite())) {
					return result;
				}
				if (FAILED(result = end_scene())) {
					return result;
				}
				return result;
			}
			//	COMMENT: スプライトのヒットテスト開始。
			HRESULT begin_hit_test() {
				HRESULT result = D3D_OK;

				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					if (FAILED(result = e.get_mapped()->begin_hit_test())) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトのヒットテスト開始に失敗しました", bad_process);
						return result;
					}
				}

				return result;
			}
			//	COMMENT: スプライトのヒットテスト終了。
			HRESULT end_hit_test() {
				HRESULT result = D3D_OK;

				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					if (FAILED(result = e.get_mapped()->end_hit_test())) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトのヒットテスト終了に失敗しました", bad_process);
						return result;
					}
				}

				return result;
			}
			//	COMMENT: スプライトのヒットテストを行う。
			//	COMMENT: スプライトのヒットテスト開始～ヒットテスト終了の間に呼ばれなければならない。
			template<typename Hit, typename Key>
			HRESULT hit_test(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) const {
				HRESULT result = D3D_OK;

				BOOST_REVERSE_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					bool h = false;
					if (FAILED(result = e.get_mapped()->hit_test(h, point))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトのヒットテストに失敗しました", bad_process);
						return result;
					}
					if (h) {
						hit = true;
						key = e.get_key();
						return result;
					}
				}

				hit = false;
				return result;
			}
			//	COMMENT: スプライトのマルチヒットテストを行う。
			//	COMMENT: スプライトのヒットテスト開始～ヒットテスト終了の間に呼ばれなければならない。
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test(Hit& hit, KeyIterator key, typename sprig::call_traits<coord_type>::param_type point) const {
				HRESULT result = D3D_OK;

				std::size_t count = 0;
				BOOST_REVERSE_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					bool h = false;
					if (FAILED(result = e.get_mapped()->hit_test(h, point))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("スプライトのヒットテストに失敗しました", bad_process);
						return result;
					}
					if (h) {
						++count;
						*key++ = e.get_key();
					}
				}

				hit = count;
				return result;
			}
			//	COMMENT: スプライトのヒットテストを行う。
			//	COMMENT: ヒットテスト開始～ヒットテスト終了のシーケンスは自動的に呼ばれる。
			template<typename Hit, typename Key>
			HRESULT hit_test_period(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) {
				HRESULT result = D3D_OK;
				if (FAILED(result = begin_hit_test())) {
					return result;
				}
				if (FAILED(result = hit_test(hit, key, point))) {
					return result;
				}
				if (FAILED(result = end_hit_test())) {
					return result;
				}
				return result;
			}
			//	COMMENT: 渡されたすべての点についてスプライトのヒットテストを行う。
			//	COMMENT: ヒットテスト開始～ヒットテスト終了のシーケンスは自動的に呼ばれる。
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				HRESULT result = D3D_OK;
				if (FAILED(result = begin_hit_test())) {
					return result;
				}
				BOOST_FOREACH(typename sprig::call_traits<coord_type>::param_type e, boost::make_iterator_range(first, last)) {
					if (FAILED(result = hit_test(*hit, *key, e))) {
						return result;
					}
					++hit;
					++key;
				}
				if (FAILED(result = end_hit_test())) {
					return result;
				}
				return result;
			}
			//	COMMENT: スプライトのマルチヒットテストを行う。
			//	COMMENT: ヒットテスト開始～ヒットテスト終了のシーケンスは自動的に呼ばれる。
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test_period(Hit& hit, KeyIterator& key, typename sprig::call_traits<coord_type>::param_type point) {
				HRESULT result = D3D_OK;
				if (FAILED(result = begin_hit_test())) {
					return result;
				}
				if (FAILED(result = multi_hit_test(hit, key, point))) {
					return result;
				}
				if (FAILED(result = end_hit_test())) {
					return result;
				}
				return result;
			}
			//	COMMENT: 渡されたすべての点についてスプライトのマルチヒットテストを行う。
			//	COMMENT: ヒットテスト開始～ヒットテスト終了のシーケンスは自動的に呼ばれる。
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT multi_hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				HRESULT result = D3D_OK;
				if (FAILED(result = begin_hit_test())) {
					return result;
				}
				BOOST_FOREACH(typename sprig::call_traits<coord_type>::param_type e, boost::make_iterator_range(first, last)) {
					if (FAILED(result = multi_hit_test(*hit, *key, e))) {
						return result;
					}
					++hit;
					++key;
				}
				if (FAILED(result = end_hit_test())) {
					return result;
				}
				return result;
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_;
			}
			sprig::call_traits<sprite_type>::getter_type get_sprite() const {
				return sprite_;
			}
			sprig::call_traits<flag_type>::getter_type get_flag() const {
				return flag_;
			}
			void set_flag(sprig::call_traits<flag_type>::param_type v) {
				flag_ = v;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("priority_map_", priority_map_)
					& boost::serialization::make_nvp("flag_", flag_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 3, sprite_drawer_manager);
		template<typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_manager<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_manager<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_manager<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_SPRITE_DRAWER_MANAGER_HPP
