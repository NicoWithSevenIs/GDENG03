#include "ScreenCapture.h"


bool ScreenCapture::init(IDXGISwapChain* swap_chain, ID3D11Device* d3d_device, ID3D11DeviceContext* context)
{
	isRecording = false;
	isEncoding = false;

	m_swap_chain = swap_chain;
	m_d3d_device = d3d_device;
	m_device_context = context;

	return true;
}

void ScreenCapture::Update()
{
	if(!isRecording || isEncoding)
		return;

	ID3D11Texture2D* buffer = NULL;
	HRESULT hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (!FAILED(hr)) {
		tex.push_back(buffer);
	}
}

bool ScreenCapture::release()
{
	for(auto t: tex)
		t->Release();
	delete this;
	return true;
}

void ScreenCapture::CaptureScreen()
{
	if (!isEncoding) {
		if (isRecording) {
			EncodeVideo();
		}

		isRecording = !isRecording;
	}
}

#include <iostream>

bool ScreenCapture::EncodeVideo()
{
	

	std::cout << "Frames: " << tex.size() << std::endl;

	std::vector<ID3D11Texture2D*> staging_tex;

	for (auto i : tex) {

		D3D11_TEXTURE2D_DESC desc = {};
		i->GetDesc(&desc);

		ID3D11Texture2D* pStaging;

		desc.BindFlags = 0;
		desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.Usage = D3D11_USAGE_STAGING;

		HRESULT hr = m_d3d_device->CreateTexture2D(&desc, nullptr, &pStaging);

		if (FAILED(hr)) {
			std::cout << "Failed to create Staging Texture" << std::endl;
			continue;
		}

		staging_tex.push_back(pStaging);
		m_device_context->CopyResource(pStaging, i);

	}
	std::cout << "Staging Frames: " << staging_tex.size() << std::endl;

	return true;
}

