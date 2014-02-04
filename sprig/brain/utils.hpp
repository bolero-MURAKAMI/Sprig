/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_UTILS_HPP
#define SPRIG_BRAIN_UTILS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/operators.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>

namespace sprig {
	namespace brain {
		//
		// position_property
		//
		//	COMMENT: 位置インタフェースをバイト型のように扱うラッパークラス
		//
		template<
			typename Types = use_default
		>
		class position_property
			: public type_base<Types>
			, private boost::operators<position_property<Types> >
		{
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		private:
			position_interface<types>& pos_;
		public:
			position_property(position_interface<types>& pos)
				: pos_(pos)
			{}
			void operator=(byte_type b) {
				set(b);
				return *this;
			}
			operator byte_type() {
				return get();
			}
			position_interface<types>& pos() {
				return pos_;
			}
			void set(byte_type b) {
				pos_.set(b);
			}
			byte_type get() {
				return pos_.get();
			}
		public:
			bool operator<(position_property const& rhs) const {
				return get() < rhs.get();
			}
			bool operator==(position_property const& rhs) const {
				return get() == rhs.get();
			}
			position_property& operator+=(position_property const& rhs) {
				set(get() + rhs.get());
				return *this;
			}
			position_property& operator-=(position_property const& rhs) {
				set(get() - rhs.get());
				return *this;
			}
			position_property& operator*=(position_property const& rhs) {
				set(get() * rhs.get());
				return *this;
			}
			position_property& operator/=(position_property const& rhs) {
				set(get() / rhs.get());
				return *this;
			}
			position_property& operator%=(position_property const& rhs) {
				set(get() % rhs.get());
				return *this;
			}
			position_property& operator|=(position_property const& rhs) {
				set(get() | rhs.get());
				return *this;
			}
			position_property& operator&=(position_property const& rhs) {
				set(get() & rhs.get());
				return *this;
			}
			position_property& operator^=(position_property const& rhs) {
				set(get() ^ rhs.get());
				return *this;
			}
			position_property& operator++() {
				set(get() + 1);
				return *this;
			}
			position_property& operator--() {
				set(get() - 1);
				return *this;
			}
		};

		//
		// position_iterator
		//
		//	COMMENT: 位置インタフェースを走査するイテレータクラス
		//	COMMENT: このクラスは渡された位置インタフェースを書き換える
		//
		template<
			typename Types = use_default
		>
		class position_iterator
			: public type_base<Types>
			, public boost::iterator_facade<
				position_iterator<Types>,
				position_property<Types>,
				boost::bidirectional_traversal_tag,
				position_property<Types>&,
				typename type_base<Types>::diff_type
			>
		{
			friend class boost::iterator_core_access;
		public:
			typedef type_base<Types> type_base_type;
			typedef typename type_base_type::types types;
			typedef typename types::byte_type byte_type;
			typedef typename types::size_type size_type;
			typedef typename types::diff_type diff_type;
			typedef typename types::tag_type tag_type;
		private:
			typedef boost::iterator_facade<
				position_iterator<Types>,
				position_property<Types>,
				boost::bidirectional_traversal_tag,
				position_property<Types>&,
				typename type_base<Types>::diff_type
			> iterator_facade_type;
		public:
			typedef typename iterator_facade_type::reference reference;
		private:
			boost::shared_ptr<position_property<types> > prop_;
		public:
			position_iterator(position_interface<types>& pos)
				: prop_(boost::make_shared<position_property<types> >(pos))
			{}
		private:
			void increment() {
				prop_->pos().next();
			}
			void decrement() {
				prop_->pos().prior();
			}
			reference dereference() const {
				return *prop_;
			}
			bool equal(position_iterator const& rhs) const {
				return prop_->pos().equal(rhs.prop_->pos());
			}
		};
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_HPP
