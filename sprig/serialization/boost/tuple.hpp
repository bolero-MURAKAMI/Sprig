#ifndef SPRIG_SERIALIZATION_BOOST_TUPLE_HPP
#define SPRIG_SERIALIZATION_BOOST_TUPLE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#if !defined(SPRIG_SERIALIZATION_BOOST_TUPLE_USING_NUMBERED) && !defined(SPRIG_SERIALIZATION_BOOST_TUPLE_USING_HEAD_TAIL)
#	define SPRIG_SERIALIZATION_BOOST_TUPLE_USING_NUMBERED
#endif

#if defined(SPRIG_SERIALIZATION_BOOST_TUPLE_USING_NUMBERED)
#	include <sprig/serialization/boost/detail/tuple_numbered.hpp>
#elif defined(SPRIG_SERIALIZATION_BOOST_TUPLE_USING_HEAD_TAIL)
#	include <sprig/serialization/boost/detail/tuple_head_tail.hpp>
#endif

#endif	// #ifndef SPRIG_SERIALIZATION_BOOST_TUPLE_HPP
