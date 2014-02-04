/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_INDENTATION_FAITHFUL_HPP
#define SPRIG_INDENTATION_FAITHFUL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/ref.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/utility/base_from_member.hpp>
#include <sprig/singleton.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/reference_holder.hpp>
#include <sprig/indentation/foundation.hpp>
#include <sprig/indentation/passive.hpp>

namespace sprig {
	//
	// indentation_flush_agent
	//
	template<typename Sponsor>
	class indentation_flush_agent {
	public:
		typedef Sponsor sponsor_type;
	public:
		indentation_flush_agent() {
			sponsor_type::flush();
		}
		~indentation_flush_agent() throw() {
			sponsor_type::flush();
		}
	};
	//
	// indentation_element_agent
	//
	template<typename Sponsor>
	class indentation_element_agent {
	public:
		typedef Sponsor sponsor_type;
		typedef typename sponsor_type::stream_type stream_type;
	private:
		typedef reference_holder<stream_type> stream_reference_type;
	private:
		stream_reference_type stream_;
	public:
		explicit indentation_element_agent(stream_type& stream)
			: stream_(stream)
		{
			sponsor_type::push_stream(stream_);
		}
		~indentation_element_agent() throw() {
			sponsor_type::pop_stream(stream_);
		}
	};
	//
	// basic_passive_faithful_indent
	//
	template<typename Value, typename Sponsor>
	class basic_passive_faithful_indent
		: private boost::base_from_member<boost::shared_ptr<indentation_flush_agent<Sponsor> > >
		, public basic_passive_indent<Value, Sponsor>
	{
	private:
		typedef basic_passive_indent<Value, Sponsor> basic_passive_indent_type;
	public:
		typedef typename basic_passive_indent_type::sponsor_type sponsor_type;
		typedef typename basic_passive_indent_type::value_type value_type;
		typedef indentation_flush_agent<sponsor_type> flush_agent_type;
	private:
		typedef boost::shared_ptr<flush_agent_type> flush_agent_instance_type;
		typedef boost::base_from_member<flush_agent_instance_type> flush_agent_instance_member_type;
	private:
		static flush_agent_instance_type create_flush_agent() {
			return flush_agent_instance_type(boost::make_shared<flush_agent_type>());
		}
	public:
		basic_passive_faithful_indent()
			: flush_agent_instance_member_type(create_flush_agent())
			, basic_passive_indent_type()
		{}
		explicit basic_passive_faithful_indent(basic_string_argument<value_type> const& tab)
			: flush_agent_instance_member_type(create_flush_agent())
			, basic_passive_indent_type(tab)
		{}
		~basic_passive_faithful_indent() throw() {
			flush_agent_instance_member_type::member.reset();
		}
	};
	template<typename Sponsor>
	struct passive_faithful_indent {
		typedef basic_passive_faithful_indent<std::string, Sponsor> type;
	};
	template<typename Sponsor>
	struct passive_stream_windent {
		typedef basic_passive_faithful_indent<std::wstring, Sponsor> type;
	};
	//
	// passive_faithful_indent_filter
	//
	template<typename Sponsor>
	class passive_faithful_indent_filter
		: public passive_indent_filter<Sponsor>
	{
	private:
		typedef passive_indent_filter<Sponsor> passive_indent_filter_type;
	public:
		typedef typename passive_indent_filter_type::sponsor_type sponsor_type;
		typedef typename sponsor_type::stream_type stream_type;
	public:
		typedef indentation_element_agent<sponsor_type> element_agent_type;
	private:
		typedef boost::shared_ptr<element_agent_type> element_agent_instance_type;
	private:
		element_agent_instance_type element_agent_;
	private:
		static element_agent_instance_type create_element_agent(stream_type& stream) {
			return boost::make_shared<element_agent_type>(boost::ref(stream));
		}
	public:
		explicit passive_faithful_indent_filter(stream_type& stream)
			: element_agent_(create_element_agent(stream))
		{}
	};
	//
	// faithful_indentation_sponsor
	//
	template<typename Tag, typename Indentation, typename Stream>
	class faithful_indentation_sponsor
		: public indentation_sponsor<Tag, Indentation>
	{
	public:
		typedef Stream stream_type;
	private:
		typedef reference_holder<stream_type> stream_reference_type;
		typedef std::vector<stream_reference_type> stream_container_type;
	private:
		class stream_container_proxy
			: public sprig::singleton<stream_container_proxy>
		{
			SPRIG_FRIEND_SINGLETON(stream_container_proxy);
		private:
			stream_container_type stream_container_;
		private:
			stream_container_proxy() {}
		public:
			stream_container_type& get() {
				return stream_container_;
			}
		};
		class flusher {
		public:
			void operator()(stream_reference_type stream) const {
				*stream << std::flush;
			}
		};
	public:
		static void flush() {
			std::for_each(
				stream_container_proxy::get_mutable_instance().get().begin(),
				stream_container_proxy::get_mutable_instance().get().end(),
				flusher()
				);
		}
		static void push_stream(stream_reference_type stream) {
			stream_container_proxy::get_mutable_instance().get().push_back(stream);
		}
		static void pop_stream(stream_reference_type stream) {
			typename stream_container_type::iterator target = std::find(
				stream_container_proxy::get_mutable_instance().get().begin(),
				stream_container_proxy::get_mutable_instance().get().end(),
				stream
				);
			stream_container_proxy::get_mutable_instance().get().erase(target);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_INDENTATION_FAITHFUL_HPP
