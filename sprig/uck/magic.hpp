#ifndef SPRIG_UCK_MAGIC_HPP
#define SPRIG_UCK_MAGIC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <string>
#include <boost/bimap/bimap.hpp>

namespace sprig {
	namespace uck {
		namespace magic {
			namespace tags {
				namespace {
					std::string const& uck_tag() {
						static std::string const v("*UCK");
						return v;
					}
					std::string const& conf_tag() {
						static std::string const v("CONF");
						return v;
					}
					std::string const& code_tag() {
						static std::string const v("CODE");
						return v;
					}
					std::string const& bits_tag() {
						static std::string const v("BITS");
						return v;
					}
					std::string const& task_tag() {
						static std::string const v("TASK");
						return v;
					}
					std::string const& pptr_tag() {
						static std::string const v("PPTR");
						return v;
					}
					std::string const& mptr_tag() {
						static std::string const v("MPTR");
						return v;
					}
				}	// anonymous-namespace
			}	// namespace types
			namespace types {
				namespace {
					std::string const& node_type() {
						static std::string const v("NODE");
						return v;
					}
					std::string const& bin_type() {
						static std::string const v(" BIN");
						return v;
					}
					std::string const& int_type() {
						static std::string const v(" INT");
						return v;
					}
					std::string const& uint_type() {
						static std::string const v("UINT");
						return v;
					}
				}	// anonymous-namespace
			}	// namespace types
			namespace indexes {
				static std::size_t const variant_node_index = 0;
				static std::size_t const variant_bin_index = 1;
				static std::size_t const variant_int_index = 2;
				static std::size_t const variant_uint_index = 3;
			}	// namespace indexes
			namespace commands {
				static unsigned char const next_command = '>';
				static unsigned char const prior_command = '<';
				static unsigned char const inc_command = '+';
				static unsigned char const dec_command = '-';
				static unsigned char const out_command = '.';
				static unsigned char const in_command = ',';
				static unsigned char const label_command = '[';
				static unsigned char const jump_command = ']';
				static unsigned char const wout_command = ':';
				static unsigned char const win_command = ';';
			}	// namespace commands
			namespace {
				//
				// type_index_bimap
				//
				boost::bimaps::bimap<std::string, std::size_t> const& type_index_bimap() {
					typedef boost::bimaps::bimap<std::string, std::size_t> result_type;
					typedef result_type::value_type value_type;
					static result_type v;
					struct initializer {
						int operator()() const {
							v.insert(value_type(types::node_type(), indexes::variant_node_index));
							v.insert(value_type(types::bin_type(), indexes::variant_bin_index));
							v.insert(value_type(types::int_type(), indexes::variant_int_index));
							v.insert(value_type(types::uint_type(), indexes::variant_uint_index));
							return 0;
						}
					};
					static int const init = initializer()();
					static_cast<void>(init);
					return v;
				}
			}	// anonymous-namespace
		}	// namespace magic
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_MAGIC_HPP