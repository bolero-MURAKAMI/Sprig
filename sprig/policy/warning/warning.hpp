#ifndef SPRIG_POLICY_WARNING_WARNING_HPP
#define SPRIG_POLICY_WARNING_WARNING_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/pred_warning.hpp>

//
// SPRIG_POLICY_WARNING((pred<x,...>))
//
#define SPRIG_POLICY_WARNING(PRED) \
	SPRIG_PRED_WARNING(PRED)

#endif	// #ifndef SPRIG_POLICY_WARNING_WARNING_HPP
