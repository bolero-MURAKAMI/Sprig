#ifndef SPRIG_DG_SPRITE_DRAWER_FILTER_MANAGER_HPP
#define SPRIG_DG_SPRITE_DRAWER_FILTER_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <utility>
#include <boost/foreach.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <sprig/serialization/sprig/priority_map.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>
#include <sprig/dg/texture_manager.hpp>
#include <sprig/dg/sprite_drawer_filter.hpp>

namespace sprig {
	namespace dg {
		//
		// sprite_drawer_filter_manager
		//
		template<
			typename Key = std::basic_string<char_type>,
			typename Priority = double
		>
		class sprite_drawer_filter_manager
			: public sprite_drawer_filter
		{
		private:
			typedef sprite_drawer_filter_manager this_type;
		public:
			typedef sprite_drawer_filter filter_type;
			typedef boost::shared_ptr<filter_type> instance_type;
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
		private:
			priority_map_type priority_map_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("priority_map_"), priority_map_, logger);
			}
			void output_members_value_info() const {
				SPRIG_DG_SECTION(TEXT("members"));
				SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("priority_map_"), priority_map_);
			}
		public:
			sprite_drawer_filter_manager() {}
			HRESULT reinitialize(sprig::call_traits<device_type>::param_type device) {
				SPRIG_DG_SECTION(TEXT("sprite_drawer_filter_manager::reinitialize"));
				HRESULT result = D3D_OK;

				BOOST_FOREACH(value_type const& e, priority_map_) {
					if (FAILED(result = e.ref_mapped()->reinitialize(device))) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("フィルタの初期化に失敗しました", bad_initialize);
						return result;
					}
				}

				return result;
			}
			result_type apply(texture_manager_type const& texture_manager) const {
				result_type result(D3D_OK, texture_manager);

				BOOST_FOREACH(value_type const& e, priority_map_.get<priority_tag_type>()) {
					if (FAILED((result = e.get_mapped()->apply(*result.second)).first)) {
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
						SPRIG_DG_ERROR("フィルタの適用に失敗しました", bad_process);
						return result;
					}
					if (!result.second) {
						return result;
					}
				}

				return result;
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
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("priority_map_", priority_map_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(0, 3, sprite_drawer_filter_manager);
		template<typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_filter_manager<> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_filter_manager<Key> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
		template<typename Key, typename Priority, typename Logger>
		SPRIG_INLINE void value_info(sprite_drawer_filter_manager<Key, Priority> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_DG_HPP
