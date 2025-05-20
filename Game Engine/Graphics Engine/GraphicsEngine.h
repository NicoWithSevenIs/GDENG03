#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

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
		ID3DBlob* m_vsblob = nullptr;
		ID3DBlob* m_psblob = nullptr;
		ID3D11VertexShader* m_vs = nullptr;
		ID3D11PixelShader* m_ps = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;

	public:
		static GraphicsEngine* get();

	public:
		GraphicsEngine();
		~GraphicsEngine();

		bool init();
		bool release();

		bool createShaders();
		bool setShaders();
		void getShaderBufferAndSize(void** bytecode, UINT* size);

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();
		VertexBuffer* createVertexBuffer();
};