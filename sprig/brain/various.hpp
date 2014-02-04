/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_BRAIN_VARIOUS_HPP
#define SPRIG_BRAIN_VARIOUS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <vector>
#include <boost/static_assert.hpp>
#include <boost/assign/list_of.hpp>
#include <sprig/literal_array.hpp>

namespace sprig {
	namespace brain {
		namespace f_ck {
			//
			// neko_mimi_literals
			//
			//	COMMENT: neko mimi Fu** �̃��e������`
			//	COMMENT: ��{�R�}���h�ɑΉ����镶������`����
			//
			struct neko_mimi_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"�l�R�~�~�I",
						"�l�R�~�~���[�h",
						"���ɂ�����",
						"���̂����ׁ[",
						"��E���E���E���E��",
						"�t���t���t�����[��",
						"�L�X�L�X�c",
						"�L�X�c�������Ȃ���������c"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// nagato_literals
			//
			//	COMMENT: ����L�� �̃��e������`
			//	COMMENT: ��{�R�}���h�ɑΉ����镶������`����
			//
			struct nagato_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"�c�c�c",
						"�c�c�c�c",
						"�c",
						"�c�c",
						"�c�c�c�c�c�c",
						"�c�c�c�c�c",
						"�u",
						"�v"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// aegi_literals
			//
			//	COMMENT: ���������L�q���� �̃��e������`
			//	COMMENT: ��{�R�}���h�ɑΉ����镶������`����
			//
			struct aegi_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"�����b",
						"���b�I",
						"���b",
						"��b",
						"�C�N�I�C�����Ⴄ�I",
						"�����Ă�̊������Ⴄ���I",
						"���Ă��I���肢�I",
						"��߂Ȃ��ł��I"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// hokuto_literals
			//
			//	COMMENT: �k�l�]��a �̃��e������`
			//	COMMENT: ��{�R�}���h�ɑΉ����镶������`����
			//
			struct hokuto_literals {
				typedef literal_array<char const, false> type;
				template<int N>
				static type const& get() {
					static type const literals[] = {
						"��",
						"��",
						"��",
						"�[",
						"���܂��͂�������ł���",
						"��",
						"��",
						"�I"
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};

			//
			// misa_literals
			//
			//	COMMENT: Misa �̃��e������`
			//	COMMENT: ��{�R�}���h�ɑΉ����镶����Z�b�g���`����
			//
			struct misa_literals {
				typedef std::vector<literal_array<char const, false> > type;
				template<int N>
				static type const& get() {
					typedef literal_array<char const, false> literal_type;
					static type const literals[] = {
						boost::assign::list_of<literal_type>(">")("��")("�`")("�["),
						boost::assign::list_of<literal_type>("<")("��")("��")("��"),
						boost::assign::list_of<literal_type>("+")("��")("��")("��")("��"),
						boost::assign::list_of<literal_type>("-")("��")("�b"),
						boost::assign::list_of<literal_type>(".")("�I"),
						boost::assign::list_of<literal_type>(",")("�H"),
						boost::assign::list_of<literal_type>("[")("�u")("�w"),
						boost::assign::list_of<literal_type>("]")("�v")("�x")
					};
					BOOST_STATIC_ASSERT(N < sizeof(literals) / sizeof(literals[0]));
					return literals[N];
				}
			};
		}	// namespace f_ck
	}	// namespace brain
}	// namespace sprig

#endif	// #ifndef SPRIG_BRAIN_VARIOUS_HPP
