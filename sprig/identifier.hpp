/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_IDENTIFIER_HPP
#define SPRIG_IDENTIFIER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/operators.hpp>
#include <sprig/singleton.hpp>

namespace sprig {
	//
	// forward
	//
	class identifier;

	//
	// global_identifier_publisher
	//
	template<typename Identifier = identifier>
	class global_identifier_publisher
		: public sprig::singleton<global_identifier_publisher<Identifier> >
		, private boost::operators<global_identifier_publisher<Identifier> >
	{
		SPRIG_FRIEND_SINGLETON(global_identifier_publisher<Identifier>);
	public:
		typedef Identifier identifier_type;
		typedef typename identifier_type::size_type size_type;
	private:
		typedef typename identifier_type::identity_type identity_type;
	private:
		identity_type next_identity_;
	private:
		global_identifier_publisher()
			: next_identity_(0)
		{}
		~global_identifier_publisher() {}
	public:
		bool operator==(global_identifier_publisher const& rhs) const {
			return this == &rhs;
		}
		identifier_type issue() {
			return identifier_type(next_identity_++);
		}
		size_type quantity() const {
			return static_cast<size_type>(next_identity_);
		}
		size_type order(identifier_type const& target) const {
			return static_cast<size_type>(target.identity_);
		}
	};

	//
	// identifier
	//
	class identifier : boost::operators<identifier> {
		friend class global_identifier_publisher<identifier>;
	private:
		typedef int identity_type;
	public:
		typedef std::size_t size_type;
	private:
		identity_type identity_;
	private:
		explicit identifier(identity_type identity)
			: identity_(identity)
		{}
	public:
		bool operator==(identifier const& rhs) const {
			return identity_ == rhs.identity_;
		}
		bool operator<(identifier const& rhs) const {
			return identity_ < rhs.identity_;
		}
		size_type order() const {
			return global_identifier_publisher<identifier>::get_mutable_instance().order(*this);
		}
	};
} // namespace sprig

#endif	// #ifndef SPRIG_IDENTIFIER_HPP
