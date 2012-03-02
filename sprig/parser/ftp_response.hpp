#ifndef SPRIG_PARSER_FTP_RESPONSE_HPP
#define SPRIG_PARSER_FTP_RESPONSE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/mpl/identity.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/size.hpp>
#include <sprig/enable_switch.hpp>
#include <sprig/tmp/pred.hpp>
#include <sprig/fusion/linear_value_at.hpp>

namespace sprig {
	namespace parser {
		namespace ftp_response_impl {
			//
			// locals_of
			//
			template<typename Tuple>
			struct locals_of
				: public boost::mpl::identity<
					boost::spirit::qi::locals<
						typename boost::remove_reference<
							typename sprig::fusion::result_of::linear_value_at_c<Tuple, 0>::type
						>::type
					>
				>
			{};
		}	// namespace ftp_response_impl
		//
		// ftp_response
		//
		template<
			typename Iterator,
			typename Tuple
		>
		class ftp_response
			: public boost::spirit::qi::grammar<
				Iterator,
				Tuple (),
				typename ftp_response_impl::locals_of<Tuple>::type
			>
		{
		public:
			typedef Iterator iterator_type;
			typedef Tuple tuple_type;
			typedef typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<tuple_type, 0>::type
			>::type status_code_type;
			typedef typename boost::remove_reference<
				typename sprig::fusion::result_of::linear_value_at_c<tuple_type, 2>::type
			>::type message_type;
		private:
			boost::spirit::qi::rule<iterator_type, tuple_type (), typename ftp_response_impl::locals_of<Tuple>::type> response_;
			boost::spirit::qi::rule<iterator_type, status_code_type ()> status_code_;
			boost::spirit::qi::rule<iterator_type, message_type ()> message_;
		public:
			explicit ftp_response(bool including_crlf = true)
				: ftp_response::base_type(response_)
			{
				response_ %= status_code_[boost::spirit::qi::_a = boost::spirit::qi::_1]
					>> -(
						'-' >> (message_ % !(boost::spirit::qi::lit(boost::spirit::qi::_a) >> ' '))
						>> boost::spirit::qi::lit(boost::spirit::qi::_a) >> &boost::spirit::qi::lit(' ')
						)
					>> ' ' >> message_
					;
				status_code_ = boost::spirit::qi::raw[
					boost::spirit::qi::repeat(3)[boost::spirit::qi::digit]
					];
				if (including_crlf) {
					message_ = boost::spirit::qi::raw[
						*(boost::spirit::qi::char_ - boost::spirit::qi::lit("\r\n"))
						>> boost::spirit::qi::lit("\r\n")
						];
				} else {
					message_ = boost::spirit::qi::raw[
						*(boost::spirit::qi::char_ - boost::spirit::qi::lit("\r\n"))
						]
						>> boost::spirit::qi::lit("\r\n")
						;
				}
			}
		};
		//
		// ftp_pasv_address_and_port
		//
		template<
			typename Iterator,
			typename Tuple
		>
		class ftp_pasv_address_and_port
			: public boost::spirit::qi::grammar<
				Iterator,
				Tuple ()
			>
		{
		public:
			typedef Iterator iterator_type;
			typedef Tuple tuple_type;
		private:
			template<int N>
			struct is_tuple_element {
				template<typename T>
				struct apply
					: public boost::fusion::traits::is_sequence<
						typename boost::remove_reference<
							typename sprig::fusion::result_of::linear_value_at_c<T, N>::type
						>::type
					>
				{};
			};
			template<int N>
			struct is_int_element {
				template<typename T>
				struct apply
					: public boost::is_integral<
						typename boost::remove_reference<
							typename sprig::fusion::result_of::linear_value_at_c<T, N>::type
						>::type
					>
				{};
			};
			template<typename T>
			struct is_elem4_elem2
				: public boost::mpl::bool_<boost::fusion::result_of::size<T>::value == 6>
			{};
			template<typename T>
			struct is_tuple4_elem2
				: public boost::mpl::and_<
					boost::mpl::apply<is_tuple_element<0>, T>,
					boost::mpl::bool_<boost::fusion::result_of::size<T>::value == 3>
				>
			{};
			template<typename T>
			struct is_elem4_tuple2
				: public boost::mpl::and_<
					boost::mpl::apply<is_tuple_element<4>, T>,
					boost::mpl::bool_<boost::fusion::result_of::size<T>::value == 5>
				>
			{};
			template<typename T>
			struct is_tuple4_tuple2
				: public boost::mpl::and_<
					boost::mpl::apply<is_tuple_element<0>, T>,
					boost::mpl::apply<is_tuple_element<1>, T>
				>
			{};
			typedef sprig::enable_switch<
				boost::mpl::quote1<is_elem4_elem2>,
				boost::mpl::quote1<is_tuple4_elem2>,
				boost::mpl::quote1<is_elem4_tuple2>,
				boost::mpl::quote1<is_tuple4_tuple2>
			> elem_tuple_switch_type;
			typedef sprig::enable_switch<
				sprig::tmp::pred_all_of<is_int_element<0>, is_int_element<4> >,
				is_int_element<0>,
				is_int_element<4>
			> address_port_switch_type;
		private:
			typedef boost::spirit::qi::uint_parser<unsigned char, 10, 1, -1> uchar_p;
		private:
			boost::spirit::qi::rule<iterator_type, tuple_type ()> address_and_port_;
		private:
			template<typename T>
			void init(
				typename boost::enable_if<
					boost::mpl::and_<
						typename elem_tuple_switch_type::template case_c<0, T>,
						typename address_port_switch_type::template case_c<0, T>
					>
				>::type* = 0
				)
			{
				address_and_port_ = boost::spirit::qi::omit[*(boost::spirit::qi::char_ - boost::spirit::qi::lit('('))]
					>> '('
					>> uchar_p() >> ',' >> uchar_p() >> ',' >> uchar_p() >> ',' >> uchar_p()
					>> ','
					>> uchar_p() >> ',' >> uchar_p()
					>> ')'
					>> boost::spirit::qi::omit[*boost::spirit::qi::char_]
					;
			}
			template<typename T>
			void init(
				typename boost::enable_if<
					boost::mpl::and_<
						typename elem_tuple_switch_type::template case_c<0, T>,
						typename address_port_switch_type::template case_c<1, T>
					>
				>::type* = 0
				)
			{
				address_and_port_ = boost::spirit::qi::omit[*(boost::spirit::qi::char_ - boost::spirit::qi::lit('('))]
					>> '('
					>> uchar_p() >> ',' >> uchar_p() >> ',' >> uchar_p() >> ',' >> uchar_p()
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ')'
					>> boost::spirit::qi::omit[*boost::spirit::qi::char_]
					;
			}
			template<typename T>
			void init(
				typename boost::enable_if<
					boost::mpl::and_<
						typename elem_tuple_switch_type::template case_c<0, T>,
						typename address_port_switch_type::template case_c<2, T>
					>
				>::type* = 0
				)
			{
				address_and_port_ = boost::spirit::qi::omit[*(boost::spirit::qi::char_ - boost::spirit::qi::lit('('))]
					>> '('
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> uchar_p() >> ',' >> uchar_p()
					>> ')'
					>> boost::spirit::qi::omit[*boost::spirit::qi::char_]
					;
			}
			template<typename T>
			void init(
				typename boost::enable_if<
					boost::mpl::and_<
						typename elem_tuple_switch_type::template case_c<0, T>,
						typename address_port_switch_type::template default_<T>
					>
				>::type* = 0
				)
			{
				address_and_port_ = boost::spirit::qi::omit[*(boost::spirit::qi::char_ - boost::spirit::qi::lit('('))]
					>> '('
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ','
					>> boost::spirit::qi::raw[+boost::spirit::qi::digit]
					>> ')'
					>> boost::spirit::qi::omit[*boost::spirit::qi::char_]
					;
			}
		public:
			explicit ftp_pasv_address_and_port()
				: ftp_pasv_address_and_port::base_type(address_and_port_)
			{
				init<tuple_type>();
			}
		};
	}	// namespace parser
}	// namespace sprig

#endif	// #ifndef SPRIG_PARSER_FTP_RESPONSE_HPP
