#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

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
		ID3DBlob* m_blob = nullptr;


		ID3DBlob* m_vsblob = nullptr;
		ID3DBlob* m_psblob = nullptr;
		ID3D11VertexShader* m_vs = nullptr;
		ID3D11PixelShader* m_ps = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;
		friend class VertexShader;
		friend class PixelShader;
		friend class ConstantBuffer;
		friend class IndexBuffer;

	public:
		static GraphicsEngine* get();

	public:
		GraphicsEngine();
		~GraphicsEngine();

		bool init();
		bool release();

		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		void releaseCompiledShader();

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();
		VertexBuffer* createVertexBuffer();
		VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
		ConstantBuffer* createConstantBuffer();
		IndexBuffer* createIndexBuffer();

		ID3D11Device* getDevice() {return m_d3d_device;}
};