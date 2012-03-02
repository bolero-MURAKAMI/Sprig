#ifndef SPRIG_DG_SPRITE_TRANSFERER_HPP
#define SPRIG_DG_SPRITE_TRANSFERER_HPP

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
#include <sprig/dg/render_transferer.hpp>
#include <sprig/dg/sprite_drawer_manager.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_transferer
		//
		template<
			typename Key = std::basic_string<char_type>,
			typename Priority = double
		>
		class sprite_transferer {
		public:
			typedef Key key_type;
			typedef Priority priority_type;
			typedef sprite_drawer_manager<key_type, priority_type> sprite_drawer_manager_type;
			typedef render_transferer<key_type, priority_type> render_transferer_type;
			typedef typename sprite_drawer_manager_type::instance_type instance_type;
			typedef typename sprite_drawer_manager_type::priority_map_defs_type priority_map_defs_type;
			typedef typename sprite_drawer_manager_type::mapped_type mapped_type;
			typedef typename sprite_drawer_manager_type::value_type value_type;
			typedef typename sprite_drawer_manager_type::key_comparator_type key_comparator_type;
			typedef typename sprite_drawer_manager_type::key_tag_type key_tag_type;
			typedef typename sprite_drawer_manager_type::priority_tag_type priority_tag_type;
			typedef typename sprite_drawer_manager_type::priority_map_type priority_map_type;
			typedef typename sprite_drawer_manager_type::key_index_type key_index_type;
			typedef typename sprite_drawer_manager_type::insert_result_type insert_result_type;
			typedef typename sprite_drawer_manager_type::flag_type flag_type;
			typedef typename sprite_drawer_manager_type::coord_type coord_type;
		private:
			device_type device_;
			sprite_drawer_manager_type sprite_drawer_manager_;
			render_transferer_type render_transferer_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("device_"), device_, logger);
				value_info_section_line(TEXT("sprite_drawer_manager_"), sprite_drawer_manager_, logger);
				value_info_section_line(TEXT("render_transferer_"), render_transferer_, logger);
			}
		public:
			HRESULT initialize(
				sprig::call_traits<device_type>::param_type device,
				sprig::call_traits<texture_manager_init_params>::param_type params
				)
			{
				SPRIG_DG_SECTION(TEXT("sprite_transferer::initialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				// スプライトドローワマネージャの初期化
				if (FAILED(result = sprite_drawer_manager_.initialize(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトドローワマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}
				// レンダートランスファラの初期化
				if (FAILED(result = render_transferer_.initialize(device_, params))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダートランスファラの初期化に失敗しました", bad_initialize);
					return result;
				}
				return result;
			}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				SPRIG_DG_SECTION(TEXT("sprite_transferer::reinitialize"));
				HRESULT result = D3D_OK;

				device_ = device;
				// スプライトドローワマネージャの初期化
				if (FAILED(result = sprite_drawer_manager_.reinitialize(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("スプライトドローワマネージャの初期化に失敗しました", bad_initialize);
					return result;
				}
				// レンダートランスファラの初期化
				if (FAILED(result = render_transferer_.reinitialize(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダートランスファラの初期化に失敗しました", bad_initialize);
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
				return render_transferer_.transfer(bits, size, pitch, pixel_size, offset, rect);
			}
			HRESULT set_render_target(DWORD render_target_index = 0) const {
				return render_transferer_.set_render_target(render_target_index);
			}
			insert_result_type insert(typename sprig::call_traits<value_type>::param_type element) {
				return sprite_drawer_manager_.insert(element);
			}
			insert_result_type insert(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority,
				typename sprig::call_traits<instance_type>::param_type sprite_drawer
				)
			{
				return sprite_drawer_manager_.insert(key, priority, sprite_drawer);
			}
			void erase(typename sprig::call_traits<typename priority_map_type::iterator>::param_type position) {
				sprite_drawer_manager_.erase(position);
			}
			typename priority_map_type::size_type erase(typename sprig::call_traits<key_type>::param_type key) {
				return sprite_drawer_manager_.erase(key);
			}
			void clear() {
				sprite_drawer_manager_.clear();
			}
			typename priority_map_type::size_type size() const {
				return sprite_drawer_manager_.size();
			}
			typename priority_map_type::const_iterator begin() const {
				return sprite_drawer_manager_.begin();
			}
			typename priority_map_type::iterator begin() {
				return sprite_drawer_manager_.begin();
			}
			typename priority_map_type::const_iterator end() const {
				return sprite_drawer_manager_.end();
			}
			typename priority_map_type::iterator end() {
				return sprite_drawer_manager_.end();
			}
			template<typename Tag>
			typename typename priority_map_type::index<Tag>::type::const_iterator begin() const {
				return sprite_drawer_manager_.begin<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::index<Tag>::type::iterator begin() {
				return sprite_drawer_manager_.begin<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::index<Tag>::type::const_iterator end() const {
				return sprite_drawer_manager_.end<Tag>();
			}
			template<typename Tag>
			typename typename priority_map_type::index<Tag>::type::iterator end() {
				return sprite_drawer_manager_.end<Tag>();
			}
			typename priority_map_type::const_iterator find(typename sprig::call_traits<key_type>::param_type key) const {
				return sprite_drawer_manager_.find(key);
			}
			typename priority_map_type::iterator find(typename sprig::call_traits<key_type>::param_type key) {
				return sprite_drawer_manager_.find(key);
			}
			bool modify_priority(
				typename sprig::call_traits<typename priority_map_type::iterator>::param_type position,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				return sprite_drawer_manager_.modify_priority(position, priority);
			}
			bool modify_priority(
				typename sprig::call_traits<key_type>::param_type key,
				typename sprig::call_traits<priority_type>::param_type priority
				)
			{
				return sprite_drawer_manager_.modify_priority(key, priority);
			}
			HRESULT begin_draw() const {
				return sprite_drawer_manager_.begin_draw();
			}
			HRESULT end_draw() const {
				return sprite_drawer_manager_.end_draw();
			}
			HRESULT draw() const {
				return sprite_drawer_manager_.draw();
			}
			HRESULT draw_sprite() const {
				return sprite_drawer_manager_.draw_sprite();
			}
			HRESULT begin_scene() const {
				return sprite_drawer_manager_.begin_scene();
			}
			HRESULT end_scene() const {
				return sprite_drawer_manager_.end_scene();
			}
			HRESULT clear_target(sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)) const {
				return sprite_drawer_manager_.clear_target(color);
			}
			HRESULT draw_scene(
				bool clear = true,
				sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)
				) const
			{
				return sprite_drawer_manager_.draw_scene(clear, color);
			}
			HRESULT draw_render_target(
				bool clear = true,
				sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00),
				DWORD render_target_index = 0
				) const
			{
				HRESULT result = D3D_OK;
				if (FAILED(result = set_render_target(render_target_index))) {
					return result;
				}
				if (FAILED(result = sprite_drawer_manager_.draw_scene(clear, color))) {
					return result;
				}
				return result;
			}
			HRESULT begin_hit_test() {
				return sprite_drawer_manager_.begin_hit_test();
			}
			HRESULT end_hit_test() {
				return sprite_drawer_manager_.end_hit_test();
			}
			template<typename Hit, typename Key>
			HRESULT hit_test(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) const {
				return sprite_drawer_manager_.hit_test(hit, key, point);
			}
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test(Hit& hit, KeyIterator key, typename sprig::call_traits<coord_type>::param_type point) const {
				return sprite_drawer_manager_.multi_hit_test(hit, key, point);
			}
			template<typename Hit, typename Key>
			HRESULT hit_test_period(Hit& hit, Key& key, typename sprig::call_traits<coord_type>::param_type point) {
				return sprite_drawer_manager_.hit_test_period(hit, key, point);
			}
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				return sprite_drawer_manager_.hit_test_period(hit, key, first, last);
			}
			template<typename Hit, typename KeyIterator>
			HRESULT multi_hit_test_period(Hit& hit, KeyIterator& key, typename sprig::call_traits<coord_type>::param_type point) {
				return sprite_drawer_manager_.multi_hit_test_period(hit, key, point);
			}
			template<typename PointIterator, typename HitIterator, typename KeyIterator>
			HRESULT multi_hit_test_period(
				HitIterator hit,
				KeyIterator key,
				PointIterator first,
				PointIterator last
				)
			{
				return sprite_drawer_manager_.multi_hit_test_period(hit, key, first, last);
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_;
			}
			sprite_drawer_manager_type& ref_sprite_drawer_manager() {
				return sprite_drawer_manager_;
			}
			typename sprig::call_traits<sprite_drawer_manager_type>::getter_type get_sprite_drawer_manager() const {
				return sprite_drawer_manager_;
			}
			render_transferer_type& ref_render_transferer() {
				return render_transferer_;
			}
			typename sprig::call_traits<render_transferer_type>::getter_type get_render_transferer() const {
				return render_transferer_;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("sprite_drawer_manager_", sprite_drawer_manager_)
					& boost::serialization::make_nvp("render_transferer_", render_transferer_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 3, sprite_transferer);
		template<typename Logger>
		SPRIG_INLINE void value_info(sprite_transferer<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(sprite_transferer<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(sprite_transferer<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace sprig
}	// namespace dg

#endif	// #ifndef SPRIG_DG_SPRITE_TRANSFERER_HPP
