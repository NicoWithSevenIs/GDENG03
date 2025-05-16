#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine {
	private:
		ID3D11Device* m_d3d_device;
		D3D_FEATURE_LEVEL m_feature_level;

		DeviceContext* m_device_context;

	private:
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;

	private:
		friend class SwapChain;

	public:
		static GraphicsEngine* get();

	public:
		GraphicsEngine();
		~GraphicsEngine();

		bool init();
		bool release();

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();
};