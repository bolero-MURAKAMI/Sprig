/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_DG_DEVICE_MANAGER_HPP
#define SPRIG_DG_DEVICE_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <sprig/call_traits.hpp>
#include <sprig/get_pointer.hpp>
#include <sprig/accept.hpp>
#include <sprig/dg/foundation.hpp>
#include <sprig/dg/value_info.hpp>

namespace sprig {
	namespace dg {
		//
		// device_manager_init_params
		//
		class device_manager_init_params {
		public:
			typedef SPRIG_DG_DEVICE_MODE mode_type;
			typedef std::size_t size_type;
			typedef std::basic_string<TCHAR> string_type;
		public:
			mode_type mode;
			size_type width;
			size_type height;
			string_type class_name;
			string_type window_name;
		public:
			device_manager_init_params(
				mode_type mode = SPRIG_DG_DEVICE_MODE_WINDOW,
				size_type width = 0,
				size_type height = 0,
				string_type const& class_name = string_type(),
				string_type const& window_name = string_type()
				)
				: mode(mode)
				, width(width)
				, height(height)
				, class_name(class_name)
				, window_name(window_name)
			{}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("mode", mode)
					& boost::serialization::make_nvp("width", width)
					& boost::serialization::make_nvp("height", height)
					& boost::serialization::make_nvp("class_name", class_name)
					& boost::serialization::make_nvp("window_name", window_name)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(device_manager_init_params);
		template<typename Logger>
		void value_info(device_manager_init_params const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			logger.section_line(TEXT("mode"), value.mode);
			logger.section_line(TEXT("width"), value.width);
			logger.section_line(TEXT("height"), value.height);
			logger.section_line(TEXT("class_name"), value.class_name);
			logger.section_line(TEXT("window_name"), value.window_name);
		}

		//
		// device_manager
		//
		class device_manager {
		public:
			typedef WNDCLASS window_class_type;
			typedef HWND window_handle_type;
			typedef D3DPRESENT_PARAMETERS present_parameters_type;
		private:
			static LRESULT CALLBACK window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param) {
				switch (message) {
				case WM_DESTROY:
					::PostQuitMessage(0);
					break;
				}
				return ::DefWindowProc(window_handle, message, w_param, l_param);
			}
			static LRESULT CALLBACK buffer_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param) {
				return ::DefWindowProc(window_handle, message, w_param, l_param);
			}
		private:
			window_class_type window_class_;
			window_handle_type window_handle_;
			present_parameters_type present_parameters_;
			object_type object_;
			device_type device_;
			surface_type back_buffer_surface_;
			device_manager_init_params init_params_;
		public:
			template<typename Logger>
			void members_value_info(Logger& logger) const {
				Logger::section_type section_(TEXT("members"), *logger);
				value_info_section_line(TEXT("window_class_"), window_class_, logger);
				value_info_section_line(TEXT("window_handle_"), window_handle_, logger);
				value_info_section_line(TEXT("present_parameters_"), present_parameters_, logger);
				value_info_section_line(TEXT("object_"), object_, logger);
				value_info_section_line(TEXT("device_"), device_, logger);
				value_info_section_line(TEXT("back_buffer_surface_"), back_buffer_surface_, logger);
				value_info_section_line(TEXT("init_params_"), init_params_, logger);
			}
		public:
			device_manager()
				: window_handle_(NULL)
			{
				// ウィンドウクラスの設定
				window_class_.style = CS_BYTEALIGNCLIENT | CS_VREDRAW | CS_HREDRAW;	// クラススタイル
				window_class_.lpfnWndProc = NULL;	// ウィンドウプロシージャ
				window_class_.cbClsExtra = 0;	// 補足メモリブロックのサイズ
				window_class_.cbWndExtra = 0;	// 補足メモリブロックのサイズ
				window_class_.hInstance = ::GetModuleHandle(NULL);	// インスタンス
				window_class_.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);	// アイコン
				window_class_.hCursor = ::LoadCursor(NULL, IDC_ARROW);	// カーソル
				window_class_.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;	// 背景色
				window_class_.lpszMenuName = NULL;	// メニュー名
				window_class_.lpszClassName = NULL;	// クラス名

				// プレゼントパラメータの設定
				present_parameters_.BackBufferWidth = 0;	// バックバッファサイズ
				present_parameters_.BackBufferHeight = 0;	// バックバッファサイズ
				present_parameters_.BackBufferFormat = D3DFMT_UNKNOWN;	// バックバッファ形式
				present_parameters_.BackBufferCount = 1;	// バックバッファ数
				present_parameters_.MultiSampleType = D3DMULTISAMPLE_NONE;	// マルチサンプリングのレベル
				present_parameters_.MultiSampleQuality = 0;	// マルチサンプリングの品質レベル
				present_parameters_.SwapEffect = D3DSWAPEFFECT_DISCARD;	// スワップエフェクト
				present_parameters_.hDeviceWindow = NULL;	// デバイスウィンドウ
				present_parameters_.Windowed = TRUE;	// ウィンドウモードか
				present_parameters_.EnableAutoDepthStencil = FALSE;	// 深度バッファを自転送に管理させるか
				present_parameters_.AutoDepthStencilFormat = D3DFMT_UNKNOWN;	// 深度バッファ形式
				present_parameters_.Flags = 0;	// オプションのフラグ
				present_parameters_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
				present_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// プレゼンテーション間隔
			}
			~device_manager() throw() {
				switch (init_params_.mode) {
				case SPRIG_DG_DEVICE_MODE_WINDOW:
					break;
				case SPRIG_DG_DEVICE_MODE_BUFFER:
					if (window_handle_) {
						if (!::DestroyWindow(window_handle_)) {
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
							SPRIG_DG_OUTPUT("ウインドウの破棄に失敗しました");
						}
						if (!::UnregisterClass(window_class_.lpszClassName, NULL)) {
							SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
							SPRIG_DG_OUTPUT("ウインドウクラスの登録解除に失敗しました");
						}
					}
					break;
				}
			}
		public:
			HRESULT initialize(device_manager_init_params const& params) {
				SPRIG_DG_SECTION(TEXT("device_manager::initialize"));
				HRESULT result = D3D_OK;

				init_params_ = params;

				// クラス名の設定
				window_class_.lpszClassName = init_params_.class_name.c_str();

				// ウィンドウプロシージャの設定
				switch (init_params_.mode) {
				case SPRIG_DG_DEVICE_MODE_WINDOW:
					window_class_.lpfnWndProc = static_cast<WNDPROC>(window_procedure);
					break;
				case SPRIG_DG_DEVICE_MODE_BUFFER:
					window_class_.lpfnWndProc = static_cast<WNDPROC>(buffer_procedure);
					break;
				}

				// ウィンドウクラスの登録
				if (!::RegisterClass(&window_class_)) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("ウインドウクラスの登録に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// メインウインドウの作成
				switch (init_params_.mode) {
				case SPRIG_DG_DEVICE_MODE_WINDOW:
					window_handle_ = ::CreateWindow(
						init_params_.class_name.c_str(),	// クラス名
						init_params_.window_name.c_str(),	// ウィンドウタイトル
						WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE,	// ウィンドウスタイル
						CW_USEDEFAULT,	// ウィンドウ位置
						CW_USEDEFAULT,	// ウィンドウ位置
						static_cast<int>(init_params_.width + GetSystemMetrics(SM_CXDLGFRAME) * 2),	// ウィンドウサイズ
						static_cast<int>(init_params_.height + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),	// ウィンドウサイズ
						NULL,	// 親ウィンドウ
						NULL,	// メニュー
						window_class_.hInstance,	// インスタンス
						NULL	// ウィンドウ作成データのアドレス
						);
					break;
				case SPRIG_DG_DEVICE_MODE_BUFFER:
					window_handle_ = ::CreateWindow(
						init_params_.class_name.c_str(),	// クラス名
						init_params_.window_name.c_str(),	// ウィンドウタイトル
						WS_POPUP,	// ウィンドウスタイル
						0,	// ウィンドウ位置
						0,	// ウィンドウ位置
						static_cast<int>(init_params_.width),	// ウィンドウサイズ
						static_cast<int>(init_params_.height),	// ウィンドウサイズ
						NULL,	// 親ウィンドウ
						NULL,	// メニュー
						window_class_.hInstance,	// インスタンス
						NULL	// ウィンドウ作成データのアドレス
						);
					break;
				}
				if (window_handle_ == NULL) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("メインウインドウ作成に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// Direct3Dオブジェクトの作成
				object_ = Direct3DCreate9(D3D_SDK_VERSION);
				if (object_ == NULL) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("Direct3Dオブジェクトの作成に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// バックバッファサイズの設定
				present_parameters_.BackBufferWidth = static_cast<UINT>(init_params_.width);
				present_parameters_.BackBufferHeight = static_cast<UINT>(init_params_.height);

				// デバイスの作成
				SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ハードウェア 頂点処理:ハードウェア)");
				if (FAILED(result = object_->CreateDevice(
					D3DADAPTER_DEFAULT,	// ディスプレイアダプタ
					D3DDEVTYPE_HAL,	// 処理:ハードウェア
					window_handle_,	// デバイスウィンドウ
					D3DCREATE_HARDWARE_VERTEXPROCESSING,	// 頂点処理:ハードウェア
					&present_parameters_,	// パラメータ
					sprig::accept(device_)
					)))
				{
					SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ハードウェア 頂点処理:ハードウェア)");
					SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ハードウェア 頂点処理:ソフトウェア)");
					if (FAILED(result = object_->CreateDevice(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,	// 処理:ハードウェア
						window_handle_,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// 頂点処理:ソフトウェア
						&present_parameters_,
						sprig::accept(device_)
						)))
					{
						SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ハードウェア 頂点処理:ソフトウェア)");
						SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ソフトウェア 頂点処理:ハードウェア)");
						if (FAILED(result = object_->CreateDevice(
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_REF,	// 処理:ソフトウェア
							window_handle_,
							D3DCREATE_HARDWARE_VERTEXPROCESSING,	// 頂点処理:ハードウェア
							&present_parameters_,
							sprig::accept(device_)
							)))
						{
							SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ソフトウェア 頂点処理:ハードウェア)");
							SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ソフトウェア 頂点処理:ソフトウェア)");
							if (FAILED(result = object_->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_REF,	// 処理:ソフトウェア
								window_handle_,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// 頂点処理:ソフトウェア
								&present_parameters_,
								sprig::accept(device_)
								)))
							{
								SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ソフトウェア 頂点処理:ソフトウェア)");
								SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
								SPRIG_DG_ERROR("デバイス作成にすべて失敗しました", bad_initialize);
								return result;
							} else {
								SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ソフトウェア 頂点処理:ソフトウェア)");
							}
						} else {
							SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ソフトウェア 頂点処理:ハードウェア)");
						}
					} else {
						SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ハードウェア 頂点処理:ソフトウェア)");
					}
				} else {
					SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ハードウェア 頂点処理:ハードウェア)");
				}

#ifdef SPRIG_DG_CONFIG_DEVICE_MANAGER_ENABLE_OUTPUT_DEVICE_CAPS
				// レンダリングデバイスの能力出力
				if (FAILED(result = output_device_caps_once(device_))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダリングデバイスの能力出力に失敗しました", bad_initialize);
					return result;
				}
#endif	// #ifdef SPRIG_DG_CONFIG_DEVICE_MANAGER_ENABLE_OUTPUT_DEVICE_CAPS

				// バックバッファのサーフェイス取得
				if (FAILED(result = device_->GetRenderTarget(0, sprig::accept(back_buffer_surface_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("バックバッファのサーフェイス取得に失敗しました", bad_initialize);
					return result;
				}

				return result;
			}
			HRESULT reinitialize(bool force = false) {
				SPRIG_DG_SECTION(TEXT("device_manager::reinitialize"));
				HRESULT result = D3D_OK;

				// 再構築を強制しない、かつ初期化済みならば何もしない
				if (!force && is_initialized()) {
					result = S_FALSE;
					return result;
				}

				// クラス名の設定
				window_class_.lpszClassName = init_params_.class_name.c_str();

				// ウィンドウプロシージャの設定
				switch (init_params_.mode) {
				case SPRIG_DG_DEVICE_MODE_WINDOW:
					window_class_.lpfnWndProc = static_cast<WNDPROC>(window_procedure);
					break;
				case SPRIG_DG_DEVICE_MODE_BUFFER:
					window_class_.lpfnWndProc = static_cast<WNDPROC>(buffer_procedure);
					break;
				}

				// ウィンドウクラスの登録
				if (!::RegisterClass(&window_class_)) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("ウインドウクラスの登録に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// メインウインドウの作成
				switch (init_params_.mode) {
				case SPRIG_DG_DEVICE_MODE_WINDOW:
					window_handle_ = ::CreateWindow(
						init_params_.class_name.c_str(),	// クラス名
						init_params_.window_name.c_str(),	// ウィンドウタイトル
						WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE,	// ウィンドウスタイル
						CW_USEDEFAULT,	// ウィンドウ位置
						CW_USEDEFAULT,	// ウィンドウ位置
						static_cast<int>(init_params_.width + GetSystemMetrics(SM_CXDLGFRAME) * 2),	// ウィンドウサイズ
						static_cast<int>(init_params_.height + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),	// ウィンドウサイズ
						NULL,	// 親ウィンドウ
						NULL,	// メニュー
						window_class_.hInstance,	// インスタンス
						NULL	// ウィンドウ作成データのアドレス
						);
					break;
				case SPRIG_DG_DEVICE_MODE_BUFFER:
					window_handle_ = ::CreateWindow(
						init_params_.class_name.c_str(),	// クラス名
						init_params_.window_name.c_str(),	// ウィンドウタイトル
						WS_POPUP,	// ウィンドウスタイル
						0,	// ウィンドウ位置
						0,	// ウィンドウ位置
						static_cast<int>(init_params_.width),	// ウィンドウサイズ
						static_cast<int>(init_params_.height),	// ウィンドウサイズ
						NULL,	// 親ウィンドウ
						NULL,	// メニュー
						window_class_.hInstance,	// インスタンス
						NULL	// ウィンドウ作成データのアドレス
						);
					break;
				}
				if (window_handle_ == NULL) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("メインウインドウ作成に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// Direct3Dオブジェクトの作成
				object_ = Direct3DCreate9(D3D_SDK_VERSION);
				if (object_ == NULL) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("Direct3Dオブジェクトの作成に失敗しました", bad_initialize);
					return E_FAIL;
				}

				// バックバッファサイズの設定
				present_parameters_.BackBufferWidth = static_cast<UINT>(init_params_.width);
				present_parameters_.BackBufferHeight = static_cast<UINT>(init_params_.height);

				// デバイスの作成
				SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ハードウェア 頂点処理:ハードウェア)");
				if (FAILED(result = object_->CreateDevice(
					D3DADAPTER_DEFAULT,	// ディスプレイアダプタ
					D3DDEVTYPE_HAL,	// 処理:ハードウェア
					window_handle_,	// デバイスウィンドウ
					D3DCREATE_HARDWARE_VERTEXPROCESSING,	// 頂点処理:ハードウェア
					&present_parameters_,	// パラメータ
					sprig::accept(device_)
					)))
				{
					SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ハードウェア 頂点処理:ハードウェア)");
					SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ハードウェア 頂点処理:ソフトウェア)");
					if (FAILED(result = object_->CreateDevice(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,	// 処理:ハードウェア
						window_handle_,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// 頂点処理:ソフトウェア
						&present_parameters_,
						sprig::accept(device_)
						)))
					{
						SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ハードウェア 頂点処理:ソフトウェア)");
						SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ソフトウェア 頂点処理:ハードウェア)");
						if (FAILED(result = object_->CreateDevice(
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_REF,	// 処理:ソフトウェア
							window_handle_,
							D3DCREATE_HARDWARE_VERTEXPROCESSING,	// 頂点処理:ハードウェア
							&present_parameters_,
							sprig::accept(device_)
							)))
						{
							SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ソフトウェア 頂点処理:ハードウェア)");
							SPRIG_DG_OUTPUT("デバイス作成を試行 (処理:ソフトウェア 頂点処理:ソフトウェア)");
							if (FAILED(result = object_->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_REF,	// 処理:ソフトウェア
								window_handle_,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// 頂点処理:ソフトウェア
								&present_parameters_,
								sprig::accept(device_)
								)))
							{
								SPRIG_DG_OUTPUT("デバイス作成に失敗 (処理:ソフトウェア 頂点処理:ソフトウェア)");
								SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
								SPRIG_DG_ERROR("デバイス作成にすべて失敗しました", bad_initialize);
								return result;
							} else {
								SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ソフトウェア 頂点処理:ソフトウェア)");
							}
						} else {
							SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ソフトウェア 頂点処理:ハードウェア)");
						}
					} else {
						SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ハードウェア 頂点処理:ソフトウェア)");
					}
				} else {
					SPRIG_DG_OUTPUT("デバイス作成に成功 (処理:ハードウェア 頂点処理:ハードウェア)");
				}

				// バックバッファのサーフェイス取得
				if (FAILED(result = device_->GetRenderTarget(0, sprig::accept(back_buffer_surface_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("バックバッファのサーフェイス取得に失敗しました", bad_initialize);
					return result;
				}

				return result;
			}
			bool is_initialized() const {
				return window_handle_ != NULL;
			}
			HRESULT restore_render_target(DWORD render_target_index = 0) const {
				using sprig::get_pointer;

				HRESULT result = D3D_OK;
				// レンダリングターゲットの再設定
				if (FAILED(result = device_->SetRenderTarget(render_target_index, get_pointer(back_buffer_surface_)))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					{
						SPRIG_DG_SECTION(TEXT("arguments"));
						SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("render_target_index"), render_target_index);
					}
					SPRIG_DG_ERROR("レンダリングターゲットの再設定に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			HRESULT begin_scene() const {
				HRESULT result = D3D_OK;
				if (FAILED(result = device_->BeginScene())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("描画開始に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			HRESULT end_scene() const {
				HRESULT result = D3D_OK;
				if (FAILED(result = device_->EndScene())) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("描画終了に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			HRESULT clear_target(sprig::call_traits<D3DCOLOR>::param_type color = D3DCOLOR_ARGB(0x00, 0x00, 0x00, 0x00)) const {
				HRESULT result = D3D_OK;
				if (FAILED(device_->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("デバイスのクリアに失敗しました", bad_process);
					return result;
				}
				return result;
			}
			HRESULT get_device_caps(D3DCAPS9& caps) const {
				HRESULT result = D3D_OK;
				if (FAILED(result = device_->GetDeviceCaps(&caps))) {
					SPRIG_DG_OUTPUT_VALUE_INFO(TEXT("this"), *this);
					SPRIG_DG_ERROR("レンダリングデバイスの能力取得に失敗しました", bad_process);
					return result;
				}
				return result;
			}
			sprig::call_traits<window_class_type>::getter_type get_window_class() const {
				return window_class_;
			}
			sprig::call_traits<window_handle_type>::getter_type get_window_handle() const {
				return window_handle_;
			}
			sprig::call_traits<present_parameters_type>::getter_type get_present_parameters() const {
				return present_parameters_;
			}
			sprig::call_traits<object_type>::getter_type get_object() const {
				return object_;
			}
			sprig::call_traits<device_type>::getter_type get_device() const {
				return device_;
			}
			sprig::call_traits<surface_type>::getter_type get_back_buffer_surface() const {
				return back_buffer_surface_;
			}
			sprig::call_traits<device_manager_init_params>::getter_type get_device_manager_init_params() const {
				return init_params_;
			}
		private:
			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, unsigned int const) {
				ar
					& boost::serialization::make_nvp("init_params_", init_params_)
					;
			}
		};
		SPRIG_DG_SPECIALIZED_VALUE_INFO(device_manager);
		template<typename Logger>
		SPRIG_INLINE void value_info(device_manager const& value, Logger& logger) {
			logger.section_line(TEXT("type"), typeid(value).name());
			value.members_value_info(logger);
		}
	}	// namespace dg
}	// namespace sprig

#endif	// #ifndef SPRIG_DG_DEVICE_MANAGER_HPP
