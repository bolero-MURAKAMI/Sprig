#ifndef SPRIG_CAST_CONVERTER_HPP
#define SPRIG_CAST_CONVERTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	//
	// cast_converter
	//
	template<typename Tag, typename Value>
	class cast_converter {};
	//
	// make_cast_converter
	//
	template<typename Tag, typename Value>
	SPRIG_INLINE cast_converter<Tag, Value> make_cast_converter(Value& param) {
		return cast_converter<Tag, Value>(param);
	}
	template<typename Tag, typename Value>
	SPRIG_INLINE cast_converter<Tag, Value const> make_cast_converter(Value const& param) {
		return cast_converter<Tag, Value const>(param);
	}

	//
	// converter_cast
	//
	template<typename Tag, typename To, typename From>
	SPRIG_INLINE To converter_cast(From& from) {
		return make_cast_converter<Tag, From>(from);
	}
	template<typename Tag, typename To, typename From>
	SPRIG_INLINE To converter_cast(From const& from) {
		return make_cast_converter<Tag, From const>(from);
	}

	//
	// cast_convert
	//
	template<typename Tag, typename To>
	struct cast_convert {
		template<typename From>
		To operator()(From& from) const {
			return converter_cast<Tag, To>(from);
		}
		template<typename From>
		To operator()(From const& from) const {
			return converter_cast<Tag, To>(from);
		}
	};

	//
	// static_cast_converter_tag
	//
	struct static_cast_converter_tag {};
	//
	// specialization static_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<static_cast_converter_tag, Value> {
	public:
		typedef static_cast_converter_tag tag_type;
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
		operator T&() {
			return static_cast<T&>(param_);
		}
		template<typename T>
		operator T const&() {
			return static_cast<T const&>(param_);
		}
	};

	//
	// dynamic_cast_converter_tag
	//
	struct dynamic_cast_converter_tag {};
	//
	// specialization dynamic_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<dynamic_cast_converter_tag, Value> {
	public:
		typedef dynamic_cast_converter_tag tag_type;
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
		operator T&() {
			return dynamic_cast<T&>(param_);
		}
		template<typename T>
		operator T const&() {
			return dynamic_cast<T const&>(param_);
		}
	};

	//
	// const_cast_converter_tag
	//
	struct const_cast_converter_tag {};
	//
	// specialization const_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<const_cast_converter_tag, Value> {
	public:
		typedef const_cast_converter_tag tag_type;
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
		operator T&() {
			return const_cast<T&>(param_);
		}
		template<typename T>
		operator T const&() {
			return const_cast<T const&>(param_);
		}
	};

	//
	// reinterpret_cast_converter_tag
	//
	struct reinterpret_cast_converter_tag {};
	//
	// specialization reinterpret_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<reinterpret_cast_converter_tag, Value> {
	public:
		typedef reinterpret_cast_converter_tag tag_type;
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
		operator T&() {
			return reinterpret_cast<T&>(param_);
		}
		template<typename T>
		operator T const&() {
			return reinterpret_cast<T const&>(param_);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_CAST_CONVERTER_HPP
