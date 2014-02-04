/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_INFO_HOLDER_HPP
#define SPRIG_TYPE_INFO_HOLDER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <typeinfo>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/utility/swap.hpp>

namespace sprig {
	//
	// type_info_holder
	//
	class type_info_holder {
	private:
		struct proxy {
			std::type_info const& info;
		public:
			proxy(std::type_info const& info)
				: info(info)
			{}
		};
	private:
		boost::shared_ptr<proxy> info_;
	public:
		type_info_holder(type_info_holder const& that)
			: info_(boost::make_shared<proxy>(that.get()))
		{}
		type_info_holder(std::type_info const& info)
			: info_(boost::make_shared<proxy>(info))
		{}
		type_info_holder& operator=(type_info_holder rhs) {
			swap(rhs);
			return *this;
		}
		bool operator==(type_info_holder const& rhs) {
			return get() == rhs.get();
		}
		bool operator==(std::type_info const& rhs) {
			return get() == rhs;
		}
		bool operator!=(type_info_holder const& rhs) {
			return get() != rhs.get();
		}
		bool operator!=(std::type_info const& rhs) {
			return get() != rhs;
		}
		int before(type_info_holder const& that) const {
			return get().before(that.get());
		}
		int before(std::type_info const& info) const {
			return get().before(info);
		}
		char const* name() const {
			return get().name();
		}
		void swap(type_info_holder& rhs) {
			boost::swap(info_, rhs.info_);
		}
		std::type_info const& get() const {
			return info_->info;
		}
		void reset(std::type_info const& info) {
			type_info_holder rhs(info);
			swap(rhs);
		}
		operator std::type_info const&() const {
			return get();
		}
	};
	//
	// make_type_info_holder
	//
	template<typename T>
	SPRIG_INLINE type_info_holder make_type_info_holder() {
		return type_info_holder(typeid(T));
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_TYPE_INFO_HOLDER_HPP
