/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_INDENTATION_PASSIVE_HPP
#define SPRIG_INDENTATION_PASSIVE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <sprig/singleton.hpp>
#include <sprig/indentation/foundation.hpp>

namespace sprig {
	//
	// basic_passive_indent
	//
	template<typename Value, typename Sponsor>
	class basic_passive_indent
		: public basic_indent<Value>
	{
	public:
		typedef Sponsor sponsor_type;
	private:
		typedef basic_indent<Value> basic_indent_type;
	public:
		typedef typename basic_indent_type::value_type value_type;
	public:
		basic_passive_indent()
			: basic_indent_type(sponsor_type()())
		{}
		explicit basic_passive_indent(basic_string_argument<value_type> const& tab)
			: basic_indent_type(sponsor_type()(), tab)
		{}
	};
	template<typename Sponsor>
	struct passive_indent {
		typedef basic_passive_indent<std::string, Sponsor> type;
	};
	template<typename Sponsor>
	struct passive_windent {
		typedef basic_passive_indent<std::wstring, Sponsor> type;
	};
	//
	// passive_indent_filter
	//
	template<typename Sponsor>
	class passive_indent_filter
		: public indent_filter<typename Sponsor::indentation_type>
	{
	public:
		typedef Sponsor sponsor_type;
	private:
		typedef indent_filter<typename Sponsor::indentation_type> indent_filter_type;
	public:
		passive_indent_filter()
			: indent_filter_type(sponsor_type()())
		{}
	};
	//
	// indentation_sponsor
	//
	template<typename Tag, typename Indentation>
	class indentation_sponsor {
	public:
		typedef Tag tag_type;
		typedef Indentation indentation_type;
		typedef typename indentation_type::value_type value_type;
		typedef typename indentation_type::depth_type depth_type;
	private:
		class indentation_proxy
			: public sprig::singleton<indentation_proxy>
		{
			SPRIG_FRIEND_SINGLETON(indentation_proxy);
		private:
			indentation_type indentation_;
		private:
			indentation_proxy() {}
		public:
			indentation_type& get() {
				return indentation_;
			}
		};
	public:
		static indentation_type& indentation() {
			return indentation_proxy::get_mutable_instance().get();
		}
		static value_type const& get() {
			return indentation_proxy::get_mutable_instance().get().get();
		}
		static value_type const& get_default() {
			return indentation_proxy::get_mutable_instance().get().get_default();
		}
		static void set_default(basic_string_argument<value_type> const& tab) {
			indentation_proxy::get_mutable_instance().get().set_default();
		}
		static depth_type depth() {
			return indentation_proxy::get_mutable_instance().get().depth();
		}
	public:
		indentation_type& operator()() {
			return indentation_proxy::get_mutable_instance().get();
		}
		operator indentation_type&() {
			return indentation_proxy::get_mutable_instance().get();
		}
	};
	template<typename Elem, typename Traits, typename Indentation, typename Tag>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		indentation_sponsor<Tag, Indentation> const& rhs)
	{
		return lhs << rhs();
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_INDENTATION_PASSIVE_HPP
