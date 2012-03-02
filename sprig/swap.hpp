#ifndef SPRIG_SWAP_HPP
#define SPRIG_SWAP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <functional>
#include <boost/utility/swap.hpp>

namespace sprig {
	//
	// swap_
	//
	template<typename T1, typename T2 = T1>
	struct swap_
		: public std::binary_function<T1, T2, void>
	{
	public:
		typedef std::binary_function<T1, T2, void> function_type;
		typedef typename function_type::first_argument_type first_argument_type;
		typedef typename function_type::second_argument_type second_argument_type;
		typedef typename function_type::result_type result_type;
	public:
		result_type operator()(
			first_argument_type& lhs,
			second_argument_type& rhs
			) const
		{
			boost::swap(lhs, rhs);
		}
	};
	//
	// any_swap_
	//
	struct any_swap_ {
		template<typename T1, typename T2>
		void operator()(T1& lhs, T2& rhs) const {
			boost::swap(lhs, rhs);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_SWAP_HPP
