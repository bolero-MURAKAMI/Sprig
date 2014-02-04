/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TYPE_TRAITS_HPP
#define SPRIG_TYPE_TRAITS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/type_traits/is_const_reference.hpp>
#include <sprig/type_traits/is_non_const_reference.hpp>
#include <sprig/type_traits/is_call_reference_param.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/add_const_reference.hpp>
#include <sprig/type_traits/remove_const_reference.hpp>
#include <sprig/type_traits/c_str_element.hpp>

#endif	// #ifndef SPRIG_TYPE_TRAITS_HPP
