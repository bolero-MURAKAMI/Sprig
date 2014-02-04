/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NTL_ERROR_HPP
#define SPRIG_NTL_ERROR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <sprig/singleton.hpp>
#include <sprig/external/ntl/tools.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	namespace ntl {
		//
		// internal_error
		//
		SPRIG_EXCEPTION_DECL(internal_error);

		//
		// error_handling
		//
		class error_handling {
		public:
			typedef void (callback_signature_type)();
			typedef boost::function<callback_signature_type> callback_type;
		private:
			typedef std::vector<callback_type> callbacks_type;
		public:
			//
			// error_callback_throw
			//
			struct error_callback_throw {
			public:
				void operator()() const {
					SPRIG_THROW_EXCEPTION(internal_error("NTL internal error"));
				}
			};
		private:
			class proxy
				: public sprig::singleton<proxy>
			{
				SPRIG_FRIEND_SINGLETON(proxy);
			private:
				callbacks_type callbacks_;
				callback_type exit_callback_;
				callback_signature_type* backup_;
			private:
				proxy() {}
			public:
				callbacks_type& callbacks() {
					return callbacks_;
				}
				callback_type& exit_callback() {
					return exit_callback_;
				}
				callback_signature_type*& backup() {
					return backup_;
				}
			};
		public:
			static void error_callback() {
				BOOST_FOREACH(callback_type const& callback, proxy::get_mutable_instance().callbacks()) {
					callback();
				}
				if (proxy::get_mutable_instance().exit_callback()) {
					proxy::get_mutable_instance().exit_callback()();
				} else {
					error_callback_throw()();
				}
			}
		public:
			static void enable() {
				proxy::get_mutable_instance().backup() = NTL::ErrorCallback;
				NTL::ErrorCallback = &error_callback;
			}
			static void disable() {
				if (NTL::ErrorCallback == &error_callback) {
					NTL::ErrorCallback = proxy::get_mutable_instance().backup();
				}
			}
			static void regist_callback(callback_type const& callback) {
				proxy::get_mutable_instance().callbacks().push_back(callback);
			}
		};
	}	// namespace ntl
}	// namespace sprig

#endif	// #ifndef SPRIG_NTL_ERROR_HPP
