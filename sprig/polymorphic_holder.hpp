/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_POLYMORPHIC_HOLDER_HPP
#define SPRIG_POLYMORPHIC_HOLDER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>

namespace sprig {
	//
	// polymorphic_holder
	//
	template<typename Base>
	class polymorphic_holder
		: public Base
	{
	private:
		typedef boost::shared_ptr<Base> ptr_type;
	public:
		typedef Base base_type;
		typedef polymorphic_holder holder_type;
	private:
		ptr_type ptr_;
	public:
		polymorphic_holder() {}
		polymorphic_holder(polymorphic_holder const& rhs)
			: ptr_(rhs.ptr_)
		{}
		template<typename Derived>
		explicit polymorphic_holder(polymorphic_holder<Derived> const& rhs)
			: ptr_(rhs.ptr_)
		{}
		template<typename Derived>
		explicit polymorphic_holder(
			Derived const& rhs,
			typename boost::disable_if<boost::is_base_and_derived<polymorphic_holder<Base>, Derived> >::type* = 0)
			: ptr_(boost::make_shared<Derived>(rhs))
		{}
		virtual ~polymorphic_holder() {}
		template<typename Derived>
		polymorphic_holder& operator=(polymorphic_holder<Derived> const& rhs) {
			ptr_ = rhs.ptr_;
			return *this;
		}
		template<typename Derived>
		polymorphic_holder& operator=(Derived const& rhs) {
			ptr_.reset(boost::make_shared<Derived>(rhs));
			return *this;
		}
		Base& get() const {
			return *ptr_;
		}
		Base* get_ptr() const {
			return ptr_.get();
		}
		operator bool() const {
			return ptr_;
		}
	};
	//
	// holder_cast
	//
	template<typename T, typename Base>
	SPRIG_INLINE typename boost::disable_if<
		boost::is_pointer<T>,
		typename boost::add_reference<T>::type
		>::type
	holder_cast(polymorphic_holder<Base> const& target) {
		BOOST_MPL_ASSERT((boost::is_base_and_derived<Base, T>));
		return dynamic_cast<typename boost::add_reference<T>::type>(target.get());
	}
	template<typename T, typename Base>
	SPRIG_INLINE typename boost::enable_if<boost::is_pointer<T>, T>::type
	holder_cast(polymorphic_holder<Base> const& target) {
		BOOST_MPL_ASSERT((boost::is_base_and_derived<Base, typename boost::remove_pointer<T>::type>));
		return dynamic_cast<T>(target.get_ptr());
	}
	//
	// type_of
	//
	template<typename Base>
	SPRIG_INLINE std::type_info const& type_of(polymorphic_holder<Base> const& target) {
		return typeid(target.get());
	}
	//
	// is_instance_of
	//
	template<typename T, typename Base>
	SPRIG_INLINE bool is_instance_of(polymorphic_holder<Base> const& target) {
		BOOST_MPL_ASSERT((
			boost::mpl::or_<
				typename boost::is_same<Base, T>::type,
				typename boost::is_base_and_derived<Base, T>::type
			>
			));
		return type_of(target) == typeid(T);
	}
	//
	// is_inheritance_of
	//
	template<typename T, typename Base>
	SPRIG_INLINE bool is_inheritance_of(polymorphic_holder<Base> const& target) {
		BOOST_MPL_ASSERT((boost::is_base_and_derived<Base, T>));
		return dynamic_cast<T*>(target.get_ptr()) != 0;
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_POLYMORPHIC_HOLDER_HPP
