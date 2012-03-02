#ifndef SPRIG_ATTRIBUTES_HPP
#define SPRIG_ATTRIBUTES_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <string>
#include <vector>
#include <boost/mpl/lambda.hpp>
#include <boost/foreach.hpp>
#include <sprig/split_literal.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>

namespace sprig {
	//
	// declares
	//
	template<typename T>
	class basic_attribute;
	template<typename T, typename ContainerF>
	class basic_attributes;

	//
	// basic_attribute
	//
	template<typename T>
	class basic_attribute {
	public:
		typedef T value_type;
	private:
		typedef basic_string_argument<value_type> string_argument_type;
	private:
		value_type name_;
		value_type value_;
	public:
		basic_attribute(
			string_argument_type const& name,
			string_argument_type const& value
			)
			: name_(name.get())
			, value_(value.get())
		{}
		value_type const& name() const {
			return name_;
		}
		value_type const& value() const {
			return value_;
		}
	};
	namespace attributes_detail {
		SPRIG_SPLIT_LITERAL_STRING_DECL(attr_begin, "=\"");
		SPRIG_SPLIT_LITERAL_STRING_DECL(attr_end, "\"");
	}	// namespace attributes_detail
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename Value>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_attribute<Value> const& rhs
		)
	{
		return lhs
			<< rhs.name()
			<< sprig::get_literal<attributes_detail::attr_begin, Elem>()
			<< rhs.value()
			<< sprig::get_literal<attributes_detail::attr_end, Elem>()
			;
	}
	//
	// attribute
	// wattribute
	//
	typedef basic_attribute<std::string> attribute;
	typedef basic_attribute<std::wstring> wattribute;
	//
	// make_attribute
	//
	template<typename T>
	SPRIG_INLINE basic_attribute<T> make_attribute(
		basic_string_argument<T> const& name,
		basic_string_argument<T> const& value
		)
	{
		return basic_attribute<T>(name, value);
	}

	//
	// basic_attributes
	//
	template<typename T, typename ContainerF = boost::mpl::lambda<std::vector<boost::mpl::_1> >::type>
	class basic_attributes {
	public:
		typedef T value_type;
		typedef basic_attribute<value_type> attribute_type;
		typedef typename ContainerF::template apply<attribute_type>::type container_type;
		typedef typename value_type::value_type char_type;
	private:
		typedef basic_string_argument<value_type> string_argument_type;
	private:
		SPRIG_SPLIT_LITERAL_STRING_DECL(space_delim, " ");
	private:
		value_type delim_;
		container_type container_;
	public:
		basic_attributes()
			: container_()
			, delim_(sprig::get_literal<space_delim, char_type>())
		{}
		basic_attributes(attribute_type const& attr)
			: container_(1, attr)
			, delim_(sprig::get_literal<space_delim, char_type>())
		{}
		basic_attributes(
			string_argument_type const& name,
			string_argument_type const& value
			)
			: container_(1, attribute_type(name, value))
			, delim_(sprig::get_literal<space_delim, char_type>())
		{}
		explicit basic_attributes(string_argument_type const& delim)
			: container_()
			, delim_(delim.get())
		{}
		basic_attributes(
			string_argument_type const& delim,
			attribute_type const& attr
			)
			: container_(1, attr)
			, delim_(delim.get())
		{}
		basic_attributes(
			string_argument_type const& delim,
			string_argument_type const& name,
			string_argument_type const& value
			)
			: container_(1, attribute_type(name, value))
			, delim_(delim.get())
		{}
		container_type const& container() const {
			return container_;
		}
		value_type const& delim() const {
			return delim_;
		}
		void set_delim(string_argument_type const& delim) {
			delim_ = delim.get();
		}
		void push_back(attribute_type const& attr) {
			container_.push_back(attr);
		}
		void push_back(
			string_argument_type const& name,
			string_argument_type const& value
			)
		{
			container_.push_back(attribute_type(name, value));
		}
		basic_attributes& operator()(string_argument_type const& delim) {
			set_delim(delim);
			return *this;
		}
		basic_attributes& operator()(attribute_type const& attr) {
			push_back(attr);
			return *this;
		}
		basic_attributes& operator()(
			string_argument_type const& name,
			string_argument_type const& value
			)
		{
			push_back(name, value);
			return *this;
		}
	};
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename Value, typename ContainerF>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_attributes<Value, ContainerF> const& rhs
		)
	{
		typedef basic_attributes<Value, ContainerF> attributes_type;
		typedef typename attributes_type::container_type container_type;
		typedef typename attributes_type::value_type string_type;
		typedef typename container_type::const_iterator iterator;
		string_type const& delim = rhs.delim();
		BOOST_FOREACH(typename container_type::value_type const& e, rhs.container()) {
			lhs << delim << e;
		}
		return lhs;
	}
	//
	// attributes
	// wattributes
	//
	typedef basic_attributes<std::string> attributes;
	typedef basic_attributes<std::wstring> wattributes;
	//
	// make_attributes
	//
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes() {
		return basic_attributes<T>();
	}
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes(
		basic_attribute<T> const& attr
		)
	{
		return basic_attributes<T>(attr);
	}
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes(
		basic_string_argument<T> const& name,
		basic_string_argument<T> const& value
		)
	{
		return basic_attributes<T>(name, value);
	}
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes(
		basic_string_argument<T> const& delim
		)
	{
		return basic_attributes<T>(delim);
	}
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes(
		basic_string_argument<T> const& delim,
		basic_attribute<T> const& attr
		)
	{
		return basic_attributes<T>(delim, attr);
	}
	template<typename T>
	SPRIG_INLINE basic_attributes<T> make_attributes(
		basic_string_argument<T> const& delim,
		basic_string_argument<T> const& name,
		basic_string_argument<T> const& value
		)
	{
		return basic_attributes<T>(delim, name, value);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ATTRIBUTES_HPP
