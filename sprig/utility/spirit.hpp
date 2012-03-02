#ifndef SPRIG_UTILITY_SPIRIT_HPP
#define SPRIG_UTILITY_SPIRIT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <iosfwd>
#include <string>
#include <boost/foreach.hpp>
#include <sprig/utility/utility.hpp>

namespace sprig {
	//
	// output_ostream_tree_parse_info
	//
	template<typename infoT, typename Stream = std::ostream>
	class output_ostream_tree_parse_info {
	public:
		typedef infoT info_type;
		typedef Stream stream_type;
	private:
		stream_type& stream_;
		std::size_t tab_;
		std::string tab_unit_;
	public:
		explicit output_ostream_tree_parse_info(stream_type& stream)
			: stream_(stream)
			, tab_(0)
			, tab_unit_("    ")
		{}
		output_ostream_tree_parse_info(stream_type& stream, std::size_t init)
			: stream_(stream)
			, tab_(init)
			, tab_unit_("    ")
		{}
		output_ostream_tree_parse_info(stream_type& stream, std::size_t init, std::string const& unit)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(unit)
		{}
		std::string tab() const {
			return sprig::multipries<std::string>(tab_unit_, tab_);
		}
		template<typename Node>
		void output_tree_node(Node const& node) {
			stream_
				<< tab()
				<< "<node"
				<< " value=\"" << std::string(node.value.begin(), node.value.end()) << "\""
				<< " id=\"" << node.value.id().to_long() << "\""
				;
			if (node.children.empty()) {
				stream_ << " />\n";
				return;
			}
			stream_ << ">\n";
			++tab_;
			BOOST_FOREACH(typename Node::children_t::value_type const& e, node.children) {
				output_tree_node(e);
			}
			--tab_;
			stream_ << tab() << "</node>\n";
		}
		void output(info_type const& info) {
			if (!info.full) {
				stream_ << tab() << "<!--parse failed-->\n";
				return;
			}
			stream_ << tab() << "<!--parse successed-->\n";
			output_tree_node(info.trees[0]);
		}
	};
	//
	// output_wostream_tree_parse_info
	//
	template<typename infoT, typename Stream = std::wostream>
	class output_wostream_tree_parse_info {
	public:
		typedef infoT info_type;
		typedef Stream stream_type;
	private:
		stream_type& stream_;
		std::size_t tab_;
		std::wstring tab_unit_;
	public:
		explicit output_wostream_tree_parse_info(stream_type& stream)
			: stream_(stream)
			, tab_(0)
			, tab_unit_(L"    ")
		{}
		output_wostream_tree_parse_info(stream_type& stream, std::size_t init)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(L"    ")
		{}
		output_wostream_tree_parse_info(stream_type& stream, std::size_t init, std::wstring const& unit)
			: stream_(stream)
			, tab_(init)
			, tab_unit_(unit)
		{}
		std::wstring tab() const {
			return sprig::multipries<std::wstring>(tab_unit_, tab_);
		}
		template<typename Node>
		void output_tree_node(Node const& node) {
			stream_
				<< tab()
				<< L"<node"
				<< L" value=\"" << std::wstring(node.value.begin(), node.value.end()) << L"\""
				<< L" id=\"" << node.value.id().to_long() << L"\""
				;
			if (node.children.empty()) {
				stream_ << L" />\n";
				return;
			}
			stream_ << L">\n";
			++tab_;
			BOOST_FOREACH(typename Node::children_t::value_type const& e, node.children) {
				output_tree_node(e);
			}
			--tab_;
			stream_ << tab() << L"</node>\n";
		}
		void output(info_type const& info) {
			if (!info.full) {
				stream_ << tab() << L"<!--parse failed-->\n";
				return;
			}
			stream_ << tab() << L"<!--parse successed-->\n";
			output_tree_node(info.trees[0]);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_UTILITY_SPIRIT_HPP
