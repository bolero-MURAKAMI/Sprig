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
