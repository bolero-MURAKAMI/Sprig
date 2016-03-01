/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_STD_STD_ENGINE_HPP
#define SPRIG_UCK_STD_STD_ENGINE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <vector>
#include <iterator>
#include <boost/integer.hpp>
#include <boost/foreach.hpp>
#include <sprig/binary.hpp>
#include <sprig/iterator/binary_iterator.hpp>
#include <sprig/utility/iterator.hpp>
#include <sprig/uck/magic.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/uck_data.hpp>
#include <sprig/uck/uck_task_element.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/std/std_io.hpp>

namespace sprig {
	namespace uck {
		//
		// std_engine
		//
		template<typename Traits = traits<> >
		class std_engine {
		public:
			typedef Traits traits_type;
			typedef types<traits_type> types_type;
			typedef std_types<traits_type> std_types_type;
			typedef uck_task_element<Traits> task_element_type;
			typedef typename task_element_type::ptr_type ptr_type;
			typedef std::vector<task_element_type> task_container_type;
		private:
			typename types_type::data_type data_;
			typename types_type::bin_type buffer_;
			std::size_t bytes_;
			task_container_type tasks_;
			typename std_types_type::output_type output_;
			typename std_types_type::input_type input_;
			std::size_t count_;
		private:
			template<typename T>
			T get_from_buffer(ptr_type p) const {
				return get_from_big_endian<T>(
					sprig::get_advance(buffer_.begin(), p),
					sprig::get_advance(buffer_.begin(), p + bytes_)
					);
			}
			template<typename T>
			void set_to_buffer(T t, ptr_type p) {
				set_to_big_endian(
					t,
					sprig::get_advance(buffer_.begin(), p),
					sprig::get_advance(buffer_.begin(), p + bytes_)
					);
			}
			template<typename T>
			T get_from_work(task_element_type const& task) const {
				return get_from_big_endian<T>(
					task.work().begin(),
					task.work().end()
					);
			}
			template<typename T>
			void set_to_work(task_element_type& task, T t) {
				set_to_big_endian(
					t,
					task.work().begin(),
					task.work().end()
					);
			}
		public:
			std_engine()
				: bytes_(0)
				, output_(io::std_output<Traits>())
				, input_(io::std_input<Traits>())
				, count_(0)
			{}
			std_engine(
				typename std_types_type::output_type output,
				typename std_types_type::input_type input
				)
				: bytes_(0)
				, output_(output)
				, input_(input)
				, count_(0)
			{}
			bool analyze(typename types_type::data_type const& data) {
				data_ = data;
				buffer_ = data_.code();
				bytes_ = data_.conf().bits() / 8;
				class insert_task_element {
				private:
					std::vector<uck_task_element<Traits> >& tasks_;
					std::size_t bytes_;
				public:
					insert_task_element(
						std::vector<uck_task_element<Traits> >& tasks,
						typename types_type::uint_type bytes
						)
						: tasks_(tasks)
						, bytes_(bytes)
					{}
					void operator()(uck_task<Traits> const& task) {
						tasks_.push_back(uck_task_element<Traits>(task, bytes_));
					}
				};
				std::for_each(data.conf().tasks().begin(), data.conf().tasks().end(), insert_task_element(tasks_, bytes_));
				count_ = 0;
				return true;
			}
			void exec() {
				BOOST_FOREACH(task_element_type& e, tasks_) {
					switch (get_from_buffer<typename types_type::byte_type>(e.pptr())) {
					case magic::commands::next_command:
						e.mptr() += bytes_;
						e.mptr() %= buffer_.size();
						if (e.mptr() < 0) {
							e.mptr() += buffer_.size();
						}
						break;
					case magic::commands::prior_command:
						e.mptr() -= bytes_;
						e.mptr() %= buffer_.size();
						if (e.mptr() < 0) {
							e.mptr() += buffer_.size();
						}
						break;
					case magic::commands::inc_command:
						set_to_buffer<typename types_type::int_type>(
							get_from_buffer<typename types_type::int_type>(e.mptr()) + 1,
							e.mptr()
							);
						break;
					case magic::commands::dec_command:
						set_to_buffer<typename types_type::int_type>(
							get_from_buffer<typename types_type::int_type>(e.mptr()) - 1,
							e.mptr()
							);
						break;
					case magic::commands::out_command:
						output_(
							sprig::get_advance(buffer_.begin(), e.mptr()),
							sprig::get_advance(buffer_.begin(), e.mptr() + bytes_),
							e.work().begin(),
							e.work().end()
							);
						break;
					case magic::commands::in_command:
						input_(
							sprig::get_advance(buffer_.begin(), e.mptr()),
							sprig::get_advance(buffer_.begin(), e.mptr() + bytes_),
							e.work().begin(),
							e.work().end()
							);
						break;
					case magic::commands::label_command:
						set_to_buffer<typename types_type::int_type>(
							e.pptr(),
							e.mptr()
							);
						break;
					case magic::commands::jump_command:
						if (!get_from_big_endian<typename types_type::int_type>(e.work().begin(), e.work().end())) {
							e.pptr() = static_cast<ptr_type>(get_from_buffer<typename types_type::int_type>(e.mptr()));
						}
						return;
					case magic::commands::wout_command:
						set_to_work(e, get_from_buffer<typename types_type::int_type>(e.mptr()));
						break;
					case magic::commands::win_command:
						set_to_buffer<typename types_type::int_type>(
							get_from_work<typename types_type::int_type>(e),
							e.mptr()
							);
						break;
					default:
						;
					}
					e.pptr() += bytes_;
				}
				++count_;
			}
			std::size_t count() const {
				return count_;
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_STD_STD_ENGINE_HPP
