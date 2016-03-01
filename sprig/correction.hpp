/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CORRECTION_HPP
#define SPRIG_CORRECTION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <functional>
#include <boost/numeric/interval.hpp>

namespace sprig {
	//
	// interval_correction
	//
	template<typename Value>
	class interval_correction {
	public:
		typedef Value value_type;
		typedef boost::numeric::interval<value_type> interval_type;
	private:
		interval_type interval_;
	public:
		interval_correction() {}
		explicit interval_correction(interval_type const& v)
			: interval_(v)
		{}
		template<typename T>
		interval_correction(interval_correction<T> const& other)
			: interval_(other.interval_)
		{}
		template<typename Lower, typename Upper>
		interval_correction(Lower const& l, Upper const& u)
			: interval_(l, u)
		{}
		virtual ~interval_correction() {}
		interval_type const& get() const {
			return interval_;
		}
		template<typename T>
		void set(T const& v) {
			interval_ = v;
		}
		template<typename Lower, typename Upper>
		void set(Lower const& l, Upper const& u) {
			interval_.set(l, u);
		}
		void internal(value_type& value) const {
			if (interval_.lower() > value) {
				value = interval_.lower();
			} else if (interval_.upper() < value) {
				value = interval_.upper();
			}
		}
		value_type get_internal(value_type const& value) const {
			if (interval_.lower() > value) {
				return interval_.lower();
			} else if (interval_.upper() < value) {
				return interval_.upper();
			}
			return value;
		}
		bool is_internal(value_type const& value) const {
			return (interval_.lower() > value || interval_.upper() < value)
				? false
				: true;
		}
		void external(value_type& value) const {
			if (interval_.lower() < value) {
				value = interval_.lower();
			} else if (interval_.upper() > value) {
				value = interval_.upper();
			}
		}
		value_type get_external(value_type const& value) const {
			if (interval_.lower() < value) {
				return interval_.lower();
			} else if (interval_.upper() > value) {
				return interval_.upper();
			}
			return value;
		}
		bool is_external(value_type const& value) const {
			return (interval_.lower() < value || interval_.upper() > value)
				? false
				: true;
		}
		template<typename T>
		void internal(T& value) const {
			if (interval_.lower() > value) {
				value = interval_.lower();
			} else if (interval_.upper() < value) {
				value = interval_.upper();
			}
		}
		template<typename T>
		T get_internal(T const& value) const {
			if (interval_.lower() > value) {
				return interval_.lower();
			} else if (interval_.upper() < value) {
				return interval_.upper();
			}
			return value;
		}
		template<typename T>
		bool is_internal(T const& value) const {
			return (interval_.lower() > value || interval_.upper() < value)
				? false
				: true;
		}
		template<typename T>
		void external(T& value) const {
			if (interval_.lower() < value) {
				value = interval_.lower();
			} else if (interval_.upper() > value) {
				value = interval_.upper();
			}
		}
		template<typename T>
		T get_external(T const& value) const {
			if (interval_.lower() < value) {
				return interval_.lower();
			} else if (interval_.upper() > value) {
				return interval_.upper();
			}
			return value;
		}
		template<typename T>
		bool is_external(T const& value) const {
			return (interval_.lower() < value || interval_.upper() > value)
				? false
				: true;
		}
	};
	//
	// internal_interval_correction
	//
	template<typename Value>
	class internal_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, void>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		internal_interval_correction() {}
		template<typename T>
		internal_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		internal_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~internal_interval_correction() {}
		void operator()(value_type const& value) const {
			this->internal(value);
		}
		template<typename T>
		void operator()(T const& value) const {
			this->internal(value);
		}
	};
	//
	// external_interval_correction
	//
	template<typename Value>
	class external_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, void>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		external_interval_correction() {}
		template<typename T>
		external_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		external_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~external_interval_correction() {}
		void operator()(value_type const& value) const {
			this->external(value);
		}
		template<typename T>
		void operator()(T const& value) const {
			this->external(value);
		}
	};
	//
	// get_internal_interval_correction
	//
	template<typename Value>
	class get_internal_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, Value>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		get_internal_interval_correction() {}
		template<typename T>
		get_internal_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		get_internal_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~get_internal_interval_correction() {}
		value_type operator()(value_type const& value) const {
			return this->get_internal(value);
		}
		template<typename T>
		T operator()(T const& value) const {
			return this->get_internal(value);
		}
	};
	//
	// get_external_interval_correction
	//
	template<typename Value>
	class get_external_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, Value>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		get_external_interval_correction() {}
		template<typename T>
		get_external_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		get_external_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~get_external_interval_correction() {}
		value_type operator()(value_type const& value) const {
			return this->get_external(value);
		}
		template<typename T>
		T operator()(T const& value) const {
			return this->get_external(value);
		}
	};
	//
	// is_internal_interval_correction
	//
	template<typename Value>
	class is_internal_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, bool>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		is_internal_interval_correction() {}
		template<typename T>
		is_internal_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		is_internal_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~is_internal_interval_correction() {}
		bool operator()(value_type const& value) const {
			return this->is_internal(value);
		}
		template<typename T>
		bool operator()(T const& value) const {
			return this->is_internal(value);
		}
	};
	//
	// is_external_interval_correction
	//
	template<typename Value>
	class is_external_interval_correction
		: public interval_correction<Value>
		, public std::unary_function<Value, bool>
	{
	public:
		typedef interval_correction<Value> base_type;
		typedef typename base_type::value_type value_type;
	public:
		is_external_interval_correction() {}
		template<typename T>
		is_external_interval_correction(T const& v)
			: base_type(v)
		{}
		template<typename Lower, typename Upper>
		is_external_interval_correction(Lower const& l, Upper const& u)
			: base_type(l, u)
		{}
		virtual ~is_external_interval_correction() {}
		bool operator()(value_type const& value) const {
			return this->is_external(value);
		}
		template<typename T>
		bool operator()(T const& value) const {
			return this->is_external(value);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CORRECTION_HPP
