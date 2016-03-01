/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_ITERATOR_OSTREAM_MANIP_ITERATOR_HPP
#define SPRIG_ITERATOR_OSTREAM_MANIP_ITERATOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <iterator>
#include <utility>
#include <boost/ref.hpp>
#include <boost/call_traits.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/reference_holder.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>

namespace sprig {
	//
	// declares
	//
	template <typename T, typename Manip, typename Elem, typename Traits>
	class ostream_manip_iterator_outputter;
	//
	// ostream_manip_iterator
	//
	template <typename T, typename Manip, typename Elem = char, typename Traits = std::char_traits<Elem> >
	class ostream_manip_iterator
		: public boost::iterator_facade<
			ostream_manip_iterator<T, Manip, Elem, Traits>,
			ostream_manip_iterator_outputter<T, Manip, Elem, Traits>,
			std::output_iterator_tag
		>
	{
		friend class boost::iterator_core_access;
	public:
		typedef T output_value_type;
		typedef Manip manip_type;
		typedef Elem char_type;
		typedef Traits traits_type;
		typedef std::basic_ostream<char_type, Traits> ostream_type;
		typedef char_type const* delim_type;
		typedef ostream_manip_iterator_outputter<output_value_type, manip_type, char_type, traits_type> outputter_type;
	private:
		typedef ostream_manip_iterator this_type;
		typedef boost::iterator_facade<
			ostream_manip_iterator,
			outputter_type,
			std::output_iterator_tag
		> iterator_facade_type;
	public:
		typedef typename iterator_facade_type::reference reference;
		typedef typename iterator_facade_type::difference_type difference_type;
	private:
		sprig::reference_holder<ostream_type> ostream_;
		manip_type manip_;
		delim_type delim_;
		boost::shared_ptr<bool> is_first_;
		boost::shared_ptr<outputter_type> outputter_;
	private:
		reference dereference() const {
			return *outputter_;
		}
		void increment() const {}
		void decrement() const {}
		void advance(difference_type n) const {}
	public:
		ostream_manip_iterator(
			ostream_type& ostream,
			typename boost::call_traits<Manip>::param_type manip,
			delim_type delim = 0
			)
			: ostream_(ostream)
			, manip_(manip)
			, delim_(delim)
			, is_first_(boost::make_shared<bool>(true))
		{
			outputter_ = boost::make_shared<outputter_type>(boost::ref(*this));
		}
		void output(typename boost::call_traits<output_value_type>::param_type value) {
			if (delim_) {
				if (*is_first_) {
					*is_first_ = false;
				} else {
					*ostream_ << delim_;
				}
			}
			*ostream_ << manip_ << value;
		}
	};
	//
	// ostream_manip_iterator_outputter
	//
	template <typename T, typename Manip, typename Elem, typename Traits>
	class ostream_manip_iterator_outputter {
	private:
		typedef ostream_manip_iterator_outputter this_type;
	public:
	public:
		typedef T output_value_type;
		typedef Manip manip_type;
		typedef Elem char_type;
		typedef Traits traits_type;
		typedef ostream_manip_iterator<output_value_type, manip_type, char_type, traits_type> target_type;
	private:
		sprig::reference_holder<target_type> target_;
	public:
		explicit ostream_manip_iterator_outputter(target_type& target)
			: target_(target)
		{}
		this_type& operator=(typename boost::call_traits<output_value_type>::param_type value) {
			target_->output(value);
			return *this;
		}
	};
	//
	// make_ostream_manip_iterator
	//
	template<typename T, typename Manip, typename Elem, typename Traits>
	SPRIG_INLINE typename boost::enable_if<
		sprig::is_call_copy_param<Manip>,
		ostream_manip_iterator<T, Manip, Elem, Traits>
	>::type
	make_ostream_manip_iterator(
		std::basic_ostream<Elem, Traits>& ostream,
		Manip manip,
		typename ostream_manip_iterator<T, Manip, Elem, Traits>::delim_type delim
		)
	{
		return ostream_manip_iterator<T, Manip, Elem, Traits>(ostream, manip, delim);
	}
	template<typename T, typename Manip, typename Elem, typename Traits>
	SPRIG_INLINE typename boost::enable_if<
		sprig::is_call_copy_param<Manip>,
		ostream_manip_iterator<T, Manip, Elem, Traits>
	>::type
	make_ostream_manip_iterator(
		std::basic_ostream<Elem, Traits>& ostream,
		Manip manip
		)
	{
		return ostream_manip_iterator<T, Manip, Elem, Traits>(ostream, manip);
	}
	template<typename T, typename Manip, typename Elem, typename Traits>
	SPRIG_INLINE typename boost::disable_if<
		sprig::is_call_copy_param<Manip>,
		ostream_manip_iterator<T, Manip, Elem, Traits>
	>::type
	make_ostream_manip_iterator(
		std::basic_ostream<Elem, Traits>& ostream,
		Manip const& manip,
		typename ostream_manip_iterator<T, Manip, Elem, Traits>::delim_type delim
		)
	{
		return ostream_manip_iterator<T, Manip, Elem, Traits>(ostream, manip, delim);
	}
	template<typename T, typename Manip, typename Elem, typename Traits>
	SPRIG_INLINE typename boost::disable_if<
		sprig::is_call_copy_param<Manip>,
		ostream_manip_iterator<T, Manip, Elem, Traits>
	>::type
	make_ostream_manip_iterator(
		std::basic_ostream<Elem, Traits>& ostream,
		Manip const& manip
		)
	{
		return ostream_manip_iterator<T, Manip, Elem, Traits>(ostream, manip);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_ITERATOR_OSTREAM_MANIP_ITERATOR_HPP
