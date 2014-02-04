/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UTILITY_UTILITY_HPP
#define SPRIG_UTILITY_UTILITY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/next_prior.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	//
	// back
	//
	template<typename Iterator>
	SPRIG_INLINE Iterator back(Iterator first, Iterator last) {
		Iterator result = first;
		for (; boost::next(result) != last; ++result)
			;
		return result;
	}
	//
	// raise_up
	//
	SPRIG_EXCEPTION_DECL(bad_raise_up);
	template<unsigned N, typename T>
	SPRIG_INLINE T raise_up(T const value) {
		T result(N);
		if (value <= 0)
			throw bad_raise_up("’l‚ª0ˆÈ‰º‚Å‚·");
		for (; result < value; result *= N)
			;
		return result;
	}
	//
	// multipries
	//
	template<typename T, typename unitT>
	SPRIG_INLINE T multipries(unitT const& unit, std::size_t size) {
		T result;
		for (std::size_t i = 0; i != size; ++i)
			result += unit;
		return result;
	}
	//
	// do_nothing
	//
	struct do_nothing {
		void operator()() const {}
		template<typename T>
		void operator()(T const&) const {}
	};
	//
	// unconditional
	//
	template<bool N>
	struct unconditional {
		bool operator()() const {return N;}
		template<typename T>
		void operator()(T const&) const {return N;}
		template<typename T>
		void operator()(T const&, T const&) const {return N;}
	};
	//
	// execute
	//
	struct execute {
		template<typename T>
		void operator()(T const& func) const {
			func();
		}
	};
	//
	// empty_class
	//
	class empty_class {};
	//
	// empty_class_type_to
	//
	template<typename T>
	class empty_class_type_to {};
	//
	// empty_class_enum
	//
	template<int N>
	class empty_class_enum {};
} // namespace sprig

#endif	// #ifndef SPRIG_UTILITY_UTILITY_HPP
