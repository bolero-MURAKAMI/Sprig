/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_ENGINE_TESTER_HPP
#define SPRIG_BRAIN_ENGINE_TESTER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <memory>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <sprig/use_default.hpp>
#include <sprig/brain/brain.hpp>
#include <sprig/brain/utils.hpp>
#include <sprig/brain/f_ck.hpp>
#include <sprig/brain/ook.hpp>
#include <sprig/performance_timer.hpp>
#include <sprig/cindent.hpp>

namespace sprig {
	namespace brain {
		//
		// engine_tester
		//
		template<
			typename Types = sprig::use_default,
			typename Commands = sprig::use_default,
			typename Memory = sprig::use_default,
			typename Position = sprig::use_default,
			typename Buffer = sprig::use_default,
			typename IO = sprig::use_default,
			typename Iteration = sprig::use_default,
			typename Executor = sprig::use_default,
			typename Engine = sprig::use_default
		>
		struct engine_tester {
		public:
			typedef typename sprig::select_default<
				Engine,
				f_ck::bf_engine<
					Types,
					Commands,
					Memory,
					Position,
					Buffer,
					IO,
					Iteration,
					Executor
				>
			>::type engine_type;
		public:
			static std::auto_ptr<engine_interface<Types> > create() {
				sprig::csection cs("create");
				std::auto_ptr<engine_interface<Types> > p(new engine_type());
				sprig::cout_section_comment("Succeeded!");
				return p;
			}
			template<typename Range>
			static void initialize(engine_interface<Types>& engine, Range const& source) {
				sprig::csection cs("initialize");
				engine.init_begin();
				BOOST_FOREACH(typename engine_type::byte_type b, source) {
					engine.load(b);
				}
				engine.init_end();
				sprig::cout_section_comment("Succeeded!");
			}
			static void execute(engine_interface<Types>& engine) {
				sprig::csection cs("execute");
				sprig::performance_timer timer;
				std::size_t step = 0;
				try {
					while (true) {
						engine.exec();
						++step;
					}
				} catch (engine_exit const& e) {
					sprig::cout_section_comment(e.what());
				} catch (...) {
					sprig::cout_section_line("step", step);
					throw;
				}
				sprig::cout_section_line("step", step);
				sprig::cout_section_line("elapsed", boost::format("%f[ms]") % (timer.elapsed() * 1000));
				sprig::cout_section_comment("Succeeded!");
			}
			template<typename Range>
			static void test(Range const& source) {
				sprig::csection cs("test");
				std::auto_ptr<engine_interface<Types> > engine = create();
				initialize(*engine, source);
				execute(*engine);
				sprig::cout_section_comment("Succeeded!");
			}
		};
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_ENGINE_TESTER_HPP
