/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAINFUCK_HPP
#define SPRIG_BRAINFUCK_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/function.hpp>
#include <boost/range.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/exception.hpp>
#include <sprig/str_length.hpp>
#include <sprig/type_traits/is_derived_basic_istream.hpp>

namespace sprig {
	namespace brainfuck {
		//
		// base_exception
		//
		SPRIG_EXCEPTION_DECL(base_exception);
		//
		// code_ended
		//
		SPRIG_EXCEPTION_INHERIT_DECL(code_ended, base_exception);
		//
		// forward_overrun
		// backward_overrun
		//
		SPRIG_EXCEPTION_INHERIT_DECL(forward_overrun, base_exception);
		SPRIG_EXCEPTION_INHERIT_DECL(backward_overrun, base_exception);
		//
		// open_paren_not_found
		// closed_paren_not_found
		//
		SPRIG_EXCEPTION_INHERIT_DECL(open_paren_not_found, base_exception);
		SPRIG_EXCEPTION_INHERIT_DECL(closed_paren_not_found, base_exception);
		//
		// engine
		//
		class engine {
		public:
			typedef unsigned char byte_type;
			typedef std::size_t size_type;
			typedef size_type pointer_type;
			typedef std::vector<byte_type> buffer_type;
			typedef boost::function<void (byte_type)> output_type;
			typedef boost::function<byte_type ()> input_type;
		public:
			static size_type const dbuffer_size = 30000;
			static pointer_type const dpointer_min = 0;
			static pointer_type const dpointer_max = dbuffer_size - 1;
		public:
			static void default_output(byte_type b) {
				std::cout << static_cast<char>(b);
			}
			static byte_type default_input() {
				char b;
				std::cin >> b;
				return b;
			}
		private:
			buffer_type pbuffer_;
			buffer_type dbuffer_;
			pointer_type ppointer_;
			pointer_type dpointer_;
			output_type output_;
			input_type input_;
		public:
			engine()
				: pbuffer_()
				, dbuffer_(dbuffer_size, 0)
				, ppointer_(0)
				, dpointer_(0)
				, output_(engine::default_output)
				, input_(engine::default_input)
			{}
			void push_code(char const* code) {
				pbuffer_.insert(
					pbuffer_.end(),
					code,
					code + sprig::str_length(code)
					);
			}
			template<typename Stream>
			void push_code(
				Stream& code,
				typename boost::enable_if<
					sprig::is_derived_basic_istream<Stream>
				>::type* = 0
				)
			{
				std::copy(
					std::istream_iterator<byte_type>(code),
					std::istream_iterator<byte_type>(),
					std::back_inserter(pbuffer_)
					);
			}
			template<typename Range>
			void push_code(
				Range const& code,
				typename boost::disable_if<
					sprig::is_derived_basic_istream<Range>
				>::type* = 0
				)
			{
				std::copy(
					boost::begin(code),
					boost::end(code),
					std::back_inserter(pbuffer_)
					);
			}
			bool is_code_end() const {
				return ppointer_ >= pbuffer_.size();
			}
			void execute() {
				if (is_code_end()) {
					SPRIG_THROW_EXCEPTION(code_ended("code ended: code ended"));
				}
				switch (pbuffer_[ppointer_]) {
				case '>':
					if (dpointer_ >= dpointer_max) {
						SPRIG_THROW_EXCEPTION(forward_overrun("forward overrun: on operator \'>\'"));
					}
					++dpointer_;
					break;
				case '<':
					if (dpointer_ <= dpointer_min) {
						SPRIG_THROW_EXCEPTION(backward_overrun("backward overrun: on operator \'<\'"));
					}
					--dpointer_;
					break;
				case '+':
					++dbuffer_[dpointer_];
					break;
				case '-':
					--dbuffer_[dpointer_];
					break;
				case '.':
					output_(dbuffer_[dpointer_]);
					break;
				case ',':
					dbuffer_[dpointer_] = input_();
					break;
				case '[':
					if (!dbuffer_[dpointer_]) {
						pointer_type ppointer = ppointer_;
						std::ptrdiff_t count = 1;
						do {
							if (ppointer + 1 >= pbuffer_.size()) {
								SPRIG_THROW_EXCEPTION(closed_paren_not_found("closed paren not found: on operator \'[\'"));
							}
							++ppointer;
							switch (pbuffer_[ppointer]) {
							case '[':
								++count;
								break;
							case ']':
								--count;
								break;
							}
						} while (count);
						ppointer_ = ppointer;
					}
					break;
				case ']':
					{
						pointer_type ppointer = ppointer_;
						std::ptrdiff_t count = -1;
						do {
							if (ppointer <= 0) {
								SPRIG_THROW_EXCEPTION(open_paren_not_found("open paren not found: on operator \']\'"));
							}
							--ppointer;
							switch (pbuffer_[ppointer]) {
							case '[':
								++count;
								break;
							case ']':
								--count;
								break;
							}
						} while (count);
						ppointer_ = ppointer - 1;
					}
					break;
				}
				++ppointer_;
			}
			buffer_type const& pbuffer() const {
				return pbuffer_;
			}
			buffer_type& pbuffer() {
				return pbuffer_;
			}
			buffer_type const& dbuffer() const {
				return dbuffer_;
			}
			buffer_type& dbuffer() {
				return dbuffer_;
			}
			pointer_type const& ppointer() const {
				return ppointer_;
			}
			pointer_type& ppointer() {
				return ppointer_;
			}
			pointer_type const& dpointer() const {
				return dpointer_;
			}
			pointer_type& dpointer() {
				return dpointer_;
			}
			output_type const& output() const {
				return output_;
			}
			output_type& output() {
				return output_;
			}
			input_type const& input() const {
				return input_;
			}
			input_type& input() {
				return input_;
			}
		};
	}	// namespace brainfuck
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAINFUCK_HPP
