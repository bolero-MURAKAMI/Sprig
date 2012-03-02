#ifndef SPRIG_KRKR_NCB_HPP
#define SPRIG_KRKR_NCB_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cassert>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/tp_stub.hpp>
#include <sprig/external/ncbind/ncbind.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/krkr/tjs.hpp>

namespace sprig {
	namespace krkr {
		namespace ncb {
			//
			// typedefs
			//
			typedef void (*regist_callback_type)();

			//
			//	COMMENT: ncbTypeConvertorを使ったtTJSVariantと他の型との相互変換
			//
			// ToTarget
			//
			template <typename T>
			SPRIG_INLINE void ToTarget(T& lhs, tTJSVariant const& rhs) {
				BOOST_STATIC_ASSERT((ncbTypeConvertor::Conversion<tTJSVariant, T>::Exists));
				ncbTypeConvertor::SelectConvertorType<tTJSVariant, T>::Type()(lhs, rhs);
			}
			template <typename T>
			SPRIG_INLINE T ToTarget(tTJSVariant const& value) {
				BOOST_STATIC_ASSERT((ncbTypeConvertor::Conversion<tTJSVariant, T>::Exists));
				T result;
				ncbTypeConvertor::SelectConvertorType<tTJSVariant, T>::Type()(result, value);
				return result;
			}
			//
			// ToVariant
			//
			template <typename T>
			SPRIG_INLINE void ToVariant(tTJSVariant& lhs, T const& rhs) {
				BOOST_STATIC_ASSERT((ncbTypeConvertor::Conversion<T, tTJSVariant>::Exists));
				ncbTypeConvertor::SelectConvertorType<T, tTJSVariant>::Type()(lhs, rhs);
			}
			template <typename T>
			SPRIG_INLINE tTJSVariant ToVariant(T const& value) {
				BOOST_STATIC_ASSERT((ncbTypeConvertor::Conversion<T, tTJSVariant>::Exists));
				tTJSVariant result;
				ncbTypeConvertor::SelectConvertorType<T, tTJSVariant>::Type()(result, value);
				return result;
			}

			//
			//	COMMENT: string_argument_type用の型変換機
			//
			// StringArgumentConvertor
			//
			template <typename T>
			class StringArgumentConvertor {
			public:
				typedef T type;
			private:
				type temp_;
			private:
				// NOTE: typename selectT::value_type::value_typeを直接boost::enable_if<>に渡すと何故かコンパイルエラーになる。
				// NOTE: それを回避するためにget_charヘルパメタ関数を使用する。
				template<typename selectT>
				struct get_char {
					typedef typename selectT::value_type::value_type type;
				};
			private:
				template <typename selectT, typename Value>
				typename boost::enable_if<boost::is_same<typename get_char<selectT>::type, tjs::char_type> >::type
				TargetToVariant(tTJSVariant& lhs, Value const& rhs) {
					lhs = ncbTypeConvertor::ToPointer<Value const&>::Get(rhs)->ref().c_str();
				}
				template <typename selectT, typename Value>
				typename boost::disable_if<boost::is_same<typename get_char<selectT>::type, tjs::char_type> >::type
				TargetToVariant(tTJSVariant& lhs, Value const& rhs) {
					lhs = sprig::str_cast<typename type::value_type>(ncbTypeConvertor::ToPointer<Value const&>::Get(rhs)->ref()).c_str();
				}
				template <typename selectT, typename Value>
				typename boost::enable_if<boost::is_same<typename get_char<selectT>::type, tjs::char_type> >::type
				VariantToTarget(Value& lhs, tTJSVariant const& rhs) {
					if (rhs.Type() == tvtString) {
						temp_ = tTJSString(rhs.AsStringNoAddRef()).c_str();
					} else {
						tTJSVariant value(rhs);
						value.ToString();
						temp_ = tTJSString(value.AsStringNoAddRef()).c_str();
					}
					lhs = ncbTypeConvertor::ToTarget<Value>::Get(&temp_);
				}
				template <typename selectT, typename Value>
				typename boost::disable_if<boost::is_same<typename get_char<selectT>::type, tjs::char_type> >::type
				VariantToTarget(Value& lhs, tTJSVariant const& rhs) {
					if (rhs.Type() == tvtString) {
						temp_ = sprig::str_cast<typename type::value_type>(tTJSString(rhs.AsStringNoAddRef()).c_str());
					} else {
						tTJSVariant value(rhs);
						value.ToString();
						temp_ = sprig::str_cast<typename type::value_type>(tTJSString(value.AsStringNoAddRef()).c_str());
					}
					lhs = ncbTypeConvertor::ToTarget<Value>::Get(&temp_);
				}
			public:
				template <typename Value>
				void operator()(tTJSVariant& lhs, Value const& rhs) const {
					TargetToVariant<type>(lhs, rhs);
				}
				template <typename Value>
				void operator()(Value& lhs, tTJSVariant const& rhs) {
					// NOTE: ValueがTへのポインタの場合、temp_のポインタを返す。
					// NOTE: すなわちValueがTへのポインタの場合、その寿命はこのコンバータの寿命と同期する。
					VariantToTarget<type>(lhs, rhs);
				}
			};
		}	// namespace ncb
	}	// namespace krkr
}	// namespace sprig

//
// SPRIG_KRKR_NCB_TYPECONV_STRING_ARGUMENT
//
#define SPRIG_KRKR_NCB_TYPECONV_STRING_ARGUMENT(TYPE) \
	NCB_TYPECONV_SRCMAP_SET(TYPE, sprig::krkr::ncb::StringArgumentConvertor<TYPE>, true); \
	NCB_TYPECONV_DSTMAP_SET(TYPE, sprig::krkr::ncb::StringArgumentConvertor<TYPE>, true);

SPRIG_KRKR_NCB_TYPECONV_STRING_ARGUMENT(sprig::string_argument);
SPRIG_KRKR_NCB_TYPECONV_STRING_ARGUMENT(sprig::wstring_argument);

#endif	// #ifndef SPRIG_KRKR_NCB_HPP
