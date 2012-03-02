#ifndef SPRIG_ANY_FUNCTIONAL_HPP
#define SPRIG_ANY_FUNCTIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <functional>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <sprig/tmp/always_which.hpp>

//
// SPRIG_ANY_FUNCTIONAL_OPERATION_BASE_DEFAULT
//
#define SPRIG_ANY_FUNCTIONAL_OPERATION_BASE_DEFAULT(NAME, TRAITS) \
	template<typename Traits = TRAITS, typename Enable = void> \
	class NAME {};
//
// SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD
//
#define SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, AT1, AM1, AT2, AM2) \
	template<typename Traits> \
	class NAME< \
		Traits, \
		typename boost::enable_if_c< \
			Traits::first_argument_tag_type::value == AT1::value \
			&& Traits::second_argument_tag_type::value == AT2::value \
		>::type \
	> { \
	public: \
		typedef Traits traits_type; \
	public: \
		/* 	CHECK: fatal error C1001 */ \
		/* 1>__FILE__(__LINE__) : fatal error C1001: コンパイラで内部エラーが発生しました。*/ \
		/* 1>(コンパイラ ファイル 'msc1.cpp'、行 1411)*/ \
		/* 1> この問題を回避するには、上記の場所付近のプログラムを単純化するか変更してください。*/ \
		/* 1>詳細については、Visual C++ ヘルプ メニューのサポート情報コマンドを*/ \
		/* 1>選択してください。またはサポート情報 ヘルプ ファイルを参照してください。*/ \
		/*template<typename Arg1, typename Arg2> \
		typename boost::enable_if< \
			boost::is_same<typename traits_type::result::template apply<Arg1, Arg2>::type, void>, \
			typename traits_type::result::template apply<Arg1, Arg2>::type \
		>::type \
		operator()(Arg1 AM1 arg1, Arg2 AM2 arg2) const { \
			arg1 OP arg2; \
		}*/ \
		template<typename Arg1, typename Arg2> \
		typename boost::disable_if< \
			boost::is_same<typename traits_type::result::template apply<Arg1, Arg2>::type, void>, \
			typename traits_type::result::template apply<Arg1, Arg2>::type \
		>::type \
		operator()(Arg1 AM1 arg1, Arg2 AM2 arg2) const { \
			return arg1 OP arg2; \
		} \
	};
//
// SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD
//
#define SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, AT, AM) \
	template<typename Traits> \
	class NAME< \
		Traits, \
		typename boost::enable_if_c<Traits::argument_tag_type::value == AT::value>::type \
	> { \
	public: \
		typedef Traits traits_type; \
	public: \
		template<typename Arg> \
		typename boost::enable_if< \
			boost::is_same<typename traits_type::result::template apply<Arg>::type, void>, \
			typename traits_type::result::template apply<Arg>::type \
		>::type \
		operator()(Arg AM arg) const { \
			OP arg; \
		} \
		template<typename Arg> \
		typename boost::disable_if< \
			boost::is_same<typename traits_type::result::template apply<Arg>::type, void>, \
			typename traits_type::result::template apply<Arg>::type \
		>::type \
		operator()(Arg AM arg) const { \
			return OP arg; \
		} \
	};
//
// SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD
//
#define SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, AT, AM) \
	template<typename Traits> \
	class NAME< \
		Traits, \
		typename boost::enable_if_c<Traits::argument_tag::value == AT::value>::type \
	> { \
	public: \
		typedef Traits traits_type; \
	public: \
		template<typename Arg> \
		typename traits_type::result::template apply<Arg>::type operator()(Arg AM arg) const { \
			return arg OP; \
		} \
	};
//
// SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE
//
#define SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, TRAITS) \
	SPRIG_ANY_FUNCTIONAL_OPERATION_BASE_DEFAULT(NAME, TRAITS); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY(), argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY(), const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY(), reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY(), const_reference_argument_tag, const&); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const, argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const, const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const, reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const, const_reference_argument_tag, const&); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &, argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &, const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &, reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &, const_reference_argument_tag, const&); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&, argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&, const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&, reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&, const_reference_argument_tag, const&);
//
// SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE
//
#define SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, TRAITS) \
	SPRIG_ANY_FUNCTIONAL_OPERATION_BASE_DEFAULT(NAME, TRAITS); \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&);
//
// SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE
//
#define SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE(NAME, OP, TRAITS) \
	SPRIG_ANY_FUNCTIONAL_OPERATION_BASE_DEFAULT(NAME, TRAITS); \
	SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, argument_tag, BOOST_PP_EMPTY()); \
	SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_argument_tag, const); \
	SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, reference_argument_tag, &); \
	SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE_OVERLOAD(NAME, OP, const_reference_argument_tag, const&);
//
// SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL
//
#define SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, any_binary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, any_compare_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, any_logical_binary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, any_bitwise_binary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, any_assign_operation_traits)
//
// SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_DECL
//
#define SPRIG_ANY_FUNCTIONAL_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_unary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_logical_unary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_bitwise_unary_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_incdec_front_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_INDIRECT_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_indirect_operation_traits)
#define SPRIG_ANY_FUNCTIONAL_ADDRESS_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, any_address_operation_traits)
//
// SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_DECL
//
#define SPRIG_ANY_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_ANY_FUNCTIONAL_BACK_UNARY_OPERATION_BASE(NAME, OP, any_incdec_back_operation_traits)

namespace sprig {
	//
	// argument tag
	//
	typedef boost::mpl::size_t<0> argument_tag;
	typedef boost::mpl::size_t<1> const_argument_tag;
	typedef boost::mpl::size_t<2> reference_argument_tag;
	typedef boost::mpl::size_t<3> const_reference_argument_tag;
	//
	// any_binary_operation_traits_base
	//
	template<
		typename ResultFunc = tmp::always_which_c<1>,
		typename Arg1Tag = const_reference_argument_tag,
		typename Arg2Tag = Arg1Tag
	>
	class any_binary_operation_traits_base {
	public:
		typedef Arg1Tag first_argument_tag_type;
		typedef Arg2Tag second_argument_tag_type;
	public:
		struct result {
			template<typename Arg1, typename Arg2>
			struct apply {
				typedef typename ResultFunc::template apply<Arg1, Arg2>::type type;
			};
		};
	};
	//
	// any_unary_operation_traits_base
	//
	template<
		typename ResultFunc = tmp::always_which_c<1>,
		typename ArgTag = const_reference_argument_tag
	>
	class any_unary_operation_traits_base {
	public:
		typedef ArgTag argument_tag_type;
	public:
		struct result {
			template<typename Arg>
			struct apply {
				typedef typename ResultFunc::template apply<Arg>::type type;
			};
		};
	};
	//
	// any binary operation traits
	//
	typedef any_binary_operation_traits_base<> any_binary_operation_traits;
	typedef any_binary_operation_traits_base<boost::mpl::always<bool> > any_compare_operation_traits;
	typedef any_binary_operation_traits_base<boost::mpl::always<bool> > any_logical_binary_operation_traits;
	typedef any_binary_operation_traits_base<> any_bitwise_binary_operation_traits;
	typedef any_binary_operation_traits_base<
		boost::mpl::lambda<boost::add_reference<tmp::always_which_c<1>::apply<boost::mpl::_1, boost::mpl::_2> > >::type,
		reference_argument_tag,
		const_reference_argument_tag
	> any_assign_operation_traits;
	//
	// any unary operation traits
	//
	typedef any_unary_operation_traits_base<> any_unary_operation_traits;
	typedef any_unary_operation_traits_base<boost::mpl::always<bool> > any_logical_unary_operation_traits;
	typedef any_unary_operation_traits_base<> any_bitwise_unary_operation_traits;
	typedef any_unary_operation_traits_base<
		boost::mpl::lambda<boost::add_reference<tmp::always_which_c<1>::apply<boost::mpl::_1, boost::mpl::_2> > >::type,
		reference_argument_tag
	> any_incdec_front_operation_traits;
	typedef any_unary_operation_traits_base<
		tmp::always_which_c<1>,
		reference_argument_tag
	> any_incdec_back_operation_traits;
	typedef any_unary_operation_traits_base<
		boost::mpl::lambda<
			boost::add_reference<
				boost::mpl::lambda<boost::remove_pointer<tmp::always_which_c<1>::apply<boost::mpl::_1> > >
			>
		>::type,
		const_reference_argument_tag
	> any_indirect_operation_traits;
	typedef any_unary_operation_traits_base<
		boost::mpl::lambda<boost::add_pointer<tmp::always_which_c<1>::apply<boost::mpl::_1> > >::type,
		reference_argument_tag
	> any_address_operation_traits;
	//
	// any binary operations
	//
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(any_plus, +);
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(any_minus, -);
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(any_multiplies, *);
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(any_devides, /);
	SPRIG_ANY_FUNCTIONAL_BINARY_OPERATION_DECL(any_modulus, %);
	//
	// any comparison operations
	//
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_equal_to, ==);
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_not_equal_to, !=);
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_greater, >);
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_less, <);
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_greater_equal, >=);
	SPRIG_ANY_FUNCTIONAL_COMPARISON_OPERATION_DECL(any_less_equal, <=);
	//
	// any logical binary operations
	//
	SPRIG_ANY_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(any_logical_and, &&);
	SPRIG_ANY_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(any_logical_or, ||);
	//
	// any bitwise binary operations
	//
	SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(any_left_shift, <<);
	SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(any_right_shift, >>);
	SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(any_bitand, &);
	SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(any_bitwise_xor, ^);
	SPRIG_ANY_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(any_bitor, |);
	//
	// any assign operations
	//
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_assign, =);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_plus_assign, +=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_minus_assign, -=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_multiplies_assign, *=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_divides_assign, /=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_modulus_assign, %=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_left_shift_assign, <<=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_right_shift_assign, >>=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_and_assign, &=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_xor_assign, ^=);
	SPRIG_ANY_FUNCTIONAL_ASSIGN_OPERATION_DECL(any_or_assign, |=);
	//
	// any unary operations
	//
	SPRIG_ANY_FUNCTIONAL_UNARY_OPERATION_DECL(any_posite, +);
	SPRIG_ANY_FUNCTIONAL_UNARY_OPERATION_DECL(any_negate, -);
	//
	// any logical unary operations
	//
	SPRIG_ANY_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(any_logical_not, !);
	//
	// any bitwise unary operations
	//
	SPRIG_ANY_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(any_bitnot, ~);
	//
	// any increase and decrease front operations
	//
	SPRIG_ANY_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(any_increase_front, ++);
	SPRIG_ANY_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(any_decrease_front, --);
	//
	// any indirect operations
	//
	SPRIG_ANY_FUNCTIONAL_INDIRECT_OPERATION_DECL(any_indirect, *);
	//
	// any address operations
	//
	SPRIG_ANY_FUNCTIONAL_ADDRESS_OPERATION_DECL(any_address, &);
	//
	// any increase and decrease back operations
	//
	SPRIG_ANY_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(any_increase_back, ++);
	SPRIG_ANY_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(any_decrease_back, --);
}	// namespace sprig

#endif	// #ifndef SPRIG_ANY_FUNCTIONAL_HPP
