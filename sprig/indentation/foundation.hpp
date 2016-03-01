/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_INDENTATION_FOUNDATION_HPP
#define SPRIG_INDENTATION_FOUNDATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/ref.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/flush.hpp>
#include <boost/iostreams/put.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/reference_holder.hpp>
#include <sprig/split_literal.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>

namespace sprig {
	//
	// basic_indent
	//
	template<typename Value>
	class basic_indent;
	//
	// basic_indentation
	//
	template<typename Value>
	class basic_indentation {
		friend class basic_indent<Value>;
	public:
		typedef Value value_type;
		typedef typename value_type::value_type char_type;
	private:
		typedef std::vector<value_type> container_type;
		typedef typename container_type::const_iterator const_iterator;
		typedef typename container_type::iterator iterator;
	public:
		typedef typename container_type::size_type depth_type;
	private:
		SPRIG_SPLIT_LITERAL_STRING_DECL(default_tab_literal, "    ");
	private:
		container_type container_;
		value_type default_tab_;
		mutable bool cached_;
		mutable value_type cache_;
	public:
		basic_indentation()
			: default_tab_(sprig::get_literal<default_tab_literal, char_type>())
			, cached_(false)
		{}
		explicit basic_indentation(basic_string_argument<value_type> const& default_tab)
			: default_tab_(default_tab.get())
			, cached_(false)
		{}
		value_type const& get() const {
			if (cached_)
				return cache_;
			cache_ = value_type();
			BOOST_FOREACH(value_type const& e, container_) {
				cache_ += e;
			}
			cached_ = true;
			return cache_;
		}
		value_type const& get_default() const {
			return default_tab_;
		}
		void set_default(basic_string_argument<value_type> const& tab) {
			default_tab_ = tab;
		}
		depth_type depth() const {
			return container_.size();
		}
		void push() {
			container_.push_back(default_tab_);
			cached_ = false;
		}
		void push(basic_string_argument<value_type> const& tab) {
			container_.push_back(tab.get());
			cached_ = false;
		}
		void pop() {
			container_.pop_back();
			cached_ = false;
		}
	};
	template<typename Elem, typename Traits, typename Value>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_indentation<Value> const& rhs)
	{
		return lhs << str_cast<std::basic_string<Elem, Traits> >(rhs.get());
	}
	//
	// indentation
	// windentation
	//
	typedef basic_indentation<std::string> indentation;
	typedef basic_indentation<std::wstring> windentation;
	//
	// basic_indent
	//
	template<typename Value>
	class basic_indent {
	public:
		typedef Value value_type;
		typedef basic_indentation<value_type> indentation_type;
		typedef typename indentation_type::depth_type depth_type;
	private:
		class indent_executor {
		private:
			reference_holder<indentation_type> indentation_;
		public:
			explicit indent_executor(indentation_type& indentation)
				: indentation_(indentation)
			{
				indentation_->push();
			}
			indent_executor(
				indentation_type& indentation,
				basic_string_argument<value_type> const& tab
				)
				: indentation_(indentation)
			{
				indentation_->push(tab);
			}
			~indent_executor() throw() {
				indentation_->pop();
			}
			indentation_type& indentation() {
				return *indentation_;
			}
			depth_type depth() const {
				return indentation_->depth();
			}
	};
	private:
		boost::shared_ptr<indent_executor> indent_executor_;
	public:
		explicit basic_indent(indentation_type& indentation)
			: indent_executor_(boost::make_shared<indent_executor>(boost::ref(indentation)))
		{}
		basic_indent(
			indentation_type& indentation,
			basic_string_argument<value_type> const& tab
			)
			: indent_executor_(boost::make_shared<indent_executor>(boost::ref(indentation), tab))
		{}
		indentation_type& indentation() {
			return indent_executor_->indentation();
		}
		depth_type depth() const {
			return indent_executor_->depth();
		}
	};
	//
	// indent
	// windent
	//
	typedef basic_indent<std::string> indent;
	typedef basic_indent<std::wstring> windent;
	//
	// indent_filter
	//
	template<typename Indentation>
	class indent_filter {
	public:
		typedef typename Indentation::char_type char_type;
		struct category
			: public boost::iostreams::output_filter_tag
			, public boost::iostreams::closable_tag
			, public boost::iostreams::flushable_tag
		{};
	public:
		typedef Indentation indentation_type;
		typedef typename indentation_type::value_type::value_type line_feed_char_type;
	private:
		BOOST_MPL_ASSERT((
			boost::mpl::or_<
				typename sprig::is_char_type<line_feed_char_type>::type,
				typename sprig::is_wchar_type<line_feed_char_type>::type
			>
			));
	private:
		SPRIG_SPLIT_LITERAL_CHAR_DECL(line_feed, '\n');
	private:
		reference_holder<indentation_type> indentation_;
		bool line_feeded_;
	public:
		explicit indent_filter(indentation_type& indentation)
			: indentation_(indentation)
			, line_feeded_(true)
		{}
		template<typename Sink>
		bool put(Sink& sink, typename boost::iostreams::char_type_of<Sink>::type c) {
			typedef typename boost::iostreams::char_type_of<Sink>::type c_type;
			if (line_feeded_) {
				line_feeded_ = false;
				BOOST_FOREACH(typename indentation_type::value_type::value_type e, indentation_->get()) {
					if (!boost::iostreams::put(sink, e)) {
						return false;
					}
				}
			}
			if (c == line_feed::template apply<c_type>::value) {
				line_feeded_ = true;
			}
			return boost::iostreams::put(sink, c);
		}
		template<typename Sink>
		void close(Sink&) {}
		template<typename Sink>
		bool flush(Sink& sink) {
			return boost::iostreams::flush(sink);
		}
	};
	template<typename Indentation>
	SPRIG_INLINE indent_filter<Indentation> make_indent_filter(Indentation& indentation) {
		return indent_filter<Indentation>(indentation);
	}
	//
	// basic_indents
	//
	template<typename Value>
	class basic_indents {
	public:
		typedef Value value_type;
		typedef typename value_type::value_type char_type;
		typedef basic_indentation<value_type> indentation_type;
		typedef basic_indent<value_type> indent_type;
		typedef indent_filter<indentation_type> indent_filter_type;
	private:
		indentation_type indentation_;
	public:
		basic_indents() {}
		explicit basic_indents(basic_string_argument<value_type> const& default_tab)
			: indentation_(default_tab)
		{}
		indentation_type& indentation() {
			return indentation_;
		}
		indent_type indent() {
			return indent_type(indentation_);
		}
		indent_type indent(basic_string_argument<value_type> const& tab) {
			return indent_type(indentation_, tab);
		}
		indent_filter_type indent_filter() {
			return indent_filter_type(indentation_);
		}
	};
	//
	// indents
	// windents
	//
	typedef basic_indents<std::string> indents;
	typedef basic_indents<std::wstring> windents;
}	// namespace sprig

#endif	// #ifndef SPRIG_INDENTATION_FOUNDATION_HPP
