#ifndef SPRIG_INDENT_LOGGER_HPP
#define SPRIG_INDENT_LOGGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <iosfwd>
#include <deque>
#include <sstream>
#include <boost/function.hpp>
#include <boost/call_traits.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ref.hpp>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/bind/bind.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/mpl/if.hpp>
#include <sprig/reference_holder.hpp>
#include <sprig/split_literal.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/indentation.hpp>
#include <sprig/section.hpp>
#include <sprig/type_traits/is_char_type.hpp>

namespace sprig {
	//
	// basic_indent_logger
	//
	template<typename String, typename Tag>
	class basic_indent_logger {
	public:
		typedef String string_type;
		typedef Tag tag_type;
		typedef typename string_type::value_type char_type;
		typedef std::basic_ostream<
			char_type,
			typename string_type::traits_type
		> ostream_type;
		typedef basic_string_argument<string_type> string_argument_type;
		typedef std::basic_ostringstream<
			char_type,
			typename string_type::traits_type,
			typename string_type::allocator_type
		> ostringstream_type;
		typedef typename boost::mpl::if_<
			typename sprig::is_char_type<char_type>::type,
			boost::iostreams::filtering_ostream,
			boost::iostreams::filtering_wostream
		>::type filtering_ostream_type;
		typedef boost::function<void (string_type const&)> function_type;
		typedef std::deque<function_type> functions_type;
		//
		// indentation
		//
		class indentation
			: public faithful_indentation_sponsor<
				indentation,
				basic_indentation<string_type>,
				ostream_type
			>
		{};
	public:
		typedef basic_passive_faithful_indent<string_type, indentation> indent;
		typedef passive_faithful_indent_filter<indentation> indent_filter;
	public:
		//
		// ostream_holder
		//
		class ostream_holder {
		private:
			//	COMMENT: ostringstreamÅ®filtering_ostream ÇÃèáÇ…âï˙Ç≥ÇÍÇ»ÇØÇÍÇŒÇ»ÇÁÇ»Ç¢ÅB
			boost::shared_ptr<ostringstream_type> oss_;
			filtering_ostream_type fos_;
		public:
			ostream_holder()
				: oss_(boost::make_shared<ostringstream_type>())
			{
				fos_.push(indent_filter(fos_));
				fos_.push(*oss_);
			}
			filtering_ostream_type& get() {
				return fos_;
			}
			void reset() {
				fos_.pop();
				oss_ = boost::make_shared<ostringstream_type>();
				fos_.push(*oss_);
			}
			string_type str() const {
				return oss_->str();
			}
		};
	private:
		SPRIG_SPLIT_LITERAL_STRING_DECL(separators, "\n");
	public:
		template<typename Sequence>
		static void trim_last_lf(Sequence& source) {
			boost::trim_right_if(
				source,
				boost::is_any_of(sprig::get_literal<separators, char_type>())
				);
		}
	private:
		ostream_holder holder_;
		functions_type functions_;
	private:
		void output_element(string_type const& s) {
			BOOST_FOREACH(typename functions_type::value_type const& e, functions_) {
				e(s);
			}
		}
		void output_sequence() {
			typedef std::deque<string_type> splited_sequence_type;
			string_type source(holder_.str());
			if (source.empty()) {
				return;
			}
			trim_last_lf(source);
			splited_sequence_type splited;
			boost::split(
				splited,
				source,
				boost::is_any_of(sprig::get_literal<separators, char_type>())
				);
			BOOST_FOREACH(typename splited_sequence_type::value_type const& e, splited) {
				output_element(e);
			}
		}
	public:
		basic_indent_logger() {}
		~basic_indent_logger() throw() {
			output_sequence();
		}
		void push(function_type const& fun) {
			functions_.push_back(fun);
		}
		void flush() {
			output_sequence();
			holder_.reset();
		}
		void output(string_argument_type const& arg) {
			holder_.get() << arg;
		}
		void output_line(string_argument_type const& arg, bool flush = true) {
			holder_.get() << arg << std::endl;
			if (flush) {
				this->flush();
			}
		}
		ostream_type& get() {
			return holder_.get();
		}
	};
	//
	// operator<<
	//
	template<typename String, typename Tag>
	SPRIG_INLINE basic_indent_logger<String, Tag>& operator<<(
		basic_indent_logger<String, Tag>& lhs,
		typename basic_indent_logger<String, Tag>::string_argument_type const& rhs
		)
	{
		lhs.output(rhs);
		return lhs;
	}
	template<typename String, typename Tag>
	SPRIG_INLINE basic_indent_logger<String, Tag>& operator<<(
		basic_indent_logger<String, Tag>& lhs,
		typename basic_indent_logger<String, Tag>::ostream_type& (*rhs)(typename basic_indent_logger<String, Tag>::ostream_type&)
		)
	{
		lhs.get() << rhs;
		return lhs;
	}
	//
	// logger_output_line
	//
	template<typename Logger>
	SPRIG_INLINE void logger_output_line(
		basic_string_argument<typename Logger::string_type> const& message,
		Logger& logger,
		bool flush = true
		)
	{
		logger.output_line(message, flush);
	}
	//
	// logger_section_line
	//
	template<typename Logger>
	SPRIG_INLINE void logger_section_line(
		basic_string_argument<typename Logger::string_type> const& name,
		basic_string_argument<typename Logger::string_type> const& contents,
		Logger& logger,
		bool flush = true
		)
	{
		logger.output_line(section_line(name, contents), flush);
	}
	//
	// logger_section_comment
	//
	template<typename Logger>
	SPRIG_INLINE void logger_section_comment(
		basic_string_argument<typename Logger::string_type> const& comment,
		Logger& logger,
		bool flush = true
		)
	{
		logger.output_line(section_comment(comment), flush);
	}
	//
	// logger_section
	//
	template<typename Logger>
	class logger_section
		: boost::noncopyable
	{
	public:
		typedef Logger logger_type;
		typedef typename logger_type::string_type string_type;
		typedef typename logger_type::tag_type tag_type;
		typedef typename logger_type::indent indent_type;
		typedef typename logger_type::string_argument_type string_argument_type;
	private:
		class outputter {
			string_type name_;
			sprig::reference_holder<logger_type> logger_;
			bool flush_;
		public:
			outputter(string_argument_type const& name, logger_type& logger, bool flush)
				: name_(name)
				, logger_(logger)
				, flush_(flush)
			{
				logger_->output_line(section_begin(name_), flush_);
			}
			~outputter() throw() {
				logger_->output_line(section_end(name_), flush_);
			}
		};
	private:
		outputter outputter_;
		indent_type indent_;
	public:
		logger_section(
			string_argument_type const& name,
			logger_type& logger,
			bool flush = true
			)
			: outputter_(name, logger, flush)
		{}
		logger_section(
			string_argument_type const& name,
			logger_type& logger,
			string_argument_type const& tab,
			bool flush = true
			)
			: outputter_(name, logger, flush)
			, indent_(tab)
		{}
	};
	//
	// flush
	//
	struct flush {};
	template<typename String, typename Tag>
	SPRIG_INLINE basic_indent_logger<String, Tag>& operator<<(
		basic_indent_logger<String, Tag>& lhs,
		flush const& rhs
		)
	{
		lhs.flush();
		return lhs;
	}
	//
	// endl
	//
	struct endl {};
	template<typename String, typename Tag>
	SPRIG_INLINE basic_indent_logger<String, Tag>& operator<<(
		basic_indent_logger<String, Tag>& lhs,
		endl const& rhs
		)
	{
		lhs << std::endl;
		lhs.flush();
		return lhs;
	}
	//
	// ends
	//
	struct ends {};
	template<typename String, typename Tag>
	SPRIG_INLINE basic_indent_logger<String, Tag>& operator<<(
		basic_indent_logger<String, Tag>& lhs,
		ends const& rhs
		)
	{
		lhs << std::ends;
		lhs.flush();
		return lhs;
	}
	//
	// local_logger
	//
	template<typename String, typename Tag>
	class local_logger
		: boost::noncopyable
	{
	public:
		typedef sprig::basic_indent_logger<String, Tag> logger_type;
		typedef typename logger_type::string_type string_type;
		typedef typename logger_type::ostringstream_type ostringstream_type;
		typedef typename logger_type::string_argument_type string_argument_type;
		typedef logger_section<logger_type> section_type;
	private:
		static void output(string_type const& arg, ostringstream_type& oss) {
			oss << arg << std::endl;
		};
	private:
		logger_type logger_;
		ostringstream_type oss_;
	public:
		local_logger() {
			logger_.push(boost::bind(&output, _1, boost::ref(oss_)));
		}
		logger_type& operator*() {
			return logger_;
		}
		string_type str() {
			logger_.flush();
			return oss_.str();
		}
		void output_line(
			string_argument_type const& message,
			bool flush = true
			)
		{
			logger_output_line(message, logger_, flush);
		}
		void section_line(
			string_argument_type const& name,
			string_argument_type const& contents,
			bool flush = true
			)
		{
			logger_section_line(name, contents, logger_, flush);
		}
		void section_comment(
			string_argument_type const& comment,
			bool flush = true
			)
		{
			logger_section_comment(comment, logger_, flush);
		}
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_INDENT_LOGGER_HPP
