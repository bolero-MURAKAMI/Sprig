/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_COM_PTR_HPP
#define SPRIG_COM_PTR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/utility/swap.hpp>

namespace sprig {
	//
	// declares
	//
	template<typename T>
	class com_ptr;
	template<typename T>
	class weak_com_ptr;

	//
	// com_ptr
	//
	template<typename T>
	class com_ptr {
		template<typename Derived>
		friend class weak_com_ptr;
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef pointer* double_pointer;
	private:
		typedef com_ptr this_type;
		typedef pointer member_element_type;
		typedef boost::shared_ptr<member_element_type> member_type;
	private:
		static void deleter(double_pointer p) {
			if (*p) {
				com_ptr_release(*p);
			}
			delete p;
		}
		template<typename U>
		static void deleter_for(U** p) {
			if (*p) {
				com_ptr_release(*p);
			}
			delete p;
		}
	private:
		member_type p_;
	private:
		com_ptr(member_type const& p)
			: p_(p)
		{}
		member_type const& get_member() const {
			return p_;
		}
	public:
		com_ptr()
			: p_(new member_element_type(0), deleter)
		{}
		explicit com_ptr(pointer p, bool add_ref = false)
			: p_(new member_element_type(p), deleter)
		{
			if (*p_ && add_ref) {
				com_ptr_add_ref(*p_);
			}
		}
		com_ptr(this_type const& rhs)
			: p_(rhs.p_)
		{}
		template<typename Derived>
		explicit com_ptr(Derived* p, bool add_ref = false)
			: p_(new member_element_type(p), deleter_for<Derived>)
		{
			if (*p_ && add_ref) {
				com_ptr_add_ref(*p_);
			}
		}
		template<typename Derived>
		com_ptr(com_ptr<Derived> const& rhs)
			: p_(rhs.p_)
		{}
		~com_ptr() throw() {}
		this_type& operator=(pointer rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		this_type& operator=(this_type const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(Derived* rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		void swap(this_type& rhs) {
			boost::swap(p_, rhs.p_);
		}
		void reset() {
			this_type().swap(*this);
		}
		void reset(pointer rhs, bool add_ref = false) {
			this_type(rhs, add_ref).swap(*this);
		}
		void reset(this_type const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(Derived* rhs, bool add_ref = false) {
			this_type(rhs, add_ref).swap(*this);
		}
		template<typename Derived>
		void reset(com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
		void replace_swap(this_type& rhs) {
			boost::swap(*p_, *rhs.p_);
		}
		void replace() {
			this_type().replace_swap(*this);
		}
		void replace(pointer rhs, bool add_ref = false) {
			this_type(rhs, add_ref).replace_swap(*this);
		}
		void replace(this_type const& rhs) {
			this_type(rhs).replace_swap(*this);
		}
		template<typename Derived>
		void replace(Derived* rhs, bool add_ref = false) {
			this_type(rhs, add_ref).replace_swap(*this);
		}
		template<typename Derived>
		void replace(com_ptr<Derived> const& rhs) {
			this_type(rhs).replace_swap(*this);
		}
		pointer get() const {
			return *p_;
		}
		double_pointer get_ptr_ptr() const {
			return p_.get();
		}
		element_type& operator*() const {
			return **p_;
		}
		pointer operator->() const {
			return *p_;
		}
		operator bool() const {
			return *p_ != 0;
		}
		bool operator!() const {
			return !*p_;
		}
	};
	//
	// operators
	//
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(com_ptr<T1> const& lhs, com_ptr<T2> const& rhs) {
		return lhs.get() == rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(com_ptr<T1> const& lhs, com_ptr<T2> const& rhs) {
		return lhs.get() != rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(com_ptr<T1> const& lhs, T2* rhs) {
		return lhs.get() == rhs;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(com_ptr<T1> const& lhs, T2* rhs) {
		return lhs.get() != rhs;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(T1* lhs, com_ptr<T2> const& rhs) {
		return lhs == rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(T1* lhs, com_ptr<T2> const& rhs) {
		return lhs != rhs.get();
	}
	template<typename Elem, typename Traits, typename T>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		com_ptr<T> const& rhs
		)
	{
		return lhs << rhs.get();
	}
	//
	// swap
	//
	template<typename T>
	SPRIG_INLINE void swap(com_ptr<T>& lhs, com_ptr<T>& rhs) {
		lhs.swap(rhs);
	}
	//
	// get_pointer
	//
	template<typename T>
	SPRIG_INLINE typename com_ptr<T>::pointer get_pointer(com_ptr<T> const& p) {
		return p.get();
	}
	//
	// accept, replace_accept
	//
	template<typename T>
	SPRIG_INLINE typename com_ptr<T>::double_pointer accept(com_ptr<T>& p) {
		p.reset();
		return p.get_ptr_ptr();
	}
	template<typename T>
	SPRIG_INLINE typename com_ptr<T>::double_pointer replace_accept(com_ptr<T>& p) {
		p.replace();
		return p.get_ptr_ptr();
	}

	//
	// weak_com_ptr
	//
	template<typename T>
	class weak_com_ptr {
	public:
		typedef com_ptr<T> com_pointer;
		typedef typename com_pointer::element_type element_type;
		typedef typename com_pointer::pointer pointer;
		typedef typename com_pointer::double_pointer double_pointer;
	private:
		typedef weak_com_ptr this_type;
		typedef boost::weak_ptr<pointer> member_type;
	private:
		member_type p_;
	public:
		weak_com_ptr()
			: p_()
		{}
		weak_com_ptr(com_pointer const& p)
			: p_(p.get_member())
		{}
		weak_com_ptr(this_type const& rhs)
			: p_(rhs.p_)
		{}
		template<typename Derived>
		explicit weak_com_ptr(com_ptr<Derived> const& p)
			: p_(p.get_member())
		{}
		template<typename Derived>
		weak_com_ptr(weak_com_ptr<Derived> const& rhs)
			: p_(rhs.p_)
		{}
		~weak_com_ptr() throw() {}
		this_type& operator=(com_pointer const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		this_type& operator=(this_type const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(weak_com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		com_pointer lock() const {
			return com_pointer(p_.lock());
		}
		bool expired() const {
			return p_.expired();
		}
		void swap(this_type& rhs) {
			boost::swap(p_, rhs.p_);
		}
		void reset() {
			this_type().swap(*this);
		}
		void reset(com_pointer const& rhs) {
			this_type(rhs).swap(*this);
		}
		void reset(this_type const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(weak_com_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
	};
	//
	// swap
	//
	template<typename T>
	SPRIG_INLINE void swap(weak_com_ptr<T>& lhs, weak_com_ptr<T>& rhs) {
		lhs.swap(rhs);
	}
}	//namespace sprig

#endif	// #ifndef SPRIG_COM_PTR_HPP
