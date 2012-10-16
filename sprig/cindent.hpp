#ifndef SPRIG_CINDENT_HPP
#define SPRIG_CINDENT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <iostream>
#include <boost/current_function.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>
#include <sprig/singleton.hpp>
#include <sprig/indentation.hpp>
#include <sprig/section.hpp>
#include <sprig/attributes.hpp>

//
// SPRIG_CINDENT_STRING_TYPE
//
#ifndef SPRIG_CINDENT_STRING_TYPE
#	define SPRIG_CINDENT_STRING_TYPE std::string
#endif	// #ifndef SPRIG_CINDENT_STRING_TYPE

namespace sprig {
	//
	// typedef
	//
	typedef SPRIG_CINDENT_STRING_TYPE cindent_string_type;
	//
	// cindentation
	//
	class cindentation
		: public faithful_indentation_sponsor<
			cindentation,
			basic_indentation<cindent_string_type>,
			std::basic_ostream<cindent_string_type::value_type, cindent_string_type::traits_type>
		>
	{};
	typedef basic_passive_faithful_indent<cindent_string_type, cindentation> cindent;
	typedef passive_faithful_indent_filter<cindentation> cindent_filter;
	//
	// icout_proxy
	//
	class icout_proxy
		: public sprig::singleton<icout_proxy>
	{
		SPRIG_FRIEND_SINGLETON(icout_proxy);
	private:
		boost::iostreams::filtering_ostream stream_;
	private:
		icout_proxy() {
			stream_.push(cindent_filter(stream_));
			stream_.push(std::cout);
		}
	public:
		cindentation::stream_type& get() {
			return stream_;
		}
	};

	//
	// icout
	//
	SPRIG_INLINE std::ostream& icout() {
		return icout_proxy::get_mutable_instance().get();
	}
	//
	// cout_some
	//
	SPRIG_INLINE void cout_some(
		basic_string_argument<cindent_string_type> const& arg
		)
	{
		icout() << arg;
	}
	//
	// cout_line
	//
	SPRIG_INLINE void cout_line(
		basic_string_argument<cindent_string_type> const& line
		)
	{
		icout() << line << std::endl;
	}
	//
	// cout_section_empty
	//
	SPRIG_INLINE void cout_section_empty(
		basic_string_argument<cindent_string_type> const& name
		)
	{
		icout() << basic_section_empty<cindent_string_type>(name) << std::endl;
	}
	SPRIG_INLINE void cout_section_empty(
		basic_string_argument<cindent_string_type> const& name,
		basic_attributes<cindent_string_type> const& attr
		)
	{
		icout() << basic_section_empty<cindent_string_type>(name, attr) << std::endl;
	}
	//
	// cout_section_line
	//
	SPRIG_INLINE void cout_section_line(
		basic_string_argument<cindent_string_type> const& name,
		basic_string_argument<cindent_string_type> const& contents
		)
	{
		icout() << basic_section_line<cindent_string_type>(name, contents) << std::endl;
	}
		SPRIG_INLINE void cout_section_line(
		basic_string_argument<cindent_string_type> const& name,
		basic_string_argument<cindent_string_type> const& contents,
		basic_attributes<cindent_string_type> const& attr
		)
	{
		icout() << basic_section_line<cindent_string_type>(name, contents, attr) << std::endl;
	}
	//
	// cout_section_comment
	//
	SPRIG_INLINE void cout_section_comment(basic_string_argument<cindent_string_type> const& comment) {
		icout() << basic_section_comment<cindent_string_type>(comment) << std::endl;
	}

	//
	// cindenter
	//
	class cindenter {
	private:
		class outputter {
		public:
			outputter() {
				icout() << std::flush;
			}
			~outputter() throw() {
				icout() << std::flush;
			}
		};
	private:
		outputter outputter_;
		cindent indent_;
	public:
		cindenter() {}
	};
	//
	// csection
	//
	class csection {
	private:
		class outputter {
			std::string name_;
		public:
			explicit outputter(basic_string_argument<cindent_string_type> const& name)
				: name_(name)
			{
				icout() << basic_section_begin<cindent_string_type>(name_) << std::endl;
			}
			outputter(basic_string_argument<cindent_string_type> const& name, basic_attributes<cindent_string_type> const& attr)
				: name_(name)
			{
				icout() << basic_section_begin<cindent_string_type>(name_, attr) << std::endl;
			}
			~outputter() throw() {
				icout() << basic_section_end<cindent_string_type>(name_) << std::endl;
			}
		};
	private:
		outputter outputter_;
		cindent indent_;
	public:
		explicit csection(basic_string_argument<cindent_string_type> const& name)
			: outputter_(name)
		{}
		csection(basic_string_argument<cindent_string_type> const& name, basic_attributes<cindent_string_type> const& attr)
			: outputter_(name, attr)
		{}
	};
	//
	// ccomment
	//
	class ccomment {
	private:
		class outputter {
			std::string name_;
		public:
			outputter() {
				icout() << basic_section_comment_begin<cindent_string_type>() << std::endl;
			}
			explicit outputter(basic_string_argument<cindent_string_type> const& name)
				: name_(name)
			{
				icout() << basic_section_comment_begin<cindent_string_type>() << name_ << std::endl;
			}
			~outputter() throw() {
				icout() << basic_section_comment_end<cindent_string_type>() << std::endl;
			}
		};
	private:
		outputter outputter_;
		cindent indent_;
	public:
		ccomment() {}
		explicit ccomment(basic_string_argument<cindent_string_type> const& name)
			: outputter_(name)
		{}
	};
} // namespace sprig

#endif	// #ifndef SPRIG_CINDENT_HPP
