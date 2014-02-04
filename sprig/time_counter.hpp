/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TIME_COUNTER_HPP
#define SPRIG_TIME_COUNTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "winmm.lib")
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <sprig/external/windows.hpp>
#include <sprig/external/mmsystem.hpp>

namespace sprig {
	class time_counter {
	public:
		typedef double value_type;
	private:
		typedef LONGLONG unit_type;
	public:
		enum USING_COUNTER {
			TIME_GET_TIME,
			QUERY_PERFORMANCE_COUNTER,
		};
	private:
		USING_COUNTER using_counter_;
		unit_type unit_;
	public:
		time_counter()
			: using_counter_(TIME_GET_TIME)
			, unit_(1000)
		{
			LARGE_INTEGER frequency_value = { 0 };
			if (::QueryPerformanceFrequency(&frequency_value)) {
				using_counter_ = QUERY_PERFORMANCE_COUNTER;
				unit_ = frequency_value.QuadPart;
			}
		}
		value_type get() const {
			value_type result = 0.0;
			switch (using_counter_) {
			case TIME_GET_TIME:
				result = static_cast<value_type>(::timeGetTime()) / unit_;
				break;
			case QUERY_PERFORMANCE_COUNTER:
				{
					LARGE_INTEGER counter_value = {0};
					::QueryPerformanceCounter(&counter_value);
					result = static_cast<value_type>(counter_value.QuadPart) / unit_;
				}
				break;
			}
			return result;
		}
		USING_COUNTER get_using_counter() const {
			return using_counter_;
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_TIME_COUNTER_HPP
