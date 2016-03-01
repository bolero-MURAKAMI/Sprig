/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_INDENTATION_UTILITY_HPP
#define SPRIG_INDENTATION_UTILITY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/noncopyable.hpp>
#include <sprig/indentation/foundation.hpp>

namespace sprig {
	//
	// indentation_default_saver
	//
	template<typename Value>
	class indentation_default_saver
		: boost::noncopyable
	{
	public:
		typedef Value value_type;
		typedef basic_indentation<value_type> indentation_type;
	private:
		indentation_type& indentation_;
		value_type value_;
	public:
		explicit indentation_default_saver(indentation_type& indentation)
			: indentation_(indentation)
			, value_(indentation_.get_default())
		{}
		~indentation_default_saver() throw() {
			indentation_.set_default(value_);
		}
		indentation_type& get_indentation() {
			return indentation_;
		}
		value_type const& get_default() const {
			return value_;
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_INDENTATION_UTILITY_HPP
