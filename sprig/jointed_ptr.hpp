/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_JOINTED_PTR_HPP
#define SPRIG_JOINTED_PTR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/utility/swap.hpp>

namespace sprig {
	//
	// declares
	//
	template<typename T>
	class jointed_ptr;
	template<typename T>
	class weak_jointed_ptr;

	//
	// jointed_ptr
	//
	template<typename T>
	class jointed_ptr {
		template<typename Derived>
		friend class weak_jointed_ptr;
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef pointer* double_pointer;
	private:
		typedef jointed_ptr this_type;
		typedef boost::shared_ptr<element_type> member_element_type;
		typedef boost::shared_ptr<member_element_type> member_type;
	private:
		member_type p_;
	private:
		jointed_ptr(member_type const& p)
			: p_(p)
		{}
		member_type const& get_member() const {
			return p_;
		}
	public:
		jointed_ptr()
			: p_(boost::make_shared<member_element_type>())
		{}
		explicit jointed_ptr(pointer p)
			: p_(boost::make_shared<member_element_type>(p))
		{}
		jointed_ptr(this_type const& rhs)
			: p_(rhs.p_)
		{}
		template<typename Deleter>
		jointed_ptr(pointer p, Deleter deleter)
			: p_(boost::make_shared<member_element_type>(p, deleter))
		{}
		template<typename Derived>
		explicit jointed_ptr(Derived* p)
			: p_(boost::make_shared<member_element_type>(p))
		{}
		template<typename Derived>
		jointed_ptr(jointed_ptr<Derived> const& rhs)
			: p_(rhs.p_)
		{}
		template<typename Derived, typename Deleter>
		explicit jointed_ptr(Derived* p, Deleter deleter)
			: p_(boost::make_shared<member_element_type>(p, deleter))
		{}
		~jointed_ptr() throw() {}
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
		this_type& operator=(jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		void swap(this_type& rhs) {
			boost::swap(p_, rhs.p_);
		}
		void reset() {
			this_type().swap(*this);
		}
		void reset(pointer rhs) {
			this_type(rhs).swap(*this);
		}
		void reset(this_type const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Deleter>
		void reset(pointer rhs, Deleter deleter) {
			this_type(rhs, deleter).swap(*this);
		}
		template<typename Derived>
		void reset(Derived* rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived, typename Deleter>
		void reset(jointed_ptr<Derived> const& rhs, Deleter deleter) {
			this_type(rhs, deleter).swap(*this);
		}
		void replace_swap(this_type& rhs) {
			boost::swap(*p_, *rhs.p_);
		}
		void replace() {
			this_type().replace_swap(*this);
		}
		void replace(pointer rhs) {
			this_type(rhs).replace_swap(*this);
		}
		void replace(this_type const& rhs) {
			this_type(rhs).replace_swap(*this);
		}
		template<typename Deleter>
		void replace(pointer rhs, Deleter deleter) {
			this_type(rhs, deleter).replace_swap(*this);
		}
		template<typename Derived>
		void replace(Derived* rhs, bool add_ref = false) {
			this_type(rhs, add_ref).replace_swap(*this);
		}
		template<typename Derived>
		void replace(jointed_ptr<Derived> const& rhs) {
			this_type(rhs).replace_swap(*this);
		}
		template<typename Derived, typename Deleter>
		void replace(jointed_ptr<Derived> const& rhs, Deleter deleter) {
			this_type(rhs, deleter).replace_swap(*this);
		}
		pointer get() const {
			return p_->get();
		}
		double_pointer get_double_pointer() {
			return p_.get();
		}
		element_type& operator*() const {
			return **p_;
		}
		pointer operator->() const {
			return p_->get();
		}
		operator bool() const {
			return *p_;
		}
		bool operator!() const {
			return !*p_;
		}
	};
	//
	// operators
	//
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(jointed_ptr<T1> const& lhs, jointed_ptr<T2> const& rhs) {
		return lhs.get() == rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(jointed_ptr<T1> const& lhs, jointed_ptr<T2> const& rhs) {
		return lhs.get() != rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(jointed_ptr<T1> const& lhs, T2* rhs) {
		return lhs.get() == rhs;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(jointed_ptr<T1> const& lhs, T2* rhs) {
		return lhs.get() != rhs;
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator==(T1* lhs, jointed_ptr<T2> const& rhs) {
		return lhs == rhs.get();
	}
	template<typename T1, typename T2>
	SPRIG_INLINE bool operator!=(T1* lhs, jointed_ptr<T2> const& rhs) {
		return lhs != rhs.get();
	}
	template<typename Elem, typename Traits, typename T>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		jointed_ptr<T> const& rhs
		)
	{
		return lhs << rhs.get();
	}
	//
	// swap
	//
	template<typename T>
	SPRIG_INLINE void swap(jointed_ptr<T>& lhs, jointed_ptr<T>& rhs) {
		lhs.swap(rhs);
	}
	//
	// get_pointer
	//
	template<typename T>
	SPRIG_INLINE typename jointed_ptr<T>::pointer get_pointer(jointed_ptr<T> const& p) {
		return p.get();
	}
	//
	// accept, replace_accept
	//
	template<typename T>
	SPRIG_INLINE typename jointed_ptr<T>::double_pointer accept(jointed_ptr<T>& p) {
		p.reset();
		return p.get_double_pointer();
	}
	template<typename T>
	SPRIG_INLINE typename jointed_ptr<T>::double_pointer replace_accept(jointed_ptr<T>& p) {
		p.replace();
		return p.get_double_pointer();
	}

	//
	// weak_jointed_ptr
	//
	template<typename T>
	class weak_jointed_ptr {
	public:
		typedef jointed_ptr<T> jointed_pointer;
		typedef typename jointed_pointer::element_type element_type;
		typedef typename jointed_pointer::pointer pointer;
		typedef typename jointed_pointer::double_pointer double_pointer;
	private:
		typedef weak_jointed_ptr this_type;
		typedef boost::weak_ptr<pointer> member_type;
	private:
		member_type p_;
	public:
		weak_jointed_ptr()
			: p_()
		{}
		weak_jointed_ptr(jointed_pointer const& p)
			: p_(p.get_member())
		{}
		weak_jointed_ptr(this_type const& rhs)
			: p_(rhs.p_)
		{}
		template<typename Derived>
		explicit weak_jointed_ptr(jointed_ptr<Derived> const& p)
			: p_(p.get_member())
		{}
		template<typename Derived>
		weak_jointed_ptr(weak_jointed_ptr<Derived> const& rhs)
			: p_(rhs.p_)
		{}
		~weak_jointed_ptr() throw() {}
		this_type& operator=(jointed_pointer const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		this_type& operator=(this_type const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		template<typename Derived>
		this_type& operator=(weak_jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		jointed_pointer lock() const {
			return jointed_pointer(p_.lock());
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
		void reset(jointed_pointer const& rhs) {
			this_type(rhs).swap(*this);
		}
		void reset(this_type const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
		template<typename Derived>
		void reset(weak_jointed_ptr<Derived> const& rhs) {
			this_type(rhs).swap(*this);
		}
	};
	//
	// swap
	//
	template<typename T>
	SPRIG_INLINE void swap(weak_jointed_ptr<T>& lhs, weak_jointed_ptr<T>& rhs) {
		lhs.swap(rhs);
	}
}	//namespace sprig

#endif	// #ifndef SPRIG_JOINTED_PTR_HPP
