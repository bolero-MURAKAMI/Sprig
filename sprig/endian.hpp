#ifndef SPRIG_ENDIAN_HPP
#define SPRIG_ENDIAN_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

namespace sprig {
	namespace {
		//
		// is_big_endian
		//
		bool is_big_endian() {
			struct checker {
				static bool check() {
					unsigned t = 1;
					return *reinterpret_cast<unsigned char*>(&t) != 1;
				}
			};
			static bool const result = checker::check();
			return result;
		}
		//
		// is_little_endian
		//
		bool is_little_endian() {
			struct checker {
				static bool check() {
					unsigned t = 1;
					return *reinterpret_cast<unsigned char*>(&t) == 1;
				}
			};
			static bool const result = checker::check();
			return result;
		}
	}	// anonymous-namespace
}	// namespace sprig

#endif	// #ifndef SPRIG_ENDIAN_HPP
