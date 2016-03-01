/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_CAST_CONVERTER_STR_CAST_HPP
#define SPRIG_CAST_CONVERTER_STR_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/str_cast.hpp>
#include <sprig/cast_converter.hpp>

namespace sprig {
	//
	// str_cast_converter_tag
	//
	struct str_cast_converter_tag {};
	//
	// specialization str_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<str_cast_converter_tag, Value> {
	public:
		typedef str_cast_converter_tag tag_type;
		typedef Value value_type;
		typedef value_type& param_type;
	private:
		param_type param_;
	private:
		cast_converter();
	public:
		cast_converter(param_type param)
			: param_(param)
		{}
		template<typename T>
		operator T() {
			return str_cast<T>(param_);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CAST_CONVERTER_STR_CAST_HPP
