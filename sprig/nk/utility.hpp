#ifndef SPRIG_NK_UTILITY_HPP
#define SPRIG_NK_UTILITY_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <sprig/nk/foundation.hpp>

namespace sprig {
	namespace nk {
		template<typename Range>
		created_unit_type create_unit(engine& e, Range const& source) {
			created_unit_type u(e.create_unit());
			e.allocate(*u, boost::size(source));
			BOOST_FOREACH(sprig::nk::byte_type const c, source) {
				e.load(*u, c);
			}
			return u;
		}
	}	// namespace nk
}	// namespace sprig

#endif	// #ifndef SPRIG_NK_UTILITY_HPP
