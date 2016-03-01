/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_EXTERNAL_YAML_CPP_YAML_HPP
#define SPRIG_EXTERNAL_YAML_CPP_YAML_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/config/lib/yamlcpp.hpp>

#if defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 205)
#	include <yaml.h>
#else	// #if defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 205)
#	include <yaml-cpp/yaml.h>
#endif

#endif	// #ifndef SPRIG_EXTERNAL_YAML_CPP_YAML_HPP
