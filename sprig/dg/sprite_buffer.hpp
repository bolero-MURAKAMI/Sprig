/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_SPRITE_BUFFER_HPP
#define SPRIG_DG_SPRITE_BUFFER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>
#include <sprig/dg/texture_manager.hpp>
#include <sprig/dg/device_manager.hpp>
#include <sprig/dg/sprite_transferer.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_buffer_init_params
		//
		class sprite_buffer_init_params {
		public:
			typedef device_manager_init_params::string_type string_type;
			typedef texture_manager_init_params texture_manager_init_params_type;
		public:
			string_type name;
			texture_manager_init_params_type tmip;
		public:
			sprite_buffer_init_params(
				string_type const& name = string_type(),
				texture_manager_init_params_type const& tmip = texture_manager_init_params_type()
				)
				: name(name)
				, tmip(tmip)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("name", name)
					& boost::serialization::make_nvp("tmip", tmip)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(sprite_buffer_init_params);
		template<typename Logger>
		void value_info(sprite_buffer_init_params const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("name"), value.name);
			{
				Logger::section_type section_(TEXT("tmip"), *logger);
				value_info(value.tmip, logger);
			}
		}

		//
		// sprite_buffer
		//
		template<
			typename Key = std::basic_string<TCHAR>,
			typename Priority = double,
			typename TextureManager = dynamic_texture
		>
		class sprite_buffer {
		public:
			typedef Key key_type;
			typedef Priority priority_type;
			typedef TextureManager texture_manager_type;
			typedef sprite_buffer_init_params init_params_type;
			typedef device_manager device_manager_type;
			typedef device_manager_init_params device_manager_init_params_type;
			typedef sprite_transferer<key_type, priority_type> sprite_transferer_type;
			typedef device_manager_type::window_class_type window_class_type;
			typedef device_manager_type::window_handle_type window_handle_type;
			typedef device_manager_type::present_parameters_type present_parameters_type;
			typedef typename sprite_transferer_type::sprite_drawer_manager_type sprite_drawer_manager_type;
			typedef typename sprite_transferer_type::render_transferer_type render_transferer_type;
			typedef typename sprite_transferer_type::instance_type instance_type;
			typedef typename sprite_transferer_type::priority_map_defs_type priority_map_defs_type;
			typedef typename sprite_transferer_type::mapped_type mapped_type;
			typedef typename sprite_transferer_type::value_type value_type;
			typedef typename sprite_transferer_type::key_comparator_type key_comparator_type;
			typedef typename sprite_transferer_type::key_tag_type key_tag_type;
			typedef typename sprite_transferer_type::priority_tag_type priority_tag_type;
			typedef typename sprite_transferer_type::priority_map_type priority_map_type;
			typedef typename sprite_transferer_type::key_index_type key_index_type;
			typedef typename sprite_transferer_type::insert_result_type insert_result_type;
			typedef typename sprite_transferer_type::flag_type flag_type;
			typedef typename sprite_transferer_type::coord_type coord_type;
		private:
			device_manager_type device_manager_;
			sprite_transferer_type sprite_transferer_;
			device_manager_init_params_type device_manager_init_params_;
			init_params_type init_params_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("device_manager_"), device_manager_, logger);
				value_info_section_line(TEXT("sprite_transferer_"), sprite_transferer_, logger);
				value_info_section_line(TEXT("device_manager_init_params_"), device_manager_init_params_, logger);
				value_info_section_line(TEXT("init_params_"), init_params_, logger);
			}
		public:
			sprite_buffer()
				: device_manager_init_params_(SPRIG_DG_DEVICE_MODE_BUFFER, 1, 1)
			{}
			HRESULT initialize(init_params_type const& params) {
				SPRIG_DG_SECTION(TEXT("sprite_buffer::initialize"));
				HRESULT result = D3D_OK;

				init_params_ = params;

				// クラス名とウィンドウ名の設定
				device_manager_init_params_.class_name = init_params_.name;
				device_manager_init_params_.window_name = init_params_.name;

				// デバイスマネージャの初期化
				if (FAILED(result = device_manager_.initialize(device_manager_init_params_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("デバイスマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}

				// スプライトトランスファラの初期化
				if (FAILED(result = sprite_transferer_.initialize(device_manager_.get_device(), init_params_.tmip))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトトランスファラの初期化に失敗しました", bad_initialize);
					return result;
				}

				return result;
			}
			HRESULT reinitialize() {
				SPRIG_DG_SECTION(TEXT("sprite_buffer::reinitialize"));
				HRESULT result = D3D_OK;

				// デバイスマネージャの初期化
				if (FAILED(result = device_manager_.reinitialize())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("デバイスマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}

				// スプライトトランスファラの初期化
				if (FAILED(result = sprite_transferer_.reinitialize(device_manager_.get_device()))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトトランスファラの初期化に失敗しました", bad_initialize);
					return result;
				}

				return result;
			}
			bool is_initialized() const {
				return device_manager_.is_initialized();
			}
			HRESULT restore_render_target(DWORD render_target_index = 0) const {
				return device_manager_.restore_render_target(render_target_index);
			}
			sprig::call_traits<window_class_type>::getter_type get_window_class() const {
				return device_manager_.get_window_class();
			}
			sprig::call_traits<window_handle_type>::getter_type get_window_handle() const {
				return device_manager_.get_window_handle();
			}
			sprig::call_traits<present_parameters_type>::getter_type get_present_parameters() const {
				return device_manager_.get_present_parameters();
			}
			sprig::call_traits<object_type>::getter_type get_object() const {
				return device_manager_.get_object();
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_manager_.get_device();
			}
			sprig::call_traits<surface_type>::getter_type get_back_buffer_surface() const {
				return device_manager_.get_back_buffer_surface();
			}
			sprig::call_traits<init_params_type>::getter_type get_device_manager_init_params() const {
				return device_manager_.get_device_manager_init_params();
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
				return sprite_transferer_.transfer(bits, size, pitch, pixel_size, offset, rect);
			}
			insert_result_type insert(typename sprig::call_traits<value_type>::param_type element) {
				return sprite_transferer_.insert(element);
			}
			insert_result_type insert(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority,
				typename sprig::call_traits<instance_type>::param_type sprite_drawer
				)
			{
				return sprite_transferer_.insert(key, priority, sprite_drawer);
			}
			void erase(typename sprig::call_traits<typename priority_map_type::iterator>::param_type position) {
				sprite_transferer_.erase(position);
			}
			typename priority_map_type::size_type erase(typename sprig::call_traits<key_type>::param_type key) {
				return sprite_transferer_.erase(key);
			}
			void clear() {
				sprite_transferer_.clear();
			}
			typename priority_map_type::size_type size() const {
				return sprite_transferer_.size();
			}
			typename priority_map_type::const_iterator begin() const {
				return sprite_transferer_.begin();
			}
			typename priority_map_type::iterator begin() {
				return sprite_transferer_.begin();
			}
			typename priority_map_type::const_iterator end() const {
				return sprite_transferer_.end();
			}
			typename priority_map_type::iterator end() {
				return sprite_transferer_.end();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::const_iterator begin() const {
				return sprite_transferer_.begin<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::iterator begin() {
				return sprite_transferer_.begin<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::const_iterator end() const {
				return sprite_transferer_.end<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::template index<Tag>::type::iterator end() {
				return sprite_transferer_.end<Tag>();
			}
			typename priority_map_type::const_iterator find(typename sprig::call_traits<key_type>::param_type key) const {
				return sprite_transferer_.find(key);
			}
			typename priority_map_type::iterator find(typename sprig::call_traits<key_type>::param_type key) {
				return sprite_transferer_.find(key);
			}
			bool modify_priority(
				typename sprig::call_traits<typename priority_map_type::iterator>::param_type position,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				return sprite_transferer_.modify_priority(position, priority);
			}
			bool modify_priority(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				return sprite_transferer_.modify_priority(key, priority);
			}
			HRESULT begin_draw()  const{
				return sprite_transferer_.begin_draw();
			}
			HRESULT end_draw() const {
				return sprite_transferer_.end_draw();
			}
			HRESULT draw() const {
				return sprite_transferer_.draw();
			}
			HRESULT draw_sprite() const {
				return sprite_transferer_.draw_sprite();
			}
			HRESULT begin_scene() const {
				return sprite_transferer_.begin_scene();
			}
			HRESULT end_scene() const {
				return sprite_transferer_.end_scene();
			}
			HRESULT clear_target(sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)) const {
				return sprite_transferer_.clear_target(color);
			}
			HRESULT draw_scene(
				bool clear = true,
				sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)
				) const
			{
				return sprite_transferer_.draw_scene(clear, color);
			}
			HRESULT draw_render_target(
				bool clear = true,
				sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00),
				DWORD render_target_index = 0
				) const
			{
				return sprite_transferer_.draw_render_target(clear, color, render_target_index);
			}
			HRESULT begin_hit_test() {
				return sprite_transferer_.begin_hit_test();
			}
			HRESULT end_hit_test() {
				return sprite_transferer_.end_hit_test();
			}
			template<typename Hit, typename Key>
			HRESULT hit_test(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) const {
				return sprite_transferer_.hit_test(hit, key, point);
			}
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test(Hit& hit, KeyIterator key, typename sprig::call_traits<coord_type>::param_type point) const {
				return sprite_transferer_.multi_hit_test(hit, key, point);
			}
			template<typename Hit, typename Key>
			HRESULT hit_test_period(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) {
				return sprite_transferer_.hit_test_period(hit, key, point);
			}
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				return sprite_transferer_.hit_test_period(hit, key, first, last);
			}
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test_period(Hit& hit, KeyIterator& key, typename sprig::call_traits<coord_type>::param_type point) {
				return sprite_transferer_.multi_hit_test_period(hit, key, point);
			}
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT multi_hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				return sprite_transferer_.multi_hit_test_period(hit, key, first, last);
			}
			HRESULT get_device_caps(D3DCAPS9& caps) const {
				return device_manager_.get_device_caps(caps);
			}
			sprite_drawer_manager_type& ref_sprite_drawer_manager() {
				return sprite_transferer_.ref_sprite_drawer_manager();
			}
			typename sprig::call_traits<sprite_drawer_manager_type>::getter_type get_sprite_drawer_manager() const {
				return sprite_transferer_.get_sprite_drawer_manager();
			}
			render_transferer_type& ref_render_transferer() {
				return sprite_transferer_.ref_render_transferer();
			}
			typename sprig::call_traits<render_transferer_type>::getter_type get_render_transferer() const {
				return sprite_transferer_.get_render_transferer();
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("device_manager_", device_manager_)
					& boost::serialization::make_nvp("sprite_transferer_", sprite_transferer_)
					& boost::serialization::make_nvp("device_manager_init_params_", device_manager_init_params_)
					& boost::serialization::make_nvp("init_params_", init_params_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 3, sprite_buffer);
		template<typename Logger>
		SPRIG_INLINE void value_info(sprite_buffer<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(sprite_buffer<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(sprite_buffer<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	//namespace dg
}	//namespace sprig

#endif	// #ifndef SPRIG_DG_SPRITE_BUFFER_HPP
