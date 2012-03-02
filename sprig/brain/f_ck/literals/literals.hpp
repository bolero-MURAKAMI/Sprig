#ifndef SPRIG_BRAIN_F_CK_LITERALS_LITERALS_HPP
#define SPRIG_BRAIN_F_CK_LITERALS_LITERALS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/static_assert.hpp>
#include <boost/mpl/integral_c.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// bf_literals
			//
			//	COMMENT: Brainf*ck のリテラル定義
			//	COMMENT: 基本コマンドに対応する単一文字を定義する
			//
			struct bf_literals {
				typedef char type;
				template<int N>
				struct get {};
			};
			template<>
			struct bf_literals::get<0>
				: public boost::mpl::integral_c<char, '>'>
			{};
			template<>
			struct bf_literals::get<1>
				: public boost::mpl::integral_c<char, '<'>
			{};
			template<>
			struct bf_literals::get<2>
				: public boost::mpl::integral_c<char, '+'>
			{};
			template<>
			struct bf_literals::get<3>
				: public boost::mpl::integral_c<char, '-'>
			{};
			template<>
			struct bf_literals::get<4>
				: public boost::mpl::integral_c<char, '.'>
			{};
			template<>
			struct bf_literals::get<5>
				: public boost::mpl::integral_c<char, ','>
			{};
			template<>
			struct bf_literals::get<6>
				: public boost::mpl::integral_c<char, '['>
			{};
			template<>
			struct bf_literals::get<7>
				: public boost::mpl::integral_c<char, ']'>
			{};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_F_CK_LITERALS_LITERALS_HPP
