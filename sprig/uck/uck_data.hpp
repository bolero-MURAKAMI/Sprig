/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UCK_UCK_DATA_HPP
#define SPRIG_UCK_UCK_DATA_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <sprig/uck/magic.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/uck_block.hpp>

namespace sprig {
	namespace uck {
		//
		// uck_data
		//
		template<typename Traits = traits<> >
		class uck_data {
		public:
			typedef types<Traits> types_type;
		private:
			uck_conf<Traits> conf_;
			typename types_type::bin_type code_;
		public:
			uck_data(
				uck_conf<Traits> const& conf = uck_conf<Traits>(),
				typename types_type::bin_type const& code = types_type::bin_type()
				)
				: conf_(conf)
				, code_(code)
			{}
			bool analyze(typename types_type::block_type const& block) {
				if (block.tag() != magic::tags::uck_tag()) {
					return false;
				}
				if (block.type() != magic::types::node_type()) {
					return false;
				}
				typename types_type::node_type const& v(boost::get<typename types_type::node_type>(block.data()));
				BOOST_FOREACH(typename types_type::node_type::value_type const& e, v) {
					typename types_type::tag_type const& tag(e->tag());
					if (tag == magic::tags::conf_tag()) {
						conf_.analyze(*e);
					} else if (tag == magic::tags::code_tag()) {
						if (e->type() != magic::types::bin_type()) {
							return false;
						}
						code_ = boost::get<typename types_type::bin_type>(e->data());
					}
				}
				return true;
			}
			uck_conf<Traits> const& conf() const {
				return conf_;
			}
			typename types_type::bin_type const& code() const {
				return code_;
			}
		};
		//
		// uck_conf
		//
		template<typename Traits = traits<> >
		class uck_conf {
		public:
			typedef types<Traits> types_type;
		private:
			typename types_type::uint_type bits_;
			std::vector<uck_task<Traits> > tasks_;
		public:
			uck_conf(
				typename types_type::uint_type bits = 8
				)
				: bits_(bits)
			{}
			bool analyze(typename types_type::block_type const& block) {
				if (block.tag() != magic::tags::conf_tag()) {
					return false;
				}
				if (block.type() != magic::types::node_type()) {
					return false;
				}
				typename types_type::node_type const& v(boost::get<typename types_type::node_type>(block.data()));
				BOOST_FOREACH(typename types_type::node_type::value_type const& e, v) {
					typename types_type::tag_type const& tag(e->tag());
					if (tag == magic::tags::bits_tag()) {
						if (e->type() != magic::types::uint_type()) {
							return false;
						}
						bits_ = boost::get<typename types_type::uint_type>(e->data());
					} else if (tag == magic::tags::task_tag()) {
						tasks_.push_back(uck_task<Traits>());
						tasks_.back().analyze(*e);
					}
				}
				if (tasks_.empty()) {
					return false;
				}
				return true;
			}
			typename types_type::uint_type bits() const {
				return bits_;
			}
			std::vector<uck_task<Traits> > const& tasks() const {
				return tasks_;
			}
		};
		//
		// uck_task
		//
		template<typename Traits = traits<> >
		class uck_task {
		public:
			typedef types<Traits> types_type;
		private:
			typename types_type::uint_type pptr_;
			typename types_type::uint_type mptr_;
		public:
			uck_task(
				typename types_type::uint_type pptr = 0,
				typename types_type::uint_type mptr = 0
				)
				: pptr_(pptr)
				, mptr_(mptr)
			{}
			bool analyze(typename types_type::block_type const& block) {
				if (block.tag() != magic::tags::task_tag()) {
					return false;
				}
				if (block.type() != magic::types::node_type()) {
					return false;
				}
				typename types_type::node_type const& v(boost::get<typename types_type::node_type>(block.data()));
				BOOST_FOREACH(typename types_type::node_type::value_type const& e, v) {
					typename types_type::tag_type const& tag(e->tag());
					if (tag == magic::tags::pptr_tag()) {
						if (e->type() != magic::types::int_type()) {
							return false;
						}
						pptr_ = boost::get<typename types_type::int_type>(e->data());
					} else if (tag == magic::tags::mptr_tag()) {
						if (e->type() != magic::types::int_type()) {
							return false;
						}
						mptr_ = boost::get<typename types_type::int_type>(e->data());
					}
				}
				return true;
			}
			typename types_type::uint_type pptr() const {
				return pptr_;
			}
			typename types_type::uint_type mptr() const {
				return mptr_;
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_UCK_DATA_HPP
