#ifndef SPRIG_PERFORMANCE_TIMER_HPP
#define SPRIG_PERFORMANCE_TIMER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/time_counter.hpp>

namespace sprig {
	//
	// performance_timer
	//
	class performance_timer {
	public:
		typedef time_counter time_counter_type;
		typedef time_counter_type::value_type value_type;
	private:
		time_counter_type time_counter_;
		value_type start_time_;
	public:
			performance_timer()
				: start_time_(time_counter_.get())
		{}
		~performance_timer() {}
			void restart() {
			start_time_ = time_counter_.get();
		}
		value_type elapsed() const {
			return time_counter_.get() - start_time_;
		}
	};
	//
	// minutes_performance_timer
	//
	class minutes_performance_timer
		: public performance_timer
	{
		value_type minutes_time_;
	public:
		minutes_performance_timer() {}
		~minutes_performance_timer() {}
		void minutes() {
			minutes_time_ = elapsed();
		}
		value_type minuted() const {
			return minutes_time_;
		}
		value_type relative_elapsed() const {
			return elapsed() - minutes_time_;
		}
		void restart() {
			performance_timer::restart();
			minutes_time_ = 0;
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_PERFORMANCE_TIMER_HPP
