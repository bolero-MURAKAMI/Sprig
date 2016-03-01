/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_RANGE_DISPLAY_RANGE_HPP
#define SPRIG_RANGE_DISPLAY_RANGE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/range/iterator_range.hpp>

namespace sprig {
	//
	// display_range
	//
	template<typename Container>
	class display_range {
	public:
		typedef Container container_type;
		typedef typename container_type::iterator iterator;
		typedef typename container_type::const_iterator const_iterator;
	private:
		container_type container_;
	public:
		template<typename Range>
		display_range(Range const& range)
			: container_(boost::begin(range), boost::end(range))
		{}
		iterator begin() {
			return container_.begin();
		}
		iterator end() {
			return container_.end();
		}
		const_iterator begin() const {
			return container_.begin();
		}
		const_iterator end() const {
			return container_.end();
		}
		boost::iterator_range<iterator> range() {
			return boost::iterator_range<iterator>(begin(), end());
		}
		boost::iterator_range<const_iterator> range() const {
			return boost::iterator_range<const_iterator>(begin(), end());
		}
	};
	template<typename Elem, typename Traits, typename Container>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		display_range<Container> const& rhs
		)
	{
		return lhs << rhs.range();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_RANGE_DISPLAY_RANGE_HPP
