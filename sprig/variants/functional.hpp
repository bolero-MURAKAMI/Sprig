#ifndef SPRIG_VARIANTS_FUNCTIONAL_HPP
#define SPRIG_VARIANTS_FUNCTIONAL_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <sprig/type_traits/remove_const_reference.hpp>
#include <sprig/variants/foundation.hpp>

namespace sprig {
	namespace variants {
		namespace functional {
			//
			// SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Arg2 = Arg1, \
				typename Result = typename sprig::remove_const_reference<Arg1>::type \
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP arg2; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Arg2 = Arg1, \
				typename Result = bool \
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP arg2; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(NAME, OP) \
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(NAME, OP)
			//
			// SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(NAME, OP) \
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(NAME, OP)
			//
			// SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Arg2 = typename boost::remove_reference<Arg1>::type const&, \
				typename Result = Arg1 \
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP arg2; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_UNARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_UNARY_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = typename sprig::remove_const_reference<Arg1>::type \
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return OP arg1; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = bool \
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return OP arg1; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(NAME, OP) \
			SPRIG_VARIANTS_FUNCTIONAL_UNARY_OPERATION_DECL(NAME, OP)
			//
			// SPRIG_VARIANTS_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = Arg1 \
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return OP arg1; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = typename boost::remove_pointer<Arg1>::type \
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return OP arg1; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_ADDRESS_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_ADDRESS_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = typename boost::remove_reference<Arg1>::type*\
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return OP arg1; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Result = typename boost::remove_reference<Arg1>::type\
			> \
			class NAME : public operator1<Arg1, Result> { \
			public: \
				typedef operator1<Arg1, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::argument_type argument_type; \
			public: \
				result_type operator()(argument_type arg1) { \
					return arg1 OP; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_COMMA_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_COMMA_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Arg2 = typename sprig::remove_const_reference<Arg1>::type&, \
				typename Result = Arg2 \
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP arg2; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_ARROW_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_ARROW_OPERATION_DECL(NAME, OP) \
			template< \
				typename Arg1, \
				typename Arg2 = typename boost::remove_reference<Arg1>::type const&, \
				typename Result = Arg1\
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP arg2; \
				} \
			}
			//
			// SPRIG_VARIANTS_FUNCTIONAL_SUBSCRIPT_OPERATION_DECL
			//
#define SPRIG_VARIANTS_FUNCTIONAL_SUBSCRIPT_OPERATION_DECL(NAME, OP1, OP2) \
			template< \
				typename Arg1, \
				typename Arg2 = int const, \
				typename Result = typename boost::remove_pointer<typename sprig::remove_const_reference<Arg1>::type>::type& \
			> \
			class NAME : public operator2<Arg1, Arg2, Result> { \
			public: \
				typedef operator2<Arg1, Arg2, Result> operator_type; \
				typedef typename operator_type::result_type result_type; \
				typedef typename operator_type::first_argument_type first_argument_type; \
				typedef typename operator_type::second_argument_type second_argument_type; \
			public: \
				result_type operator()(first_argument_type arg1, second_argument_type arg2) { \
					return arg1 OP1 arg2 OP2; \
				} \
			}
			//
			// binary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(plus, +);
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(minus, -);
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(multiplies, *);
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(divides, /);
			SPRIG_VARIANTS_FUNCTIONAL_BINARY_OPERATION_DECL(modulus, %);
			//
			// comparison operators
			//
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(equal_to, ==);
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(not_equal_to, !=);
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(greater, >);
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(less, <);
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(greater_equal, >=);
			SPRIG_VARIANTS_FUNCTIONAL_COMPARISON_OPERATION_DECL(less_equal, <=);
			//
			// logical binary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(and_, &&);
			SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_BINARY_OPERATION_DECL(or_, ||);
			//
			// bitwise binary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(shift_left, <<);
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(shift_right, >>);
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitand_, &);
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitxor_, ^);
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_BINARY_OPERATION_DECL(bitor_, |);
			//
			// assign operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(plus_assign, +=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(minus_assign, -=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(multiplies_assign, *=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(divides_assign, /=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(modulus_assign, %=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(left_shift_assign, <<=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(right_shift_assign, >>=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(and_assign, &=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(xor_assign, ^=);
			SPRIG_VARIANTS_FUNCTIONAL_ASSIGN_OPERATION_DECL(or_assign, |=);
			//
			// unary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_UNARY_OPERATION_DECL(posite, +);
			SPRIG_VARIANTS_FUNCTIONAL_UNARY_OPERATION_DECL(negate, -);
			//
			// logical unary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_LOGICAL_UNARY_OPERATION_DECL(not_, !);
			//
			// bitwise unary operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_BITWISE_UNARY_OPERATION_DECL(bitnot_, ~);
			//
			// increase and decrease front operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(increase_front, ++);
			SPRIG_VARIANTS_FUNCTIONAL_INCDEC_FRONT_UNARY_OPERATION_DECL(decrease_front, --);
			//
			// indirect operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_OPERATION_DECL(indirect, *);
			//
			// address operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_ADDRESS_OPERATION_DECL(address, &);
			//
			// increase and decrease back operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(increase_back, ++);
			SPRIG_VARIANTS_FUNCTIONAL_INCDEC_BACK_UNARY_OPERATION_DECL(decrease_back, --);
			//
			// comma operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_COMMA_OPERATION_DECL(comma, BOOST_PP_COMMA());
			//
			// indirect arrow operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_INDIRECT_ARROW_OPERATION_DECL(indirect_arrow, ->*);
			//
			// subscript operations
			//
			SPRIG_VARIANTS_FUNCTIONAL_SUBSCRIPT_OPERATION_DECL(subscript, [, ]);
		}	// namespace functional
	}	// namespace variants
}	// namespace sprig

#endif	// #ifndef SPRIG_VARIANTS_FUNCTIONAL_HPP
