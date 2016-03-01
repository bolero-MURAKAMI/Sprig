/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_VARIANTS_DYNAMIC_VARIANT_HPP
#define SPRIG_VARIANTS_DYNAMIC_VARIANT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <map>
#include <typeinfo>
#include <boost/any.hpp>
#include <boost/current_function.hpp>
#include <boost/throw_exception.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/optional/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/info.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/exception.hpp>
#include <sprig/variants/foundation.hpp>

namespace sprig {
	namespace variants {
		//
		// dynamic_variant
		//
		template<typename Tag>
		class dynamic_variant {
		private:
			typedef dynamic_variant this_type;
		public:
			typedef Tag tag_type;
		private:
			//
			// map_operations
			//
			struct map_operations {
				template<typename Ooperation>
				static caller1_base& get_caller1(types::type_info_type arg1) {
					typename types::operator1_map_type::iterator i(Ooperation::map.find(typename types::operator1_map_type::key_type(arg1)));
					if (i == Ooperation::map.end()) {
						throw operator_not_found("operator not found.")
							<< boost::throw_function(BOOST_CURRENT_FUNCTION)
							<< boost::throw_file(__FILE__)
							<< boost::throw_line((int)__LINE__)
							<< boost::error_info<nth_argument_tag<1>, char const*>(arg1.name())
							;
					}
					return *i->second;
				}
				template<typename Ooperation>
				static caller2_base& get_caller2(types::type_info_type arg1, types::type_info_type arg2) {
					typename types::operator2_map_type::iterator i(Ooperation::map.find(typename types::operator2_map_type::key_type(arg1, arg2)));
					if (i == Ooperation::map.end()) {
						throw operator_not_found("operator not found.")
							<< boost::throw_function(BOOST_CURRENT_FUNCTION)
							<< boost::throw_file(__FILE__)
							<< boost::throw_line((int)__LINE__)
							<< boost::error_info<nth_argument_tag<1>, char const*>(arg1.name())
							<< boost::error_info<nth_argument_tag<2>, char const*>(arg2.name())
							;
					}
					return *i->second;
				}
				template<typename Ooperation, typename Operator>
				static std::pair<typename types::operator1_map_type::iterator, bool> insert1(Operator const& v) {
					typedef typename Operator::result_type result_type;
					typedef typename Operator::argument_type argument_type;
					typedef caller1<argument_type, result_type> caller_type;
					typedef typename types::operator1_map_type::value_type value_type;
					typedef typename types::operator1_map_type::key_type key_type;
					typedef typename types::operator1_map_type::mapped_type mapped_type;
					boost::shared_ptr<Operator> op(boost::make_shared<Operator>(v));
					boost::shared_ptr<caller_type> caller(boost::make_shared<caller_type>(op));
					return Ooperation::map.insert(value_type(
						key_type(typeid(argument_type)),
						mapped_type(caller)
						));
				}
				template<typename Ooperation, typename Operator>
				static std::pair<typename types::operator2_map_type::iterator, bool> insert2(Operator const& v) {
					typedef typename Operator::result_type result_type;
					typedef typename Operator::first_argument_type first_argument_type;
					typedef typename Operator::second_argument_type second_argument_type;
					typedef caller2<first_argument_type, second_argument_type, result_type> caller_type;
					typedef typename types::operator2_map_type::value_type value_type;
					typedef typename types::operator2_map_type::key_type key_type;
					typedef typename types::operator2_map_type::mapped_type mapped_type;
					boost::shared_ptr<Operator> op(boost::make_shared<Operator>(v));
					boost::shared_ptr<caller_type> caller(boost::make_shared<caller_type>(op));
					return Ooperation::map.insert(value_type(
						key_type(typeid(first_argument_type), typeid(second_argument_type)),
						mapped_type(caller)
						));
				}
			};
		private:
			//
			// operation1_base, operation2_base
			//
			template<typename selfT>
			class operation1_base {
				friend class dynamic_variant;
			private:
				static types::operator1_map_type map;
			public:
				template<typename T>
				static std::pair<typename types::operator1_map_type::iterator, bool> insert(T const& v) {
					return map_operations::template insert1<selfT>(v);
				}
				//static dynamic_variant operate(dynamic_variant const& arg1) {
				//	return map_operations::template get_caller1<selfT>(arg1.type())(arg1.get());
				//}
				static dynamic_variant operate(dynamic_variant& arg1) {
					return map_operations::template get_caller1<selfT>(arg1.type())(arg1.get());
				}
			};
			template<typename selfT>
			class operation2_base {
				friend class dynamic_variant;
			private:
				static types::operator2_map_type map;
			public:
				template<typename T>
				static std::pair<typename types::operator2_map_type::iterator, bool> insert(T const& v) {
					return map_operations::template insert2<selfT>(v);
				}
				//static dynamic_variant operate(dynamic_variant const& arg1, dynamic_variant const& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2.get());
				//}
				//static dynamic_variant operate(dynamic_variant const& arg1, dynamic_variant& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2.get());
				//}
				//static dynamic_variant operate(dynamic_variant& arg1, dynamic_variant const& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2.get());
				//}
				static dynamic_variant operate(dynamic_variant& arg1, dynamic_variant& arg2) {
					return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2.get());
				}
				//static dynamic_variant operate(dynamic_variant const& arg1, reference_wrapper_base& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2);
				//}
				static dynamic_variant operate(dynamic_variant& arg1, reference_wrapper_base& arg2) {
					return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2);
				}
				//static dynamic_variant operate(reference_wrapper_base& arg1, dynamic_variant const& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1, arg2.get());
				//}
				static dynamic_variant operate(reference_wrapper_base& arg1, dynamic_variant& arg2) {
					return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1, arg2.get());
				}
				//static dynamic_variant operate(dynamic_variant const& arg1, const_reference_wrapper_base& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2);
				//}
				static dynamic_variant operate(dynamic_variant& arg1, const_reference_wrapper_base& arg2) {
					return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1.get(), arg2);
				}
				//static dynamic_variant operate(const_reference_wrapper_base& arg1, dynamic_variant const& arg2) {
				//	return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1, arg2.get());
				//}
				static dynamic_variant operate(const_reference_wrapper_base& arg1, dynamic_variant& arg2) {
					return map_operations::template get_caller2<selfT>(arg1.type(), arg2.type())(arg1, arg2.get());
				}
			};
		public:
			//
			// SPRIG_VARIANTS_BINARY_OPERATION_DECL
			//
	#define SPRIG_VARIANTS_BINARY_OPERATION_DECL(NAME) \
			class NAME : public operation2_base<NAME> {}
	#define SPRIG_VARIANTS_UNARY_OPERATION_DECL(NAME) \
			class NAME : public operation1_base<NAME> {}
			//
			// binary operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(plus);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(minus);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(multiplies);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(divides);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(modulus);
			//
			// comparison operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(equal_to);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(not_equal_to);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(greater);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(less);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(greater_equal);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(less_equal);
			//
			// logical binary operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(and_);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(or_);
			//
			// bitwise binary operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(shift_left);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(shift_right);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(bitand_);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(bitxor_);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(bitor_);
			//
			// assign operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(plus_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(minus_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(multiplies_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(divides_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(modulus_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(left_shift_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(right_shift_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(and_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(xor_assign);
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(or_assign);
			//
			// unary operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(posite);
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(negate);
			//
			// logical unary operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(not_);
			//
			// bitwise unary operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(bitnot_);
			//
			// increase and decrease front operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(increase_front);
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(decrease_front);
			//
			// indirect operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(indirect);
			//
			// address operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(address);
			//
			// increase and decrease back operations
			//
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(increase_back);
			SPRIG_VARIANTS_UNARY_OPERATION_DECL(decrease_back);
			//
			// comma operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(comma);
			//
			// indirect arrow operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(indirect_arrow);
			//
			// subscript operations
			//
			SPRIG_VARIANTS_BINARY_OPERATION_DECL(subscript);
		private:
			types::any_type value_;
		public:
			dynamic_variant() {}
			dynamic_variant(this_type const& that)
				: value_(that.value_)
			{}
			template<typename Value>
			dynamic_variant(Value const& value)
				: value_(value)
			{}
			this_type& operator=(this_type const& rhs) {
				this_type(rhs).swap(*this);
				return *this;
			}
			template<typename T>
			this_type& operator=(T const& rhs) {
				this_type(rhs).swap(*this);
				return *this;
			}
			void swap(this_type& rhs) {
				boost::swap(value_, rhs.value_);
			}
			std::type_info const& type() const {
				return value_.type();
			}
			types::any_type const& get() const {
				return value_;
			}
			types::any_type& get() {
				return value_;
			}
		public:
			//this_type operator[](this_type const& arg2) const {
			//	return subscript::operate(*this, arg2);
			//}
			//this_type operator[](this_type& arg2) const {
			//	return subscript::operate(*this, arg2);
			//}
			//template<typename Value>
			//this_type operator[](Value& arg2) const {
			//	return subscript::operate(*this, reference_wrapper<Value>(arg2));
			//}
			this_type operator[](this_type& arg2) {
				return subscript::operate(*this, arg2);
			}
			//template<typename Value>
			//this_type operator[](Value& arg2) const {
			//	return subscript::operate(*this, reference_wrapper<Value>(arg2));
			//}
			template<typename Value>
			this_type operator[](Value& arg2) {
				return subscript::operate(*this, reference_wrapper<Value>(arg2));
			}
			//template<typename Value>
			//this_type operator[](Value const& arg2) const {
			//	return subscript::operate(*this, const_reference_wrapper<Value const>(arg2));
			//}
			template<typename Value>
			this_type operator[](Value const& arg2) {
				return subscript::operate(*this, const_reference_wrapper<Value const>(arg2));
			}
			//	CHECK: error C3767
			//		: probrem(<boost/exception/detail/object_hex_dump.hpp>)
			//		: probrem(<boost/operators.hpp>)
		public:
			dynamic_variant operator&() {
				return address::operate(*this);
			}
		};
		template<typename Tag>
		template<typename selfT>
		types::operator1_map_type dynamic_variant<Tag>::operation1_base<selfT>::map;
		template<typename Tag>
		template<typename selfT>
		types::operator2_map_type dynamic_variant<Tag>::operation2_base<selfT>::map;
		//
		// SPRIG_VARIANTS_BINARY_OPERATOR_DECL
		//
#define SPRIG_VARIANTS_BINARY_OPERATOR_DECL(name, op) \
		/*template<typename Tag>*/ \
		/*dynamic_variant<Tag> operator op(dynamic_variant<Tag> const& arg1, dynamic_variant<Tag> const& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1, arg2);*/ \
		/*}*/ \
		/*template<typename Tag>*/ \
		/*dynamic_variant<Tag> operator op(dynamic_variant<Tag> const& arg1, dynamic_variant<Tag>& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1, arg2);*/ \
		/*}*/ \
		/*template<typename Tag>*/ \
		/*dynamic_variant<Tag> operator op(dynamic_variant<Tag>& arg1, dynamic_variant<Tag> const& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1, arg2);*/ \
		/*}*/ \
		template<typename Tag> \
		dynamic_variant<Tag> operator op(dynamic_variant<Tag>& arg1, dynamic_variant<Tag>& arg2) { \
			return dynamic_variant<Tag>::name::operate(arg1, arg2); \
		} \
		/*template<typename Value, typename Tag>*/ \
		/*typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type*/ \
		/*operator op(dynamic_variant<Tag> const& arg1, Value& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1, reference_wrapper<Value>(arg2));*/ \
		/*}*/ \
		template<typename Value, typename Tag> \
		typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type \
		operator op(dynamic_variant<Tag>& arg1, Value& arg2) { \
			return dynamic_variant<Tag>::name::operate(arg1, reference_wrapper<Value>(arg2)); \
		} \
		/*template<typename Value, typename Tag>*/ \
		/*typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type*/ \
		/*operator op(Value& arg1, dynamic_variant<Tag> const& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(reference_wrapper<Value>(arg1), arg2);*/ \
		/*}*/ \
		template<typename Value, typename Tag> \
		typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type \
		operator op(Value& arg1, dynamic_variant<Tag>& arg2) { \
			return dynamic_variant<Tag>::name::operate(reference_wrapper<Value>(arg1), arg2); \
		} \
		/*template<typename Value, typename Tag>*/ \
		/*typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type*/ \
		/*operator op(dynamic_variant<Tag> const& arg1, Value const& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1, const_reference_wrapper<Value const>(arg2));*/ \
		/*}*/ \
		template<typename Value, typename Tag> \
		typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type \
		operator op(dynamic_variant<Tag>& arg1, Value const& arg2) { \
			return dynamic_variant<Tag>::name::operate(arg1, const_reference_wrapper<Value const>(arg2)); \
		} \
		/*template<typename Value, typename Tag>*/ \
		/*typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type*/ \
		/*operator op(Value const& arg1, dynamic_variant<Tag> const& arg2) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(const_reference_wrapper<Value const>(arg1), arg2);*/ \
		/*}*/ \
		template<typename Value, typename Tag> \
		typename boost::disable_if<boost::is_same<Value, dynamic_variant<Tag> >, dynamic_variant<Tag> >::type \
		operator op(Value const& arg1, dynamic_variant<Tag>& arg2) { \
			return dynamic_variant<Tag>::name::operate(const_reference_wrapper<Value const>(arg1), arg2); \
		}
		//
		// SPRIG_VARIANTS_UNARY_OPERATOR_DECL
		//
#define SPRIG_VARIANTS_UNARY_OPERATOR_DECL(name, op) \
		/*template<typename Tag>*/ \
		/*dynamic_variant<Tag> operator op(dynamic_variant<Tag> const& arg1) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1);*/ \
		/*}*/ \
		template<typename Tag> \
		dynamic_variant<Tag> operator op(dynamic_variant<Tag>& arg1) { \
			return dynamic_variant<Tag>::name::operate(arg1); \
		}
		//
		// SPRIG_VARIANTS_BACK_UNARY_OPERATOR_DECL
		//
#define SPRIG_VARIANTS_BACK_UNARY_OPERATOR_DECL(name, op) \
		/*template<typename Tag>*/ \
		/*dynamic_variant<Tag> operator op(dynamic_variant<Tag> const& arg1, int) {*/ \
		/*	return dynamic_variant<Tag>::name::operate(arg1);*/ \
		/*}*/ \
		template<typename Tag> \
		dynamic_variant<Tag> operator op(dynamic_variant<Tag>& arg1, int) { \
			return dynamic_variant<Tag>::name::operate(arg1); \
		}
		//
		// binary operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(plus, +);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(minus, -);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(multiplies, *);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(divides, /);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(modulus, %);
		//
		// comparison operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(equal_to, ==);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(not_equal_to, !=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(greater, >);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(less, <);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(greater_equal, >=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(less_equal, <=);
		//
		// logical binary operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(and_, &&);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(or_, ||);
		//
		// bitwise binary operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(shift_left, <<);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(shift_right, >>);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(bitand_, &);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(bitxor_, ^);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(bitor_, |);
		//
		// assign operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(plus_assign, +=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(minus_assign, -=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(multiplies_assign, *=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(divides_assign, /=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(modulus_assign, %=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(left_shift_assign, <<=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(right_shift_assign, >>=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(and_assign, &=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(xor_assign, ^=);
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(or_assign, |=);
		//
		// unary operators
		//
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(posite, +);
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(negate, -);
		//
		// logical unary operators
		//
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(not_, !);
		//
		// bitwise unary operators
		//
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(bitnot_, ~);
		//
		// increase and decrease front operators
		//
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(increase_front, ++);
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(decrease_front, --);
		//
		// indirect operators
		//
		SPRIG_VARIANTS_UNARY_OPERATOR_DECL(indirect, *);
		//
		// address operators
		//
		//	CHECK: error C3767
		//		: probrem(<boost/exception/detail/object_hex_dump.hpp>)
		//		: probrem(<boost/operators.hpp>)
		//SPRIG_VARIANTS_UNARY_OPERATOR_DECL(address, &);
		//
		// increase and decrease back operators
		//
		SPRIG_VARIANTS_BACK_UNARY_OPERATOR_DECL(increase_back, ++);
		SPRIG_VARIANTS_BACK_UNARY_OPERATOR_DECL(decrease_back, --);
		//
		// comma operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(comma, BOOST_PP_COMMA());
		//
		// indirect arrow operators
		//
		SPRIG_VARIANTS_BINARY_OPERATOR_DECL(indirect_arrow, ->*);
		//
		// any_cast
		//
		template<typename Value, typename Tag>
		SPRIG_INLINE Value any_cast(dynamic_variant<Tag> const& v) {
			return boost::any_cast<Value>(v.get());
		}
		template<typename Value, typename Tag>
		SPRIG_INLINE Value any_cast(dynamic_variant<Tag>& v) {
			return boost::any_cast<Value>(v.get());
		}
	}	// namespace variants
	//
	// usings
	//
	using variants::dynamic_variant;
	using variants::any_cast;
}	// namespace sprig

#endif	// #ifndef SPRIG_VARIANTS_DYNAMIC_VARIANT_HPP
