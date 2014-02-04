/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_WIN32_HPP
#define SPRIG_WIN32_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <sprig/external/windows.hpp>

namespace sprig {
	namespace win32 {
		//
		// scoped_paint
		//
		class scoped_paint {
		public:
			typedef HDC handle_type;
			typedef boost::remove_pointer<handle_type>::type target_type;
		private:
			class deleter {
			private:
				HWND const hwnd_;
				PAINTSTRUCT const* const ps_;
			public:
				deleter(
					HWND hwnd,
					PAINTSTRUCT const* ps
					)
					: hwnd_(hwnd)
					, ps_(ps)
				{}
				void operator()(handle_type handle) const {
					::ReleaseDC(hwnd_, handle);
					::EndPaint(hwnd_, ps_);
				}
			};
		private:
			boost::shared_ptr<target_type> handle_;
		public:
			scoped_paint(
				HWND hwnd,
				PAINTSTRUCT* ps
				)
				: handle_(
					::BeginPaint(hwnd, ps),
					deleter(hwnd, ps)
					)
			{}
			handle_type get() const {
				return handle_.get();
			}
			operator bool() const {
				return handle_;
			}
			operator handle_type() const {
				return get();
			}
		};
		//
		// scoped_compatible_dc
		//
		class scoped_compatible_dc {
		public:
			typedef HDC handle_type;
			typedef boost::remove_pointer<handle_type>::type target_type;
		private:
			class deleter {
			public:
				deleter() {}
				void operator()(handle_type handle) const {
					::DeleteDC(handle);
				}
			};
		private:
			boost::shared_ptr<target_type> handle_;
		public:
			scoped_compatible_dc(
				HDC hdc
				)
				: handle_(
					::CreateCompatibleDC(hdc),
					deleter()
					)
			{}
			handle_type get() const {
				return handle_.get();
			}
			operator bool() const {
				return handle_;
			}
			operator handle_type() const {
				return get();
			}
		};
		//
		// scoped_select_object
		//
		class scoped_select_object {
		public:
			typedef HGDIOBJ handle_type;
			typedef boost::remove_pointer<handle_type>::type target_type;
		private:
			class deleter {
			private:
				HDC const hdc_;
			public:
				deleter(HDC hdc)
					: hdc_(hdc)
				{}
				void operator()(handle_type handle) const {
					::SelectObject(hdc_, handle);
				}
			};
		private:
			boost::shared_ptr<target_type> handle_;
		public:
			scoped_select_object(
				HDC hdc,
				HGDIOBJ hgdiobj
				)
				: handle_(
					::SelectObject(hdc, hgdiobj),
					deleter(hdc)
					)
			{}
			handle_type get() const {
				return handle_.get();
			}
			operator bool() const {
				return handle_;
			}
			operator handle_type() const {
				return get();
			}
		};
	}	// namespace win32
}	// namespace sprig

#endif	// #ifndef SPRIG_WIN32_HPP
