/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_LOCALE_SAVER_HPP
#define SPRIG_LOCALE_SAVER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <clocale>
#include <string>
#include <boost/noncopyable.hpp>

namespace sprig {
	//
	// locale_saver
	//
	class locale_saver
		: boost::noncopyable
	{
		int category_;
		std::string locale_;
	public:
		explicit locale_saver(int category = LC_ALL)
			: category_(category)
			, locale_(std::setlocale(category, 0))
		{}
		~locale_saver() {
			std::setlocale(category_, locale_.c_str());
		}
	};
} // namespace sprig

#endif	// #ifndef SPRIG_LOCALE_SAVER_HPP
