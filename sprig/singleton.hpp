#ifndef SPRIG_SINGLETON_HPP
#define SPRIG_SINGLETON_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/serialization/singleton.hpp>

//
// SPRIG_FRIEND_SINGLETON
//
#define SPRIG_FRIEND_SINGLETON(CLASS) \
	friend class boost::serialization::detail::singleton_wrapper<CLASS>

namespace sprig {
	//
	// singleton
	//
	template<typename T>
	class singleton
		: private boost::serialization::singleton<T>
	{
	public:
		typedef T instance_type;
	private:
		typedef boost::serialization::singleton<instance_type> singleton_impl_type;
	public:
		static instance_type& get_mutable_instance(){
			return singleton_impl_type::get_mutable_instance();
		}
		static instance_type const& get_const_instance(){
			return singleton_impl_type::get_const_instance();
		}
		static bool is_destroyed(){
			return singleton_impl_type::is_destroyed();
		}
		static void lock(){
			singleton_impl_type::lock();
		}
		static void unlock(){
			singleton_impl_type::unlock();
		}
		static bool is_locked() {
			return singleton_impl_type::is_locked();
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_SINGLETON_HPP
