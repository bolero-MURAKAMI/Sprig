/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TRANSFER_HPP
#define SPRIG_TRANSFER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <boost/call_traits.hpp>

namespace sprig {
	//
	// transfer
	//
	template<typename T, typename Trans>
	class transfer {
	public:
		typedef T value_type;
		typedef Trans trans_type;
	private:
		value_type value_;
	public:
		transfer()
			: value_()
		{}
		explicit transfer(typename boost::call_traits<value_type>::param_type value)
			: value_(value)
		{}
		operator value_type const&() const {
			return value_;
		}
		operator value_type&() {
			return value_;
		}
		template<typename Elem, typename Traits>
		std::basic_ostream<Elem, Traits>& out(
			std::basic_ostream<Elem, Traits>& os
			) const
		{
			return os << static_cast<trans_type>(value_);
		}
		template<typename Elem, typename Traits>
		std::basic_istream<Elem, Traits>& in(
			std::basic_istream<Elem, Traits>& is
			)
		{
			trans_type trans;
			is >> trans;
			value_ = static_cast<value_type>(trans);
			return is;
		}
	};
	template<typename T, typename Trans, typename Elem, typename Traits>
	std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		transfer<T, Trans> const& rhs
		)
	{
		return rhs.out(lhs);
	}
	template<typename T, typename Trans, typename Elem, typename Traits>
	std::basic_istream<Elem, Traits>& operator>>(
		std::basic_istream<Elem, Traits>& lhs,
		transfer<T, Trans>& rhs
		)
	{
		return rhs.in(lhs);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_TRANSFER_HPP
