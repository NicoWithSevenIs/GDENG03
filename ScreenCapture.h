#pragma once
#include <d3d11.h>
#include <vector>
#include <string>

#include <ScreenGrab.h>
#include <wincodec.h>
#include <filesystem>
#include <iostream>

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/opt.h>
	#include <libswscale/swscale.h>
}

class ScreenCapture
{	

	public:
		static const std::filesystem::path path;
		static const std::filesystem::path output;

	private:
		IDXGISwapChain* m_swap_chain;
		ID3D11Device* m_d3d_device;
		ID3D11DeviceContext* m_device_context;
		std::vector<ID3D11Texture2D*> tex;

	private:
		bool isRecording;
		bool isEncoding;

	public:
		bool init(IDXGISwapChain* swap_chain, ID3D11Device* d3d_device, ID3D11DeviceContext* context);
		void Update();
		bool release();
		void CaptureScreen();

	private:
		bool EncodeVideo();
};

