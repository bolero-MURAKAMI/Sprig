#ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_HPP
#define SPRIG_PROPERTY_TREE_YAML_PARSER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iterator>
#include <vector>
#include <string>
#include <locale>
#include <ostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <sprig/external/yaml-cpp/yaml.hpp>
#include <sprig/property_tree/yaml_parser_error.hpp>
#include <sprig/property_tree/yaml_parser_flags.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	namespace property_tree {
		namespace yaml_parser {
			namespace parser_detail {
				//
				// is_internal_implemented
				//
				template<typename Ptree>
				class is_internal_implemented
					: public boost::mpl::and_<
						boost::is_same<typename Ptree::key_type, std::string>,
						boost::is_same<typename Ptree::data_type, std::string>
					>
				{};
			}	// namespace parser_detail
			namespace parser_detail {
				//
				// read_yaml_impl_process
				//
#if defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 205)
				template<typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.GetType()) {
					case YAML::CT_NONE:
						break;
					case YAML::CT_SCALAR:
						node >> pt.data();
						break;
					case YAML::CT_SEQUENCE:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename);
						}
						break;
					case YAML::CT_MAP:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it.first();
							YAML::Node const& second = it.second();
							if (first.GetType() != YAML::CT_NONE && first.GetType() != YAML::CT_SCALAR) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.GetType() == YAML::CT_SCALAR) {
								first >> key;
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename,
					Converter converter
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.GetType()) {
					case YAML::CT_NONE:
						break;
					case YAML::CT_SCALAR:
						{
							std::string temp;
							node >> temp;
							pt.data() = converter.from_str(temp);
						}
						break;
					case YAML::CT_SEQUENCE:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename, converter);
						}
						break;
					case YAML::CT_MAP:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it.first();
							YAML::Node const& second = it.second();
							if (first.GetType() != YAML::CT_NONE && first.GetType() != YAML::CT_SCALAR) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.GetType() == YAML::CT_SCALAR) {
								std::string temp;
								first >> temp;
								key = converter.from_str(temp);
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename, converter);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
#elif defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 300)
				template<typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.Type()) {
					case YAML::NodeType::Null:
						break;
					case YAML::NodeType::Scalar:
						node >> pt.data();
						break;
					case YAML::NodeType::Sequence:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename);
						}
						break;
					case YAML::NodeType::Map:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it.first();
							YAML::Node const& second = it.second();
							if (first.Type() != YAML::NodeType::Null && first.Type() != YAML::NodeType::Scalar) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.Type() == YAML::NodeType::Scalar) {
								first >> key;
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename,
					Converter converter
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.Type()) {
					case YAML::NodeType::Null:
						break;
					case YAML::NodeType::Scalar:
						{
							std::string temp;
							node >> temp;
							pt.data() = converter.from_str(temp);
						}
						break;
					case YAML::NodeType::Sequence:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename, converter);
						}
						break;
					case YAML::NodeType::Map:
						for (YAML::Iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it.first();
							YAML::Node const& second = it.second();
							if (first.Type() != YAML::NodeType::Null && first.Type() != YAML::NodeType::Scalar) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.Type() == YAML::NodeType::Scalar) {
								std::string temp;
								first >> temp;
								key = converter.from_str(temp);
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename, converter);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
#else	// #elif defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 300)
				template<typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.Type()) {
					case YAML::NodeType::Null:
						break;
					case YAML::NodeType::Scalar:
						pt.data() = node.Scalar();
						break;
					case YAML::NodeType::Sequence:
						for (YAML::Node::const_iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename);
						}
						break;
					case YAML::NodeType::Map:
						for (YAML::Node::const_iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it.first();
							YAML::Node const& second = it.second();
							if (first.Type() != YAML::NodeType::Null && first.Type() != YAML::NodeType::Scalar) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.Type() == YAML::NodeType::Scalar) {
								key = first.Scalar();
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_yaml_impl_process(
					YAML::Node const& node,
					Ptree& pt,
					std::string const& filename,
					Converter converter
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					switch (node.Type()) {
					case YAML::NodeType::Null:
						break;
					case YAML::NodeType::Scalar:
						pt.data() = converter.from_str(node.Scalar());
						break;
					case YAML::NodeType::Sequence:
						for (YAML::Node::const_iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(*it, pt.back().second, filename, converter);
						}
						break;
					case YAML::NodeType::Map:
						for (YAML::Node::const_iterator it = node.begin(), last_it = node.end(); it != last_it; ++it) {
							YAML::Node const& first = it->first;
							YAML::Node const& second = it->second;
							if (first.Type() != YAML::NodeType::Null && first.Type() != YAML::NodeType::Scalar) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("unsupported multi-content-key", filename, 0)
									);
							}
							key_type key;
							if (first.Type() == YAML::NodeType::Scalar) {
								key = converter.from_str(first.Scalar());
							}
							pt.push_back(value_type(key, ptree_type()));
							read_yaml_impl_process(second, pt.back().second, filename, converter);
						}
						break;
					default:
						SPRIG_THROW_EXCEPTION(
							yaml_parser_error("undefined content-type", filename, 0)
							);
					}
				}
#endif
				//
				// read_yaml_impl
				//
#if defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 300)
				template<typename Ptree>
				SPRIG_INLINE void read_yaml_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					int flags = 0,
					typename boost::enable_if<
						is_internal_implemented<Ptree>
					>::type* = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					YAML::Parser parser(stream);
					YAML::Node doc;
					if (flags & reader_flags::multi_document) {
						while (parser.GetNextDocument(doc)) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(doc, pt.back().second, filename);
						}
					} else {
						if (!parser.GetNextDocument(doc)) {
							SPRIG_THROW_EXCEPTION(
								yaml_parser_error("empty source", filename, 0)
								);
						}
						read_yaml_impl_process(doc, pt, filename);
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_yaml_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					Converter converter,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					key_type src;
					std::copy(
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(stream),
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(),
						std::back_inserter(src)
						);
					{
						std::istringstream stream(
							converter.to_str(src)
							);
						YAML::Parser parser(stream);
						YAML::Node doc;
						if (flags & reader_flags::multi_document) {
							while (parser.GetNextDocument(doc)) {
								pt.push_back(value_type(key_type(), ptree_type()));
								read_yaml_impl_process(doc, pt.back().second, filename, converter);
							}
						} else {
							if (!parser.GetNextDocument(doc)) {
								SPRIG_THROW_EXCEPTION(
									yaml_parser_error("empty source", filename, 0)
									);
							}
							read_yaml_impl_process(doc, pt, filename, converter);
						}
					}
				}
#else	// #if defined(SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION) && (SPRIG_CONFIG_EXTERNAL_YAML_CPP_VERSION <= 300)
				template<typename Ptree>
				SPRIG_INLINE void read_yaml_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					int flags = 0,
					typename boost::enable_if<
						is_internal_implemented<Ptree>
					>::type* = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					if (flags & reader_flags::multi_document) {
						std::vector<YAML::Node> docs = YAML::LoadAll(stream);
						BOOST_FOREACH(std::vector<YAML::Node>::value_type const& doc, docs) {
							pt.push_back(value_type(key_type(), ptree_type()));
							read_yaml_impl_process(doc, pt.back().second, filename);
						}
					} else {
						YAML::Node doc = YAML::Load(stream);
						read_yaml_impl_process(doc, pt, filename);
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void read_yaml_impl(
					std::basic_istream<typename Ptree::key_type::value_type>& stream,
					Ptree& pt,
					std::string const& filename,
					Converter converter,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					key_type src;
					std::copy(
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(stream),
						std::istreambuf_iterator<typename Ptree::key_type::value_type>(),
						std::back_inserter(src)
						);
					{
						std::istringstream stream(
							converter.to_str(src)
							);
						if (flags & reader_flags::multi_document) {
							std::vector<YAML::Node> docs = YAML::LoadAll(stream);
							BOOST_FOREACH(std::vector<YAML::Node>::value_type const& doc, docs) {
								pt.push_back(value_type(key_type(), ptree_type()));
								read_yaml_impl_process(doc, pt.back().second, filename, converter);
							}
						} else {
							YAML::Node doc = YAML::Load(stream);
							read_yaml_impl_process(doc, pt, filename, converter);
						}
					}
				}
#endif
			}	// namespace parser_detail
			//
			// read_yaml
			//
			template<typename Ptree>
			SPRIG_INLINE void read_yaml(
				std::basic_istream<typename Ptree::key_type::value_type>& stream,
				Ptree& pt,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				parser_detail::read_yaml_impl(stream, pt, std::string(), flags);
			}
			template<typename Ptree>
			SPRIG_INLINE void read_yaml(
				std::string const& filename,
				Ptree& pt,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				std::basic_ifstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						yaml_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::read_yaml_impl(stream, pt, filename, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void read_yaml(
				std::basic_istream<typename Ptree::key_type::value_type>& stream,
				Ptree& pt,
				Converter converter,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				parser_detail::read_yaml_impl(stream, pt, std::string(), converter, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void read_yaml(
				std::string const& filename,
				Ptree& pt,
				Converter converter,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_reader_flags(flags));
				std::basic_ifstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						yaml_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::read_yaml_impl(stream, pt, filename, converter, flags);
			}
			namespace parser_detail {
				//
				// write_yaml_impl_process
				//
				template<typename Ptree>
				SPRIG_INLINE void write_yaml_impl_process(
					YAML::Emitter& emitter,
					Ptree const& pt,
					std::string const& filename
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					if (pt.empty()) {
						emitter << pt.data();
					} else {
						if (!pt.data().empty()) {
							SPRIG_THROW_EXCEPTION(
								yaml_parser_error("invalid format for YAML", filename, 0)
								);
						}
						if (pt.count(key_type()) == pt.size()) {
							emitter << YAML::BeginSeq;
							BOOST_FOREACH(value_type const& e, pt) {
								write_yaml_impl_process(emitter, e.second, filename);
							}
							emitter << YAML::EndSeq;
						} else {
							emitter << YAML::BeginMap;
							BOOST_FOREACH(value_type const& e, pt) {
								emitter << YAML::Key << e.first;
								emitter << YAML::Value;
								write_yaml_impl_process(emitter, e.second, filename);
							}
							emitter << YAML::EndMap;
						}
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void write_yaml_impl_process(
					YAML::Emitter& emitter,
					Ptree const& pt,
					std::string const& filename,
					Converter converter
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					if (pt.empty()) {
						emitter << converter.to_str(pt.data());
					} else {
						if (!pt.data().empty()) {
							SPRIG_THROW_EXCEPTION(
								yaml_parser_error("invalid format for YAML", filename, 0)
								);
						}
						if (pt.count(key_type()) == pt.size()) {
							emitter << YAML::BeginSeq;
							BOOST_FOREACH(value_type const& e, pt) {
								write_yaml_impl_process(emitter, e.second, filename, converter);
							}
							emitter << YAML::EndSeq;
						} else {
							emitter << YAML::BeginMap;
							BOOST_FOREACH(value_type const& e, pt) {
								emitter << YAML::Key << converter.to_str(e.first);
								emitter << YAML::Value;
								write_yaml_impl_process(emitter, e.second, filename, converter);
							}
							emitter << YAML::EndMap;
						}
					}
				}
				//
				// write_yaml_impl
				//
				template<typename Ptree>
				SPRIG_INLINE void write_yaml_impl(
					std::basic_ostream<typename Ptree::key_type::value_type>& stream,
					Ptree const& pt,
					std::string const& filename,
					int flags = 0,
					typename boost::enable_if<
						is_internal_implemented<Ptree>
					>::type* = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					if (flags & writer_flags::multi_document) {
						if (pt.count(key_type()) != pt.size()) {
							SPRIG_THROW_EXCEPTION(
								yaml_parser_error("illegal multi-document", filename, 0)
								);
						}
						{
							YAML::Emitter emitter;
							BOOST_FOREACH(value_type const& e, pt) {
								emitter << YAML::BeginDoc;
								write_yaml_impl_process(emitter, e.second, filename);
								if (flags & writer_flags::insert_end_of_document) {
									emitter << YAML::EndDoc;
								}
							}
							stream << emitter.c_str() << std::endl;
						}
					} else {
						YAML::Emitter emitter;
						emitter << YAML::BeginDoc;
						write_yaml_impl_process(emitter, pt, filename);
						if (flags & writer_flags::insert_end_of_document) {
							emitter << YAML::EndDoc;
						}
						stream << emitter.c_str() << std::endl;
					}
				}
				template<typename Converter, typename Ptree>
				SPRIG_INLINE void write_yaml_impl(
					std::basic_ostream<typename Ptree::key_type::value_type>& stream,
					Ptree const& pt,
					std::string const& filename,
					Converter converter,
					int flags = 0
					)
				{
					typedef Ptree ptree_type;
					typedef typename ptree_type::value_type value_type;
					typedef typename ptree_type::key_type key_type;
					if (flags & writer_flags::multi_document) {
						if (pt.count(key_type()) != pt.size()) {
							SPRIG_THROW_EXCEPTION(
								yaml_parser_error("illegal multi-document", filename, 0)
								);
						}
						{
							YAML::Emitter emitter;
							BOOST_FOREACH(value_type const& e, pt) {
								emitter << YAML::BeginDoc;
								write_yaml_impl_process(emitter, e.second, filename, converter);
								if (flags & writer_flags::insert_end_of_document) {
									emitter << YAML::EndDoc;
								}
							}
							stream << converter.from_str(emitter.c_str()) << std::endl;
						}
					} else {
						YAML::Emitter emitter;
						emitter << YAML::BeginDoc;
						write_yaml_impl_process(emitter, pt, filename, converter);
						if (flags & writer_flags::insert_end_of_document) {
							emitter << YAML::EndDoc;
						}
						stream << converter.from_str(emitter.c_str()) << std::endl;
					}
				}
			}	// namespace parser_detail
			//
			// write_yaml
			//
			template<typename Ptree>
			SPRIG_INLINE void write_yaml(
				std::basic_ostream<typename Ptree::key_type::value_type>& stream,
				Ptree const& pt,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_writer_flags(flags));
				parser_detail::write_yaml_impl(stream, pt, std::string(), flags);
			}
			template<typename Ptree>
			SPRIG_INLINE void write_yaml(
				std::string const& filename,
				Ptree const& pt,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_writer_flags(flags));
				std::basic_ofstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						yaml_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::write_yaml_impl(stream, pt, filename, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void write_yaml(
				std::basic_ostream<typename Ptree::key_type::value_type>& stream,
				Ptree const& pt,
				Converter converter,
				int flags = 0
				)
			{
				BOOST_ASSERT(validate_writer_flags(flags));
				parser_detail::write_yaml_impl(stream, pt, std::string(), converter, flags);
			}
			template<typename Converter, typename Ptree>
			SPRIG_INLINE void write_yaml(
				std::string const& filename,
				Ptree const& pt,
				Converter converter,
				int flags = 0,
				std::locale const& loc = std::locale()
				)
			{
				BOOST_ASSERT(validate_writer_flags(flags));
				std::basic_ofstream<typename Ptree::key_type::value_type> stream(filename.c_str());
				if (!stream) {
					SPRIG_THROW_EXCEPTION(
						yaml_parser_error("cannot open file", filename, 0)
						);
				}
				stream.imbue(loc);
				parser_detail::write_yaml_impl(stream, pt, filename, converter, flags);
			}
		}	// namespace yaml_parser

		//
		// read_yaml
		// write_yaml
		//
		using yaml_parser::read_yaml;
		using yaml_parser::write_yaml;

	}	// namespace property_tree
}	// namespace sprig

#endif	// #ifndef SPRIG_PROPERTY_TREE_YAML_PARSER_HPP
