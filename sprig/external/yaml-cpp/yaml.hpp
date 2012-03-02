#ifndef SPRIG_EXTERNAL_YAML_CPP_YAML_HPP
#define SPRIG_EXTERNAL_YAML_CPP_YAML_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/config/lib/yamlcpp.hpp>

#ifdef SPRIG_CONFIG_EXTERNAL_YAML_CPP_USING_VERSION_UNDER_205
#	include <yaml.h>
#else	// #ifdef SPRIG_CONFIG_EXTERNAL_YAML_CPP_USING_VERSION_UNDER_205
#	include <yaml-cpp/yaml.h>
#endif	// #ifdef SPRIG_CONFIG_EXTERNAL_YAML_CPP_USING_VERSION_UNDER_205

#endif	// #ifndef SPRIG_EXTERNAL_YAML_CPP_YAML_HPP
