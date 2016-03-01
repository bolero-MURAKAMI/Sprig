/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TIMER_HPP
#define SPRIG_TIMER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#ifdef SPRIG_HAS_PRAGMA_COMMENT
#	pragma comment(lib, "winmm.lib")
#endif	// #ifdef SPRIG_HAS_PRAGMA_COMMENT

#include <cstddef>
#include <cmath>
#include <iosfwd>
#include <string>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/windows.hpp>
#include <sprig/external/mmsystem.hpp>
#include <sprig/assert.hpp>

namespace sprig {
	//
	// timer
	//
	class timer {
	public:
		typedef DWORD value_type;
	private:
		value_type start_time_;
	public:
		timer()
				: start_time_(::timeGetTime())
		{}
		void restart() {
			start_time_ = ::timeGetTime();
		}
		value_type elapsed() const {
			return ::timeGetTime() - start_time_;
		}
	};
	//
	// minutes_timer
	//
	class minutes_timer
		: public timer
	{
		value_type minutes_time_;
	public:
		minutes_timer() {}
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
			timer::restart();
			minutes_time_ = 0;
		}
	};
	//
	// drive_counter
	//
	template<typename Timer = minutes_timer>
	class drive_counter {
	public:
		typedef Timer timer_type;
		typedef typename timer_type::value_type value_type;
		typedef std::size_t size_type;
	public:
		enum drive_state {
			started,
			driving,
			suspended,
		};
	private:
		drive_state drive_state_;
		timer_type timer_;
		value_type unit_time_;
		value_type elapsed_;
	private:
		template<typename T>
		typename boost::enable_if<
			boost::is_integral<T>,
			size_type
		>::type get_drive_count_impl() {
			value_type const range = timer_.minuted() - elapsed_;
			return static_cast<size_type>((range - range % unit_time_) / unit_time_);
		}
		template<typename T>
		typename boost::enable_if<
			boost::is_float<T>,
			size_type
		>::type get_drive_count_impl() {
			value_type const range = timer_.minuted() - elapsed_;
			return static_cast<size_type>(std::floor(range / unit_time_));
		}
	public:
		drive_counter()
			: drive_state_(started)
			, unit_time_(0)
			, elapsed_(0)
		{}
		explicit drive_counter(value_type unit_time)
			: drive_state_(started)
			, unit_time_(unit_time)
			, elapsed_(0)
		{}
		drive_state get_drive_state() const {
			return drive_state_;
		}
		value_type get_unit_time() const {
			return unit_time_;
		}
		void reset_unit_time(value_type unit_time) {
			unit_time_ = unit_time;
			if (!is_valid())
				drive_state_ = started;
			if (drive_state_ == driving) {
				timer_.minutes();
				elapsed_ = timer_.minuted();
			}
		}
		void suspend() {
			drive_state_ = suspended;
			elapsed_ = 0;
		}
		void restart() {
			if (drive_state_ == suspended)
				drive_state_ = started;
		}
		size_type get_drive_count() {
			if (!is_valid())
				return 0;
			switch (drive_state_) {
			case started:
				drive_state_ = driving;
				timer_.restart();
				elapsed_ = 0;
				return 0;
			case driving:
				timer_.minutes();
				return get_drive_count_impl<value_type>();
			case suspended:
				return 0;
			default:
				SPRIG_ASSERT(0);
			}
			return 0;
		}
		void advance() {
			if (drive_state_ == driving) {
				elapsed_ = timer_.minuted();
			}
		}
		bool is_valid() const {
			return unit_time_ != 0;
		}
	};
	//
	// time_logger
	//
	template<typename Stream = std::ostream, typename String = std::string>
	class time_logger {
	public:
		typedef Stream stream_type;
		typedef String string_type;
		typedef minutes_timer timer_type;
	private:
		stream_type& stream_;
		string_type name_;
		timer_type timer_;
	private:
		void output_construct() {
			name_.empty()
				? stream_ << "<begin />\n"
				: stream_ << "<begin name=\"" << name_ << "\" />\n"
				;
		}
		void output_destruct() {
			timer_.minutes();
			(name_.empty()
				? stream_ << "<end>"
				: stream_ << "<end name=\"" << name_ << "\">"
				)
				<< timer_.minuted()
				<< "</end>\n"
				;
		}
	public:
		explicit time_logger(stream_type& stream)
			: stream_(stream)
		{
			output_construct();
		}
		time_logger(
			stream_type& stream,
			string_type const& name
			)
			: stream_(stream)
			, name_(name)
		{
			output_construct();
		}
		~time_logger() throw() {
			output_destruct();
		}
		timer_type::value_type measure() {
			timer_.minutes();
			name_.empty()
				? stream_ << "<measurememt>"
				: stream_ << "<measurememt name=\"" << name_ << "\">"
				<< timer_.minuted()
				<< "</measurememt>\n"
				;
			return timer_.minuted();
		}
		timer_type::value_type measure(string_type const& phase) {
			timer_.minutes();
			name_.empty()
				? stream_ << "<measurememt "
				: stream_ << "<measurememt name=\"" << name_ << "\" "
				<< "phase=\"" << phase << "\">"
				<< timer_.minuted()
				<< "</measurememt>\n"
				;
			return timer_.minuted();
		}
		stream_type& stream() {
			return stream_;
		}
		stream_type const& stream() const {
			return stream_;
		}
		string_type const& name() const {
			return name_;
		}
		timer_type const& timer() const {
			return timer_;
		}
	};
	//
	// time_wlogger
	//
	template<typename Stream = std::wostream, typename String = std::wstring>
	class time_wlogger {
	public:
		typedef Stream stream_type;
		typedef String string_type;
		typedef minutes_timer timer_type;
	private:
		stream_type& stream_;
		string_type name_;
		timer_type timer_;
	private:
		void output_construct() {
			name_.empty()
				? stream_ << L"<begin />\n"
				: stream_ << L"<begin name=\"" << name_ << L"\" />\n"
				;
		}
		void output_destruct() {
			timer_.minutes();
			name_.empty()
				? stream_ << L"<end>"
				: stream_ << L"<end name=\"" << name_ << L"\">"
				<< timer_.minuted()
				<< L"</end>\n"
				;
		}
	public:
		explicit time_wlogger(stream_type& stream)
			: stream_(stream)
		{
			output_construct();
		}
		time_wlogger(
			stream_type& stream,
			string_type const& name
			)
			: stream_(stream)
			, name_(name)
		{
			output_construct();
		}
		~time_wlogger() throw() {
			output_destruct();
		}
		timer_type::value_type measure() {
			timer_.minutes();
			name_.empty()
				? stream_ << L"<measurememt>"
				: stream_ << L"<measurememt name=\"" << name_ << L"\">"
				<< timer_.minuted()
				<< L"</measurememt>\n"
				;
			return timer_.minuted();
		}
		timer_type::value_type measure(string_type const& phase) {
			timer_.minutes();
			name_.empty()
				? stream_ << L"<measurememt "
				: stream_ << L"<measurememt name=\"" << name_ << L"\" "
				<< L"phase=\"" << phase << L"\">\n"
				<< timer_.minuted()
				<< L"</measurememt>\n"
				;
			return timer_.minuted();
		}
		stream_type& stream() {
			return stream_;
		}
		stream_type const& stream() const {
			return stream_;
		}
		string_type const& name() const {
			return name_;
		}
		timer_type const& timer() const {
			return timer_;
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_TIMER_HPP
