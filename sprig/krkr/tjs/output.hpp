/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_KRKR_TJS_OUTPUT_HPP
#define SPRIG_KRKR_TJS_OUTPUT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/singleton.hpp>
#include <sprig/indentation.hpp>
#include <sprig/section.hpp>
#include <sprig/indent_logger.hpp>
#include <sprig/krkr/tjs/typedef.hpp>
#include <sprig/krkr/macro/text.hpp>

namespace sprig {
	namespace krkr {
		namespace tjs {
			//
			// outputter
			//
			struct outputter {
				void operator()(string_argument_type const& arg) const {
					::TVPAddLog(arg.get().c_str());
				}
			};
			//
			// logger_tag, indent_logger_type
			//
			struct logger_tag {};
			typedef sprig::basic_indent_logger<string_type, logger_tag> indent_logger_type;
			//
			// indent_logger_proxy
			//
			class indent_logger_proxy
				: public sprig::singleton<indent_logger_proxy>
			{
				SPRIG_FRIEND_SINGLETON(indent_logger_proxy);
			private:
				indent_logger_type indent_logger_;
				boost::scoped_ptr<indent_logger_type::indent> prefix_;
			private:
				indent_logger_proxy() {
					indent_logger_.push(outputter());
					prefix_.reset(
						new indent_logger_type::indent(
							sprig::basic_section_comment<string_type>(TJS_W("KTL"))
							)
						);
				}
			public:
				indent_logger_type& get() {
					return indent_logger_;
				}
			};

			//
			// indent_logger
			//
			SPRIG_INLINE indent_logger_type& indent_logger() {
				return indent_logger_proxy::get_mutable_instance().get();
			}
			//
			// output
			//
			SPRIG_INLINE void output(string_argument_type const& message) {
				sprig::logger_output_line(message, indent_logger());
			}
			//
			// output_value
			//
			SPRIG_INLINE void output_value(string_argument_type const& name, string_argument_type const& contents) {
				sprig::logger_section_line(name, contents, indent_logger());
			}
			//
			// output_comment
			//
			SPRIG_INLINE void output_comment(string_argument_type const& comment) {
				sprig::logger_section_comment(comment, indent_logger());
			}

			//
			// section
			//
			class section
				: boost::noncopyable
			{
			private:
				sprig::logger_section<indent_logger_type> section_;
			public:
				explicit section(string_argument_type const& name)
					: section_(name, indent_logger())
				{}
				explicit section(
					string_argument_type const& name,
					string_argument_type const& tab
					)
					: section_(name, indent_logger(), tab)
				{}
			};

			//
			// local_logger_tag, local_logger_type
			//
			struct local_logger_tag {};
			typedef sprig::local_logger<string_type, local_logger_tag> local_logger_type;
		}	// namespace tjs
	}	// namespace krkr
}	// namespace sprig

#endif	// #ifndef SPRIG_KRKR_TJS_OUTPUT_HPP
