#ifndef SPRIG_VARIANTS_FOUNDATION_HPP
#define SPRIG_VARIANTS_FOUNDATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstring>
#include <map>
#include <functional>
#include <typeinfo>
#include <boost/any.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/optional/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/addressof.hpp>
#include <sprig/type_traits/remove_const_reference.hpp>
#include <sprig/exception.hpp>

namespace sprig {
	namespace variants {
		//
		// types
		//
		namespace types {
			typedef boost::any any_type;
			typedef std::type_info const& type_info_type;
			typedef boost::optional<type_info_type> type_info_element_type;
			typedef boost::tuple<type_info_element_type> signature1_type;
			typedef boost::tuple<type_info_element_type, type_info_element_type> signature2_type;
		}	// namespace types
		//
		// nth_argument_tag
		//
		template<int N>
		struct nth_argument_tag {};
		//
		// operator_not_found
		//
		SPRIG_EXCEPTION_DECL(operator_not_found);
		//
		// signature1_comparator, signature2_comparator
		//
		struct signature1_comparator {
			bool operator()(types::signature1_type const& lhs, types::signature1_type const& rhs) const {
				return strcmp(lhs.get<0>()->name(), rhs.get<0>()->name()) < 0;
			}
		};
		struct signature2_comparator {
			bool operator()(types::signature2_type const& lhs, types::signature2_type const& rhs) const {
				return strcmp(lhs.get<0>()->name(), rhs.get<0>()->name()) < 0;
			}
		};
		//
		// reference_wrapper_base, reference_wrapper
		//
		class reference_wrapper_base {
		public:
			virtual ~reference_wrapper_base() {}
			virtual types::type_info_type type() const = 0;
		};
		template<typename T>
		class reference_wrapper
			: public reference_wrapper_base
		{
		public:
			typedef T value_type;
		private:
			value_type* t_;
			static types::type_info_type type_;
		public:
			explicit reference_wrapper(value_type& t)
				: t_(boost::addressof(t))
			{}
			types::type_info_type type() const {
				return type_;
			}
			operator value_type&() const {
				return *t_;
			}
			value_type& get() const {
				return *t_;
			}
			value_type* get_pointer() const {
				return t_;
			}
		};
		template<typename T>
		types::type_info_type reference_wrapper<T>::type_(typeid(reference_wrapper<T>::value_type));
		//
		// const_reference_wrapper_base, const_reference_wrapper
		//
		class const_reference_wrapper_base {
		public:
			virtual ~const_reference_wrapper_base() {}
			virtual types::type_info_type type() const = 0;
		};
		template<typename T>
		class const_reference_wrapper
			: public const_reference_wrapper_base
		{
		public:
			typedef T value_type;
		private:
			value_type* t_;
			static types::type_info_type type_;
		public:
			explicit const_reference_wrapper(value_type& t)
				: t_(boost::addressof(t))
			{}
			types::type_info_type type() const {
				return type_;
			}
			operator value_type&() const {
				return *t_;
			}
			value_type& get() const {
				return *t_;
			}
			value_type* get_pointer() const {
				return t_;
			}
		};
		template<typename T>
		types::type_info_type const_reference_wrapper<T>::type_(typeid(const_reference_wrapper<T>::value_type));
		//
		// operator_base, operator1, operator2
		//
		class operator_base {
		public:
			virtual ~operator_base() {}
		};
		template<typename Arg1, typename Result>
		class operator1
			: public operator_base
			, public std::unary_function<Arg1, Result>
		{
		public:
			typedef std::unary_function<Arg1, Result> function_type;
			typedef typename function_type::result_type result_type;
			typedef typename function_type::argument_type argument_type;
		public:
			virtual result_type operator()(argument_type) = 0;
		};
		template<typename Arg1, typename Arg2, typename Result>
		class operator2
			: public operator_base
			, public std::binary_function<Arg1, Arg2, Result>
		{
		public:
			typedef std::binary_function<Arg1, Arg2, Result> function_type;
			typedef typename function_type::result_type result_type;
			typedef typename function_type::first_argument_type first_argument_type;
			typedef typename function_type::second_argument_type second_argument_type;
		public:
			virtual result_type operator()(first_argument_type, second_argument_type) = 0;
		};
		//
		// caller1_base, caller1
		//
		class caller1_base {
		public:
			virtual ~caller1_base() {}
			//virtual types::any_type operator()(types::any_type const&) = 0;
			virtual types::any_type operator()(types::any_type&) = 0;
		};
		template<typename Arg1, typename Result>
		class caller1
			: public caller1_base
			, public std::unary_function<Arg1, Result>
		{
		public:
			typedef std::unary_function<Arg1, Result> function_type;
			typedef typename function_type::result_type result_type;
			typedef typename function_type::argument_type argument_type;
		private:
			boost::shared_ptr<operator_base> op_;
		public:
			caller1(boost::shared_ptr<operator_base> const& v)
				: op_(v)
			{}
			//types::any_type operator()(types::any_type const& arg1) {
			//	return dynamic_cast<operator1<argument_type, result_type>&>(*op_)(
			//		boost::any_cast<argument_type>(arg1)
			//		);
			//}
			types::any_type operator()(types::any_type& arg1) {
				return dynamic_cast<operator1<argument_type, result_type>&>(*op_)(
					boost::any_cast<argument_type>(arg1)
					);
			}
		};
		//
		// caller2_base, caller2
		//
		class caller2_base {
		public:
			virtual ~caller2_base() {}
			//virtual types::any_type operator()(types::any_type const&, types::any_type const&) = 0;
			//virtual types::any_type operator()(types::any_type const&, types::any_type &) = 0;
			//virtual types::any_type operator()(types::any_type&, types::any_type const&) = 0;
			virtual types::any_type operator()(types::any_type&, types::any_type&) = 0;
			//virtual types::any_type operator()(types::any_type const&, reference_wrapper_base&) = 0;
			virtual types::any_type operator()(types::any_type&, reference_wrapper_base&) = 0;
			//virtual types::any_type operator()(reference_wrapper_base&, types::any_type const&) = 0;
			virtual types::any_type operator()(reference_wrapper_base&, types::any_type&) = 0;
			//virtual types::any_type operator()(types::any_type const&, const_reference_wrapper_base&) = 0;
			virtual types::any_type operator()(types::any_type&, const_reference_wrapper_base&) = 0;
			//virtual types::any_type operator()(const_reference_wrapper_base&, types::any_type const&) = 0;
			virtual types::any_type operator()(const_reference_wrapper_base&, types::any_type&) = 0;
		};
		template<typename Arg1, typename Arg2, typename Result>
		class caller2
			: public caller2_base
			, public std::binary_function<Arg1, Arg2, Result>
		{
		public:
			typedef std::binary_function<Arg1, Arg2, Result> function_type;
			typedef typename function_type::result_type result_type;
			typedef typename function_type::first_argument_type first_argument_type;
			typedef typename function_type::second_argument_type second_argument_type;
		private:
			boost::shared_ptr<operator_base> op_;
		public:
			caller2(boost::shared_ptr<operator_base> const& v)
				: op_(v)
			{}
			//types::any_type operator()(types::any_type const& arg1, types::any_type const& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		boost::any_cast<first_argument_type>(arg1),
			//		boost::any_cast<second_argument_type>(arg2)
			//		);
			//}
			//types::any_type operator()(types::any_type const& arg1, types::any_type& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		boost::any_cast<first_argument_type>(arg1),
			//		boost::any_cast<second_argument_type>(arg2)
			//		);
			//}
			//types::any_type operator()(types::any_type& arg1, types::any_type const& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		boost::any_cast<first_argument_type>(arg1),
			//		boost::any_cast<second_argument_type>(arg2)
			//		);
			//}
			types::any_type operator()(types::any_type& arg1, types::any_type& arg2) {
				return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
					boost::any_cast<first_argument_type>(arg1),
					boost::any_cast<second_argument_type>(arg2)
					);
			}
			//types::any_type operator()(types::any_type const& arg1, reference_wrapper_base& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		boost::any_cast<first_argument_type>(arg1),
			//		dynamic_cast<reference_wrapper<typename sprig::remove_const_reference<second_argument_type>::type>&>(arg2).get()
			//		);
			//}
			types::any_type operator()(types::any_type& arg1, reference_wrapper_base& arg2) {
				return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
					boost::any_cast<first_argument_type>(arg1),
					dynamic_cast<reference_wrapper<typename sprig::remove_const_reference<second_argument_type>::type>&>(arg2).get()
					);
			}
			//types::any_type operator()(reference_wrapper_base& arg1, types::any_type const& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		dynamic_cast<reference_wrapper<typename sprig::remove_const_reference<first_argument_type>::type>&>(arg1).get(),
			//		boost::any_cast<second_argument_type>(arg2)
			//		);
			//}
			types::any_type operator()(reference_wrapper_base& arg1, types::any_type& arg2) {
				return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
					dynamic_cast<reference_wrapper<typename sprig::remove_const_reference<first_argument_type>::type>&>(arg1).get(),
					boost::any_cast<second_argument_type>(arg2)
					);
			}
			//types::any_type operator()(types::any_type const& arg1, const_reference_wrapper_base& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		boost::any_cast<first_argument_type>(arg1),
			//		dynamic_cast<const_reference_wrapper<typename boost::remove_reference<second_argument_type>::type>&>(arg2).get()
			//		);
			//}
			types::any_type operator()(types::any_type& arg1, const_reference_wrapper_base& arg2) {
				return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
					boost::any_cast<first_argument_type>(arg1),
					dynamic_cast<const_reference_wrapper<typename boost::remove_reference<second_argument_type>::type>&>(arg2).get()
					);
			}
			//types::any_type operator()(const_reference_wrapper_base& arg1, types::any_type const& arg2) {
			//	return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
			//		dynamic_cast<const_reference_wrapper<typename boost::remove_reference<first_argument_type>::type>&>(arg1).get(),
			//		boost::any_cast<second_argument_type>(arg2)
			//		);
			//}
			types::any_type operator()(const_reference_wrapper_base& arg1, types::any_type& arg2) {
				return dynamic_cast<operator2<first_argument_type, second_argument_type, result_type>&>(*op_)(
					dynamic_cast<const_reference_wrapper<typename boost::remove_reference<first_argument_type>::type>&>(arg1).get(),
					boost::any_cast<second_argument_type>(arg2)
					);
			}
		};
		//
		// types
		//
		namespace types {
			typedef boost::shared_ptr<caller1_base> caller1_instance_type;
			typedef boost::shared_ptr<caller2_base> caller2_instance_type;
			typedef std::map<types::signature1_type, caller1_instance_type, signature1_comparator> operator1_map_type;
			typedef std::map<types::signature2_type, caller2_instance_type, signature2_comparator> operator2_map_type;
		}	// namespace types
	}	// namespace variants
}	// namespace sprig

#endif	// #ifndef SPRIG_VARIANTS_FOUNDATION_HPP
