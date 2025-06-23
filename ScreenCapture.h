#pragma once
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

class ScreenCapture
{
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

