/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_NK_BASIC_HPP
#define SPRIG_NK_BASIC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <deque>
#include <algorithm>
#include <iterator>
#include <boost/range.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <sprig/nk/foundation.hpp>

namespace sprig {
	namespace nk {
		//
		// basic_unit
		//
		class basic_unit
			: public unit
		{
		public:
			typedef std::deque<byte_type> memory_type;
		private:
			memory_type input_;
			memory_type output_;
			unit_info info_;
		public:
			basic_unit() {}
		public:
			unit_id_type const get_id() {
				return 0;
			}
			unit_info const get_info() const {
				return info_;
			}
			void set_info(unit_info const& info) {
				info_ = info;
			}
			void push_input(byte_type const in) {
				input_.push_back(in);
			}
			popped_byte_type const pop_input() {
				popped_byte_type result;
				if (!input_.empty()) {
					result = input_.front();
					input_.pop_front();
				}
				return result;
			}
			bool const empty_input() {
				return input_.empty();
			}
			void push_output(byte_type const out) {
				output_.push_back(out);
			}
			popped_byte_type const pop_output() {
				popped_byte_type result;
				if (!output_.empty()) {
					result = output_.front();
					output_.pop_front();
				}
				return result;
			}
			bool const empty_output() {
				return output_.empty();
			}
		};

		//
		// basic_engine
		//
		class basic_engine
			: public engine
		{
		public:
			typedef std::deque<byte_type> memory_type;
		private:
			memory_type forward_;
			memory_type backward_;
			bool is_allocated_;
			size_type loaded_size_;
			bool is_executable_;
			unit_info info_;
		private:
			bool const is_out_of_bounds(ptr_type const p) {
				return p >= 0
					? p >= static_cast<ptr_type>(forward_.size())
					: -p - 1 >= static_cast<ptr_type>(backward_.size())
					;
			}
			byte_type& at(ptr_type const p) {
				return p >= 0
					? forward_.at(p)
					: backward_.at(-p - 1)
					;
			}
			void push(ptr_type const p) {
				p >= 0
					? forward_.push_back(0)
					: backward_.push_back(0)
					;
			}
			void move(ptr_type const p) {
				if (is_out_of_bounds(p)) {
					push(p);
				}
			}
			bool const search_forward(unit& u, unit_info& info) {
				ptr_type p = info.pptr;
				for (int i = 1; ; ++p) {
					if (is_out_of_bounds(p)) {
						info.state = abnormal;
						info.error = out_of_bounds_forward;
						return false;
					}
					if (at(p) == '[') {
						++i;
					} else if (at(p) == ']') {
						--i;
					}
					if (!i) {
						info.state = normal;
						info.error = no_error;
						info.pptr = p + 1;
						return true;
					}
				}
				return true;
			}
			bool const search_backward(unit& u, unit_info& info) {
				ptr_type p = info.pptr;
				for (int i = -1; ; --p) {
					if (is_out_of_bounds(p)) {
						info.state = abnormal;
						info.error = out_of_bounds_backward;
						return false;
					}
					if (at(p) == '[') {
						++i;
					} else if (at(p) == ']') {
						--i;
					}
					if (!i) {
						info.state = normal;
						info.error = no_error;
						info.pptr = p;
						return true;
					}
				}
				return true;
			}
		public:
			basic_engine()
				: is_allocated_(false)
				, loaded_size_(0)
			{}
			template<typename Range>
			void load_forward(Range const& range) {
				std::copy(
					boost::begin(range),
					boost::end(range),
					std::back_inserter(forward_)
					);
			}
			template<typename Range>
			void load_backward(Range const& range) {
				std::copy(
					boost::begin(range),
					boost::end(range),
					std::front_inserter(backward_)
					);
			}
			template<typename Iterator>
			void save_forward(Iterator iter) {
				std::copy(
					boost::begin(forward_),
					boost::end(forward_),
					iter
					);
			}
			template<typename Iterator>
			void save_backward(Iterator iter) {
				std::copy(
					boost::begin(backward_),
					boost::end(backward_),
					iter
					);
			}
		public:
			created_unit_type create_unit() {
				return created_unit_type(new basic_unit());
			}
			interval_type const referenced_interval(unit& u) const {
				return interval_type(-static_cast<ptr_type>(backward_.size()), static_cast<ptr_type>(forward_.size()));
			}
			bool const allocate(unit& u, size_type const s) {
				if (is_allocated(u)) {
					return false;
				}
				memory_type new_forward_(s, 0);
				memory_type new_backward_;
				forward_.swap(new_forward_);
				backward_.swap(new_backward_);
				loaded_size_ = 0;
				is_allocated_ = true;
				return true;
			}
			size_type const allocated_size(unit& u) const {
				return forward_.size();
			}
			bool const is_allocated(unit& u) const {
				return is_allocated_;
			}
			bool const load(unit& u, byte_type const c) {
				if (!is_allocated(u) || is_full_loaded(u)) {
					return false;
				}
				forward_.at(loaded_size_++) = c;
				return true;
			}
			bool const is_full_loaded(unit& u) const {
				return is_allocated(u) && loaded_size(u) == allocated_size(u);
			}
			size_type const loaded_size(unit& u) const {
				return loaded_size_;
			}
			bool const is_executable(unit& u) const {
				return is_allocated(u) /*&& is_full_loaded(u)*/ && is_executable_;
			}
			bool const begin_execution(unit& u) {
				is_executable_ = true;
				return true;
			}
			bool const end_execution(unit& u) {
				is_executable_ = false;
				return true;
			}
			bool const execute(unit& u) {
				unit_info info(info_);
				if (!is_executable(u)) {
					info.state = abnormal;
					info.error = un_executable;
					u.set_info(info_);
					return false;
				}
				switch (info_.error) {
				case out_of_bounds_forward:
					search_forward(u, info);
					u.set_info(info_ = info);
					return true;
				case out_of_bounds_backward:
					search_backward(u, info);
					u.set_info(info_ = info);
					return true;
				}
				if (is_out_of_bounds(info_.pptr)) {
					info.state = stopped;
					info.error = no_error;
					u.set_info(info_ = info);
					return true;
				}
				switch (at(info_.pptr)) {
				case '>':
					move(++info.dptr);
					info.state = normal;
					info.error = no_error;
					++info.pptr;
					break;
				case '<':
					move(--info.dptr);
					info.state = normal;
					info.error = no_error;
					++info.pptr;
					break;
				case '+':
					++at(info.dptr);
					info.state = normal;
					info.error = no_error;
					++info.pptr;
					break;
				case '-':
					--at(info.dptr);
					info.state = normal;
					info.error = no_error;
					++info.pptr;
					break;
				case '.':
					u.push_output(at(info.dptr));
					info.state = normal;
					info.error = no_error;
					++info.pptr;
					break;
				case ',':
					if (u.empty_input()) {
						info.state = requires_input;
						info.error = no_error;
					} else {
						at(info.dptr) = *u.pop_input();
						info.state = normal;
						info.error = no_error;
						++info.pptr;
					}
					break;
				case '[':
					if (!at(info.dptr)) {
						++info.pptr;
						search_forward(u, info);
					} else {
						info.state = normal;
						info.error = no_error;
						++info.pptr;
					}
					break;
				case ']':
					--info.pptr;
					search_backward(u, info);
					break;
				default:
					info.state = normal;
					info.error = no_error;
					++info.pptr;
				}
				u.set_info(info_ = info);
				return true;
			}
		};
	}	// namespace nk
}	// namespace sprig

#endif	// #ifndef SPRIG_NK_BASIC_HPP
