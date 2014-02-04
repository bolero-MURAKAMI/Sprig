/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_TMP_PRED_HPP
#define SPRIG_TMP_PRED_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <sprig/tmp/na.hpp>

//
// SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY
//
#ifndef SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY
#	define SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY 16
#endif	// #ifndef SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY

#define SPRIG_TMP_PREDICATE_ENUM_ARGS_T() \
	BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY, typename Arg, sprig::tmp::na)
#define SPRIG_TMP_PREDICATE_ENUM_ARGS() \
	BOOST_PP_ENUM_PARAMS(SPRIG_TMP_PREDICATE_ARGS_MAX_ARITY, Arg)
#define SPRIG_TMP_PREDICATE_PACK_ARGS_TO_VECTOR() \
	typename sprig::tmp::remove_na<boost::mpl::vector<SPRIG_TMP_PREDICATE_ENUM_ARGS()> >::type

namespace sprig {
	namespace tmp {
		//
		// apply_pred_seq
		// apply_pred
		//
		template<typename Seq>
		struct apply_pred_seq {
		public:
			template<typename Pred>
			struct apply
				: public boost::mpl::apply<
					boost::mpl::unpack_args<Pred>,
					Seq
				>
			{};
			typedef apply_pred_seq type;
		};
		template<SPRIG_TMP_PREDICATE_ENUM_ARGS_T()>
		struct apply_pred
			: public apply_pred_seq<SPRIG_TMP_PREDICATE_PACK_ARGS_TO_VECTOR()>
		{
		public:
			typedef apply_pred type;
		};

		//
		// pred_all_of_seq
		// pred_all_of
		//
		template<typename PredSeq>
		struct pred_all_of_seq {
		public:
			template<SPRIG_TMP_PREDICATE_ENUM_ARGS_T()>
			struct apply
				: public boost::mpl::equal_to<
					boost::mpl::count_if<
						PredSeq,
						apply_pred<SPRIG_TMP_PREDICATE_ENUM_ARGS()>
					>,
					boost::mpl::size<PredSeq>
				>
			{};
			typedef pred_all_of_seq type;
		};
		template<SPRIG_TMP_PREDICATE_ENUM_ARGS_T()>
		struct pred_all_of
			: public pred_all_of_seq<SPRIG_TMP_PREDICATE_PACK_ARGS_TO_VECTOR()>
		{
		public:
			typedef pred_all_of type;
		};

		//
		// pred_any_of_seq
		// pred_any_of
		//
		template<typename PredSeq>
		struct pred_any_of_seq {
		public:
			template<SPRIG_TMP_PREDICATE_ENUM_ARGS_T()>
			struct apply
				: public boost::mpl::not_<
					boost::is_same<
						typename boost::mpl::find_if<
							PredSeq,
							apply_pred<SPRIG_TMP_PREDICATE_ENUM_ARGS()>
						>::type,
						typename boost::mpl::end<PredSeq>::type
					>
				>
			{};
			typedef pred_any_of_seq type;
		};
		template<SPRIG_TMP_PREDICATE_ENUM_ARGS_T()>
		struct pred_any_of
			: public pred_any_of_seq<SPRIG_TMP_PREDICATE_PACK_ARGS_TO_VECTOR()>
		{
		public:
			typedef pred_any_of type;
		};
	}	// namespace tmp
}	// namespace sprig

#undef SPRIG_TMP_PREDICATE_ENUM_ARGS_T
#undef SPRIG_TMP_PREDICATE_ENUM_ARGS
#undef SPRIG_TMP_PREDICATE_PACK_ARGS_TO_VECTOR

#endif	// #ifndef SPRIG_TMP_PRED_HPP
