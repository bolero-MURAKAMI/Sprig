#ifndef SPRIG_DG_VALUE_INFO_HPP
#define SPRIG_DG_VALUE_INFO_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <typeinfo>
#include <vector>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/range/reference.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/dg/foundation.hpp>

//	COMMENT: use value_info
#include <utility>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/optional/optional.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <sprig/external/windows.hpp>
#include <sprig/external/d3d9.hpp>
#include <sprig/external/d3dx9.hpp>
#include <sprig/priority_map.hpp>
#include <sprig/com_ptr.hpp>

//
// SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_GEN, SPRIG_DG_VALUE_INFO_ARGS_GEN
//
#define SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_GEN(z, n, d) typename BOOST_PP_CAT(T, n)
#define SPRIG_DG_VALUE_INFO_ARGS_GEN(z, n, d) BOOST_PP_CAT(T, n)
//
// SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_ENUM, SPRIG_DG_VALUE_INFO_ARGS_ENUM
//
#define SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_ENUM(n) BOOST_PP_ENUM(n, SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_GEN, BOOST_PP_EMPTY())
#define SPRIG_DG_VALUE_INFO_ARGS_ENUM(n) BOOST_PP_ENUM(n, SPRIG_DG_VALUE_INFO_ARGS_GEN, BOOST_PP_EMPTY())

//
// SPRIG_DG_SPECIALIZED_VALUE_INFO
//
#define SPRIG_DG_SPECIALIZED_VALUE_INFO(type) \
	template<> \
	struct is_specialized_value_info<type> \
		: boost::mpl::true_ \
	{}
//
// SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE
//
#define SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(n, template_type) \
	template<SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_ENUM(n)> \
	struct is_specialized_value_info<template_type<SPRIG_DG_VALUE_INFO_ARGS_ENUM(n)> > \
		: boost::mpl::true_ \
	{}

//
// SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_GEN
//
#define SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_GEN(z, n, d) \
	SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(n, d);
//
// SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS
//
#define SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS(first, last, template_type) \
	BOOST_PP_REPEAT_FROM_TO(first, last, SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_GEN, template_type)

//
// SPRIG_DG_ENABLE_TRACKING_VALUE_INFO
//
#define SPRIG_DG_ENABLE_TRACKING_VALUE_INFO(type) \
	template<> \
	struct is_enable_tracking_value_info<type> \
		: boost::mpl::true_ \
	{}
//
// SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE
//
#define SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE(n, template_type) \
	template<SPRIG_DG_VALUE_INFO_TYPENAME_ARGS_ENUM(n)> \
	struct is_enable_tracking_value_info<template_type<SPRIG_DG_VALUE_INFO_ARGS_ENUM(n)> > \
		: boost::mpl::true_ \
	{}

//
// SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE_GEN
//
#define SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE_GEN(z, n, d) \
	SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE(n, d);
//
// SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE_OVERLOADS
//
#define SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE_OVERLOADS(first, last, template_type) \
	BOOST_PP_REPEAT_FROM_TO(first, last, SPRIG_DG_ENABLE_TRACKING_VALUE_INFO_TEMPLATE_GEN, template_type)

namespace sprig {
	namespace dg {
		//
		// is_specialized_value_info
		//
		template<typename T>
		struct is_specialized_value_info : boost::mpl::false_ {};

		//
		// is_enable_tracking_value_info
		//
		//	COMMENT: is_pointer || is_arithmetic || is_specialized_value_info
		template<typename T>
		struct is_enable_tracking_value_info {
		private:
			typedef typename boost::remove_const<T>::type track_type;
		public:
			typedef typename boost::mpl::or_<
				typename boost::is_pointer<track_type>::type,
				typename boost::is_arithmetic<track_type>::type,
				typename is_specialized_value_info<track_type>::type
			>::type type;
			static bool const value = type::value;
		};

		//
		// stringize_value_info
		//
		template<typename T>
		SPRIG_INLINE typename boost::enable_if<sprig::is_call_copy_param<T>, string_type>::type
		stringize_value_info(T const value) {
			local_logger_type logger;
			{
				value_info_section_line(TEXT("sprig:dg:value_info"), value, logger);
			}
			return logger.str();
		}
		template<typename T>
		SPRIG_INLINE typename boost::disable_if<sprig::is_call_copy_param<T>, string_type>::type
		stringize_value_info(T const& value) {
			local_logger_type logger;
			{
				value_info_section_line(TEXT("sprig:dg:value_info"), value, logger);
			}
			return logger.str();
		}

		//
		// value_info_section_line
		//
		template<typename Name, typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename sprig::is_call_copy_param<Name>::type,
				typename sprig::is_call_copy_param<T>::type
			>
		>::type
		value_info_section_line(Name const name, T const value, Logger& logger) {
			Logger::section_type section_(name, *logger);
			value_info(value, logger);
		}
		template<typename Name, typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename sprig::is_call_copy_param<Name>::type,
				typename boost::mpl::not_<typename sprig::is_call_copy_param<T>::type>::type
			>
		>::type
		value_info_section_line(Name const name, T const& value, Logger& logger) {
			Logger::section_type section_(name, *logger);
			value_info(value, logger);
		}
		template<typename Name, typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename sprig::is_call_copy_param<Name>::type>::type,
				typename sprig::is_call_copy_param<T>::type
			>
		>::type
		value_info_section_line(Name const& name, T const value, Logger& logger) {
			Logger::section_type section_(name, *logger);
			value_info(value, logger);
		}
		template<typename Name, typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename sprig::is_call_copy_param<Name>::type>::type,
				typename boost::mpl::not_<typename sprig::is_call_copy_param<T>::type>::type
			>
		>::type
		value_info_section_line(Name const& name, T const& value, Logger& logger) {
			Logger::section_type section_(name, *logger);
			value_info(value, logger);
		}

		//
		// value_info
		//
		//	COMMENT: !is_specialized_value_info && !is_pointer && !is_member_pointer && !is_array && is_call_copy_param
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename is_specialized_value_info<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_pointer<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_member_pointer<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_array<T>::type>::type,
				typename sprig::is_call_copy_param<T>::type
			>
		>::type
		value_info(T const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("stringized"), value);
		}
		//	COMMENT: !is_specialized_value_info && !is_pointer && !is_member_pointer && !is_array && !is_call_copy_param
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename is_specialized_value_info<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_pointer<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_member_pointer<T>::type>::type,
				typename boost::mpl::not_<typename boost::is_array<T>::type>::type,
				typename boost::mpl::not_<typename sprig::is_call_copy_param<T>::type>::type
			>
		>::type
		value_info(T const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("stringized"), value);
		}

		//
		// value_info_dereference_type, value_info_track
		//
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::is_same<typename boost::remove_const<typename boost::remove_pointer<T>::type>::type, void>
		>::type
		value_info_dereference_type(T const value, Logger& logger) {
			logger.section_line(TEXT("dereference-type"), TEXT("void"));
		}
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::disable_if<
			boost::is_same<typename boost::remove_const<typename boost::remove_pointer<T>::type>::type, void>
		>::type
		value_info_dereference_type(T const value, Logger& logger) {
			logger.section_line(TEXT("dereference-type"), typeid(*value).name());
		}
		//	COMMENT: is_enable_tracking_value_info
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			is_enable_tracking_value_info<typename boost::remove_pointer<T>::type>
		>::type
		value_info_track(T const value, Logger& logger) {
			logger.section_comment(TEXT("enable pointer-tracking"));
			if (value) {
				//value_info_dereference_type(value, logger);
				value_info_section_line(TEXT("pointer-tracking"), *value, logger);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}
		//	COMMENT: !is_enable_tracking_value_info
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::disable_if<
			is_enable_tracking_value_info<typename boost::remove_pointer<T>::type>
		>::type
		value_info_track(T const value, Logger& logger) {
			logger.section_comment(TEXT("disable pointer-tracking"));
			if (value) {
				//value_info_dereference_type(value, logger);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}

		//
		// value_info_enumerate_range
		//
		template<typename Range, typename Logger>
		SPRIG_INLINE void value_info_enumerate_range(Range const value, Logger& logger) {
			Logger::section_type section_(TEXT("range-enumerating"), *logger);
			BOOST_FOREACH(typename boost::range_reference<Range>::type e, value) {
				value_info(e, logger);
			}
		}

		//
		// overload value_info
		//
		//	COMMENT: !is_specialized_value_info && is_pointer
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename is_specialized_value_info<T>::type>::type,
				typename boost::is_pointer<T>::type
			>
		>::type
		value_info(T const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("stringized"), value);
			value_info_track(value, logger);
		}
		//	COMMENT: !is_specialized_value_info && is_member_pointer
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename is_specialized_value_info<T>::type>::type,
				typename boost::is_member_pointer<T>::type
			>
		>::type
		value_info(T const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("stringized"), value);
		}
		//	COMMENT: !is_specialized_value_info && is_array
		template<typename T, typename Logger>
		SPRIG_INLINE typename boost::enable_if<
			boost::mpl::and_<
				typename boost::mpl::not_<typename is_specialized_value_info<T>::type>::type,
				typename boost::is_array<T>::type
			>
		>::type
		value_info(T const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("stringized"), value);
			value_info_enumerate_range(value, logger);
		}

		//
		// specialized value_info : POD
		//
		SPRIG_DG_SPECIALIZED_VALUE_INFO(char const*);
		template<typename Logger>
		SPRIG_INLINE void value_info(char const* const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			if (value) {
				logger.section_line(TEXT("stringized"), value);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}
		SPRIG_DG_SPECIALIZED_VALUE_INFO(char*);
		template<typename Logger>
		SPRIG_INLINE void value_info(char* const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			if (value) {
				logger.section_line(TEXT("stringized"), value);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}
		SPRIG_DG_SPECIALIZED_VALUE_INFO(wchar_t const*);
		template<typename Logger>
		SPRIG_INLINE void value_info(wchar_t const* const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			if (value) {
				logger.section_line(TEXT("stringized"), value);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}
		SPRIG_DG_SPECIALIZED_VALUE_INFO(wchar_t*);
		template<typename Logger>
		SPRIG_INLINE void value_info(wchar_t* const value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			if (value) {
				logger.section_line(TEXT("stringized"), value);
			} else {
				logger.section_comment(TEXT("null-pointer"));
			}
		}
		//
		// specialized value_info : std
		//
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(2, std::pair);
		template<typename T1, typename T2, typename Logger>
		SPRIG_INLINE void value_info(std::pair<T1, T2> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value_info_section_line(TEXT("first"), value.first, logger);
			value_info_section_line(TEXT("second"), value.second, logger);
		}
		//
		// specialized value_info : windows
		//
		//	COMMENT: POINT
		SPRIG_DG_SPECIALIZED_VALUE_INFO(POINT);
		template<typename Logger>
		SPRIG_INLINE void value_info(POINT const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("x"), value.x);
			logger.section_line(TEXT("y"), value.y);
		}
		//	COMMENT: SIZE
		SPRIG_DG_SPECIALIZED_VALUE_INFO(SIZE);
		template<typename Logger>
		SPRIG_INLINE void value_info(SIZE const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("cx"), value.cx);
			logger.section_line(TEXT("cy"), value.cy);
		}
		//	COMMENT: RECT
		SPRIG_DG_SPECIALIZED_VALUE_INFO(RECT);
		template<typename Logger>
		SPRIG_INLINE void value_info(RECT const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("left"), value.left);
			logger.section_line(TEXT("top"), value.top);
			logger.section_line(TEXT("right"), value.right);
			logger.section_line(TEXT("bottom"), value.bottom);
		}
		//	COMMENT: WNDCLASS
		SPRIG_DG_SPECIALIZED_VALUE_INFO(WNDCLASS);
		template<typename Logger>
		SPRIG_INLINE void value_info(WNDCLASS const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("style"), value.style);
			logger.section_line(TEXT("lpfnWndProc"), value.lpfnWndProc);
			logger.section_line(TEXT("cbClsExtra"), value.cbClsExtra);
			logger.section_line(TEXT("cbWndExtra"), value.cbWndExtra);
			logger.section_line(TEXT("hInstance"), value.hInstance);
			logger.section_line(TEXT("hIcon"), value.hIcon);
			logger.section_line(TEXT("hCursor"), value.hCursor);
			logger.section_line(TEXT("hbrBackground"), value.hbrBackground);
			//	COMMENT: 未初期化である可能性があるので、汎用ポインタにキャストして出力。
			//logger.section_line(TEXT("lpszMenuName"), value.lpszMenuName);
			//logger.section_line(TEXT("lpszClassName"), value.lpszClassName);
			logger.section_line(TEXT("lpszMenuName"), static_cast<void const*>(value.lpszMenuName));
			logger.section_line(TEXT("lpszClassName"), static_cast<void const*>(value.lpszClassName));
		}
		//
		// specialized value_info : D3D
		//
		//	COMMENT: D3DPRESENT_PARAMETERS
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DPRESENT_PARAMETERS);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DPRESENT_PARAMETERS const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("BackBufferWidth"), value.BackBufferWidth);
			logger.section_line(TEXT("BackBufferHeight"), value.BackBufferHeight);
			logger.section_line(TEXT("BackBufferFormat"), value.BackBufferFormat);
			logger.section_line(TEXT("BackBufferCount"), value.BackBufferCount);
			logger.section_line(TEXT("MultiSampleType"), value.MultiSampleType);
			logger.section_line(TEXT("MultiSampleQuality"), value.MultiSampleQuality);
			logger.section_line(TEXT("SwapEffect"), value.SwapEffect);
			logger.section_line(TEXT("hDeviceWindow"), value.hDeviceWindow);
			logger.section_line(TEXT("Windowed"), value.Windowed);
			logger.section_line(TEXT("EnableAutoDepthStencil"), value.EnableAutoDepthStencil);
			logger.section_line(TEXT("AutoDepthStencilFormat"), value.AutoDepthStencilFormat);
			logger.section_line(TEXT("FullScreen_RefreshRateInHz"), value.FullScreen_RefreshRateInHz);
			logger.section_line(TEXT("PresentationInterval"), value.PresentationInterval);
		}
		//	COMMENT: D3DSURFACE_DESC
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DSURFACE_DESC);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DSURFACE_DESC const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("Format"), value.Format);
			logger.section_line(TEXT("Type"), value.Type);
			logger.section_line(TEXT("Usage"), value.Usage);
			logger.section_line(TEXT("Pool"), value.Pool);
			logger.section_line(TEXT("MultiSampleType"), value.MultiSampleType);
			logger.section_line(TEXT("MultiSampleQuality"), value.MultiSampleQuality);
			logger.section_line(TEXT("Width"), value.Width);
			logger.section_line(TEXT("Height"), value.Height);
		}
		//	COMMENT: D3DLOCKED_RECT
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DLOCKED_RECT);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DLOCKED_RECT const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("Pitch"), value.Pitch);
			logger.section_line(TEXT("pBits"), value.pBits);
		}
		//
		// specialized value_info : D3DX
		//
		//	COMMENT: D3DXVECTOR2
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DXVECTOR2);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DXVECTOR2 const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("[0]"), static_cast<FLOAT const*>(value)[0]);
			logger.section_line(TEXT("[1]"), static_cast<FLOAT const*>(value)[1]);
		}
		//	COMMENT: D3DXVECTOR3
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DXVECTOR3);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DXVECTOR3 const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("[0]"), static_cast<FLOAT const*>(value)[0]);
			logger.section_line(TEXT("[1]"), static_cast<FLOAT const*>(value)[1]);
			logger.section_line(TEXT("[2]"), static_cast<FLOAT const*>(value)[2]);
		}
		//	COMMENT: D3DXMATRIX
		SPRIG_DG_SPECIALIZED_VALUE_INFO(D3DXMATRIX);
		template<typename Logger>
		SPRIG_INLINE void value_info(D3DXMATRIX const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("_11"), value._11);
			logger.section_line(TEXT("_12"), value._12);
			logger.section_line(TEXT("_13"), value._13);
			logger.section_line(TEXT("_14"), value._14);
			logger.section_line(TEXT("_21"), value._21);
			logger.section_line(TEXT("_22"), value._22);
			logger.section_line(TEXT("_23"), value._23);
			logger.section_line(TEXT("_24"), value._24);
			logger.section_line(TEXT("_31"), value._31);
			logger.section_line(TEXT("_32"), value._32);
			logger.section_line(TEXT("_33"), value._33);
			logger.section_line(TEXT("_34"), value._34);
			logger.section_line(TEXT("_41"), value._41);
			logger.section_line(TEXT("_42"), value._42);
			logger.section_line(TEXT("_43"), value._43);
			logger.section_line(TEXT("_44"), value._44);
		}
		//
		// specialized value_info : boost
		//
		//	COMMENT: boost::shared_ptr
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(1, boost::shared_ptr);
		template<typename T, typename Logger>
		SPRIG_INLINE void value_info(boost::shared_ptr<T> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("get"), value.get());
			logger.section_line(TEXT("use_count"), value.use_count());
			value_info(value.get(), logger);
		}
		//	COMMENT: boost::scoped_ptr
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(1, boost::scoped_ptr);
		template<typename T, typename Logger>
		SPRIG_INLINE void value_info(boost::scoped_ptr<T> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("get"), value.get());
			value_info(value.get(), logger);
		}
		//	COMMENT: boost::optional
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(1, boost::optional);
		template<typename T, typename Logger>
		SPRIG_INLINE void value_info(boost::optional<T> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("get_ptr"), value.get_ptr());
			value_info(value.get_ptr(), logger);
		}
		//	COMMENT: boost::multi_index_container
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(3, boost::multi_index_container);
		template<typename Value, typename indexSpecifierListT, typename allocatorT, typename Logger>
		SPRIG_INLINE void value_info(boost::multi_index_container<Value, indexSpecifierListT, allocatorT> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value_info_enumerate_range(value, logger);
		}
		//
		// specialized value_info : sprig
		//
		//	COMMENT: sprig::priority_map_element
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(3, sprig::priority_map_element);
		template<typename Key, typename Priority, typename Mapped, typename Logger>
		SPRIG_INLINE void value_info(sprig::priority_map_element<Key, Priority, Mapped> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value_info_section_line(TEXT("get_key"), value.get_key(), logger);
			value_info_section_line(TEXT("get_priority"), value.get_priority(), logger);
			value_info_section_line(TEXT("get_mapped"), value.get_mapped(), logger);
		}
		//	COMMENT: sprig::com_ptr
		SPRIG_DG_SPECIALIZED_VALUE_INFO_TEMPLATE(1, sprig::com_ptr);
		template<typename T, typename Logger>
		SPRIG_INLINE void value_info(sprig::com_ptr<T> const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("get_ptr_ptr"), value.get_ptr_ptr());
			value_info(value.get_ptr_ptr(), logger);
		}

		//
		// SPRIG_DG_OUTPUT_VALUE_INFO
		//
#define SPRIG_DG_OUTPUT_VALUE_INFO(name, contents) \
	{ \
		SPRIG_DG_SECTION(name); \
		sprig::dg::string_type s(sprig::dg::stringize_value_info(contents)); \
		sprig::dg::indent_logger_type::trim_last_lf(s); \
		SPRIG_DG_OUTPUT(s); \
	}

	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_VALUE_INFO_HPP
