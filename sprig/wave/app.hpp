/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_WAVE_APP_HPP
#define SPRIG_WAVE_APP_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/println.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/iostreams/adapter.hpp>
#include <sprig/cindent.hpp>
#include <sprig/cin_acquire.hpp>

namespace sprig {
	namespace wave {
		namespace app {
			//
			// typedefs
			//
			typedef boost::program_options::options_description options_description_type;
			typedef boost::program_options::variables_map variables_map_type;
			//
			// options
			//
			class options {
			public:
				typedef std::string string_type;
				typedef unsigned length_type;
			private:
				options_description_type common_desc_;
				options_description_type command_line_desc_;
			public:
				static length_type const m_default_line_length;
			public:
				options(
					string_type const& caption = "options",
					string_type const& default_config = "config.txt",
					length_type line_length = m_default_line_length
					)
					: common_desc_(caption + "(common)", line_length)
					, command_line_desc_(caption + "(command-line)", line_length)
				{
					//	COMMENT: 共通オプションの設定
					common_desc_.add_options()
						("support-long_long", "Enable long long support.")
						("support-variadics", "Enable variadics and placemarkers.")
						("support-c99", "Enable C99 mode.")
						("support-insert_whitespace", "Enable insert whitespace.")
						("support-preserve_comments", "Enable preserve comments.")
						("support-no_character_validation", "Enable no character validation.")
						("support-convert_trigraphs", "Enable convert trigraphs.")
						("support-single_line", "Enable single line.")
						("support-prefer_pp_numbers", "Enable prefer pp numbers.")
						("support-emit_line_directives", "Enable emit line directives.")
						("support-emit_pragma_directives", "Enable emit pragma directives.")
						("disable-include_guard_detection", "Disable include guard detection.")
						(
							"macro",
							boost::program_options::value<std::vector<std::string> >(),
							"Specify a macro to define."
							)
						(
							"sysinclude",
							boost::program_options::value<std::vector<std::string> >(),
							"Specify an additional system include directory."
							)
						(
							"include",
							boost::program_options::value<std::vector<std::string> >(),
							"Specify an additional include directory."
							)
						(
							"input-file,i",
							boost::program_options::value<std::string>(),
							"Input source file."
							)
						(
							"output-file,o",
							boost::program_options::value<std::string>(),
							"Output source file."
							)
						("output-stdout", "Output source to stdout.")
						("output-log", "Output source to log.")
						(
							"output-depth_limit",
							boost::program_options::value<std::string>()->default_value("-1"),
							"Output source file depth limit."
							)
						(
							"log-file,l",
							boost::program_options::value<std::string>(),
							"Output log file."
							)
						("log-stdout", "Output log to stdout.")
						("log-trace_include", "Output log for include tracing.")
						;
					//	COMMENT: コマンドラインオプションの設定
					command_line_desc_.add_options()
						("help,h", "Print out program usage. (this message)")
						(
							"config,c",
							boost::program_options::value<std::string>()->default_value(default_config),
							"Configration file."
							)
						;
					//	COMMENT: コマンドラインに共通オプションを追加
					command_line_desc_.add(common_desc_);
				}
				options_description_type const& common_desc() const {
					return common_desc_;
				}
				options_description_type const& command_line_desc() const {
					return command_line_desc_;
				}
				template<typename Char>
				bool analy(
					variables_map_type& vmap,
					int argc,
					Char* argv[]
					) const
				{
					//	COMMENT: コマンドラインからオプション解析
					boost::program_options::store(
						boost::program_options::parse_command_line(argc, argv, command_line_desc_),
						vmap
						);
					//	COMMENT: （存在すれば）ファイルからからオプション解析
					boost::filesystem::path config_path(vmap["config"].as<std::string>());
					bool exists_config
						= boost::filesystem::exists(config_path)
						&& !boost::filesystem::is_directory(config_path)
						;
					if (exists_config) {
						boost::filesystem::ifstream ifs(config_path);
						boost::program_options::store(
							boost::program_options::parse_config_file(ifs, common_desc_),
							vmap
							);
					}
					boost::program_options::notify(vmap);
					//	COMMENT: ファイルが存在したか返す
					return exists_config;
				}
			};
			options::length_type const options::m_default_line_length = options_description_type::m_default_line_length;
			//
			// include_trace_hook
			//
			template <typename Token, typename Elem, typename Traits = std::char_traits<Elem> >
			class include_trace_hook
				: public boost::wave::context_policies::eat_whitespace<Token>
			{
			public:
				typedef Elem element_type;
				typedef Traits traits_type;
				typedef std::basic_ostream<element_type, traits_type> ostream_type;
			private:
				ostream_type& log_;
				std::vector<std::string> filename_stack_;
				bool logging_;
			public:
				explicit include_trace_hook(ostream_type& log, bool logging = true)
					: log_(log)
					, logging_(logging)
				{}
			public:
				template<typename Context>
				bool found_include_directive(
					Context const& context,
					std::string const& filename,
					bool include_next
					)
				{
					if (logging_) {
						println(log_)("// include : ")(filename);
					}
					return false;
				}
				template <typename Context>
				void opened_include_file(
					Context const& context,
					std::string const& rel_filename,
					std::string const& abs_filename,
					bool is_system_include
					)
				{
					if (logging_) {
						filename_stack_.push_back(abs_filename);
						println(log_)("// opened : ")(filename_stack_.back());
					}
				}
				template <typename Context>
				void returning_from_include_file(
					Context const& context
					)
				{
					if (logging_) {
						println(log_)("// returning : ")(filename_stack_.back());
						filename_stack_.pop_back();
					}
				}
			};
			//
			// context_traits
			//
			template<typename Elem>
			struct context_traits {
				typedef typename std::basic_string<Elem>::iterator iterator_type;
				typedef boost::wave::cpplexer::lex_iterator<
					boost::wave::cpplexer::lex_token<>
				> lex_iterator_type;
				typedef boost::wave::iteration_context_policies::load_file_to_string input_policy_type;
				typedef include_trace_hook<
					lex_iterator_type::token_type,
					Elem
				> context_policy_type;
				typedef context_policy_type hooks_type;
				typedef boost::wave::context<
					iterator_type,
					lex_iterator_type,
					input_policy_type,
					context_policy_type
				> context_type;
			};
		}	// namespace app
		//
		// print_value
		//
		SPRIG_INLINE void print_value(
			string_argument const& name,
			string_argument const& value
			)
		{
			println(icout())("--")(name)(" = ")(value);
		}
		//
		// print_option_exists
		//
		SPRIG_INLINE bool print_option_exists(
			boost::program_options::variables_map const& vmap,
			std::string const& name
			)
		{
			bool exists = vmap.count(name) != 0;
			print_value(name, (exists ? "yes" : "no"));
			return exists;
		}
		//
		// print_option_as
		//
		template<typename T>
		SPRIG_INLINE T const& print_option_as(
			boost::program_options::variables_map const& vmap,
			std::string const& name
			)
		{
			T const& value = vmap[name].as<T>();
			print_value(name, value);
			return value;
		}
		//
		// analy_options
		//
		SPRIG_INLINE void analy_options(
			boost::program_options::variables_map& vmap,
			int argc,
			char* argv[]
			)
		{
			println(icout())("Analy options:");
			cindent ci("  ");

			app::options options;
			bool const exists_config = options.analy(vmap, argc, argv);

			print_option_as<std::string>(vmap, "config");
			if (exists_config) {
				println(icout())("Configration file found.");
			} else {
				println(icout())("Configration file not found.");
			}

			if (vmap.count("help")) {
				println(icout())("Show help:");
				std::cout << options.command_line_desc();
				std::string s;
				cin_acquire_any(s, ">Press Enter: ");
			}

			println(icout())("Succeeded!");
		}
		//
		// is_file_exists
		//
		struct is_file_exists {
			bool operator()(std::string const& v) const {
				boost::filesystem::path file_path(v);
				return boost::filesystem::exists(file_path)
					&& !boost::filesystem::is_directory(file_path)
					;
			}
		};
		//
		// get_input_path
		//
		SPRIG_INLINE boost::filesystem::path get_input_path(
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Get input path:");
			cindent ci("  ");

			struct acquire_input {
				void operator()(boost::filesystem::path& input_path) const {
					std::string input_path_string;
					cin_acquire_any_repeat_until(input_path_string, is_file_exists(), ">input-file: ");
					input_path = input_path_string;
				}
			};

			boost::filesystem::path input_path;
			if (vmap.count("input-file")) {
				println(icout())("Input file configrated.");
				input_path = print_option_as<std::string>(vmap, "input-file");
				if (boost::filesystem::exists(input_path)
					&& !boost::filesystem::is_directory(input_path)
					)
				{
					println(icout())("Input file found.");
				} else {
					println(icout())("Input file not found.");
					acquire_input()(input_path);
				}
			} else {
				println(icout())("Input file not configrated.");
				acquire_input()(input_path);
			}

			print_value("input-file", input_path);

			println(icout())("Succeeded!");
			return input_path;
		}
		//
		// get_input
		//
		template<typename Elem>
		SPRIG_INLINE std::basic_string<Elem> get_input(
			boost::filesystem::path const& path,
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Get input:");
			cindent ci("  ");

			std::basic_string<Elem> input;
			{
				boost::filesystem::ifstream ifs(path);
				std::string buffer(
					std::istreambuf_iterator<char>(ifs.rdbuf()),
					std::istreambuf_iterator<char>()
					);
				input = str_cast<std::basic_string<Elem> >(buffer);
			}

			println(icout())("Succeeded!");
			return input;
		}
		//
		// setup_context
		//
		template<typename Context>
		SPRIG_INLINE void setup_context(
			Context& context,
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Setup context:");
			cindent ci("  ");

			unsigned long support = boost::wave::support_cpp;
			bool support_long_long = print_option_exists(vmap, "support-long_long");
			bool support_variadics = print_option_exists(vmap, "support-variadics");
			bool support_c99 = print_option_exists(vmap, "support-c99");
			bool support_insert_whitespace = print_option_exists(vmap, "support-insert_whitespace");
			bool support_preserve_comments = print_option_exists(vmap, "support-preserve_comments");
			bool support_no_character_validation = print_option_exists(vmap, "support-no_character_validation");
			bool support_convert_trigraphs = print_option_exists(vmap, "support-convert_trigraphs");
			bool support_single_line = print_option_exists(vmap, "support-single_line");
			bool support_prefer_pp_numbers = print_option_exists(vmap, "support-prefer_pp_numbers");
			bool support_emit_line_directives = print_option_exists(vmap, "support-emit_line_directives");
			bool support_emit_pragma_directives = print_option_exists(vmap, "support-emit_pragma_directives");
			bool disable_include_guard_detection = print_option_exists(vmap, "disable-include_guard_detection");

			if (support_long_long) {
				support |= boost::wave::support_option_long_long;
			}
			if (support_variadics) {
				support |= boost::wave::support_option_variadics;
			}
			if (support_c99) {
				support |= boost::wave::support_c99;
			}
			if (support_insert_whitespace) {
				support |= boost::wave::support_option_insert_whitespace;
			}
			if (support_preserve_comments) {
				support |= boost::wave::support_option_preserve_comments;
			}
			if (support_no_character_validation) {
				support |= boost::wave::support_option_no_character_validation;
			}
			if (support_convert_trigraphs) {
				support |= boost::wave::support_option_convert_trigraphs;
			}
			if (support_single_line) {
				support |= boost::wave::support_option_single_line;
			}
			if (support_prefer_pp_numbers) {
				support |= boost::wave::support_option_prefer_pp_numbers;
			}
			if (support_emit_line_directives) {
				support |= boost::wave::support_option_emit_line_directives;
			}
			if (support_emit_pragma_directives) {
				support |= boost::wave::support_option_emit_pragma_directives;
			}
			if (disable_include_guard_detection) {
				support &= ~boost::wave::support_option_include_guard_detection;
			}

			std::vector<std::string> macros;
			std::vector<std::string> sysincludes;
			std::vector<std::string> includes;
			if (vmap.count("macro")) {
				macros = vmap["macro"].as<std::vector<std::string> >();
			}
			if (vmap.count("sysinclude")) {
				sysincludes = vmap["sysinclude"].as<std::vector<std::string> >();
			}
			if (vmap.count("include")) {
				includes = vmap["include"].as<std::vector<std::string> >();
			}
			BOOST_FOREACH(std::string const& e, macros) {
				print_value("macro", e);
			}
			BOOST_FOREACH(std::string const& e, sysincludes) {
				print_value("sysinclude", e);
			}
			BOOST_FOREACH(std::string const& e, includes) {
				print_value("include", e);
			}

			context.set_language(boost::wave::language_support(support));

			BOOST_FOREACH(std::string const& e, macros) {
				context.add_macro_definition(e);
			}
			BOOST_FOREACH(std::string const& e, sysincludes) {
				context.add_sysinclude_path(e.c_str());
			}
			BOOST_FOREACH(std::string const& e, includes) {
				context.add_include_path(e.c_str());
			}

			println(icout())("Succeeded!");
		}
		//
		// push_stdout_output
		//
		template<typename Elem>
		SPRIG_INLINE void push_stdout_output(
			boost::iostreams::filtering_stream<boost::iostreams::output, Elem>& os,
			typename boost::enable_if<boost::is_same<Elem, char> >::type* = 0
			)
		{
			os.push(std::cout);
		}
		template<typename Elem>
		SPRIG_INLINE void push_stdout_output(
			boost::iostreams::filtering_stream<boost::iostreams::output, Elem>& os,
			typename boost::enable_if<boost::is_same<Elem, wchar_t> >::type* = 0
			)
		{
			os.push(std::wcout);
		}
		//
		// setup_output
		//
		template<typename Elem>
		SPRIG_INLINE void setup_output(
			boost::iostreams::filtering_stream<boost::iostreams::output, Elem>& code,
			boost::iostreams::filtering_stream<boost::iostreams::output, Elem>& log,
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Setup output:");
			cindent ci("  ");

			boost::filesystem::path output_file;
			if (vmap.count("output-file")) {
				println(icout())("Output file configrated.");
				output_file = print_option_as<std::string>(vmap, "output-file");
			} else {
				println(icout())("Output file not configrated.");
			}
			bool output_stdout = print_option_exists(vmap, "output-stdout");
			bool output_log = print_option_exists(vmap, "output-log");

			boost::filesystem::path log_file;
			if (vmap.count("log-file")) {
				println(icout())("Log file configrated.");
				log_file = print_option_as<std::string>(vmap, "log-file");
			} else {
				println(icout())("Log file not configrated.");
			}
			bool log_stdout = print_option_exists(vmap, "log-stdout");

			if (vmap.count("output-file")) {
				if (output_stdout
					|| output_log && vmap.count("log-file")
					)
				{
					code.push(boost::iostreams::tee(boost::iostreams::file_sink(output_file.string())));
				} else {
					code.push(boost::iostreams::file_sink(output_file.string()));
				}
			}
			if (output_log && vmap.count("log-file")) {
				if (output_stdout) {
					code.push(boost::iostreams::tee(iostreams::to_sink(log)));
				} else {
					code.push(iostreams::to_sink(log));
				}
			}
			if (output_stdout) {
				push_stdout_output<Elem>(code);
			}

			if (vmap.count("log-file")) {
				if (log_stdout) {
					log.push(boost::iostreams::tee(boost::iostreams::file_sink(log_file.string())));
				} else {
					log.push(boost::iostreams::file_sink(log_file.string()));
				}
			}
			if (log_stdout) {
				push_stdout_output<Elem>(log);
			}

			println(icout())("Succeeded!");
		}
		//
		// iterate_context
		//
		template<typename Context, typename Elem, typename Traits>
		SPRIG_INLINE bool iterate_context(
			Context& context,
			std::basic_ostream<Elem, Traits>& code,
			std::basic_ostream<Elem, Traits>& log,
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Iterate context:");
			cindent ci("  ");

			bool succeeded = true;

			int output_depth_limit = -1;
			try {
				output_depth_limit = boost::lexical_cast<int>(
					print_option_as<std::string>(vmap, "output-depth_limit")
					);
			} catch (boost::bad_lexical_cast&) {
				println(icout())("Exception handling.");
				{
					println(icout())("Error Details:");
					cindent ci("  ");

					println(icout())("Option \"output-depth_limit\" could not be converted to a numeric value.");
				}
				throw;
			}

			{
				println(icout())("Iteration:");
				cindent ci("  ");

				typename Context::iterator_type i = context.begin();
				typename Context::iterator_type last = context.end();
				for (; ; ) {
					try {
						if (i == last) {
							break;
						}
						if (output_depth_limit < 0
							|| context.get_iteration_depth() <= static_cast<std::size_t>(output_depth_limit)
							)
						{
							code << i->get_value();
						}
						++i;
					} catch (boost::wave::preprocess_exception& e) {
						code << std::flush;

						int const severity = e.get_severity();
						char const* const severity_text = boost::wave::util::get_severity(severity);

						println(log)("// ")(severity_text)(" : ")(e.file_name())("(")(e.line_no())(")(")(e.column_no())(") : ")(e.description());

						bool should_interrupt = false;
						switch (severity) {
						case boost::wave::util::severity_remark:
						case boost::wave::util::severity_warning:
							break;
						case boost::wave::util::severity_error:
						case boost::wave::util::severity_fatal:
						case boost::wave::util::severity_commandline_error:
						default:
							should_interrupt = true;
							break;
						}
						if (should_interrupt) {
							succeeded = false;
							println(icout())("Preprocess interrupted.");
							break;
						}
					} catch (...) {
						code << std::flush;
						println(icout())("Unknown error in preprocess.");
						throw;
					}
				}
				code << std::flush;
				if (succeeded) {
					println(log)("// message : Preprocess succeeded.");
				} else {
					println(log)("// message : Preprocess interrupted.");
				}
			}

			if (succeeded) {
				println(icout())("Succeeded!");
			}
			return succeeded;
		}
		//
		// setup_hooks
		//
		template<typename Elem>
		SPRIG_INLINE typename app::context_traits<Elem>::hooks_type setup_hooks(
			boost::iostreams::filtering_stream<boost::iostreams::output, Elem>& log,
			boost::program_options::variables_map const& vmap
			)
		{
			println(icout())("Setup hooks:");
			cindent ci("  ");

			bool log_trace_include = print_option_exists(vmap, "log-trace_include");

			println(icout())("Succeeded!");
			return typename app::context_traits<Elem>::hooks_type(log, log_trace_include);
		}
		//
		// execute
		//
		SPRIG_INLINE bool execute(int argc, char* argv[]) {
			println(icout())("Execute:");
			cindent ci("  ");

			//	COMMENT: オプション解析
			boost::program_options::variables_map vmap;
			analy_options(vmap, argc, argv);

			//	COMMENT: 入力ファイル取得
			boost::filesystem::path input_path = get_input_path(vmap);
			std::string input = get_input<char>(input_path, vmap);

			//	COMMENT: 出力セットアップ
			boost::iostreams::filtering_stream<boost::iostreams::output, char> code;
			boost::iostreams::filtering_stream<boost::iostreams::output, char> log;
			setup_output<char>(code, log, vmap);

			//	COMMENT: フック処理セットアップ
			app::context_traits<char>::hooks_type hooks = setup_hooks(log, vmap);

			//	COMMENT: コンテキストセットアップ
			app::context_traits<char>::context_type context(
				input.begin(),
				input.end(),
				input_path.string().c_str(),
				hooks
				);
			setup_context(context, vmap);

			//	COMMENT: イテレ―ション
			bool succeeded = iterate_context(context, code, log, vmap);

			if (succeeded) {
				println(icout())("Succeeded!");
			}

			return succeeded;
		}
	}	// namespace wave
}	// namespace sprig

#endif	// #ifndef SPRIG_WAVE_APP_HPP
