#ifndef SPRIG_NULL_PTR_HPP
#define SPRIG_NULL_PTR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>

namespace sprig {
	//
	// null_ptr_t
	//
	class null_ptr_t {
	public:
		template<typename T>
		operator T*() const {
			return 0;
		}
		template<typename Class, typename T>
		operator T Class::*() const {
			return 0;
		}
	private:
		void operator&() const;
	};
	template<typename Elem, typename Traits>
	std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		null_ptr_t const rhs
		)
	{
		return lhs << static_cast<void*>(rhs);
	}
	//
	// null_ptr
	//
	static null_ptr_t const null_ptr = null_ptr_t();
}	// namespace sprig

#endif	// #ifndef SPRIG_NULL_PTR_HPP
