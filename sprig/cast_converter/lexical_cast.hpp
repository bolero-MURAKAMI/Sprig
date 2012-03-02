#ifndef SPRIG_CAST_CONVERTER_LEXICAL_CAST_HPP
#define SPRIG_CAST_CONVERTER_LEXICAL_CAST_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/lexical_cast.hpp>
#include <sprig/cast_converter.hpp>

namespace sprig {
	//
	// lexical_cast_converter_tag
	//
	struct lexical_cast_converter_tag {};
	//
	// specialization lexical_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<lexical_cast_converter_tag, Value> {
	public:
		typedef lexical_cast_converter_tag tag_type;
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
			return boost::lexical_cast<T>(param_);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CAST_CONVERTER_LEXICAL_CAST_HPP
