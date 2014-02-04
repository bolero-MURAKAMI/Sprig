/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_FOUNDATION_HPP
#define SPRIG_DG_FOUNDATION_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/current_function.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <sprig/external/windows.hpp>
#include <sprig/external/d3d9.hpp>
#include <sprig/external/d3dx9.hpp>
#include <sprig/external/dxerr.hpp>
#include <sprig/singleton.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/string_argument.hpp>
#include <sprig/indentation.hpp>
#include <sprig/section.hpp>
#include <sprig/indent_logger.hpp>
#include <sprig/exception.hpp>
#include <sprig/com_ptr/unknown.hpp>

namespace sprig {
	namespace dg {
		//
		// SPRIG_DG_DEVICE_MODE
		//
		enum SPRIG_DG_DEVICE_MODE {
			SPRIG_DG_DEVICE_MODE_WINDOW,
			SPRIG_DG_DEVICE_MODE_BUFFER,
		};

		//
		// exceptions
		//
		SPRIG_EXCEPTION_DECL(exception);
		SPRIG_EXCEPTION_INHERIT_DECL(bad_initialize, exception);
		SPRIG_EXCEPTION_INHERIT_DECL(bad_process, exception);
		SPRIG_EXCEPTION_INHERIT_DECL(bad_operation, exception);

		//
		// typedefs
		//
		// interface-types
		//
		typedef IDirect3D9 object_interface_type;
		typedef IDirect3DDevice9 device_interface_type;
		typedef IDirect3DTexture9 texture_interface_type;
		typedef IDirect3DSurface9 surface_interface_type;
		typedef ID3DXSprite sprite_interface_type;
		//
		// types
		//
		typedef sprig::com_ptr<object_interface_type> object_type;
		typedef sprig::com_ptr<device_interface_type> device_type;
		typedef sprig::com_ptr<texture_interface_type> texture_type;
		typedef sprig::com_ptr<surface_interface_type> surface_type;
		typedef sprig::com_ptr<sprite_interface_type> sprite_type;
		//
		// weak-types
		//
		typedef sprig::weak_com_ptr<object_interface_type> object_weak_type;
		typedef sprig::weak_com_ptr<device_interface_type> device_weak_type;
		typedef sprig::weak_com_ptr<texture_interface_type> texture_weak_type;
		typedef sprig::weak_com_ptr<surface_interface_type> surface_weak_type;
		typedef sprig::weak_com_ptr<sprite_interface_type> sprite_weak_type;
		//
		// string-types
		//
		typedef TCHAR char_type;
		typedef std::basic_string<char_type> string_type;
		typedef sprig::basic_string_argument<string_type> string_argument_type;

		//
		// outputter
		//
		struct outputter {
			void operator()(string_argument_type const& arg) const {
				DXTRACE_MSG(arg.get().c_str());
			}
		};
		//
		// logger_tag, indent_logger_type
		//
		struct logger_tag {};
		typedef sprig::basic_indent_logger<string_type, logger_tag> indent_logger_type;
		//
		// indent_logger_proxy
		//
		class indent_logger_proxy
			: public sprig::singleton<indent_logger_proxy>
		{
			SPRIG_FRIEND_SINGLETON(indent_logger_proxy);
		private:
			indent_logger_type indent_logger_;
			boost::scoped_ptr<indent_logger_type::indent> prefix_;
		private:
			indent_logger_proxy() {
				indent_logger_.push(outputter());
				prefix_.reset(
					new indent_logger_type::indent(
						sprig::basic_section_comment<string_type>(TEXT("sprig:dg"))
						)
					);
			}
		public:
			indent_logger_type& get() {
				return indent_logger_;
			}
		};

		//
		// indent_logger
		//
		SPRIG_INLINE indent_logger_type& indent_logger() {
			return indent_logger_proxy::get_mutable_instance().get();
		}
		//
		// output
		//
		SPRIG_INLINE void output(string_argument_type const& message) {
			sprig::logger_output_line(message, indent_logger());
		}
		//
		// output_value
		//
		SPRIG_INLINE void output_value(string_argument_type const& name, string_argument_type const& contents) {
			sprig::logger_section_line(name, contents, indent_logger());
		}
		//
		// output_comment
		//
		SPRIG_INLINE void output_comment(string_argument_type const& comment) {
			sprig::logger_section_comment(comment, indent_logger());
		}

		//
		// section
		//
		class section
			: boost::noncopyable
		{
		private:
			sprig::logger_section<indent_logger_type> section_;
		public:
			explicit section(string_argument_type const& name)
				: section_(name, indent_logger())
			{}
			explicit section(
				string_argument_type const& name,
				string_argument_type const& tab
				)
				: section_(name, indent_logger(), tab)
			{}
		};
		//
		// SPRIG_DG_SECTION
		//
#define SPRIG_DG_SECTION(name) \
	sprig::dg::section section_(name)
		//
		// SPRIG_DG_OUTPUT
		//
#define SPRIG_DG_OUTPUT(message) \
	DXTRACE_MSG(sprig::basic_section_comment<sprig::dg::string_type>(TEXT("sprig:dg:output")).c_str()); \
	sprig::dg::output(message)
		//
		// SPRIG_DG_OUTPUT_VALUE
		//
#define SPRIG_DG_OUTPUT_VALUE(name, contents) \
	DXTRACE_MSG(sprig::basic_section_comment<sprig::dg::string_type>(TEXT("sprig:dg:output_value")).c_str()); \
	sprig::dg::output_value(name, contents)
		//
		// SPRIG_DG_OUTPUT_COMMENT
		//
#define SPRIG_DG_OUTPUT_COMMENT(comment) \
	DXTRACE_MSG(sprig::basic_section_comment<sprig::dg::string_type>(TEXT("sprig:dg:output_comment")).c_str()); \
	sprig::dg::output_comment(comment)

		//
		// SPRIG_DG_ERROR_MESSAGE
		//
#	define SPRIG_DG_ERROR_MESSAGE(message) \
		DXTRACE_MSG(sprig::basic_section_comment<sprig::dg::string_type>(TEXT("sprig:dg:error")).c_str()); \
		{ \
			SPRIG_DG_SECTION(TEXT("sprig:dg:error")); \
			SPRIG_DG_OUTPUT_VALUE(TEXT("message"), (message)); \
			SPRIG_DG_OUTPUT_VALUE(TEXT("file"), TEXT(__FILE__)); \
			SPRIG_DG_OUTPUT_VALUE(TEXT("line"), __LINE__); \
			SPRIG_DG_OUTPUT_VALUE(TEXT("function"), TEXT(BOOST_CURRENT_FUNCTION)); \
		}
		//
		// SPRIG_DG_ERROR
		//
#ifndef SPRIG_DG_CONFIG_DISABLE_THROW_EXCEPTION
#	define SPRIG_DG_ERROR(message, type) \
		SPRIG_DG_ERROR_MESSAGE(message); \
		throw SPRIG_ADD_EXCEPTION_INFO(type(sprig::section_line("sprig:dg:error", (message)).c_str()));
#else	// #ifndef SPRIG_DG_CONFIG_DISABLE_THROW_EXCEPTION
#	define SPRIG_DG_ERROR(message, type) \
		SPRIG_DG_ERROR_MESSAGE(message);
#endif	// #ifndef SPRIG_DG_CONFIG_DISABLE_THROW_EXCEPTION

		//
		// local_logger_tag, local_logger_type
		//
		struct local_logger_tag {};
		typedef sprig::local_logger<string_type, local_logger_tag> local_logger_type;

		//
		// output_device_caps
		//
		HRESULT output_device_caps(sprig::call_traits<device_type>::param_type device) {
			HRESULT result = D3D_OK;

			D3DCAPS9 caps;
			if (FAILED(result = device->GetDeviceCaps(&caps))) {
				SPRIG_DG_ERROR("レンダリングデバイスの能力取得に失敗しました", bad_process);
				return result;
			}

			switch (caps.DeviceType) {
			case D3DDEVTYPE_HAL:
				SPRIG_DG_OUTPUT_VALUE(TEXT("DeviceType"), TEXT("D3DDEVTYPE_HAL"));
				break;
			case D3DDEVTYPE_NULLREF:
				SPRIG_DG_OUTPUT_VALUE(TEXT("DeviceType"), TEXT("D3DDEVTYPE_NULLREF"));
				break;
			case D3DDEVTYPE_REF:
				SPRIG_DG_OUTPUT_VALUE(TEXT("DeviceType"), TEXT("D3DDEVTYPE_REF"));
				break;
			case D3DDEVTYPE_SW:
				SPRIG_DG_OUTPUT_VALUE(TEXT("DeviceType"), TEXT("D3DDEVTYPE_SW"));
				break;
			}
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスの種類を表します。"));
			SPRIG_DG_OUTPUT_COMMENT(TEXT("D3DDEVTYPE_HAL でない場合、ハードウェアによるラスタ化が行われずボトルネックになる可能性があります。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("D3DCAPS3_COPY_TO_SYSTEMMEM"), (caps.Caps3 & D3DCAPS3_COPY_TO_SYSTEMMEM) != 0);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスがローカルビデオメモリからシステムメモリへのメモリコピーを高速化できるかを表します。"));
			SPRIG_DG_OUTPUT_COMMENT(TEXT("偽の場合、高速化できずボトルネックになる可能性があります。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("D3DPTEXTURECAPS_ALPHA"), (caps.TextureCaps & D3DPTEXTURECAPS_ALPHA) != 0);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスがテクスチャピクセルでのアルファをサポートするかを表します。"));
			SPRIG_DG_OUTPUT_COMMENT(TEXT("偽の場合、アルファ処理が正常に行われない可能性があります。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("D3DPMISCCAPS_SEPARATEALPHABLEND"), (caps.PrimitiveMiscCaps & D3DPMISCCAPS_SEPARATEALPHABLEND) != 0);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスがアルファチャンネルに対する個別のブレンド設定をサポートするかを表します。"));
			SPRIG_DG_OUTPUT_COMMENT(TEXT("偽の場合、描画結果のアルファチャンネルが正常にならない可能性があります。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("D3DPMISCCAPS_BLENDOP"), (caps.PrimitiveMiscCaps & D3DPMISCCAPS_BLENDOP) != 0);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスが D3DBLENDOP_ADD 以外のアルファブレンディング処理をサポートするかを表します。"));
			SPRIG_DG_OUTPUT_COMMENT(TEXT("偽の場合、一部の描画処理が正常に行われない可能性があります。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("MaxTextureWidth"), caps.MaxTextureWidth);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスが作成可能なテクスチャの最大幅です。"));

			SPRIG_DG_OUTPUT_VALUE(TEXT("MaxTextureHeight"), caps.MaxTextureHeight);
			SPRIG_DG_OUTPUT_COMMENT(TEXT("この値は、デバイスが作成可能なテクスチャの最大高さです。"));

			SPRIG_DG_OUTPUT_COMMENT(TEXT("レンダリングデバイスの能力を出力します。"));
			{
				// DeviceType
				SPRIG_DG_SECTION(TEXT("DeviceType"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.DeviceType);
				switch (caps.DeviceType) {
				case D3DDEVTYPE_HAL:
					SPRIG_DG_OUTPUT_VALUE(TEXT("enum"), TEXT("D3DDEVTYPE_HAL"));
					break;
				case D3DDEVTYPE_NULLREF:
					SPRIG_DG_OUTPUT_VALUE(TEXT("enum"), TEXT("D3DDEVTYPE_NULLREF"));
					break;
				case D3DDEVTYPE_REF:
					SPRIG_DG_OUTPUT_VALUE(TEXT("enum"), TEXT("D3DDEVTYPE_REF"));
					break;
				case D3DDEVTYPE_SW:
					SPRIG_DG_OUTPUT_VALUE(TEXT("enum"), TEXT("D3DDEVTYPE_SW"));
					break;
				}
			}
			{
				// AdapterOrdinal
				SPRIG_DG_SECTION(TEXT("AdapterOrdinal"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.AdapterOrdinal);
			}
			{
				// Caps
				SPRIG_DG_SECTION(TEXT("Caps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.Caps);
				SPRIG_DG_OUTPUT_VALUE(TEXT("D3DCAPS_READ_SCANLINE"), caps.Caps & D3DCAPS_READ_SCANLINE);
			}
			{
				// Caps2
				SPRIG_DG_SECTION(TEXT("Caps2"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.Caps2);
			}
			{
				// Caps3
				SPRIG_DG_SECTION(TEXT("Caps3"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.Caps3);
			}
			{
				// PresentationIntervals
				SPRIG_DG_SECTION(TEXT("PresentationIntervals"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.PresentationIntervals);
			}
			{
				// CursorCaps
				SPRIG_DG_SECTION(TEXT("CursorCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.CursorCaps);
			}
			{
				// DevCaps
				SPRIG_DG_SECTION(TEXT("DevCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.DevCaps);
			}
			{
				// PrimitiveMiscCaps
				SPRIG_DG_SECTION(TEXT("PrimitiveMiscCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.PrimitiveMiscCaps);
			}
			{
				// RasterCaps
				SPRIG_DG_SECTION(TEXT("RasterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.RasterCaps);
			}
			{
				// ZCmpCaps
				SPRIG_DG_SECTION(TEXT("ZCmpCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.ZCmpCaps);
			}
			{
				// SrcBlendCaps
				SPRIG_DG_SECTION(TEXT("SrcBlendCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.SrcBlendCaps);
			}
			{
				// ZCmpCaps
				SPRIG_DG_SECTION(TEXT("ZCmpCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.ZCmpCaps);
			}
			{
				// DestBlendCaps
				SPRIG_DG_SECTION(TEXT("DestBlendCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.DestBlendCaps);
			}
			{
				// AlphaCmpCaps
				SPRIG_DG_SECTION(TEXT("AlphaCmpCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.AlphaCmpCaps);
			}
			{
				// ShadeCaps
				SPRIG_DG_SECTION(TEXT("ShadeCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.ShadeCaps);
			}
			{
				// ZCmpCaps
				SPRIG_DG_SECTION(TEXT("TextureCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.TextureCaps);
			}
			{
				// TextureFilterCaps
				SPRIG_DG_SECTION(TEXT("TextureFilterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.TextureFilterCaps);
			}
			{
				// CubeTextureFilterCaps
				SPRIG_DG_SECTION(TEXT("CubeTextureFilterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.CubeTextureFilterCaps);
			}
			{
				// VolumeTextureFilterCaps
				SPRIG_DG_SECTION(TEXT("VolumeTextureFilterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.VolumeTextureFilterCaps);
			}
			{
				// TextureAddressCaps
				SPRIG_DG_SECTION(TEXT("TextureAddressCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.TextureAddressCaps);
			}
			{
				// VolumeTextureAddressCaps
				SPRIG_DG_SECTION(TEXT("VolumeTextureAddressCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.TextureFilterCaps);
			}
			{
				// LineCaps
				SPRIG_DG_SECTION(TEXT("LineCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.LineCaps);
			}
			{
				// MaxTextureWidth
				SPRIG_DG_SECTION(TEXT("MaxTextureWidth"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxTextureWidth);
			}
			{
				// MaxTextureHeight
				SPRIG_DG_SECTION(TEXT("MaxTextureHeight"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxTextureHeight);
			}
			{
				// MaxVolumeExtent
				SPRIG_DG_SECTION(TEXT("MaxVolumeExtent"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVolumeExtent);
			}
			{
				// MaxTextureRepeat
				SPRIG_DG_SECTION(TEXT("MaxTextureRepeat"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxTextureRepeat);
			}
			{
				// MaxTextureAspectRatio
				SPRIG_DG_SECTION(TEXT("MaxTextureAspectRatio"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxTextureAspectRatio);
			}
			{
				// MaxAnisotropy
				SPRIG_DG_SECTION(TEXT("MaxAnisotropy"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxAnisotropy);
			}
			{
				// MaxVertexW
				SPRIG_DG_SECTION(TEXT("MaxVertexW"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexW);
			}
			{
				// GuardBandLeft
				SPRIG_DG_SECTION(TEXT("GuardBandLeft"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.GuardBandLeft);
			}
			{
				// GuardBandTop
				SPRIG_DG_SECTION(TEXT("GuardBandTop"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.GuardBandTop);
			}
			{
				// GuardBandRight
				SPRIG_DG_SECTION(TEXT("GuardBandRight"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.GuardBandRight);
			}
			{
				// GuardBandBottom
				SPRIG_DG_SECTION(TEXT("GuardBandBottom"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.GuardBandBottom);
			}
			{
				// ExtentsAdjust
				SPRIG_DG_SECTION(TEXT("ExtentsAdjust"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.ExtentsAdjust);
			}
			{
				// StencilCaps
				SPRIG_DG_SECTION(TEXT("StencilCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.StencilCaps);
			}
			{
				// FVFCaps
				SPRIG_DG_SECTION(TEXT("FVFCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.FVFCaps);
			}
			{
				// TextureOpCaps
				SPRIG_DG_SECTION(TEXT("TextureOpCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.TextureOpCaps);
			}
			{
				// MaxTextureBlendStages
				SPRIG_DG_SECTION(TEXT("MaxTextureBlendStages"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxTextureBlendStages);
			}
			{
				// MaxSimultaneousTextures
				SPRIG_DG_SECTION(TEXT("MaxSimultaneousTextures"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxSimultaneousTextures);
			}
			{
				// VertexProcessingCaps
				SPRIG_DG_SECTION(TEXT("VertexProcessingCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.VertexProcessingCaps);
			}
			{
				// MaxActiveLights
				SPRIG_DG_SECTION(TEXT("MaxActiveLights"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxActiveLights);
			}
			{
				// MaxUserClipPlanes
				SPRIG_DG_SECTION(TEXT("MaxUserClipPlanes"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxUserClipPlanes);
			}
			{
				// MaxVertexBlendMatrices
				SPRIG_DG_SECTION(TEXT("MaxVertexBlendMatrices"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexBlendMatrices);
			}
			{
				// MaxVertexBlendMatrixIndex
				SPRIG_DG_SECTION(TEXT("MaxVertexBlendMatrixIndex"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexBlendMatrixIndex);
			}
			{
				// MaxPointSize
				SPRIG_DG_SECTION(TEXT("MaxPointSize"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxPointSize);
			}
			{
				// MaxPrimitiveCount
				SPRIG_DG_SECTION(TEXT("MaxPrimitiveCount"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxPrimitiveCount);
			}
			{
				// MaxVertexIndex
				SPRIG_DG_SECTION(TEXT("MaxVertexIndex"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexIndex);
			}
			{
				// MaxStreams
				SPRIG_DG_SECTION(TEXT("MaxStreams"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxStreams);
			}
			{
				// MaxStreamStride
				SPRIG_DG_SECTION(TEXT("MaxStreamStride"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxStreamStride);
			}
			{
				// VertexShaderVersion
				SPRIG_DG_SECTION(TEXT("VertexShaderVersion"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.VertexShaderVersion);
			}
			{
				// MaxVertexShaderConst
				SPRIG_DG_SECTION(TEXT("MaxVertexShaderConst"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexShaderConst);
			}
			{
				// PixelShaderVersion
				SPRIG_DG_SECTION(TEXT("PixelShaderVersion"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.PixelShaderVersion);
			}
			{
				// PixelShader1xMaxValue
				SPRIG_DG_SECTION(TEXT("PixelShader1xMaxValue"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.PixelShader1xMaxValue);
			}
			{
				// DevCaps2
				SPRIG_DG_SECTION(TEXT("DevCaps2"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.DevCaps2);
			}
			{
				// MasterAdapterOrdinal
				SPRIG_DG_SECTION(TEXT("MasterAdapterOrdinal"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MasterAdapterOrdinal);
			}
			{
				// AdapterOrdinalInGroup
				SPRIG_DG_SECTION(TEXT("AdapterOrdinalInGroup"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.AdapterOrdinalInGroup);
			}
			{
				// NumberOfAdaptersInGroup
				SPRIG_DG_SECTION(TEXT("NumberOfAdaptersInGroup"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.NumberOfAdaptersInGroup);
			}
			{
				// DeclTypes
				SPRIG_DG_SECTION(TEXT("DeclTypes"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.DeclTypes);
			}
			{
				// NumSimultaneousRTs
				SPRIG_DG_SECTION(TEXT("NumSimultaneousRTs"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.NumSimultaneousRTs);
			}
			{
				// StretchRectFilterCaps
				SPRIG_DG_SECTION(TEXT("StretchRectFilterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.StretchRectFilterCaps);
			}
			//{
			//	// VS20Caps
			//	SPRIG_DG_SECTION(TEXT("VS20Caps"));
			//	SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.VS20Caps);
			//}
			//{
			//	// PS20Caps
			//	SPRIG_DG_SECTION(TEXT("PS20Caps"));
			//	SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.PS20Caps);
			//}
			{
				// VertexTextureFilterCaps
				SPRIG_DG_SECTION(TEXT("VertexTextureFilterCaps"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.VertexTextureFilterCaps);
			}
			{
				// MaxVShaderInstructionsExecuted
				SPRIG_DG_SECTION(TEXT("MaxVShaderInstructionsExecuted"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVShaderInstructionsExecuted);
			}
			{
				// MaxPShaderInstructionsExecuted
				SPRIG_DG_SECTION(TEXT("MaxPShaderInstructionsExecuted"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxPShaderInstructionsExecuted);
			}
			{
				// MaxVertexShader30InstructionSlots
				SPRIG_DG_SECTION(TEXT("MaxVertexShader30InstructionSlots"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxVertexShader30InstructionSlots);
			}
			{
				// MaxPixelShader30InstructionSlots
				SPRIG_DG_SECTION(TEXT("MaxPixelShader30InstructionSlots"));
				SPRIG_DG_OUTPUT_VALUE(TEXT("value"), caps.MaxPixelShader30InstructionSlots);
			}

			return result;
		}

		//
		// output_device_caps_once_flag
		//
		class output_device_caps_once_flag
			: public sprig::singleton<output_device_caps_once_flag>
		{
			SPRIG_FRIEND_SINGLETON(output_device_caps_once_flag);
		private:
			bool called_;
		private:
			output_device_caps_once_flag()
				: called_(false)
			{}
		public:
			bool get() {
				if (!called_) {
					called_ = true;
					return true;
				}
				return false;
			}
		};

		//
		// output_device_caps_once
		//
		SPRIG_INLINE HRESULT output_device_caps_once(sprig::call_traits<device_type>::param_type device) {
			HRESULT result = D3D_OK;
			if (output_device_caps_once_flag::get_mutable_instance().get()) {
				result = output_device_caps(device);
			}
			return result;
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_FOUNDATION_HPP
