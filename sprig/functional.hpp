#ifndef SPRIG_FUNCTIONAL_HPP
#define SPRIG_FUNCTIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <functional>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <sprig/call_traits.hpp>

//
// SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE
//
#define SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, DEF_ARG1, DEF_ARG2, DEF_RESULT, TRAITS) \
	template< \
		typename Arg1 DEF_ARG1, \
		typename Arg2 DEF_ARG2, \
		typename Result DEF_RESULT, \
		typename Traits = TRAITS<Arg1, Arg2, Result>, \
		typename Enable = void \
	> \
	class NAME {}; \
	template<typename Arg1, typename Arg2, typename Result, typename Traits> \
	class NAME< \
		Arg1, \
		Arg2, \
		Result, \
		Traits, \
		typename boost::enable_if<boost::is_same<typename Traits::result_type, void> >::type \
	> \
		: public binary_function<Arg1, Arg2, Result, Traits> \
	{ \
	public: \
		typedef binary_function<Arg1, Arg2, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::first_argument_type arg1, \
			typename traits_type::second_argument_type arg2 \
			) const \
		{ \
			arg1 OP arg2; \
		} \
	}; \
	template<typename Arg1, typename Arg2, typename Result, typename Traits> \
	class NAME< \
		Arg1, \
		Arg2, \
		Result, \
		Traits, \
		typename boost::disable_if<boost::is_same<typename Traits::result_type, void> >::type \
	> \
		: public binary_function<Arg1, Arg2, Result, Traits> \
	{ \
	public: \
		typedef binary_function<Arg1, Arg2, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::first_argument_type arg1, \
			typename traits_type::second_argument_type arg2 \
			) const \
		{ \
			return arg1 OP arg2; \
		} \
	};
//
// SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE
//
#define SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, DEF_ARG, DEF_RESULT, TRAITS) \
	template< \
		typename Arg DEF_ARG, \
		typename Result DEF_RESULT, \
		typename Traits = TRAITS<Arg, Result>, \
		typename Enable = void \
	> \
	class NAME {}; \
	template<typename Arg, typename Result, typename Traits> \
	class NAME< \
		Arg, \
		Result, \
		Traits, \
		typename boost::enable_if<boost::is_same<typename Traits::result_type, void> >::type \
	> \
		: public unary_function<Arg, Result, Traits> \
	{ \
	public: \
		typedef unary_function<Arg, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::argument_type arg \
			) const \
		{ \
			OP arg; \
		} \
	}; \
	template<typename Arg, typename Result, typename Traits> \
	class NAME<Arg, Result, Traits, typename boost::disable_if<boost::is_same<typename Traits::result_type, void> >::type> \
		: public unary_function<Arg, Result, Traits> \
	{ \
	public: \
		typedef unary_function<Arg, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::argument_type arg \
			) const \
		{ \
			return OP arg; \
		} \
	};
//
// SPRIG_FUNCTIONAL_BACK_UNARY_OPERATION_BASE
//
#define SPRIG_FUNCTIONAL_BACK_UNARY_OPERATION_BASE(NAME, OP, DEF_ARG, DEF_RESULT, TRAITS) \
	template< \
		typename Arg DEF_ARG, \
		typename Result DEF_RESULT, \
		typename Traits = TRAITS<Arg, Result>, \
		typename Enable = void \
	> \
	class NAME {}; \
	template<typename Arg, typename Result, typename Traits> \
	class NAME< \
		Arg, \
		Result, \
		Traits, \
		typename boost::enable_if<boost::is_same<typename Traits::result_type, void> >::type \
	> \
		: public unary_function<Arg, Result, Traits> \
	{ \
	public: \
		typedef unary_function<Arg, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::argument_type arg \
			) const \
		{ \
			arg OP; \
		} \
	}; \
	template<typename Arg, typename Result, typename Traits> \
	class NAME< \
		Arg, \
		Result, \
		Traits, \
		typename boost::disable_if<boost::is_same<typename Traits::result_type, void> >::type \
	> \
		: public unary_function<Arg, Result, Traits> \
	{ \
	public: \
		typedef unary_function<Arg, Result, Traits> function_type; \
		typedef typename function_type::traits_type traits_type; \
	public: \
		typename traits_type::result_type operator()( \
			typename traits_type::argument_type arg \
			) const \
		{ \
			return arg OP; \
		} \
	};
//
// SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL
//
#define SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg1, = Arg1, binary_operation_traits)
#define SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg1, = bool, compare_operation_traits)
#define SPRIG_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg1, = bool, logical_binary_operation_traits)
#define SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg1, = Arg1, bitwise_binary_operation_traits)
#define SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BINARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg1, = Arg1, assign_operation_traits)
//
// SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_DECL
//
#define SPRIG_FUNCTIONAL_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg, unary_operation_traits)
#define SPRIG_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = bool, logical_unary_operation_traits)
#define SPRIG_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg, bitwise_unary_operation_traits)
#define SPRIG_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg, incdec_front_operation_traits)
#define SPRIG_FUNCTIONAL_INDIRECT_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = typename boost::remove_pointer<Arg>::type, indirect_operation_traits)
#define SPRIG_FUNCTIONAL_ADDRESS_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_FRONT_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = typename boost::add_pointer<Arg>::type, address_operation_traits)
//
// SPRIG_FUNCTIONAL_BACK_UNARY_OPERATION_DECL
//
#define SPRIG_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(NAME, OP) \
	SPRIG_FUNCTIONAL_BACK_UNARY_OPERATION_BASE(NAME, OP, BOOST_PP_EMPTY(), = Arg, incdec_back_peration_traits)
//
// SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS
//
#define SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS(NAME) \
	template<typename Arg1, typename Arg2, typename Result> \
	class NAME { \
	public: \
		typedef typename sprig::call_traits<Arg1>::param_type first_argument_type; \
		typedef typename sprig::call_traits<Arg2>::param_type second_argument_type; \
		typedef typename sprig::call_traits<Result>::value_type result_type; \
	};
#define SPRIG_FUNCTIONAL_ASSIGN_OPERATION_TRAITS(NAME) \
	template<typename Arg1, typename Arg2, typename Result> \
	class NAME { \
	public: \
		typedef typename sprig::call_traits<Arg1>::reference first_argument_type; \
		typedef typename sprig::call_traits<Arg2>::param_type second_argument_type; \
		typedef typename sprig::call_traits<Result>::reference result_type; \
	};
//
// SPRIG_FUNCTIONAL_UNARY_OPERATION_TRAITS
//
#define SPRIG_FUNCTIONAL_UNARY_OPERATION_TRAITS(NAME) \
	template<typename Arg, typename Result> \
	class NAME { \
	public: \
		typedef typename boost::call_traits<Arg>::param_type argument_type; \
		typedef typename sprig::call_traits<Result>::value_type result_type; \
	};
#define SPRIG_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_TRAITS(NAME) \
	template<typename Arg, typename Result> \
	class NAME { \
	public: \
		typedef typename boost::call_traits<Arg>::reference argument_type; \
		typedef typename sprig::call_traits<Result>::reference result_type; \
	};
#define SPRIG_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_TRAITS(NAME) \
	template<typename Arg, typename Result> \
	class NAME { \
	public: \
		typedef typename boost::call_traits<Arg>::reference argument_type; \
		typedef typename sprig::call_traits<Result>::value_type const result_type; \
	};
#define SPRIG_FUNCTIONAL_INDIRECT_OPERATION_TRAITS(NAME) \
	template<typename Arg, typename Result> \
	class NAME { \
	public: \
		typedef typename boost::call_traits<Arg>::reference argument_type; \
		typedef typename sprig::call_traits<Result>::reference result_type; \
	};
#define SPRIG_FUNCTIONAL_ADDRESS_OPERATION_TRAITS(NAME) \
	template<typename Arg, typename Result> \
	class NAME { \
	public: \
		typedef typename boost::call_traits<Arg>::reference argument_type; \
		typedef typename sprig::call_traits<Result>::value_type result_type; \
	};

namespace sprig {
	//
	// binary_function
	//
	template<
		typename Arg1,
		typename Arg2,
		typename Result,
		typename Traits
	>
	class binary_function
		: public std::binary_function<Arg1, Arg2, Result>
	{
	public:
		typedef Traits traits_type;
	};
	//
	// unary_function
	//
	template<
		typename Arg,
		typename Result,
		typename Traits
	>
	class unary_function
		: public std::unary_function<Arg, Result>
	{
	public:
		typedef Traits traits_type;
	};
	//
	// binary operation traits
	//
	SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS(binary_operation_traits);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS(compare_operation_traits);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS(logical_binary_operation_traits);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_TRAITS(bitwise_binary_operation_traits);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_TRAITS(assign_operation_traits);
	//
	// unary operation traits
	//
	SPRIG_FUNCTIONAL_UNARY_OPERATION_TRAITS(unary_operation_traits);
	SPRIG_FUNCTIONAL_UNARY_OPERATION_TRAITS(logical_unary_operation_traits);
	SPRIG_FUNCTIONAL_UNARY_OPERATION_TRAITS(bitwise_unary_operation_traits);
	SPRIG_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_TRAITS(incdec_front_operation_traits);
	SPRIG_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_TRAITS(incdec_back_peration_traits);
	SPRIG_FUNCTIONAL_INDIRECT_OPERATION_TRAITS(indirect_operation_traits);
	SPRIG_FUNCTIONAL_ADDRESS_OPERATION_TRAITS(address_operation_traits);
	//
	// binary operation
	//
	SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(plus, +);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(minus, -);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(multiplies, *);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(devides, /);
	SPRIG_FUNCTIONAL_BINARY_OPERATION_DECL(modulus, %);
	//
	// compare operation
	//
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(equal_to, ==);
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(not_equal_to, !=);
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(greater, >);
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(less, <);
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(greater_equal, >=);
	SPRIG_FUNCTIONAL_COMPARE_OPERATION_DECL(less_equal, <=);
	//
	// logical binary operation
	//
	SPRIG_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(and_, &&);
	SPRIG_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(or_, ||);
	//
	// bitwise binary operation
	//
	SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(shift_left, <<);
	SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(shift_right, >>);
	SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitand_, &);
	SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitxor_, ^);
	SPRIG_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitor_, |);
	//
	// assign operation
	//
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(assign, =);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(plus_assign, +=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(minus_assign, -=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(multiplies_assign, *=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(shift_left_assign, <<=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(shift_right_assign, >>=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(and_assign, &=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(xor_assign, ^=);
	SPRIG_FUNCTIONAL_ASSIGN_OPERATION_DECL(or_assign, |=);
	//
	// unary operation
	//
	SPRIG_FUNCTIONAL_UNARY_OPERATION_DECL(posite, +);
	SPRIG_FUNCTIONAL_UNARY_OPERATION_DECL(negate, -);
	//
	// logical unary operation
	//
	SPRIG_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(not_, !);
	//
	// bitwise unary operation
	//
	SPRIG_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(bitnot_, ~);
	//
	// increase and decrease front operation
	//
	SPRIG_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(increase_front, ++);
	SPRIG_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(decrease_front, --);
	//
	// indirect operation
	//
	SPRIG_FUNCTIONAL_INDIRECT_OPERATION_DECL(indirect, *);
	//
	// address operation
	//
	SPRIG_FUNCTIONAL_ADDRESS_OPERATION_DECL(address, &);
	//
	// increase and decrease back operation
	//
	SPRIG_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(increase_back, ++);
	SPRIG_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(decrease_back, --);
}	// namespace sprig

#endif	// #ifndef SPRIG_FUNCTIONAL_HPP
