/*=============================================================================
  Copyright (c) 2010-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_FUNCTIONS_HPP
#define SPRIG_DG_FUNCTIONS_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstring>
#include <boost/none.hpp>
#include <boost/optional/optional.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/get_pointer.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>

namespace sprig {
	namespace dg {
		//
		// declares
		//
		static LONG rect_width(RECT const& rect);
		static LONG rect_height(RECT const& rect);
		static RECT make_rect(UINT left, UINT top, UINT right, UINT bottom);
		static POINT make_point(LONG x, LONG y);
		static SIZE make_size(LONG cx, LONG cy);
		static D3DXMATRIX& matrix_inverse(
			D3DXMATRIX& dest,
			sprig::call_traits<D3DXMATRIX>::param_type src
			);
		static D3DXMATRIX matrix_inverse(
			sprig::call_traits<D3DXMATRIX>::param_type src
			);
		static D3DXVECTOR2& vec2_transformation_coord(
			D3DXVECTOR2& dest,
			sprig::call_traits<D3DXVECTOR2>::param_type src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			);
		static D3DXVECTOR2 vec2_transformation_coord(
			D3DXVECTOR2& src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			);
		static D3DXVECTOR3& vec3_transformation_coord(
			D3DXVECTOR3& dest,
			sprig::call_traits<D3DXVECTOR3>::param_type src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			);
		static D3DXVECTOR3 vec3_transformation_coord(
			D3DXVECTOR3& src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			);
		static D3DXMATRIX& matrix_transformation_2d(
			D3DXMATRIX& matrix,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling = boost::none,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation = boost::none
			);
		static D3DXMATRIX matrix_transformation_2d(
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling = boost::none,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation = boost::none
			);
		static D3DXMATRIX& matrix_inverse_transformation_2d(
			D3DXMATRIX& matrix,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling = boost::none,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation = boost::none
			);
		static D3DXMATRIX matrix_inverse_transformation_2d(
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling = boost::none,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation = boost::none
			);
		static HRESULT set_sprite_transform(
			sprig::call_traits<sprite_type>::param_type sprite,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling = boost::none,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation = boost::none
			);
		static HRESULT draw_sprite(
			sprig::call_traits<sprite_type>::param_type sprite,
			sprig::call_traits<texture_type>::param_type texture,
			boost::optional<sprig::call_traits<RECT>::param_type> rect = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR3>::param_type> center = boost::none,
			boost::optional<sprig::call_traits<D3DXVECTOR3>::param_type> position = boost::none,
			boost::optional<sprig::call_traits<D3DCOLOR>::param_type> color = boost::none
			);
		static HRESULT fill_surface(
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			boost::optional<sprig::call_traits<RECT>::param_type> rect = boost::none,	// �t�B�����������`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static void transfer_bits_from_render_target(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,	// ���b�N���ꂽ�̈�
			sprig::call_traits<RECT>::param_type surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset	// �R�s�[��̃I�t�Z�b�g
			);
		static HRESULT normalize_texture_rect(
			RECT& texture_rect,	// �e�N�X�`���̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<texture_type>::param_type texture,	// �e�N�X�`��
			sprig::call_traits<RECT>::param_type rect,	// ��`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static HRESULT normalize_surface_rect(
			RECT& surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<RECT>::param_type rect,	// ��`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static HRESULT normalize_surface_rect_from_memory(
			RECT& surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static void transfer_bits_from_memory(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,	// ���b�N���ꂽ�̈�
			sprig::call_traits<RECT>::param_type surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<RECT>::param_type rect	// �R�s�[���̋�`
			);
		static HRESULT transfer_from_memory(
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static HRESULT transfer_from_render_target(
			sprig::call_traits<device_type>::param_type device,	// �f�o�C�X
			sprig::call_traits<surface_type>::param_type render_target_surface,	// �����_�[�^�[�Q�b�g
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none	// �q���g�ƂȂ�T�[�t�F�C�X���
			);
		static HRESULT lock_rect(
			D3DLOCKED_RECT& locked_rect,
			sprig::call_traits<texture_type>::param_type texture,
			sprig::call_traits<DWORD>::param_type flags,
			boost::optional<sprig::call_traits<RECT>::param_type> rect = boost::none,
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none,
			sprig::call_traits<UINT>::param_type level = 0
			);
		static HRESULT lock_rect(
			D3DLOCKED_RECT& locked_rect,
			sprig::call_traits<surface_type>::param_type surface,
			sprig::call_traits<DWORD>::param_type flags,
			boost::optional<sprig::call_traits<RECT>::param_type> rect = boost::none,
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc = boost::none
			);
		static HRESULT unlock_rect(
			sprig::call_traits<texture_type>::param_type texture,
			sprig::call_traits<UINT>::param_type level = 0
			);
		static HRESULT unlock_rect(
			sprig::call_traits<surface_type>::param_type surface
			);
		static D3DCOLOR get_pixel(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,
			sprig::call_traits<POINT>::param_type point
			);

		//
		// rect_width
		//
		SPRIG_INLINE LONG rect_width(RECT const& rect) {
			return rect.right - rect.left;
		}

		//
		// rect_height
		//
		SPRIG_INLINE LONG rect_height(RECT const& rect) {
			return rect.bottom - rect.top;
		}

		//
		// make_rect
		//
		SPRIG_INLINE RECT make_rect(UINT left = 0, UINT top = 0, UINT right = 0, UINT bottom = 0) {
			RECT result = {left, top, right, bottom};
			return result;
		}

		//
		// make_point
		//
		SPRIG_INLINE POINT make_point(LONG x = 0, LONG y = 0) {
			POINT result = {x, y};
			return result;
		}

		//
		// make_size
		//
		SPRIG_INLINE SIZE make_size(LONG cx = 0, LONG cy = 0) {
			SIZE result = {cx, cy};
			return result;
		}

		//
		// matrix_inverse
		//
		SPRIG_INLINE D3DXMATRIX& matrix_inverse(
			D3DXMATRIX& dest,
			sprig::call_traits<D3DXMATRIX>::param_type src
			)
		{
			return *D3DXMatrixInverse(&dest, 0, &src);
		}
		SPRIG_INLINE D3DXMATRIX matrix_inverse(
			sprig::call_traits<D3DXMATRIX>::param_type src
			)
		{
			D3DXMATRIX dest;
			return matrix_inverse(dest, src);
		}

		//
		// vec2_transformation_coord
		//
		SPRIG_INLINE D3DXVECTOR2& vec2_transformation_coord(
			D3DXVECTOR2& dest,
			sprig::call_traits<D3DXVECTOR2>::param_type src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			)
		{
			return *D3DXVec2TransformCoord(&dest, &src, &matrix);
		}
		SPRIG_INLINE D3DXVECTOR2 vec2_transformation_coord(
			D3DXVECTOR2& src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			)
		{
			D3DXVECTOR2 dest;
			return vec2_transformation_coord(dest, src, matrix);
		}

		//
		// vec3_transformation_coord
		//
		SPRIG_INLINE D3DXVECTOR3& vec3_transformation_coord(
			D3DXVECTOR3& dest,
			sprig::call_traits<D3DXVECTOR3>::param_type src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			)
		{
			return *D3DXVec3TransformCoord(&dest, &src, &matrix);
		}
		SPRIG_INLINE D3DXVECTOR3 vec3_transformation_coord(
			D3DXVECTOR3& src,
			sprig::call_traits<D3DXMATRIX>::param_type matrix
			)
		{
			D3DXVECTOR3 dest;
			return vec3_transformation_coord(dest, src, matrix);
		}

		//
		// matrix_transformation_2d
		//
		SPRIG_INLINE D3DXMATRIX& matrix_transformation_2d(
			D3DXMATRIX& matrix,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation
			)
		{
			D3DXMATRIX scaling_matrix;
			D3DXMATRIX rotation_matrix;
			D3DXMATRIX translation_matrix;
			if (scaling) {
				D3DXMatrixScaling(&scaling_matrix, scaling->x, scaling->y, 1.0f);
			} else {
				D3DXMatrixScaling(&scaling_matrix, 1.0f, 1.0f, 1.0f);
			}
			if (rotation) {
				D3DXMatrixRotationZ(&rotation_matrix, *rotation);
			} else {
				D3DXMatrixRotationZ(&rotation_matrix, 0.0f);
			}
			if (translation) {
				D3DXMatrixTranslation(&translation_matrix, translation->x, translation->y, 0.0f);
			} else {
				D3DXMatrixTranslation(&translation_matrix, 0.0f, 0.0f, 0.0f);
			}
			matrix = scaling_matrix * rotation_matrix * translation_matrix;
			return matrix;
		}
		SPRIG_INLINE D3DXMATRIX matrix_transformation_2d(
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation
			)
		{
			D3DXMATRIX matrix;
			return matrix_transformation_2d(matrix, scaling, rotation, translation);
		}

		//
		// matrix_inverse_transformation_2d
		//
		SPRIG_INLINE D3DXMATRIX& matrix_inverse_transformation_2d(
			D3DXMATRIX& matrix,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation
			)
		{
			return matrix_inverse(
				matrix,
				matrix_transformation_2d(
					matrix,
					scaling,
					rotation,
					translation
					)
				);
		}
		SPRIG_INLINE D3DXMATRIX matrix_inverse_transformation_2d(
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation
			)
		{
			D3DXMATRIX matrix;
			return matrix_inverse_transformation_2d(matrix, scaling, rotation, translation);
		}

		//
		// set_sprite_transform
		//
		SPRIG_INLINE HRESULT set_sprite_transform(
			sprig::call_traits<sprite_type>::param_type sprite,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> scaling,
			boost::optional<sprig::call_traits<FLOAT>::param_type> rotation,
			boost::optional<sprig::call_traits<D3DXVECTOR2>::param_type> translation
			)
		{
			HRESULT result = D3D_OK;
			D3DXMATRIX matrix;
			matrix_transformation_2d(matrix, scaling, rotation, translation);
			if (FAILED(result = sprite->SetTransform(&matrix))) {
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("sprite"), sprite);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("scaling"), scaling);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rotation"), rotation);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("translation"), translation);
				}
				SPRIG_DG_ERROR("�X�v���C�g�֍��W�ϊ��s��ݒ�Ɏ��s���܂���", bad_process);
				return result;
			}
			return result;
		}

		//
		// draw_sprite
		//
		SPRIG_INLINE HRESULT draw_sprite(
			sprig::call_traits<sprite_type>::param_type sprite,
			sprig::call_traits<texture_type>::param_type texture,
			boost::optional<sprig::call_traits<RECT>::param_type> rect,
			boost::optional<sprig::call_traits<D3DXVECTOR3>::param_type> center,
			boost::optional<sprig::call_traits<D3DXVECTOR3>::param_type> position,
			boost::optional<sprig::call_traits<D3DCOLOR>::param_type> color
			)
		{
			using sprig::get_pointer;

			HRESULT result = D3D_OK;
			if (FAILED(result = sprite->Draw(
				get_pointer(texture),
				get_pointer(rect),	// �`��͈�
				get_pointer(center),	// ���S���W
				get_pointer(position),	// �`��ʒu
				color.get_value_or(0xffffffff)	// �A���t�@
				)))
			{
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("sprite"), sprite);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("texture"), texture);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("center"), center);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("position"), position);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("color"), color);
				}
				SPRIG_DG_ERROR("�X�v���C�g�̕`��Ɏ��s���܂���", bad_process);
				return result;
			}
			return result;
		}

		//
		// fill_surface
		//
		//	COMMENT: �T�[�t�F�C�X�̃s�N�Z���f�[�^���[���t�B������B
		//	COMMENT: �����_�����t�H�[�}�b�g�̃e�N�X�`���ɑ΂��Ă͂����炭�����n�ˑ��B
		//
		SPRIG_INLINE HRESULT fill_surface(
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			boost::optional<sprig::call_traits<RECT>::param_type> rect,	// �t�B�����������`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			using sprig::get_pointer;

			HRESULT result = D3D_OK;

			// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			RECT surface_rect;
			if (rect) {
				if (hint_desc) {
					surface_rect.left = std::min<LONG>(std::max<LONG>(rect->left, 0L), hint_desc->Width);
					surface_rect.top = std::min<LONG>(std::max<LONG>(rect->top, 0L), hint_desc->Height);
					surface_rect.right = std::min<LONG>(std::max<LONG>(rect->right, 0L), hint_desc->Width);
					surface_rect.bottom = std::min<LONG>(std::max<LONG>(rect->bottom, 0L), hint_desc->Height);
				} else {
					// �T�[�t�F�C�X���̎擾
					D3DSURFACE_DESC desc;
					if (FAILED(result = surface->GetDesc(&desc))) {
						{
							SPRIG_DG_SECTION(TEXT("arguments"));
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
						}
						SPRIG_DG_ERROR("�T�[�t�F�C�X���̎擾�Ɏ��s���܂���", bad_process);
						return result;
					}
					surface_rect.left = std::min<LONG>(std::max<LONG>(rect->left, 0L), desc.Width);
					surface_rect.top = std::min<LONG>(std::max<LONG>(rect->top, 0L), desc.Height);
					surface_rect.right = std::min<LONG>(std::max<LONG>(rect->right, 0L), desc.Width);
					surface_rect.bottom = std::min<LONG>(std::max<LONG>(rect->bottom, 0L), desc.Height);
				}
			} else {
				if (hint_desc) {
					surface_rect.left = 0L;
					surface_rect.top = 0L;
					surface_rect.right = hint_desc->Width;
					surface_rect.bottom = hint_desc->Height;
				} else {
					// �T�[�t�F�C�X���̎擾
					D3DSURFACE_DESC desc;
					if (FAILED(result = surface->GetDesc(&desc))) {
						{
							SPRIG_DG_SECTION(TEXT("arguments"));
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
						}
						SPRIG_DG_ERROR("�T�[�t�F�C�X���̎擾�Ɏ��s���܂���", bad_process);
						return result;
					}
					surface_rect.left = 0L;
					surface_rect.top = 0L;
					surface_rect.right = desc.Width;
					surface_rect.bottom = desc.Height;
				}
			}

			// ���b�N���ꂽ�̈�
			D3DLOCKED_RECT locked_rect;

			//	CHECK: ���b�N�����`��NULL�ȊO���w�肷��ƃG���[��Ԃ��B�����s���B
			// �T�[�t�F�C�X�̃��b�N
			if (FAILED(result = surface->LockRect(
				&locked_rect,	// ���b�N���ꂽ�̈�
				NULL,//&surface_rect,	// ���b�N�����`
				D3DLOCK_READONLY	// ���b�L���O�t���O
				)))
			{
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
				}
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃��b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			// �s�N�Z���f�[�^�̗L���̈�Ɏ��܂�悤�␳�����T�C�Y
			SIZE const bits_size = {
				surface_rect.right - surface_rect.left,
				surface_rect.bottom - surface_rect.top
			};

			// �s�N�Z���f�[�^�R�s�[���̃T�C�Y
			std::size_t const block_size = bits_size.cx * pixel_size;

			// �s�N�Z���f�[�^�R�s�[���̃s�b�`
			std::size_t const dst_pitch = locked_rect.Pitch;

			//	CHECK: �S���b�N���Ă��邽�ߕ␳���K�v�B
			D3DLOCKED_RECT locked_rect_ = locked_rect;
			locked_rect_.pBits = reinterpret_cast<unsigned char*>(locked_rect.pBits)
				+ surface_rect.top * locked_rect.Pitch * pixel_size
				+ surface_rect.left * pixel_size
				;
			// �T�[�t�F�C�X����]����փ������u���b�N�̃R�s�[
			unsigned char* dst = static_cast<unsigned char*>(locked_rect_/*locked_rect*/.pBits);
			for(std::size_t i = 0, last = bits_size.cy; i != last; ++i){
				std::memset(dst, 0, block_size);
				dst += dst_pitch;
			}

			// �T�[�t�F�C�X�̃A�����b�N
			if (FAILED(result = surface->UnlockRect())) {
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
				}
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃A�����b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			return result;
		}

		//
		// normalize_texture_rect
		//
		SPRIG_INLINE HRESULT normalize_texture_rect(
			RECT& texture_rect,	// �e�N�X�`���̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<texture_type>::param_type texture,	// �e�N�X�`��
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			HRESULT result = D3D_OK;

			if (hint_desc) {
				texture_rect.left = std::min<LONG>(std::max<LONG>(rect.left, 0L), hint_desc->Width);
				texture_rect.top = std::min<LONG>(std::max<LONG>(rect.top, 0L), hint_desc->Height);
				texture_rect.right = std::min<LONG>(std::max<LONG>(rect.right, 0L), hint_desc->Width);
				texture_rect.bottom = std::min<LONG>(std::max<LONG>(rect.bottom, 0L), hint_desc->Height);
			} else {
				// �T�[�t�F�C�X���̎擾
				D3DSURFACE_DESC desc;
				if (FAILED(result = texture->GetLevelDesc(0, &desc))) {
					{
						SPRIG_DG_SECTION(TEXT("arguments"));
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("texture"), texture);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
					}
					SPRIG_DG_ERROR("�T�[�t�F�C�X���̎擾�Ɏ��s���܂���", bad_process);
					return result;
				}
				texture_rect.left = std::min<LONG>(std::max<LONG>(rect.left, 0L), desc.Width);
				texture_rect.top = std::min<LONG>(std::max<LONG>(rect.top, 0L), desc.Height);
				texture_rect.right = std::min<LONG>(std::max<LONG>(rect.right, 0L), desc.Width);
				texture_rect.bottom = std::min<LONG>(std::max<LONG>(rect.bottom, 0L), desc.Height);
			}

			return result;
		}

		//
		// normalize_surface_rect
		//
		SPRIG_INLINE HRESULT normalize_surface_rect(
			RECT& surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			HRESULT result = D3D_OK;

			if (hint_desc) {
				surface_rect.left = std::min<LONG>(std::max<LONG>(rect.left, 0L), hint_desc->Width);
				surface_rect.top = std::min<LONG>(std::max<LONG>(rect.top, 0L), hint_desc->Height);
				surface_rect.right = std::min<LONG>(std::max<LONG>(rect.right, 0L), hint_desc->Width);
				surface_rect.bottom = std::min<LONG>(std::max<LONG>(rect.bottom, 0L), hint_desc->Height);
			} else {
				// �T�[�t�F�C�X���̎擾
				D3DSURFACE_DESC desc;
				if (FAILED(result = surface->GetDesc(&desc))) {
					{
						SPRIG_DG_SECTION(TEXT("arguments"));
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
					}
					SPRIG_DG_ERROR("�T�[�t�F�C�X���̎擾�Ɏ��s���܂���", bad_process);
					return result;
				}
				surface_rect.left = std::min<LONG>(std::max<LONG>(rect.left, 0L), desc.Width);
				surface_rect.top = std::min<LONG>(std::max<LONG>(rect.top, 0L), desc.Height);
				surface_rect.right = std::min<LONG>(std::max<LONG>(rect.right, 0L), desc.Width);
				surface_rect.bottom = std::min<LONG>(std::max<LONG>(rect.bottom, 0L), desc.Height);
			}

			return result;
		}

		//
		// normalize_surface_rect_from_memory
		//
		SPRIG_INLINE HRESULT normalize_surface_rect_from_memory(
			RECT& surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			HRESULT result = D3D_OK;

			if (hint_desc) {
				surface_rect.left = std::min<LONG>(std::max<LONG>(offset.x, 0L), hint_desc->Width);
				surface_rect.top = std::min<LONG>(std::max<LONG>(offset.y, 0L), hint_desc->Height);
				surface_rect.right = std::min<LONG>(std::max<LONG>(offset.x + rect.right - rect.left, 0L), hint_desc->Width);
				surface_rect.bottom = std::min<LONG>(std::max<LONG>(offset.y + rect.bottom - rect.top, 0L), hint_desc->Height);
			} else {
				// �T�[�t�F�C�X���̎擾
				D3DSURFACE_DESC desc;
				if (FAILED(result = surface->GetDesc(&desc))) {
					{
						SPRIG_DG_SECTION(TEXT("arguments"));
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("offset"), offset);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect);
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc);
					}
					SPRIG_DG_ERROR("�T�[�t�F�C�X���̎擾�Ɏ��s���܂���", bad_process);
					return result;
				}
				surface_rect.left = std::min<LONG>(std::max<LONG>(offset.x, 0L), desc.Width);
				surface_rect.top = std::min<LONG>(std::max<LONG>(offset.y, 0L), desc.Height);
				surface_rect.right = std::min<LONG>(std::max<LONG>(offset.x + rect.right - rect.left, 0L), desc.Width);
				surface_rect.bottom = std::min<LONG>(std::max<LONG>(offset.y + rect.bottom - rect.top, 0L), desc.Height);
			}

			return result;
		}

		//
		// transfer_bits_from_memory
		//
		SPRIG_INLINE void transfer_bits_from_memory(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,	// ���b�N���ꂽ�̈�
			sprig::call_traits<RECT>::param_type surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<RECT>::param_type rect	// �R�s�[���̋�`
			)
		{
			// �s�N�Z���f�[�^�̗L���̈�Ɏ��܂�悤�␳�����I�t�Z�b�g
			POINT const bits_offset = {
				std::min<LONG>(std::max<LONG>(rect.left, 0L), size.cx),
				std::min<LONG>(std::max<LONG>(rect.top, 0L), size.cy)
			};

			// �s�N�Z���f�[�^�̗L���̈�Ɏ��܂�悤�␳�����T�C�Y
			SIZE const bits_size = {
				std::min<LONG>(surface_rect.right - surface_rect.left, size.cx - bits_offset.x),
				std::min<LONG>(surface_rect.bottom - surface_rect.top, size.cy - bits_offset.y)
			};

			// �s�N�Z���f�[�^�R�s�[���̃I�t�Z�b�g�ƃT�C�Y
			std::size_t const offset_size = bits_offset.x * pixel_size;
			std::size_t const block_size = bits_size.cx * pixel_size;

			// �s�N�Z���f�[�^�R�s�[���̃s�b�`
			std::size_t const dst_pitch = locked_rect.Pitch;
			std::size_t const src_pitch = pitch;

			// �T�[�t�F�C�X�փ������u���b�N�̃R�s�[
			unsigned char* dst = static_cast<unsigned char*>(locked_rect.pBits);
			unsigned char* src = static_cast<unsigned char*>(bits) + bits_offset.y * pitch + offset_size;
			for(std::size_t i = 0, last = bits_size.cy; i != last; ++i){
				std::memcpy(dst, src, block_size);
				dst += dst_pitch;
				src += src_pitch;
			}
		}

		//
		// transfer_bits_from_render_target
		//
		SPRIG_INLINE void transfer_bits_from_render_target(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,	// ���b�N���ꂽ�̈�
			sprig::call_traits<RECT>::param_type surface_rect,	// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset	// �R�s�[��̃I�t�Z�b�g
			)
		{
			// �s�N�Z���f�[�^�̗L���̈�Ɏ��܂�悤�␳�����I�t�Z�b�g
			POINT const bits_offset = {
				std::min<LONG>(std::max<LONG>(offset.x, 0L), size.cx),
				std::min<LONG>(std::max<LONG>(offset.y, 0L), size.cy)
			};

			// �s�N�Z���f�[�^�̗L���̈�Ɏ��܂�悤�␳�����T�C�Y
			SIZE const bits_size = {
				std::min<LONG>(surface_rect.right - surface_rect.left, size.cx - bits_offset.x),
				std::min<LONG>(surface_rect.bottom - surface_rect.top, size.cy - bits_offset.y)
			};

			// �s�N�Z���f�[�^�R�s�[���̃I�t�Z�b�g�ƃT�C�Y
			std::size_t const offset_size = bits_offset.x * pixel_size;
			std::size_t const block_size = bits_size.cx * pixel_size;

			// �s�N�Z���f�[�^�R�s�[���̃s�b�`
			std::size_t const dst_pitch = pitch;
			std::size_t const src_pitch = locked_rect.Pitch;

			// �T�[�t�F�C�X���烁�����u���b�N�̃R�s�[
			unsigned char* dst = static_cast<unsigned char*>(bits) + bits_offset.y * pitch + offset_size;
			unsigned char* src = static_cast<unsigned char*>(locked_rect.pBits);
			for(std::size_t i = 0, last = bits_size.cy; i != last; ++i){
				std::memcpy(dst, src, block_size);
				dst += dst_pitch;
				src += src_pitch;
			}
		}

		//
		// SPRIG_DG_TRANSFER_FROM_MEMORY_OUTPUT_ARGUMENTS
		//
#define SPRIG_DG_TRANSFER_FROM_MEMORY_OUTPUT_ARGUMENTS() \
		{ \
			SPRIG_DG_SECTION(TEXT("arguments")); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("bits"), bits); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("size"), size); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pitch"), pitch); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("offset"), offset); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc); \
		}
		//
		// transfer_from_memory
		//
		SPRIG_INLINE HRESULT transfer_from_memory(
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			using sprig::get_pointer;

			HRESULT result = D3D_OK;

			// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			RECT surface_rect;

			// �T�[�t�F�C�X�̗L���̈��`�̌v�Z
			if (FAILED(result = normalize_surface_rect_from_memory(
				surface_rect,
				surface,
				offset,
				rect,
				hint_desc
				)))
			{
				SPRIG_DG_TRANSFER_FROM_MEMORY_OUTPUT_ARGUMENTS();
				return result;
			}

			// ���b�N���ꂽ�̈�
			D3DLOCKED_RECT locked_rect;

			//	CHECK: ���b�N�����`��NULL�ȊO���w�肷��ƃG���[��Ԃ��B�����s���B
			// �T�[�t�F�C�X�̃��b�N
			if (FAILED(result = surface->LockRect(
				&locked_rect,	// ���b�N���ꂽ�̈�
				NULL,//&surface_rect,	// ���b�N�����`
				D3DLOCK_DISCARD	// ���b�L���O�t���O
				)))
			{
				SPRIG_DG_TRANSFER_FROM_MEMORY_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃��b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			//	CHECK: �S���b�N���Ă��邽�ߕ␳���K�v�B
			D3DLOCKED_RECT locked_rect_ = locked_rect;
			locked_rect_.pBits = reinterpret_cast<unsigned char*>(locked_rect.pBits)
				+ surface_rect.top * locked_rect.Pitch * pixel_size
				+ surface_rect.left * pixel_size
				;
			// �T�[�t�F�C�X�փ������u���b�N�̃R�s�[
			transfer_bits_from_memory(
				locked_rect_,//locked_rect,
				surface_rect,
				bits,
				size,
				pitch,
				pixel_size,
				rect
				);

			// �T�[�t�F�C�X�̃A�����b�N
			if (FAILED(result = surface->UnlockRect())) {
				SPRIG_DG_TRANSFER_FROM_MEMORY_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃A�����b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			return result;
		}

		//
		// SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS
		//
#define SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS() \
		{ \
			SPRIG_DG_SECTION(TEXT("arguments")); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("device"), device); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("render_target_surface"), render_target_surface); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("bits"), bits); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("size"), size); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pitch"), pitch); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("pixel_size"), pixel_size); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("offset"), offset); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc); \
		}
		//
		// transfer_from_render_target
		//
		SPRIG_INLINE HRESULT transfer_from_render_target(
			sprig::call_traits<device_type>::param_type device,	// �f�o�C�X
			sprig::call_traits<surface_type>::param_type render_target_surface,	// �����_�[�^�[�Q�b�g
			sprig::call_traits<surface_type>::param_type surface,	// �T�[�t�F�C�X
			sprig::call_traits<void*>::param_type bits,	// �s�N�Z���f�[�^
			sprig::call_traits<SIZE>::param_type size,	// �s�N�Z���f�[�^�̃T�C�Y
			sprig::call_traits<std::size_t>::param_type pitch,	// �s�N�Z���f�[�^�̃s�b�`
			sprig::call_traits<std::size_t>::param_type pixel_size,	// �s�N�Z���f�[�^�̃s�N�Z���o�C�g��
			sprig::call_traits<POINT>::param_type offset,	// �R�s�[��̃I�t�Z�b�g
			sprig::call_traits<RECT>::param_type rect,	// �R�s�[���̋�`
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc	// �q���g�ƂȂ�T�[�t�F�C�X���
			)
		{
			using sprig::get_pointer;

			HRESULT result = D3D_OK;

			// �����_�[�^�[�Q�b�g���烏�[�N�T�[�t�F�C�X�փR�s�[
			if (FAILED(result = device->GetRenderTargetData(get_pointer(render_target_surface), get_pointer(surface)))) {
				SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�����_�[�^�[�Q�b�g���烏�[�N�T�[�t�F�C�X�փR�s�[�Ɏ��s���܂���", bad_process);
				return result;
			}

			// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
			RECT surface_rect;
			if (FAILED(result = normalize_surface_rect(
				surface_rect,
				surface,
				rect,
				hint_desc
				)))
			{
				SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̗L���̈��`�̌v�Z�Ɏ��s���܂���", bad_process);
				return result;
			}

			// ���b�N���ꂽ�̈�
			D3DLOCKED_RECT locked_rect;

			// �T�[�t�F�C�X�̃��b�N
			if (FAILED(result = surface->LockRect(
				&locked_rect,	// ���b�N���ꂽ�̈�
				&surface_rect,	// ���b�N�����`
				D3DLOCK_READONLY	// ���b�L���O�t���O
				)))
			{
				SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃��b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			// �T�[�t�F�C�X���烁�����u���b�N�̃R�s�[
			transfer_bits_from_render_target(
				locked_rect,
				surface_rect,
				bits,
				size,
				pitch,
				pixel_size,
				offset
				);

			// �T�[�t�F�C�X�̃A�����b�N
			if (FAILED(result = surface->UnlockRect())) {
				SPRIG_DG_TRANSFER_FROM_RENDER_TARGET_OUTPUT_ARGUMENTS();
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃A�����b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			return result;
		}

		//
		// SPRIG_DG_LOCK_RECT_TEXTURE_ARGUMENTS
		//
#define SPRIG_DG_LOCK_RECT_TEXTURE_ARGUMENTS() \
		{ \
			SPRIG_DG_SECTION(TEXT("arguments")); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("locked_rect"), locked_rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("texture"), texture); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("level"), level); \
		}
		//
		// lock_rect
		//
		SPRIG_INLINE HRESULT lock_rect(
			D3DLOCKED_RECT& locked_rect,
			sprig::call_traits<texture_type>::param_type texture,
			sprig::call_traits<DWORD>::param_type flags,
			boost::optional<sprig::call_traits<RECT>::param_type> rect,
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc,
			sprig::call_traits<UINT>::param_type level
			)
		{
			HRESULT result = D3D_OK;

			if (rect) {
				// �e�N�X�`���̗L���̈�Ɏ��܂�悤�␳������`
				RECT texture_rect;
				if (FAILED(result = normalize_texture_rect(
					texture_rect,
					texture,
					*rect,
					hint_desc
					)))
				{
					SPRIG_DG_LOCK_RECT_TEXTURE_ARGUMENTS();
					SPRIG_DG_ERROR("�e�N�X�`���̗L���̈��`�̌v�Z�Ɏ��s���܂���", bad_process);
					return result;
				}

				// �e�N�X�`���̃��b�N
				if (FAILED(result = texture->LockRect(
					level,	// ���x��
					&locked_rect,	// ���b�N���ꂽ�̈�
					&texture_rect,	// ���b�N�����`
					flags	// ���b�L���O�t���O
					)))
				{
					SPRIG_DG_LOCK_RECT_TEXTURE_ARGUMENTS();
					SPRIG_DG_ERROR("�e�N�X�`���̃��b�N�Ɏ��s���܂���", bad_process);
					return result;
				}
			} else {
				// �e�N�X�`���̃��b�N
				if (FAILED(result = texture->LockRect(
					level,	// ���x��
					&locked_rect,	// ���b�N���ꂽ�̈�
					0,	// ���b�N�����`
					flags	// ���b�L���O�t���O
					)))
				{
					SPRIG_DG_LOCK_RECT_TEXTURE_ARGUMENTS();
					SPRIG_DG_ERROR("�e�N�X�`���̃��b�N�Ɏ��s���܂���", bad_process);
					return result;
				}
			}

			return result;
		}
		//
		// SPRIG_DG_LOCK_RECT_SURFACE_ARGUMENTS
		//
#define SPRIG_DG_LOCK_RECT_SURFACE_ARGUMENTS() \
		{ \
			SPRIG_DG_SECTION(TEXT("arguments")); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("locked_rect"), locked_rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("rect"), rect); \
			SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("hint_desc"), hint_desc); \
		}
		//
		// lock_rect
		//
		SPRIG_INLINE HRESULT lock_rect(
			D3DLOCKED_RECT& locked_rect,
			sprig::call_traits<surface_type>::param_type surface,
			sprig::call_traits<DWORD>::param_type flags,
			boost::optional<sprig::call_traits<RECT>::param_type> rect,
			boost::optional<sprig::call_traits<D3DSURFACE_DESC>::param_type> hint_desc
			)
		{
			HRESULT result = D3D_OK;

			if (rect) {
				// �T�[�t�F�C�X�̗L���̈�Ɏ��܂�悤�␳������`
				RECT surface_rect;
				if (FAILED(result = normalize_surface_rect(
					surface_rect,
					surface,
					*rect,
					hint_desc
					)))
				{
					SPRIG_DG_LOCK_RECT_SURFACE_ARGUMENTS();
					SPRIG_DG_ERROR("�T�[�t�F�C�X�̗L���̈��`�̌v�Z�Ɏ��s���܂���", bad_process);
					return result;
				}

				// �T�[�t�F�C�X�̃��b�N
				if (FAILED(result = surface->LockRect(
					&locked_rect,	// ���b�N���ꂽ�̈�
					&surface_rect,	// ���b�N�����`
					flags	// ���b�L���O�t���O
					)))
				{
					SPRIG_DG_LOCK_RECT_SURFACE_ARGUMENTS();
					SPRIG_DG_ERROR("�e�N�X�`���̃��b�N�Ɏ��s���܂���", bad_process);
					return result;
				}
			} else {
				// �T�[�t�F�C�X�̃��b�N
				if (FAILED(result = surface->LockRect(
					&locked_rect,	// ���b�N���ꂽ�̈�
					0,	// ���b�N�����`
					flags	// ���b�L���O�t���O
					)))
				{
					SPRIG_DG_LOCK_RECT_SURFACE_ARGUMENTS();
					SPRIG_DG_ERROR("�T�[�t�F�C�X�̃��b�N�Ɏ��s���܂���", bad_process);
					return result;
				}
			}

			return result;
		}

		//
		// unlock_rect
		//
		SPRIG_INLINE HRESULT unlock_rect(
			sprig::call_traits<texture_type>::param_type texture,
			sprig::call_traits<UINT>::param_type level
			)
		{
			HRESULT result = D3D_OK;

			// �e�N�X�`���̃A�����b�N
			if (FAILED(result = texture->UnlockRect(level))) {
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("texture"), texture);
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("level"), level);
				}
				SPRIG_DG_ERROR("�e�N�X�`���̃A�����b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			return result;
		}
		SPRIG_INLINE HRESULT unlock_rect(
			sprig::call_traits<surface_type>::param_type surface
			)
		{
			HRESULT result = D3D_OK;

			// �T�[�t�F�C�X�̃A�����b�N
			if (FAILED(result = surface->UnlockRect())) {
				{
					SPRIG_DG_SECTION(TEXT("arguments"));
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("surface"), surface);
				}
				SPRIG_DG_ERROR("�T�[�t�F�C�X�̃A�����b�N�Ɏ��s���܂���", bad_process);
				return result;
			}

			return result;
		}

		//
		// get_pixel
		//
		SPRIG_INLINE D3DCOLOR get_pixel(
			sprig::call_traits<D3DLOCKED_RECT>::param_type locked_rect,
			sprig::call_traits<POINT>::param_type point
			)
		{
			return reinterpret_cast<D3DCOLOR const*>(
				reinterpret_cast<unsigned char const*>(locked_rect.pBits) + locked_rect.Pitch * point.y
				)[point.x];
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_FUNCTIONS_HPP
