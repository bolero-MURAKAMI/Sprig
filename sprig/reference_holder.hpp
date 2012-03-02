#ifndef SPRIG_REFERENCE_HOLDER_HPP
#define SPRIG_REFERENCE_HOLDER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/addressof.hpp>

namespace sprig {
	//
	// reference_holder
	//
	template<typename T>
	class reference_holder {
	public:
		typedef T type;
		typedef type& reference;
		typedef type const& const_reference;
		typedef type* pointer;
		typedef type const* const_pointer;
	private:
		pointer target_;
	public:
		reference_holder()
			: target_(0)
		{}
		reference_holder(reference target)
			: target_(boost::addressof(target))
		{}
		bool operator==(reference_holder const& rhs) const {
			return target_ == rhs.target_;
		}
		bool operator!=(reference_holder const& rhs) const {
			return target_ != rhs.target_;
		}
		operator reference() {
			return *target_;
		}
		operator const_reference() const {
			return *target_;
		}
		reference operator*() {
			return *target_;
		}
		const_reference operator*() const {
			return *target_;
		}
		pointer operator->() {
			return target_;
		}
		const_pointer operator->() const {
			return target_;
		}
		reference get() {
			return *target_;
		}
		const_reference get() const {
			return *target_;
		}
		pointer get_pointer() {
			return target_;
		}
		const_pointer get_pointer() const {
			return target_;
		}
		reference get_mutable() const {
			return *target_;
		}
		pointer get_mutable_pointer() const {
			return target_;
		}
		bool null() const {
			return target_;
		}
	};
	//
	// make_reference_holder
	//
	template<typename T>
	SPRIG_INLINE reference_holder<T> make_reference_holder(T& target)
	{
		return reference_holder<T>(target);
	}
	template<typename T>
	SPRIG_INLINE reference_holder<T const> make_reference_holder(T const& target)
	{
		return reference_holder<T const>(target);
	}
	//
	// make_const_reference_holder
	//
	template<typename T>
	SPRIG_INLINE reference_holder<T const> make_const_reference_holder(T const& target)
	{
		return reference_holder<T const>(target);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_REFERENCE_HOLDER_HPP
