#include "GraphicsEngine.h"
#include "SwapChain/SwapChain.h"
#include "DeviceContext/DeviceContext.h"

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{

	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);
	ID3D11DeviceContext* imm_context;

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) {
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, 
			num_feature_levels, D3D11_SDK_VERSION, &this->m_d3d_device, &this->m_feature_level, &imm_context);

		if (SUCCEEDED(res))
			break;

		++driver_type_index;
	}

	if (FAILED(res)) {
		return false;
	}

	this->m_device_context = new DeviceContext(imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**) &m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**) &m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	this->m_dxgi_device->Release();
	this->m_dxgi_adapter->Release();
	this->m_dxgi_factory->Release();

	this->m_device_context->release();
	this->m_d3d_device->Release();
	return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_device_context;
}
