#ifndef SPRIG_ENABLE_SWITCH_HPP
#define SPRIG_ENABLE_SWITCH_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

//
// SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY
// SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY
//
#ifndef SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY
#	define SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY 16
#endif	// #ifndef SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY
#ifndef SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY
#	define SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY 16
#endif	// #ifndef SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY

namespace sprig {
	//
	// case_match
	//
	template<long N>
	struct case_match
		: public boost::mpl::long_<N>
	{};
	//
	// default_match
	//
	struct default_match
		: public boost::mpl::long_<-1>
	{};

	namespace enable_switch_detail {
		template<typename Seq>
		struct remove_void
			: public boost::mpl::remove<Seq, boost::mpl::void_>
		{};
#		define SPRIG_ENABLE_SWITCH_ENUM_ARGS_T() \
			BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY, typename Arg, boost::mpl::void_)
#		define SPRIG_ENABLE_SWITCH_ENUM_ARGS() \
			BOOST_PP_ENUM_PARAMS(SPRIG_ENABLE_SWITCH_ARGS_MAX_ARITY, Arg)
		template<typename CaseSeq>
		struct enable_switch_impl {
		public:
			typedef CaseSeq args_type;
		private:
			template<SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct apply_match {
				template<typename Pred>
				struct apply
					: public boost::mpl::apply<
						boost::mpl::unpack_args<Pred>,
						typename enable_switch_detail::remove_void<boost::mpl::vector<SPRIG_ENABLE_SWITCH_ENUM_ARGS()> >::type
					>
				{};
			};
			template<SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct match_pos
				: public boost::mpl::find_if<
					args_type,
					apply_match<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>
				>::type::pos
			{};
			template<typename Pos>
			struct pos_to_result
				: public boost::mpl::if_c<
					(Pos::value != boost::mpl::size<args_type>::value),
					case_match<Pos::value>,
					default_match
				>::type
			{};
		public:
			//
			// match
			//
			template<SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct match
				: public pos_to_result<
					match_pos<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>
				>::type
			{};
			//
			// case_c
			// case_
			// default_
			//
			template<long N, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct case_c
				: public boost::mpl::bool_<match<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>::value == N>
			{};
			template<typename N, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct case_
				: public case_c<N::value, SPRIG_ENABLE_SWITCH_ENUM_ARGS()>::type
			{};
			template<SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct default_
				: public boost::mpl::bool_<match<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>::value == -1>
			{};
			//
			// enable_case_c
			// enable_case
			// enable_default
			//
			template<long N, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_case_c
				: public boost::enable_if<
					case_c<N, SPRIG_ENABLE_SWITCH_ENUM_ARGS()>
				>
			{};
			template<typename N, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_case
				: public boost::enable_if<
					case_<N, SPRIG_ENABLE_SWITCH_ENUM_ARGS()>
				>
			{};
			template<SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_default
				: public boost::enable_if<
					default_<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>
				>
			{};
			//
			// enable_case_ret_c
			// enable_case_ret
			// enable_default_ret
			//
			template<long N, typename Ret = void, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_case_ret_c
				: public boost::enable_if<
					case_c<N, SPRIG_ENABLE_SWITCH_ENUM_ARGS()>,
					Ret
				>
			{};
			template<typename N, typename Ret = void, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_case_ret
				: public boost::enable_if<
					case_<N, SPRIG_ENABLE_SWITCH_ENUM_ARGS()>,
					Ret
				>
			{};
			template<typename Ret = void, SPRIG_ENABLE_SWITCH_ENUM_ARGS_T()>
			struct enable_default_ret
				: public boost::enable_if<
					default_<SPRIG_ENABLE_SWITCH_ENUM_ARGS()>,
					Ret
				>
			{};
		};
#		undef SPRIG_ENABLE_SWITCH_ENUM_ARGS_T
#		undef SPRIG_ENABLE_SWITCH_ENUM_ARGS
	}	// namespace enable_switch_detail

	//
	// enable_switch_seq
	//
	template<typename CaseSeq>
	struct enable_switch_seq
		: public enable_switch_detail::enable_switch_impl<CaseSeq>
	{
	public:
		typedef enable_switch_seq type;
	};
	//
	// enable_switch
	//
	template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY, typename Case, boost::mpl::void_)>
	struct enable_switch
		: public enable_switch_detail::enable_switch_impl<
			typename enable_switch_detail::remove_void<boost::mpl::vector<BOOST_PP_ENUM_PARAMS(SPRIG_ENABLE_SWITCH_CASE_MAX_ARITY, Case)> >::type
		>
	{
	public:
		typedef enable_switch type;
	};
}	// namespace sprig

#endif	// #ifndef SPRIG_ENABLE_SWITCH_HPP
